/*
 * controle.c
 *
 *  Created on: 2013-11-04
 */

#include "icontrole.h"
#include <stdio.h>

#define RIGHT	130
#define LEFT	132
#define UP		129
#define DOWN	131
#define PAUSE	137
#define EXIT	155
#define BRIGHT	160
#define START	138


extern bool fini;
controle bindCtrl;
controle pushedCtrl;
extern inputBuf input;
static inputBuf localBuf;
Ctrl_cfg ctrl_cfg = NOTHING;
extern Menu main_menu;
extern Options_cfg opt_cfg;
extern Etat etat;
bool choose = false;
int vertical_opt = 1;
static int hor_opt = 0;
int vol_opt = 3;
static int local_vol_opt = 5;
int bal_opt = 1;
static int local_bal_opt = 5;
bool started = false;
extern Application app;
int mapID;
static bool cExit = false;
extern Opt_audio opt_audio;
extern bool change;
bool menuChange = true;
bool errorCheckControles = false;
bool menuIn = false;
bool menuOut = false;
bool menuSelect = false;
bool menuError = false;
extern ac97_core CfgAC97;

void SetBalance()
{


}

void copyBuf (inputBuf org, inputBuf* copy){
	int i;
	for(i = 0; i < org.bufSize; ++i){
		copy->buf[i] = org.buf[i];
	}
	copy->bufSize = org.bufSize;
}

void initPushButton(){
	pushedCtrl.bright = RELEASED;
	pushedCtrl.left = RELEASED;
	pushedCtrl.pause = RELEASED;
	pushedCtrl.right = RELEASED;
	pushedCtrl.tmpExit = RELEASED;
	pushedCtrl.up = RELEASED;
	pushedCtrl.start = RELEASED;
}

void controle_Init(){

	unsigned char buf[6] = {'j','o','u','e','u','r'};

	bindCtrl.right = RIGHT;
	bindCtrl.left = LEFT;
	bindCtrl.up = UP;
	bindCtrl.pause = PAUSE;
	bindCtrl.tmpExit = EXIT;
	bindCtrl.bright = BRIGHT;
	bindCtrl.start = START;
	pushedCtrl.bright = RELEASED;
	pushedCtrl.left = RELEASED;
	pushedCtrl.pause = RELEASED;
	pushedCtrl.right = RELEASED;
	pushedCtrl.tmpExit = RELEASED;
	pushedCtrl.up = RELEASED;
	pushedCtrl.start = RELEASED;

	int i;
	for(i = 0; i < 6; ++i){
		localBuf.buf[i] = buf[i];
		localBuf.bufSize++;
	}
	copyBuf(localBuf, &input);
}

void controle_GetPushedButtons(controle *ctrl){
	ctrl->bright = pushedCtrl.bright;
	ctrl->left = pushedCtrl.left;
	ctrl->pause = pushedCtrl.pause;
	ctrl->right = pushedCtrl.right;
	ctrl->tmpExit = pushedCtrl.tmpExit;
	ctrl->up = pushedCtrl.up;
	ctrl->start = pushedCtrl.start;
}

bool checkPlayCtrl(){
	if(bindCtrl.right == bindCtrl.left || bindCtrl.right == bindCtrl.up
			|| bindCtrl.right == bindCtrl.pause || bindCtrl.right == bindCtrl.tmpExit
			|| bindCtrl.right == bindCtrl.bright || bindCtrl.right == bindCtrl.start){
		return false;
	}else if(bindCtrl.left == bindCtrl.up || bindCtrl.left == bindCtrl.pause
			|| bindCtrl.left == bindCtrl.tmpExit || bindCtrl.left == bindCtrl.bright
			|| bindCtrl.left == bindCtrl.start){
		return false;
	}else if(bindCtrl.up == bindCtrl.pause || bindCtrl.up == bindCtrl.tmpExit
			|| bindCtrl.up == bindCtrl.bright || bindCtrl.up == bindCtrl.start){
		return false;
	}else if(bindCtrl.pause == bindCtrl.tmpExit || bindCtrl.pause == bindCtrl.bright
			|| bindCtrl.pause == bindCtrl.start){
		return false;
	}else if(bindCtrl.tmpExit == bindCtrl.bright || bindCtrl.tmpExit == bindCtrl.start){
		return false;
	}else if(bindCtrl.bright == bindCtrl.start){
		return false;
	}
	return true;
}

