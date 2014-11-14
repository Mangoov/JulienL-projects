#ifndef AC97_H
#define AC97_H

#include "xac97_l.h"

#include "xbasic_types.h"
#include "xparameters.h"

typedef struct ac97_core
{
	Xuint32 baseAddress;
	Xuint16 master_volume;
	Xuint8  left_volume;
	Xuint8  right_volume;
} ac97_core;

void AC97_init(struct ac97_core *, Xuint32 baseAddr);

// Volume control
void AC97_setVolume(struct ac97_core *, Xuint32);
void AC97_muteVolume(struct ac97_core *);
void AC97_unMuteVolume(struct ac97_core *);
void AC97_resetVolume(struct ac97_core *);
void AC97_setBalance(struct ac97_core *, Xint32);

// Status
int  AC97_outFifoEmpty(struct ac97_core *);

// Playback
void AC97_adjustPCMrate(struct ac97_core *, Xuint32);
void AC97_playSample(struct ac97_core *, Xuint32);

void AC97_interruptHandler(void *);
void AC97_enable_interrupt(struct ac97_core *);

void AC97_clearFifos(struct ac97_core *ac97);


#endif // AC97_H
