/* 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For more ,please contact QQ:4108863  wechat:httpwaf   mail:4108863@qq.com
 * http://www.hihttps.com
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "sql.h"
#include "../libinjection/libinjection_sqli.h"
#include "../detect/sqli_detect.h"




/* port for protocol registration */
#define TCP_PORT_MySQL   3306

/* client/server capabilities
 * Source: http://dev.mysql.com/doc/internals/en/capability-flags.html
 * Source: mysql_com.h
 */
#define MYSQL_CAPS_LP 0x0001 /* CLIENT_LONG_PASSWORD */
#define MYSQL_CAPS_FR 0x0002 /* CLIENT_FOUND_ROWS */
#define MYSQL_CAPS_LF 0x0004 /* CLIENT_LONG_FLAG */
#define MYSQL_CAPS_CD 0x0008 /* CLIENT_CONNECT_WITH_DB */
#define MYSQL_CAPS_NS 0x0010 /* CLIENT_NO_SCHEMA */
#define MYSQL_CAPS_CP 0x0020 /* CLIENT_COMPRESS */
#define MYSQL_CAPS_OB 0x0040 /* CLIENT_ODBC */
#define MYSQL_CAPS_LI 0x0080 /* CLIENT_LOCAL_FILES */
#define MYSQL_CAPS_IS 0x0100 /* CLIENT_IGNORE_SPACE */
#define MYSQL_CAPS_CU 0x0200 /* CLIENT_PROTOCOL_41 */
#define MYSQL_CAPS_IA 0x0400 /* CLIENT_INTERACTIVE */
#define MYSQL_CAPS_SL 0x0800 /* CLIENT_SSL */
#define MYSQL_CAPS_II 0x1000 /* CLIENT_IGNORE_SPACE */
#define MYSQL_CAPS_TA 0x2000 /* CLIENT_TRANSACTIONS */
#define MYSQL_CAPS_RS 0x4000 /* CLIENT_RESERVED */
#define MYSQL_CAPS_SC 0x8000 /* CLIENT_SECURE_CONNECTION */


/* field flags */
#define MYSQL_FLD_NOT_NULL_FLAG       0x0001
#define MYSQL_FLD_PRI_KEY_FLAG        0x0002
#define MYSQL_FLD_UNIQUE_KEY_FLAG     0x0004
#define MYSQL_FLD_MULTIPLE_KEY_FLAG   0x0008
#define MYSQL_FLD_BLOB_FLAG           0x0010
#define MYSQL_FLD_UNSIGNED_FLAG       0x0020
#define MYSQL_FLD_ZEROFILL_FLAG       0x0040
#define MYSQL_FLD_BINARY_FLAG         0x0080
#define MYSQL_FLD_ENUM_FLAG           0x0100
#define MYSQL_FLD_AUTO_INCREMENT_FLAG 0x0200
#define MYSQL_FLD_TIMESTAMP_FLAG      0x0400
#define MYSQL_FLD_SET_FLAG            0x0800

/* extended capabilities: 4.1+ client only
 *
 * These are libmysqlclient flags and NOT present
 * in the protocol:
 * CLIENT_SSL_VERIFY_SERVER_CERT (1UL << 30)
 * CLIENT_REMEMBER_OPTIONS (1UL << 31)
 */
#define MYSQL_CAPS_MS 0x0001 /* CLIENT_MULTI_STATMENTS */
#define MYSQL_CAPS_MR 0x0002 /* CLIENT_MULTI_RESULTS */
#define MYSQL_CAPS_PM 0x0004 /* CLIENT_PS_MULTI_RESULTS */
#define MYSQL_CAPS_PA 0x0008 /* CLIENT_PLUGIN_AUTH */
#define MYSQL_CAPS_CA 0x0010 /* CLIENT_CONNECT_ATTRS */
#define MYSQL_CAPS_AL 0x0020 /* CLIENT_PLUGIN_AUTH_LENENC_CLIENT_DATA */
#define MYSQL_CAPS_EP 0x0040 /* CLIENT_CAN_HANDLE_EXPIRED_PASSWORDS */
#define MYSQL_CAPS_ST 0x0080 /* CLIENT_SESSION_TRACK */
#define MYSQL_CAPS_DE 0x0100 /* CLIENT_DEPRECATE_EOF */
#define MYSQL_CAPS_UNUSED 0xFE00

/* status bitfield */
#define MYSQL_STAT_IT 0x0001
#define MYSQL_STAT_AC 0x0002
#define MYSQL_STAT_MU 0x0004
#define MYSQL_STAT_MR 0x0008
#define MYSQL_STAT_BI 0x0010
#define MYSQL_STAT_NI 0x0020
#define MYSQL_STAT_CR 0x0040
#define MYSQL_STAT_LR 0x0080
#define MYSQL_STAT_DR 0x0100
#define MYSQL_STAT_BS 0x0200
#define MYSQL_STAT_MC 0x0400
#define MYSQL_STAT_QUERY_WAS_SLOW 0x0800
#define MYSQL_STAT_PS_OUT_PARAMS 0x1000
#define MYSQL_STAT_TRANS_READONLY 0x2000
#define MYSQL_STAT_SESSION_STATE_CHANGED 0x4000