void manipulateMenu(unsigned int button){
	//select menu

	if(button == UP){
		vertical_opt--;change = true;
	}else if(button == DOWN ){
		vertical_opt++;change = true;
	}else if(button == START){
		choose = true;change = true;
		menuIn = true;
	}else if(button == LEFT){
		hor_opt--;change = true;
	}else if(button == RIGHT){
		hor_opt++;change = true;
	}else if(button == EXIT){
		cExit = true;change = true;
		menuOut = true;
	}

	/*******************A REVOIR************************/
	if(main_menu == NOTHING && !started )
	{
		if(vertical_opt <= 0){
			vertical_opt = 1;
			menuError = true;
		}else if(vertical_opt > 2){
			vertical_opt = 2;
			menuError = true;
		}else
			menuSelect = true;
		//choose menu
		if(choose){
			switch (vertical_opt){
			case 1:
				main_menu = play;
				break;
			case 2:
				main_menu = options;
				break;
			}
			choose = false;
			vertical_opt = 1;
			menuChange = true;
		}
		if(cExit){
			cExit = false;
		}
	}else if (main_menu == NOTHING )
	{
		//XTft_ClearZone(0, 0, 640, 480, 0x0);
		if(vertical_opt <= 0){
			vertical_opt = 1;
			menuError = true;
		}else if(vertical_opt > 3){
			vertical_opt = 3;
			menuError = true;
		}else
			menuSelect = true;
		//choose menu
		if(choose){
			switch (vertical_opt){
			case 1:
				main_menu = play;
				break;
			case 2:
				main_menu = continu_playing;
				cExit = true;
				break;
			case 3:
				main_menu = options;
				break;
			}
			choose = false;
			vertical_opt = 1;
			menuChange = true;
		}
		if(cExit){
			cExit = false;
			pushedCtrl.tmpExit = PUSHED;
		}
	}
	/********************************************************/
	else if(main_menu == play){

		if(vertical_opt <= 0){
			vertical_opt = 1;
			menuError = true;
		}else if(vertical_opt > summary.levelSummaryArrayLen){
			vertical_opt = summary.levelSummaryArrayLen;
			menuError = true;
		}else
			menuSelect = true;

		displayMenuJouer();
		if(choose){
			//get map info function here
			mapID = vertical_opt -1;
			etat = downloading;
			main_menu = NOTHING;
			choose = false;
			vertical_opt = 1;
		}
		if(cExit){
			cExit = false;
			main_menu = NOTHING;
			vertical_opt = 1;
			menuChange = true;
		}
	}else if((main_menu == options) && (opt_cfg == NOTHING)){
		if(vertical_opt <= 0){
			vertical_opt = 1;
			menuError = true;
		}else if(vertical_opt > 3){
			vertical_opt = 3;
			menuError = true;
		}
		else
			menuSelect = true;

		//choose option menu
		if(choose){
			switch (vertical_opt){
			case 1:
				opt_cfg = player_id;
				break;
			case 2:
				opt_cfg = audio;
				break;
			case 3:
				opt_cfg = ctrl;
				break;
			}
			choose = false;
			vertical_opt = 1;
			menuChange = true;
		}
		if(cExit){
			cExit = false;
			vertical_opt = 2;
			main_menu = NOTHING;
			menuChange = true;
		}
	}else if((main_menu == options) && opt_cfg == player_id){
		//hit enter
		if(choose){
			choose = false;
			opt_cfg = NOTHING;
			vertical_opt = 1;
			//save the player name in the local buffer
			copyBuf(input, &localBuf);
			menuChange = true;
		}else if(button == ((button & RELEASE_MASK)) && (button != (START & RELEASE_MASK))){
			if(button == '\b' && input.bufSize > 0){
				--input.bufSize;
				change = true;
			}else if((((button > 96) && (button < 123)) || (button == 32) || ((button > 47) && button < 58)) && (input.bufSize < 16)){
				input.buf[input.bufSize] = (unsigned char)button;
				++input.bufSize;
				change = true;
			}
		}
		if(cExit){
			cExit = false;
			vertical_opt = 1;
			opt_cfg = NOTHING;
			copyBuf(localBuf, &input);
			menuChange = true;
		}
	}else if((main_menu == options) && opt_cfg == audio && opt_audio == NOTHING){
		if(vertical_opt <= 0){
			vertical_opt = 1;
			menuError = true;
		}else if(vertical_opt > 2){
			vertical_opt = 2;
			menuError = true;
		}else
			menuSelect = true;

		if(choose){
			switch (vertical_opt){
			case 1:
				opt_audio = volume;
				break;
			case 2:
				opt_audio = balance;
				break;
			}
			choose = false;
			hor_opt = 0;
		}
		if(cExit){
			cExit = false;
			vertical_opt = 2;
			opt_cfg = NOTHING;
			menuChange = true;
		}
	}else if((main_menu == options) && opt_cfg == audio && opt_audio == volume){
		vol_opt += hor_opt;
		hor_opt = 0;
		if(vol_opt < 0){
			vol_opt = 0;
			menuError = true;
		}else if(vol_opt > 3){
			vol_opt = 3;
			menuError = true;
		}else
			menuSelect = true;

		if(choose){
			local_vol_opt = vol_opt;
			switch(vol_opt)
			{
			case 0:
				XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_MasterVol, AC97_VOL_MUTE);
				XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_AuxOutVol, AC97_VOL_ATTN_46_0_DB);
				XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_PCMOutVol, AC97_VOL_ATTN_46_0_DB);
				break;
			case 1:
				XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_MasterVol, AC97_VOL_MIN);
				XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_AuxOutVol, AC97_VOL_ATTN_38_5_DB);
				XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_PCMOutVol, AC97_VOL_ATTN_38_5_DB);
				break;
			case 2:
				XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_MasterVol, AC97_VOL_MID);
				XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_AuxOutVol, AC97_VOL_ATTN_34_0_DB);
				XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_PCMOutVol, AC97_VOL_ATTN_34_0_DB);
				break;
			case 3:
				XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_MasterVol, AC97_VOL_MAX);
				XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_AuxOutVol, AC97_VOL_ATTN_28_0_DB);
				XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_PCMOutVol, AC97_VOL_ATTN_28_0_DB);
				break;
			default:
			break;
			}
			opt_audio = NOTHING;
			choose = false;
			hor_opt = 0;
			vertical_opt = 1;
		}
		if(cExit){
			cExit = false;
			opt_audio = NOTHING;
			hor_opt = 0;
			vertical_opt = 1;
			vol_opt = local_vol_opt;
		}
	}else if((main_menu == options) && opt_cfg == audio && opt_audio == balance){
		bal_opt += hor_opt;
		hor_opt = 0;
		if(bal_opt < 0){
			bal_opt = 0;
			menuError = true;
		}else if(bal_opt > 2){
			bal_opt = 2;
			menuError = true;
		}else
			menuSelect = true;

		if(choose){

			//call set balance function
			local_bal_opt = bal_opt;
			opt_audio = NOTHING;
			choose = false;
			hor_opt = 0;
			vertical_opt = 2;
		}
		if(cExit){
			opt_audio = NOTHING;
			hor_opt = 0;
			cExit = false;
			vertical_opt = 2;
			bal_opt = local_bal_opt;
		}
	}else if((main_menu == options) && (opt_cfg == ctrl) && (ctrl_cfg == NOTHING)){
		if(vertical_opt <= 0){
			vertical_opt = 1;
			menuError = true;
		}else if(vertical_opt > 6){
			vertical_opt = 6;
			menuError = true;
		}else
			menuSelect = true;

		if(choose){
			switch (vertical_opt){
			case 1:
				ctrl_cfg = right;
				break;
			case 2:
				ctrl_cfg = left;
				break;
			case 3:
				ctrl_cfg = up;
				break;
			case 4:
				ctrl_cfg = ctrl_pause;
				break;
			case 5:
				ctrl_cfg = ctrl_bright;
				break;
			case 6:
				ctrl_cfg = esc;
				break;
			default:
				break;
			}
			choose = false;
		}
		if(cExit){
			cExit = false;
			menuChange = true;
			if(!checkPlayCtrl()){
				errorCheckControles = true;
				return;
			}
			opt_cfg = NOTHING;
			vertical_opt = 3;
		}
	}else if((main_menu == options) && (opt_cfg == ctrl) && (ctrl_cfg == right) && (button & PUSHED_MASK) && (button != START)){
		bindCtrl.right = button;
		ctrl_cfg = NOTHING;
		change = true;
		vertical_opt = 1;
		choose = false;
	}else if((main_menu == options) && (opt_cfg == ctrl) && (ctrl_cfg == left) && (button & PUSHED_MASK) && (button != START)){
		bindCtrl.left = button;
		ctrl_cfg = NOTHING;
		change = true;
		vertical_opt = 2;
		choose = false;
	}else if((main_menu == options) && (opt_cfg == ctrl) && (ctrl_cfg == up) && (button & PUSHED_MASK) && (button != START)){
		bindCtrl.up = button;
		ctrl_cfg = NOTHING;
		change = true;
		vertical_opt = 3;
		choose = false;
	}else if((main_menu == options) && (opt_cfg == ctrl) && (ctrl_cfg == ctrl_pause) && (button & PUSHED_MASK) && (button != START)){
		bindCtrl.pause = button;
		ctrl_cfg = NOTHING;
		change = true;
		vertical_opt = 4;
		choose = false;
	}else if((main_menu == options) && (opt_cfg == ctrl) && (ctrl_cfg == ctrl_bright) && (button & PUSHED_MASK) && (button != START)){
		bindCtrl.bright = button;
		ctrl_cfg = NOTHING;
		change = true;
		vertical_opt = 5;
		choose = false;
	}else if((main_menu == options) && (opt_cfg == ctrl) && (ctrl_cfg == esc) && (button & PUSHED_MASK) && (button != START)){
		bindCtrl.tmpExit = button;
		ctrl_cfg = NOTHING;
		change = true;
		vertical_opt = 6;
		choose = false;
	}
}

