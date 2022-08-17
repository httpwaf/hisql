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


#define DROP  1
#define ALLOW 0

int process_mysql(char *buf,int len);
int process_postgresql(char *buf,int len);
int process_oracle(char *buf,int len);
int process_maria(char *buf,int len);