/* bitfield for MYSQL_REFRESH */
#define MYSQL_RFSH_GRANT   1   /* Refresh grant tables */
#define MYSQL_RFSH_LOG     2   /* Start on new log file */
#define MYSQL_RFSH_TABLES  4   /* close all tables */
#define MYSQL_RFSH_HOSTS   8   /* Flush host cache */
#define MYSQL_RFSH_STATUS  16  /* Flush status variables */
#define MYSQL_RFSH_THREADS 32  /* Flush thread cache */
#define MYSQL_RFSH_SLAVE   64  /* Reset master info and restart slave thread */
#define MYSQL_RFSH_MASTER  128 /* Remove all bin logs in the index and truncate the index */

/* MySQL command codes (enum_server_command in mysql-server.git:include/my_command.h) */
#define MYSQL_SLEEP               0  /* not from client */
#define MYSQL_QUIT                1
#define MYSQL_INIT_DB             2
#define MYSQL_QUERY               3
#define MYSQL_FIELD_LIST          4
#define MYSQL_CREATE_DB           5
#define MYSQL_DROP_DB             6
#define MYSQL_REFRESH             7
#define MYSQL_SHUTDOWN            8
#define MYSQL_STATISTICS          9
#define MYSQL_PROCESS_INFO        10
#define MYSQL_CONNECT             11 /* not from client */
#define MYSQL_PROCESS_KILL        12
#define MYSQL_DEBUG               13
#define MYSQL_PING                14
#define MYSQL_TIME                15 /* not from client */
#define MYSQL_DELAY_INSERT        16 /* not from client */
#define MYSQL_CHANGE_USER         17
#define MYSQL_BINLOG_DUMP         18 /* replication */
#define MYSQL_TABLE_DUMP          19 /* replication */
#define MYSQL_CONNECT_OUT         20 /* replication */
#define MYSQL_REGISTER_SLAVE      21 /* replication */
#define MYSQL_STMT_PREPARE        22
#define MYSQL_STMT_EXECUTE        23
#define MYSQL_STMT_SEND_LONG_DATA 24
#define MYSQL_STMT_CLOSE          25
#define MYSQL_STMT_RESET          26
#define MYSQL_SET_OPTION          27
#define MYSQL_STMT_FETCH          28
#define MYSQL_DAEMON              29
#define MYSQL_BINLOG_DUMP_GTID    30 /* replication */
#define MYSQL_RESET_CONNECTION    31


/* MySQL cursor types */

#define MYSQL_CURSOR_TYPE_NO_CURSOR  0
#define MYSQL_CURSOR_TYPE_READ_ONLY  1
#define MYSQL_CURSOR_TYPE_FOR_UPDATE 2
#define MYSQL_CURSOR_TYPE_SCROLLABLE 4

/* MySQL parameter flags -- used internally by the dissector */

#define MYSQL_PARAM_FLAG_STREAMED 0x01

/* Compression states, internal to the dissector */
#define MYSQL_COMPRESS_NONE   0
#define MYSQL_COMPRESS_INIT   1
#define MYSQL_COMPRESS_ACTIVE 2

/* Generic Response Codes */
#define MYSQL_RESPONSE_OK   0x00
#define MYSQL_RESPONSE_ERR  0xFF
#define MYSQL_RESPONSE_EOF  0xFE


/* VALUE TO STRING MATCHING */

typedef struct _value_string {
    unsigned int  value;
    const char   *strptr;
} value_string;


/* decoding table: command */
static const value_string mysql_command_vals[] = {
	{MYSQL_SLEEP,   "SLEEP"},
	{MYSQL_QUIT,   "Quit"},
	{MYSQL_INIT_DB,  "Use Database"},
	{MYSQL_QUERY,   "Query"},
	{MYSQL_FIELD_LIST, "Show Fields"},
	{MYSQL_CREATE_DB,  "Create Database"},
	{MYSQL_DROP_DB , "Drop Database"},
	{MYSQL_REFRESH , "Refresh"},
	{MYSQL_SHUTDOWN , "Shutdown"},
	{MYSQL_STATISTICS , "Statistics"},
	{MYSQL_PROCESS_INFO , "Process List"},
	{MYSQL_CONNECT , "Connect"},
	{MYSQL_PROCESS_KILL , "Kill Server Thread"},
	{MYSQL_DEBUG , "Dump Debuginfo"},
	{MYSQL_PING , "Ping"},
	{MYSQL_TIME , "Time"},
	{MYSQL_DELAY_INSERT , "Insert Delayed"},
	{MYSQL_CHANGE_USER , "Change User"},
	{MYSQL_BINLOG_DUMP , "Send Binlog"},
	{MYSQL_TABLE_DUMP, "Send Table"},
	{MYSQL_CONNECT_OUT, "Slave Connect"},
	{MYSQL_REGISTER_SLAVE, "Register Slave"},
	{MYSQL_STMT_PREPARE, "Prepare Statement"},
	{MYSQL_STMT_EXECUTE, "Execute Statement"},
	{MYSQL_STMT_SEND_LONG_DATA, "Send BLOB"},
	{MYSQL_STMT_CLOSE, "Close Statement"},
	{MYSQL_STMT_RESET, "Reset Statement"},
	{MYSQL_SET_OPTION, "Set Option"},
	{MYSQL_STMT_FETCH, "Fetch Data"},
	{MYSQL_BINLOG_DUMP_GTID, "Send Binlog GTID"},
	{0, NULL}
};




