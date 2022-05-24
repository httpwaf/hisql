package dbshield

import (
	"encoding/binary"
	"fmt"
	"io"
	"net"
	"os"
	"os/signal"
	"strings"
	"time"

	"github.com/boltdb/bolt"
	"github.com/nim4/DBShield/dbshield/config"
	"github.com/nim4/DBShield/dbshield/dbms"
	"github.com/nim4/DBShield/dbshield/logger"
	"github.com/nim4/DBShield/dbshield/training"
	"github.com/nim4/DBShield/dbshield/utils"
)

const (
	mysql = iota
	mssql
	postgres
	db2
	oracle
)

//initial boltdb database
func initModel(path string) {
	logger.Infof("Internal DB: %s", path)
	if training.DBCon == nil {
		training.DBCon, _ = bolt.Open(path, 0600, nil)
		training.DBCon.Update(func(tx *bolt.Tx) error {
			tx.CreateBucketIfNotExists([]byte("pattern"))
			tx.CreateBucketIfNotExists([]byte("abnormal"))
			b, _ := tx.CreateBucketIfNotExists([]byte("state"))
			v := b.Get([]byte("QueryCounter"))
			if v != nil {
				training.QueryCounter = binary.BigEndian.Uint64(v)
			}
			v = b.Get([]byte("AbnormalCounter"))
			if v != nil {
				training.AbnormalCounter = binary.BigEndian.Uint64(v)
			}
			return nil
		})
	}

	if config.Config.SyncInterval != 0 {
		training.DBCon.NoSync = true
		ticker := time.NewTicker(config.Config.SyncInterval)
		go func() {
			for range ticker.C {
				training.DBCon.Sync()
			}
		}()
	}
}

func closeHandlers() {
	if training.DBCon != nil {
		training.DBCon.Update(func(tx *bolt.Tx) error {
			//Supplied value must remain valid for the life of the transaction
			qCount := make([]byte, 8)
			abCount := make([]byte, 8)

			b := tx.Bucket([]byte("state"))
			binary.BigEndian.PutUint64(qCount, training.QueryCounter)
			b.Put([]byte("QueryCounter"), qCount)

			binary.BigEndian.PutUint64(abCount, training.AbnormalCounter)
			b.Put([]byte("AbnormalCounter"), abCount)

			return nil
		})
		training.DBCon.Sync()
		training.DBCon.Close()
	}
	if logger.Output != nil {
		logger.Output.Close()
	}
}

//catching Interrupts
func signalHandler() {
	term := make(chan os.Signal)
	signal.Notify(term, os.Interrupt)
	<-term
	logger.Info("Shutting down...")
	//Closing open handler politely
	closeHandlers()
}

//initLogging redirect log output to file/stdout/stderr
func initLogging() {
	err := logger.Init(config.Config.LogPath, config.Config.LogLevel)
	if err != nil {
		panic(err)
	}
}

//maps database name to corresponding struct
func dbNameToStruct(db string) (d uint, err error) {
	switch strings.ToLower(db) {
	case "db2":
		d = db2
	case "mssql":
		d = mssql
	case "mysql", "mariadb":
		d = mysql
	case "oracle":
		d = oracle
	case "postgres":
		d = postgres
	default:
		err = fmt.Errorf("Unknown DBMS: %s", db)
	}
	return
}

//generateDBMS instantiate a new instance of DBMS
func generateDBMS() (utils.DBMS, func(io.Reader) ([]byte, error)) {
	switch config.Config.DB {
	case mssql:
		return new(dbms.MSSQL), dbms.MSSQLReadPacket
	case mysql:
		return new(dbms.MySQL), dbms.MySQLReadPacket
	case postgres:
		return new(dbms.Postgres), dbms.ReadPacket //TODO: implement explicit reader
	case oracle:
		return new(dbms.Oracle), dbms.ReadPacket //TODO: implement explicit reader
	case db2:
		return new(dbms.DB2), dbms.ReadPacket //TODO: implement explicit reader
	default:
		return nil, nil
	}
}

func handleClient(listenConn net.Conn, serverAddr *net.TCPAddr) error {
	d, reader := generateDBMS()
	logger.Debugf("Connected from: %s", listenConn.RemoteAddr())
	serverConn, err := net.DialTCP("tcp", nil, serverAddr)
	if err != nil {
		logger.Warning(err)
		listenConn.Close()
		return err
	}
	if config.Config.Timeout > 0 {
		if err = listenConn.SetDeadline(time.Now().Add(config.Config.Timeout)); err != nil {
			return err
		}
		if err = serverConn.SetDeadline(time.Now().Add(config.Config.Timeout)); err != nil {
			return err
		}
	}
	logger.Debugf("Connected to: %s", serverConn.RemoteAddr())
	d.SetSockets(listenConn, serverConn)
	d.SetCertificate(config.Config.TLSCertificate, config.Config.TLSPrivateKey)
	d.SetReader(reader)
	err = d.Handler()
	if err != nil {
		logger.Warning(err)
	}
	return err
}
