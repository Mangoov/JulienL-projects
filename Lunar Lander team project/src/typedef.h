/*
 * typedef.h
 *
 *  Created on: 2013-11-11
 */

#ifndef TYPEDEF_H_
#define TYPEDEF_H_


#define BUF_SIZE			50
#define NOTHING				-1

typedef enum ETAT {init, computing, end, menu, waiting, etat_pause, downloading, drawBackground, checkVic} Etat;
typedef enum MENU {etat_start, play, options, continu_playing, retry}Menu;
typedef enum CONTROLE{right, left, up, ctrl_pause, ctrl_bright, esc} Ctrl_cfg;
typedef enum OPTION{player_id, audio, ctrl} Options_cfg;
typedef enum AUDIO_OPTION{volume, balance} Opt_audio;
typedef struct{
	unsigned int right;
	unsigned int left;
	unsigned int up;
	unsigned int pause;
	unsigned int bright;
	unsigned int tmpExit;
	unsigned int start;
}controle;

typedef struct{
	unsigned int bufSize;
	unsigned char buf[BUF_SIZE];
}inputBuf;

typedef int bool;
enum { false, true };

#endif /* TYPEDEF_H_ */
