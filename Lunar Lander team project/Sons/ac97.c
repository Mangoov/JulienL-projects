/*
 * ac97.c
 *
 *  Created on: 2013-11-12
 */

#include "ac97.h"

#define NUM_VOL_INCREMENTS 20;
const Xint32 VOLUME_MOD = (AC97_VOL_MIN - AC97_VOL_MAX) / NUM_VOL_INCREMENTS;


void AC97_init(struct ac97_core *ac97, Xuint32 baseAddr)
{
	ac97->baseAddress = baseAddr;

	XAC97_HardReset(ac97->baseAddress);
	XAC97_InitAudio(ac97->baseAddress, 0);
	AC97_clearFifos(ac97);
	AC97_resetVolume(ac97);
	AC97_enable_interrupt(ac97);
}

void AC97_enable_interrupt(struct ac97_core *ac97)
{
	XAC97_mSetControl(ac97->baseAddress, AC97_ENABLE_IN_FIFO_INTERRUPT);
}

void AC97_disable_interrupt(struct ac97_core *ac97)
{
	XAC97_mSetControl(ac97->baseAddress, AC97_ENABLE_IN_FIFO_INTERRUPT);
}

void AC97_setVolume(struct ac97_core *ac97, Xuint32 volumePercentage)
{
	if (volumePercentage >= 0 && volumePercentage <= 100)
	{
		Xuint8 side_volume = (( 100 - volumePercentage ) * (Xuint8) AC97_VOL_MIN ) / 100;
		ac97->master_volume = (side_volume << 8) | side_volume;
		XAC97_WriteReg(ac97->baseAddress, AC97_MasterVol, ac97->master_volume);
	}
}

void AC97_muteVolume(struct ac97_core *ac97)
{
	XAC97_WriteReg(ac97->baseAddress, AC97_MasterVol, AC97_VOL_MUTE);
}

void AC97_unMuteVolume(struct ac97_core *ac97)
{
	XAC97_WriteReg(ac97->baseAddress, AC97_MasterVol, ac97->master_volume);
}

void AC97_resetVolume(struct ac97_core *ac97)
{
	ac97->master_volume = AC97_VOL_MID;

	XAC97_WriteReg(ac97->baseAddress, AC97_MasterVol, ac97->master_volume);
	XAC97_WriteReg(ac97->baseAddress, AC97_AuxOutVol, AC97_VOL_MAX);
	XAC97_WriteReg(ac97->baseAddress, AC97_PCMOutVol, AC97_VOL_MAX);
}

void AC97_setBalance(struct ac97_core *ac97, Xint32 balance)
{
	// [ -100 to   0 [ : balance on the left channel
	// ]    0 to 100 ] : balance on the right
	if (balance >= 0 && balance <= 200)
	{
	}
}

int AC97_inFifoEmpty(struct ac97_core *ac97)
{
	return XAC97_isInFIFOEmpty(ac97->baseAddress);
}

void AC97_adjustPCMrate(struct ac97_core *ac97, Xuint32 pcmRate)
{
	/** Enable VRA Mode **/
	XAC97_WriteReg(ac97->baseAddress, AC97_ExtendedAudioStat, 1);

	/** Assign DAC PCM rate **/
	XAC97_WriteReg(ac97->baseAddress, AC97_PCM_DAC_Rate, pcmRate);
}

void AC97_playSample(struct ac97_core *ac97, Xuint32 sample)
{
	XAC97_WriteFifo(ac97->baseAddress, sample);
}


void AC97_clearFifos(struct ac97_core *ac97)
{
	XAC97_ClearFifos(ac97->baseAddress);
}
