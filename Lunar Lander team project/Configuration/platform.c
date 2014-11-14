///////////////////////////////////////////////////////////////////////////
/// @file platform.c
/// @author Chady El Feghaly 
/// @date 2013-10
/// @description Gestions des intérruptions pour le uartlite et pour le tick de notre timer.
/// @version 1.0
/// @update by Olivier Moussavou Cotte
///	@date 2013-11
/// @description Implémentation des ISR pour l'uart réalisée par l'équipe et du traitement intérruptions pour le son.
///	@version 1.1
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

 /* Includes */
#include "arch/cc.h"
#include "platform.h"
#include "platform_config.h"
#include "xil_cache.h"
#include "xparameters.h"
#include "xintc.h"
#include "xil_exception.h"
#include "../src/video.h"
#include "lwip/tcp.h"
#include "lwip/init.h"
#include "../src/icontrole.h"
#include "../src/physics.h"
#include "../src/typedef.h"
#include "../src/menuDisplay.h"
#include "../RealtimeDisplay/RealtimeDisplay.h"
#include "../Sons/tar.h"
#include "../Sons/ac97.h"

/* Variables */
XIntc InterruptController;     /* The instance of the Interrupt Controller */
extern controle scontrole;
extern Etat etat;
extern Menu main_menu;
extern Opt_audio opt_audio;
extern Options_cfg opt_cfg;
extern Ctrl_cfg ctrl_cfg;
extern GamePhysics phys;
extern XTft TftInstance;
extern ac97_core CfgAC97;
extern int bal_opt;
bool change = true;
unsigned int tick = 0;
extern int victory;
bool fini = false;
static int lwipCount = 0;
extern ac97_core CfgAC97;
extern bool land;
extern bool menuIn;
extern bool menuOut;
extern bool menuSelect;
extern bool menuError;
typedef enum { disable = 0, enable } interrupt_state;
extern int totalTime;
Sound sound;


///////////////////////////////////////////////////////////////////////////
void DeclenchementArretSon()
{
	if(etat == waiting || etat == computing || etat == checkVic)
	{
		if(scontrole.up || scontrole.left || scontrole.right)
		{
			InitCurrentSound(JET);
		}
	}
}


///////////////////////////////////////////////////////////////////////////
void PlayCurrentSound()
{
	uint32_t i = 0;
	uint32_t begin, end;
	if(sound.CurrentState == PLAYING)
	{
		begin = sound.CurrentIndex;
		end = sound.CurrentIndex + 256;
		if(end >= sound.FileSize)
		{
			sound.CurrentState = IDLE;
			end = sound.FileSize;
		}
		else
		{
			sound.CurrentIndex = end + 1;
		}
		AC97_adjustPCMrate(&CfgAC97, archive.WaveFileHeader[sound.SoundType].bytesPerSec);
		for(i = begin; i < end; ++i)
		{

			switch (bal_opt)
			{
				case 0: AC97_playSample(&CfgAC97, sound.Sample[i]>>16);
					break;
				case 1: AC97_playSample(&CfgAC97, sound.Sample[i]);
					break;
				case 2: AC97_playSample(&CfgAC97, sound.Sample[i]<<16);
					break;
			}
		}
	}
	else
	{
		while(!XAC97_isInFIFOFull(XPAR_PLB_AC97_0_BASEADDR))
		{
			AC97_playSample(&CfgAC97, 0);
		}
	}
}


///////////////////////////////////////////////////////////////////////////
void setup_ac97()
{
	/* Initialisation de plb_ac97 : */
	XAC97_HardReset(XPAR_PLB_AC97_0_BASEADDR);
	XAC97_InitAudio(XPAR_PLB_AC97_0_BASEADDR, 0);
	XAC97_ClearFifos(XPAR_PLB_AC97_0_BASEADDR);

	/**/
	AC97_init(&CfgAC97, XPAR_PLB_AC97_0_BASEADDR);
	AC97_setVolume(&CfgAC97, 25);

	/* Ajustement du volume audio : */
	XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_MasterVol, AC97_VOL_MAX);
	XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_AuxOutVol, AC97_VOL_ATTN_28_0_DB);
	XAC97_WriteReg(XPAR_PLB_AC97_0_BASEADDR, AC97_PCMOutVol, AC97_VOL_ATTN_28_0_DB);
}


///////////////////////////////////////////////////////////////////////////
void ac97_ISR(void *CallBackRef)
{
	PlayCurrentSound();
	XIntc_Acknowledge(&InterruptController, XPAR_XPS_INTC_0_PLB_AC97_0_INTERRUPT_INTR);
}


///////////////////////////////////////////////////////////////////////////
void uart_plb_equipe_3_ISR(void *CallBackRef)
{
	u32 status;

	status = uart_read_status((void*)BASE);

	tx_state = status & KU_SR_TX_ACTIVE;
	rx_state = status & KU_SR_RX_ACTIVE;

	if(rx_state == 0x8)
	{
		rx = uart_read((void*)BASE);
		controle_PushedButton(rx);
	}

	XIntc_Acknowledge(&InterruptController, XPAR_XPS_INTC_0_UART_PLB_EQUIPE_3_0_INTERRUPT_INTR);
}


