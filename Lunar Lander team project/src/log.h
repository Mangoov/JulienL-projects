/*
 * log.h
 *
 *  Created on: 2013-11-06
 */

#ifndef LOG_H_
#define LOG_H_


#define NET_DEBUG
#define STAT_DEBUG


#ifdef NET_DEBUG
#define NET_PRINT
#else
#define NET_PRINT
#endif

#ifdef STAT_DEBUG
#define STAT_PRINT
#else
#define STAT_PRINT
#endif

void printBuf(unsigned char *buf, unsigned int size);

#endif /* LOG_H_ */
