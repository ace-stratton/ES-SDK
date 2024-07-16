/**
 * Copyright (C) 2017, STMicroelectronics, all right reserved. 
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 ******************************************************************************
 */

#ifndef __LWIPOPTS__H__
#define __LWIPOPTS__H__

#include "main.h"

/*-----------------------------------------------------------------------------*/
/* Current version of LwIP supported by CubeMx: 2.1.2 -*/
/*-----------------------------------------------------------------------------*/

/* Within 'USER CODE' section, code will be kept by default at each generation */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

#ifdef __cplusplus
 extern "C" {
#endif

/* STM32CubeMX Specific Parameters (not defined in opt.h) ---------------------*/
/* Parameters set in STM32CubeMX LwIP Configuration GUI -*/
/*----- WITH_RTOS enabled (Since FREERTOS is set) -----*/
#define WITH_RTOS 1
/* Temporary workaround to avoid conflict on errno defined in STM32CubeIDE and lwip sys_arch.c errno */
#undef LWIP_PROVIDE_ERRNO
/*----- CHECKSUM_BY_HARDWARE disabled -----*/
#define CHECKSUM_BY_HARDWARE 0
/*-----------------------------------------------------------------------------*/

/* LwIP Stack Parameters (modified compared to initialization value in opt.h) -*/
/* Parameters set in STM32CubeMX LwIP Configuration GUI -*/
/*----- Default value in ETH configuration GUI in CubeMx: 1524 -----*/
#define ETH_RX_BUFFER_SIZE 1524
/*----- Value in opt.h for MEM_ALIGNMENT: 1 -----*/
#define MEM_ALIGNMENT 4
/*----- Default Value for MEM_SIZE: 1600 ---*/
#define MEM_SIZE (14*1024)
/*----- Value supported for H7 devices: 1 -----*/
#define LWIP_SUPPORT_CUSTOM_PBUF 1
/*----- Value in opt.h for LWIP_ETHERNET: LWIP_ARP || PPPOE_SUPPORT -*/
#define LWIP_ETHERNET 1
/*----- Value in opt.h for LWIP_DNS_SECURE: (LWIP_DNS_SECURE_RAND_XID | LWIP_DNS_SECURE_NO_MULTIPLE_OUTSTANDING | LWIP_DNS_SECURE_RAND_SRC_PORT) -*/
#define LWIP_DNS_SECURE 7
/*----- Value in opt.h for TCP_SND_QUEUELEN: (4*TCP_SND_BUF + (TCP_MSS - 1))/TCP_MSS -----*/
#define TCP_SND_QUEUELEN 9
/*----- Value in opt.h for TCP_SNDLOWAT: LWIP_MIN(LWIP_MAX(((TCP_SND_BUF)/2), (2 * TCP_MSS) + 1), (TCP_SND_BUF) - 1) -*/
#define TCP_SNDLOWAT 1071
/*----- Value in opt.h for TCP_SNDQUEUELOWAT: LWIP_MAX(TCP_SND_QUEUELEN)/2, 5) -*/
#define TCP_SNDQUEUELOWAT 5
/*----- Value in opt.h for TCP_WND_UPDATE_THRESHOLD: LWIP_MIN(TCP_WND/4, TCP_MSS*4) -----*/
#define TCP_WND_UPDATE_THRESHOLD 536
/*----- Value in opt.h for LWIP_NETIF_LINK_CALLBACK: 0 -----*/
#define LWIP_NETIF_LINK_CALLBACK 1
/*----- Value in opt.h for TCPIP_THREAD_STACKSIZE: 0 -----*/
#define TCPIP_THREAD_STACKSIZE 2048
/*----- Value in opt.h for TCPIP_THREAD_PRIO: 1 -----*/
#define TCPIP_THREAD_PRIO 24
/*----- Value in opt.h for TCPIP_MBOX_SIZE: 0 -----*/
#define TCPIP_MBOX_SIZE 6
/*----- Value in opt.h for SLIPIF_THREAD_STACKSIZE: 0 -----*/
#define SLIPIF_THREAD_STACKSIZE 2048
/*----- Value in opt.h for SLIPIF_THREAD_PRIO: 1 -----*/
#define SLIPIF_THREAD_PRIO 25
/*----- Value in opt.h for DEFAULT_THREAD_STACKSIZE: 0 -----*/
#define DEFAULT_THREAD_STACKSIZE 2048
/*----- Value in opt.h for DEFAULT_THREAD_PRIO: 1 -----*/
#define DEFAULT_THREAD_PRIO 3
/*----- Value in opt.h for DEFAULT_UDP_RECVMBOX_SIZE: 0 -----*/
#define DEFAULT_UDP_RECVMBOX_SIZE 6
/*----- Value in opt.h for DEFAULT_TCP_RECVMBOX_SIZE: 0 -----*/
#define DEFAULT_TCP_RECVMBOX_SIZE 6
/*----- Value in opt.h for DEFAULT_ACCEPTMBOX_SIZE: 0 -----*/
#define DEFAULT_ACCEPTMBOX_SIZE 6
/*----- Value in opt.h for RECV_BUFSIZE_DEFAULT: INT_MAX -----*/
#define RECV_BUFSIZE_DEFAULT 2000000000
/*----- Value in opt.h for LWIP_STATS: 1 -----*/
#define LWIP_STATS 0
/*----- Default Value for LWIP_CHECKSUM_CTRL_PER_NETIF: 0 ---*/
#define LWIP_CHECKSUM_CTRL_PER_NETIF 1
/*-----------------------------------------------------------------------------*/


#define HTTP_SERVER
/** Set this to 1 to include "fsdata_custom.c" instead of "fsdata.c" for the
 * file system (to prevent changing the file included in CVS) */
#define HTTPD_USE_CUSTOM_FSDATA   1


/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#define PBUF_POOL_BUFSIZE       1536

/* TCP Maximum segment size. */
#define TCP_MSS                 (1500 - 40)	  /* TCP_MSS = (Ethernet MTU - IP header size - TCP header size) */


#if CHECKSUM_BY_HARDWARE == 1
	#undef CHECKSUM_GEN_IP
	#undef CHECKSUM_GEN_UDP
	#undef CHECKSUM_GEN_TCP
	#undef CHECKSUM_GEN_ICMP6
	#undef CHECKSUM_CHECK_IP
	#undef CHECKSUM_CHECK_UDP
	#undef CHECKSUM_CHECK_TCP
	#undef CHECKSUM_CHECK_ICMP6
	#undef CHECKSUM_GEN_ICMP
	/* CHECKSUM_GEN_IP==0: Generate checksums by hardware for outgoing IP packets.*/
	#define CHECKSUM_GEN_IP                 0
	/* CHECKSUM_GEN_UDP==0: Generate checksums by hardware for outgoing UDP packets.*/
	#define CHECKSUM_GEN_UDP                0
	/* CHECKSUM_GEN_TCP==0: Generate checksums by hardware for outgoing TCP packets.*/
	#define CHECKSUM_GEN_TCP                0
	/* CHECKSUM_CHECK_IP==0: Check checksums by hardware for incoming IP packets.*/
	#define CHECKSUM_CHECK_IP               0
	/* CHECKSUM_CHECK_UDP==0: Check checksums by hardware for incoming UDP packets.*/
	#define CHECKSUM_CHECK_UDP              0
	/* CHECKSUM_CHECK_TCP==0: Check checksums by hardware for incoming TCP packets.*/
	#define CHECKSUM_CHECK_TCP              0
	/* CHECKSUM_GEN_ICMP==1: Check checksums by hardware for outgoing ICMP packets.*/
	/* Hardware TCP/UDP checksum insertion not supported when packet is an IPv4 fragment */
	#define CHECKSUM_GEN_ICMP               1
	/* CHECKSUM_CHECK_ICMP==0: Check checksums by hardware for incoming ICMP packets.*/
	#define CHECKSUM_CHECK_ICMP             0
#else
// The default is a check and generate done in software!
// see opt.h
#endif


extern int _LWIP_RAM_HEAP_START_;
extern int _LWIP_RX_POOL_AND_HEAP_START_;
extern int ETH_STACK_DATA_MEMORY_BASE;

#undef LWIP_RAM_HEAP_POINTER
#define LWIP_RAM_HEAP_POINTER  (void*)&_LWIP_RAM_HEAP_START_

#undef __LWIP_RX_TX_DESCRIPTORS_START__
#define __LWIP_RX_TX_DESCRIPTORS_START__ (uint32_t)&ETH_STACK_DATA_MEMORY_BASE
#undef __LWIP_POOL_AND_HEAP_START__
#define __LWIP_POOL_AND_HEAP_START__ (uint32_t)&_LWIP_RX_POOL_AND_HEAP_START_


/* UDP local connection port */
#define UDP_SERVER_PORT    7
/* UDP remote connection port */
#define UDP_CLIENT_PORT    7

 /*Static IP ADDRESS*/
#define ETH_IP_ADDR0 ((uint8_t)192U)
#define ETH_IP_ADDR1 ((uint8_t)168U)
#define ETH_IP_ADDR2 ((uint8_t)69U)
#define ETH_IP_ADDR3 ((uint8_t)10U)

 /*NETMASK*/
#define ETH_NETMASK_ADDR0 ((uint8_t)255U)
#define ETH_NETMASK_ADDR1 ((uint8_t)255U)
#define ETH_NETMASK_ADDR2 ((uint8_t)255U)
#define ETH_NETMASK_ADDR3 ((uint8_t)0U)

 /*Gateway Address*/
#define ETH_GW_ADDR0 ((uint8_t)192U)
#define ETH_GW_ADDR1 ((uint8_t)168U)
#define ETH_GW_ADDR2 ((uint8_t)69U)
#define ETH_GW_ADDR3 ((uint8_t)1U)

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif /*__LWIPOPTS__H__ */