///////////////////////////////////////////////////////////////////////////
void tick_handler(void *CallBackRef, u8 TmrCtrNumber)
{
	if(etat == computing || etat == waiting){
		tick++;
		if(tick == 20){
			tick = 0;
			if(totalTime > 0)
				totalTime--;
			else
				etat = checkVic;
			displayTime();
		}
	}

	lwipCount++;
	if(lwipCount == 4){
		timer_callback();
		lwipCount = 0;
	}

	controle_GetPushedButtons(&scontrole);
	DeclenchementArretSon();
	if(etat == waiting)
	{
		XTft_CapsuleMove(LanderBMP.Image, LanderBMP.Width, LanderBMP.Height,&phys);
		displayRealTimeData();
		XTft_CapsuleMove(LanderBMP.Image, LanderBMP.Width, LanderBMP.Height,&phys);
		etat = computing;
	}else if(etat == menu && change){
		displayMenu(main_menu,opt_cfg, ctrl_cfg, opt_audio, false);
		if(menuIn){
			InitCurrentSound(MENUIN);
			menuIn = false;
		}else if(menuOut){
			InitCurrentSound(MENUOUT);
			menuOut = false;
		}else if(menuError){
			InitCurrentSound(MENUERROR);
			menuError = false;
		}else if(menuSelect){
			InitCurrentSound(MENUSELECT);
			menuSelect = false;
		}
	}else if (etat == end && !fini){
		fini = true;
		displayEndGame(victory);
	}
	if(land){
		InitCurrentSound(LAND);
		land = false;
	}
	XIntc_Acknowledge(&InterruptController, XPAR_XPS_INTC_0_FIT_TIMER_0_INTERRUPT_INTR);
}


///////////////////////////////////////////////////////////////////////////
void timer_callback()
{
	/* we need to call tcp_fasttmr & tcp_slowtmr at intervals specified by lwIP.
	 * It is not important that the timing is absoluetly accurate.
	 */

	static int odd = 1;
	tcp_fasttmr();

	odd = !odd;
	if (odd)
		tcp_slowtmr();
}


///////////////////////////////////////////////////////////////////////////
void setup_uart_plb_equipe_3()
{
	u32 status;
	interrupt_state interrupt = enable;

	uart_set_enable_interrupts((void*)BASE, interrupt);
	uart_set_enable_rx_full_intr((void*)BASE, interrupt);
	uart_set_enable_tx_empty_intr((void*)BASE, interrupt);

	status = uart_read_status((void*)BASE);
	tx_state = status & KU_SR_TX_ACTIVE;
	rx_state = status & KU_SR_RX_ACTIVE;
}


///////////////////////////////////////////////////////////////////////////
int platform_setup_interrupts()
{
	int Status;

	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	Status = XIntc_Initialize(&InterruptController, PLATFORM_INTC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Start the interrupt controller such that interrupts are enabled for
	 * all devices that cause interrupts, specific real mode so that
	 * the UartLite can cause interrupts through the interrupt controller.
	 */
	Status = XIntc_Start(&InterruptController, XIN_REAL_MODE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/* Start the interrupt controller */
	XIntc_MasterEnable(PLATFORM_INTC_BASEADDR);

	microblaze_register_handler((XInterruptHandler)XIntc_InterruptHandler, &InterruptController);

	/*
	 * Connect a device driver handler that will be called when an interrupt
	 * for the device occurs, the device driver handler performs the
	 * specific interrupt processing for the device.
	 */
	Status = XIntc_Connect(&InterruptController, XPAR_XPS_INTC_0_FIT_TIMER_0_INTERRUPT_INTR, (XInterruptHandler)tick_handler, (void *)0);
	if (Status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}

	/*
	 * Enable the interrupt for the fit timers device.
	 */
	XIntc_Enable(&InterruptController,XPAR_XPS_INTC_0_FIT_TIMER_0_INTERRUPT_INTR);

	setup_uart_plb_equipe_3();

	Status = XIntc_Connect(&InterruptController, XPAR_XPS_INTC_0_UART_PLB_EQUIPE_3_0_INTERRUPT_INTR, (XInterruptHandler)uart_plb_equipe_3_ISR, (void *)0);
	if (Status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}

	/*
	* Enable the interrupt for the uart_plb_equipe_3
	*/
	XIntc_Enable(&InterruptController, XPAR_XPS_INTC_0_UART_PLB_EQUIPE_3_0_INTERRUPT_INTR);

	setup_ac97();

	Status = XIntc_Connect(&InterruptController, XPAR_XPS_INTC_0_PLB_AC97_0_INTERRUPT_INTR, (XInterruptHandler)ac97_ISR, (void *)0);
	if (Status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}

	/*
	 * Enable the interrupt for the ac97 codec
	 */
	XIntc_Enable(&InterruptController, XPAR_XPS_INTC_0_PLB_AC97_0_INTERRUPT_INTR);

	return XST_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////
void platform_enable_interrupts()
{
	microblaze_enable_interrupts();
}


///////////////////////////////////////////////////////////////////////////
void enable_caches()
{
#ifdef XPAR_MICROBLAZE_USE_ICACHE
	Xil_ICacheEnable();
#endif
#ifdef XPAR_MICROBLAZE_USE_DCACHE
	Xil_DCacheEnable();
#endif
}


///////////////////////////////////////////////////////////////////////////
void disable_caches()
{
	Xil_DCacheDisable();
	Xil_ICacheDisable();
}


///////////////////////////////////////////////////////////////////////////
int init_platform()
{
	int Status;
	enable_caches();

	Status = platform_setup_interrupts();
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////
void cleanup_platform()
{
	disable_caches();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////