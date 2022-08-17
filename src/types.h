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

#include <time.h>
#include <stdint.h>

typedef enum _rule_type ruleType;
enum _rule_type {
	allowRule,
	denyRule,
};

typedef struct _rule Rule;
struct _rule
{
	char *pattern;
	ruleType type;
};

typedef struct _server_info ServerInfo;
struct _server_info {
	SOCKET fd;

	/* In network order, for network purposes */
	struct addrinfo *fromAddrInfo, *toAddrInfo, *sourceAddrInfo;

	/* In ASCII, for logging purposes */
	char *fromHost, *toHost;

	/* Offset and count into list of allow and deny rules. Any rules
		prior to globalAllowRules and globalDenyRules are global rules. */
	int rulesStart, rulesCount;
	/* Timeout for UDP traffic before we consider the connection
		was dropped by the remote host. */
	int serverTimeout;
};

typedef struct _socket Socket;
struct _socket
{
	SOCKET fd;
	int family, protocol;
	/* recv: received on this socket
		sent: sent through this socket from the other buffer */
	int recvPos, sentPos;
	uint64_t totalBytesIn, totalBytesOut;
	char *buffer;
};

typedef struct _connection_info ConnectionInfo;
struct _connection_info
{
	Socket remote, local;
	struct sockaddr_storage remoteAddress;
	time_t remoteTimeout;
	int coClosing;
	int coLog;
	ServerInfo const *server; // only useful for logEvent
};

/* Option parsing */

typedef struct _rinetd_options RinetdOptions;
struct _rinetd_options
{
	char const *conf_file;
	int foreground;
};

