/*
 * icontrole.h
 *
 *  Created on: 2013-11-03
 */

#ifndef ICONTROLE_H_
#define ICONTROLE_H_

#include "typedef.h"
#include "../NetworkInterface/NetworkInterface.h"
#include "../Sons/tar.h"
#include "../Sons/ac97.h"

#define RELEASED			0
#define PUSHED				1
#define RELEASE_MASK		127
#define PUSHED_MASK			128
#define BUF_SIZE			50


void controle_Init();
void controle_PushedButton(unsigned int button);
void controle_GetPushedButtons(controle *ctrl);
void initPushButton();

#endif /* ICONTROLE_H_ */
