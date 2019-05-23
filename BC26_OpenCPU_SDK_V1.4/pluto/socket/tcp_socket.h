/*
 * tcp_socket.h
 *
 *  Created on: 2016��5��4��
 *      Author: lort
 */

#ifndef USER_TCP_SOCKET_H_
#define USER_TCP_SOCKET_H_

extern int tcp_socket_init(uint32 ip,uint16 port);
extern int tcp_socket_deinit(void);
extern int tcp_socket_send(uint32 ip, uint16 port, uint8 *pdata, uint16 len);

extern void tcp_enable(osState state);

#endif /* USER_TCP_SOCKET_H_ */
