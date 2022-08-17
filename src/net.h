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

#if _WIN32
	/* Define this to a reasonably large value */
#	define FD_SETSIZE 4096
#	include <winsock2.h>
#	include <ws2ipdef.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <sys/ioctl.h>
#	include <netdb.h>
#	include <netinet/in.h>
#	include <arpa/inet.h>
#endif

#include <stdint.h>

#if defined HAVE_ERRNO_H
#	include <errno.h>
#endif

#if defined HAVE_UNISTD_H
#	include <unistd.h>
#endif

/* We've got to get FIONBIO from somewhere. Try the Solaris location
	if it isn't defined yet by the above includes. */
#ifndef FIONBIO
#	include <sys/filio.h>
#endif /* FIONBIO */

#if HAVE_SSIZE_T
#	define SSIZE_T ssize_t
#else
#	define SSIZE_T int
#endif

#if HAVE_SOCKLEN_T
#	define SOCKLEN_T socklen_t
#else
#	define SOCKLEN_T int
#endif

#if _WIN32
#	define FIONBIO_ARG_T u_long
#else
#	define FIONBIO_ARG_T int
#endif

#if _WIN32
	/* _WIN32 doesn't really have WSAEAGAIN */
#	ifndef WSAEAGAIN
#		define WSAEAGAIN WSAEWOULDBLOCK
#	endif
#	ifdef gai_strerror
#		undef gai_strerror
#		define gai_strerror gai_strerrorA
#	endif
#else
	/* Windows sockets compatibility defines */
#	define INVALID_SOCKET (-1)
#	define SOCKET_ERROR (-1)
static inline int closesocket(int s) {
	return close(s);
}
#	define WSAEWOULDBLOCK EWOULDBLOCK
#	define WSAEAGAIN EAGAIN
#	define WSAEINPROGRESS EINPROGRESS
#	define WSAEINTR EINTR
#	define SOCKET int
static inline int GetLastError(void) {
	return errno;
}
#endif /* _WIN32 */

void setSocketDefaults(SOCKET fd);
int sameSocketAddress(struct sockaddr_storage *a, struct sockaddr_storage *b);
int getAddrInfoWithProto(char *address, char *port, int protocol, struct addrinfo **ai);
uint16_t getPort(struct addrinfo* ai);
