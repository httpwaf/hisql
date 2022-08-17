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
 * http://www.hihttps.com   https://github.com/httpwaf/  https://gitee.com/httpwaf/
 */


#pragma once

#include <stdint.h>

/* Constants */

static int const RINETD_BUFFER_SIZE = 16384;
static int const RINETD_LISTEN_BACKLOG = 128;
static int const RINETD_DEFAULT_UDP_TIMEOUT = 72;

#define RINETD_CONFIG_FILE "/etc/hisql.conf"
#define RINETD_PID_FILE "/var/run/hisql.pid"

/* Global configuration */

extern Rule *allRules;
extern int allRulesCount;
extern int globalRulesCount;

extern ServerInfo *seInfo;
extern int seTotal;

extern char *logFileName;
extern char *pidLogFileName;
extern int logFormatCommon;
extern FILE *logFile;

/* Functions */

void logError(char const *fmt, ...);
void logInfo(char const *fmt, ...);
void addServer(char *bindAddress, char *bindPort, int bindProtocol,
               char *connectAddress, char *connectPort, int connectProtocol,
               int serverTimeout, char *sourceAddress);
