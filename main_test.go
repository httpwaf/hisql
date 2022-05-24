package main

import (
	"bytes"
	"flag"
	"io/ioutil"
	"os"
	"testing"
)

func TestEveryThing(t *testing.T) {
	usage(true)

	os.Args = []string{os.Args[0], "-k", "-c", "conf/dbshield.yml"}
	main()

	flag.CommandLine = flag.NewFlagSet(os.Args[0], flag.ContinueOnError)
	os.Args = []string{os.Args[0], "-purge", "-c", "conf/dbshield.yml"}
	main()

	flag.CommandLine = flag.NewFlagSet(os.Args[0], flag.ContinueOnError)
	os.Args = []string{os.Args[0], "-l", "-c", "conf/invalid.yml"}
	main()

	flag.CommandLine = flag.NewFlagSet(os.Args[0], flag.ContinueOnError)
	os.Args = []string{os.Args[0], "-l", "-c", "conf/dbshield.yml"}
	main()

	flag.CommandLine = flag.NewFlagSet(os.Args[0], flag.ContinueOnError)
	os.Args = []string{os.Args[0], "-a", "-c", "conf/dbshield.yml"}
	main()

	flag.CommandLine = flag.NewFlagSet(os.Args[0], flag.ContinueOnError)
	os.Args = []string{os.Args[0], "-r", "XYZ", "-c", "conf/dbshield.yml"}
	main()

	flag.CommandLine = flag.NewFlagSet(os.Args[0], flag.ContinueOnError)
	os.Args = []string{os.Args[0], "-version"}
	main()

	flag.CommandLine = flag.NewFlagSet(os.Args[0], flag.ContinueOnError)
	os.Args = []string{os.Args[0], "-h"}
	main()

	flag.CommandLine = flag.NewFlagSet(os.Args[0], flag.ContinueOnError)
	dat, err := ioutil.ReadFile("conf/dbshield.yml")
	if err != nil {
		t.Fatal(err)
	}
	path := os.TempDir() + "/tempconfig.yml"
	dat = bytes.Replace(dat, []byte("logPath: "), []byte("logPath: "+os.TempDir()+" #"), 1)
	err = ioutil.WriteFile(path, dat, 0600)
	if err != nil {
		t.Fatal(err)
	}
	os.Args = []string{os.Args[0], "-c", path}
	defer func() {
		if r := recover(); r == nil {
			t.Error("Expected panic")
		}
	}()
	main()
}