void controle_PushedButton(unsigned int button){
	//select and choose menu
	if((etat == menu)){
		manipulateMenu(button);
	}else if ((etat == end) && (button == bindCtrl.start)){
		etat = menu;
		fini = false;
		XTft_ClearZone(82,40, 558, 448, 0x0);
	}else{
		if(button == bindCtrl.right){
		pushedCtrl.right = PUSHED;
		}else if(button == (bindCtrl.right & RELEASE_MASK)){
		pushedCtrl.right = RELEASED;
		}else if(button == bindCtrl.left){
		pushedCtrl.left = PUSHED;
		}else if(button == (bindCtrl.left & RELEASE_MASK)){
		pushedCtrl.left = RELEASED;
		}else if(button == bindCtrl.up){
		pushedCtrl.up = PUSHED;
		}else if(button == (bindCtrl.up & RELEASE_MASK)){
		pushedCtrl.up = RELEASED;
		}else if(button == bindCtrl.bright){
		pushedCtrl.bright = PUSHED;
		}/*else if(button == (bindCtrl.bright & RELEASE_MASK)){
		pushedCtrl.bright = RELEASED;
		}*/else if(button == bindCtrl.pause){
		pushedCtrl.pause = PUSHED;
		}/*else if(button == (bindCtrl.pause & RELEASE_MASK)){
		pushedCtrl.pause = RELEASED;
		}*/else if(button == bindCtrl.tmpExit){
		pushedCtrl.tmpExit = PUSHED;
		}/*else if(button == (bindCtrl.tmpExit & RELEASE_MASK)){
		pushedCtrl.tmpExit = RELEASED;
		}*/else if(button == bindCtrl.start){
		pushedCtrl.start = PUSHED;
		}/*else if(button == (bindCtrl.start & RELEASE_MASK)){
		pushedCtrl.start = RELEASED;
		}*/
	}/*else if(button == bindCtrl.start){
		pushedCtrl.start = PUSHED;
		input.buf[input.bufSize] = '\0';
		++input.bufSize;
		getId = false;
	}
	else if((button == (button & RELEASE_MASK)) && (button != (bindCtrl.start & RELEASE_MASK))){
		input.buf[input.bufSize] = (unsigned char)button;
		++input.bufSize;
	}*/
}