static const value_string mysql_response_code_vals[] = {
    { MYSQL_RESPONSE_OK,    "OK Packet" },
    { MYSQL_RESPONSE_ERR,   "ERR Packet" },
    { MYSQL_RESPONSE_EOF,   "EOF Packet" },
    { 0, NULL }
};





typedef enum mysql_state {
	UNDEFINED,
	LOGIN,
	REQUEST,
	RESPONSE_OK,
	RESPONSE_MESSAGE,
	RESPONSE_TABULAR,
	RESPONSE_SHOW_FIELDS,
	FIELD_PACKET,
	ROW_PACKET,
	RESPONSE_PREPARE,
	PREPARED_PARAMETERS,
	PREPARED_FIELDS,
	AUTH_SWITCH_REQUEST,
	AUTH_SWITCH_RESPONSE
} mysql_state_t;





/* function prototypes */


/**
* print_data 调试16进制打印输出
*
* @name 名字
* @data 打印的内容
* len   打印的字节数
* @return 无
*/

static void print_data(const char *name,unsigned char *data,int len)
{
	int i,j,k;

	//if(!debug_mode)
		//return;
	
	if(name) printf("-------%s-------%dbytes-----------------------------\n",name,len);

	for (i=0; i<len; i+=16) {
        printf("| ");
        for (j=i, k=0; k<16 && j<len; ++j, ++k)
            printf("%.2x ",data[j]);
        for (; k<16; ++k)
            printf("   ");
       printf("|");
        for (j=i, k=0; k<16 && j<len; ++j, ++k) {
            unsigned char c = data[j];
            if (!isprint(c) || (c=='\t')) c = '.';
            printf("%c",c);
        }
        for (; k<16; ++k)
            printf("   ");
        printf("|\n");
    }

}



int mysql_query(char *buf,int len){
    char    sql[1024];
    size_t  size;
    sfilter state; 
    

    size = len > 1000 ? 1000: (len - 4);     
    snprintf(sql,size,"%s",buf + 4);

    
    //printf("SQL QUERY:%s\n",sql);  print_data("sql",(unsigned char *)(buf),len); 

    libinjection_sqli_init(&state, (const char *)sql, strlen(sql), FLAG_NONE);
    if (libinjection_is_sqli(&state) == 1 && 0 < sqli_detect(sql, strlen(sql))) {      
        printf("SQL Injection:%s\n",sql);
        #ifdef HAVE_DROP
           return DORP;
        #endif
    }

    /*You can add sql to machine learning here*/
   #ifdef USE_WORD2VEC  
      generate_word2vec(sql);     
   #endif

   #ifdef USE_LOG
      output_log(sql);
   #endif
    
   return ALLOW;
};

int mysql_connect(char *buf,int len) {
    char    *user;

    
    if (len < 48)
        return ALLOW;

    if (buf[32] != 0x00 || buf[33] != 0x00 || buf[34] != 0x00 || buf[35] != 0x00)
        return ALLOW;

    if (buf[36] < 0x30 || buf[36] > 0x7B)         
        return ALLOW;

    user = buf + 36;
    printf("mysql login user=%s\n",user);
    
    /*请这里添加对用户的登录、密码破解等审计代码*/
 
    return ALLOW;
}

int process_mysql(char *buf,int len){

    int     ret = ALLOW;
       
    if (len < 8)
        return ALLOW;

    
    

    if (buf[3] == 0x1) {
        ret = mysql_connect(buf,len);
    }

    switch (buf[4]) {
        case MYSQL_CONNECT:           
            break;
        case MYSQL_QUIT:
            //print_data("quit",(unsigned char *)(buf),len);  
            break;
        case MYSQL_DROP_DB: /*删库跑路 Coding Hungry,Coding Foolish*/      
            break;
        case MYSQL_QUERY:
            ret = mysql_query(buf,len);
            break; 
        case MYSQL_INIT_DB: /*Use DB*/
            break; 
        case MYSQL_PING:
            break;     
        case MYSQL_CREATE_DB:             
            break;     
        case MYSQL_SHUTDOWN:
            break;     
        default:
            break;
    }
    
    
    
    return ret;
}


