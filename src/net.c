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


#if HAVE_CONFIG_H
#	include "config.h"
#endif

#include <stdio.h>
#include "net.h"

void setSocketDefaults(SOCKET fd) {
	/* Make socket non-blocking (FIXME: this uses legacy API) */
	FIONBIO_ARG_T ioctltmp = 1;
#if _WIN32
	ioctlsocket(fd, FIONBIO, &ioctltmp);
#else
	ioctl(fd, FIONBIO, &ioctltmp);
#endif

#if defined __linux__
	int tmp = 0;
	setsockopt(fd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));
#endif

#if !defined __linux__ && !defined _WIN32
	int tmp = 1024;
	setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &tmp, sizeof(tmp));
#endif
}

int getAddrInfoWithProto(char *address, char *port, int protocol, struct addrinfo **ai)
{
	struct addrinfo hints = {
		.ai_family = AF_UNSPEC,
		.ai_protocol = protocol,
		.ai_socktype = protocol == IPPROTO_UDP ? SOCK_DGRAM : SOCK_STREAM,
		.ai_flags = AI_PASSIVE,
	};

	int ret = getaddrinfo(address, port, &hints, ai);
	if (ret != 0) {
		fprintf(stderr, "cannot resolve host \"%s\" port %s "
				"(getaddrinfo() error: %s)\n",
			address, port ? port : "<null>", gai_strerror(ret));
	}

	return ret;
}

int sameSocketAddress(struct sockaddr_storage *a, struct sockaddr_storage *b) {
	if (a->ss_family != b->ss_family)
		return 0;

	switch (a->ss_family) {
		case AF_INET: {
			struct sockaddr_in *a4 = (struct sockaddr_in *)a;
			struct sockaddr_in *b4 = (struct sockaddr_in *)b;
			return a4->sin_port == b4->sin_port
				&& a4->sin_addr.s_addr == b4->sin_addr.s_addr;
		}
		case AF_INET6: {
			struct sockaddr_in6 *a6 = (struct sockaddr_in6 *)a;
			struct sockaddr_in6 *b6 = (struct sockaddr_in6 *)b;
			return a6->sin6_port == b6->sin6_port
				&& a6->sin6_addr.s6_addr == b6->sin6_addr.s6_addr;
		}
	}
	return 0;
}

uint16_t getPort(struct addrinfo* ai) {
	switch (ai->ai_family) {
		case AF_INET:
			return ntohs(((struct sockaddr_in*)ai->ai_addr)->sin_port);
		case AF_INET6:
			return ntohs(((struct sockaddr_in6*)ai->ai_addr)->sin6_port);
		default:
			return 0;
	}
}
