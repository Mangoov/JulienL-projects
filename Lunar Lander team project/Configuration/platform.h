///////////////////////////////////////////////////////////////////////////
/// @file platform.h
/// @author Chady El Feghaly 
/// @date 2013-10
/// @description Gestions des intérruptions pour le uartlite et pour le tick de notre timer.
/// @version 1.0
/// @update by Olivier Moussavou Cotte
///	@date 2013-11
/// @description Ajout des ISR pour l'uart réalisée par l'équipe et du traitement intérruptions pour le son.
/// @Fonctions ajoutées: setup_ac97, ac97_ISR, setup_uart_plb_equipe_3, uart_plb_equipe_3_ISR, PlayCurrentSound, DeclenchementArretSon
///	@version 1.1
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __PLATFORM_H_
#define __PLATFORM_H_

/* Includes */
#include "xintc.h"
#include "xuartlite.h"
#include "mb_interface.h"
#include "uart_plb_equipe3.h"
#include "../Sons/ac97.h"


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		init_platform
//						Enable la cache du MicroBlaze.
//						Active les intérruptions pour le Microblaze.
// PARAMETRES: 			Aucune.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:           	À appeler au tout début du main.
////////////////////////////////////////////////////////////////////////////////
int init_platform();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		cleanup_platform
//						Disable la cache du MicroBlaze.
// PARAMETRES: 			Aucune.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Dans l'état courant du programme, n'est jamais appelé
////////////////////////////////////////////////////////////////////////////////
void cleanup_platform();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		timer_callback
//						lwip exige que l'on appel tcp_fasttmr & tcp_slowtmr à intervalle de 250 ms (approx.)
//						pour vider la FIFO de ces paquets.
// PARAMETRES: 			WAV_FILE_TYPE SoundType: Le type de son à être entendu.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Appelé dans le tick_handler.
////////////////////////////////////////////////////////////////////////////////
void timer_callback();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		platform_enable_interrupts
//						Active les intérruptions pour le Microblaze.
//						Initialise l'intc.
//						Enregistre l'intc au MicroBlaze.
//						Enregistre tous les périphériques qui produisent des inttéruptions à l'intc.
//						Initialise tous les périphériques qui produisent des intérruptions.
// PARAMETRES: 			Aucune
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Appelé par init_platform.
////////////////////////////////////////////////////////////////////////////////
void platform_enable_interrupts();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		setup_ac97
//						Initialise le contrôlleur ac97
// PARAMETRES: 			Aucun
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Appelé dans platform_enable_interrupts
////////////////////////////////////////////////////////////////////////////////
void setup_ac97();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		PlayCurrentSound
//						S'il y a un son à jouer, le joue par paquet de 256 samples, dans le cas contraire écrit du silence dans le FIFO du ac97.
// PARAMETRES: 			Aucune
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Appelé dans l'ISR du ac97. Utilise la variable sound.
////////////////////////////////////////////////////////////////////////////////
void PlayCurrentSound();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		DeclenchementArretSon
//						Sert à déterminer si un son doit être joué en mettant à jour la variable sound.
// PARAMETRES: 			Aucune.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Appelé dans le tick_handler.
////////////////////////////////////////////////////////////////////////////////
void DeclenchementArretSon();


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		ac97_ISR
//						Gère l'intérruption du ac97.
//						Est appelé lorsque la FIFO du contrôlleur ac97 est à moitié pleine.
//						S'il y a un son à jour un le joue par paquet de 256 échantillon.
//						Dans le cas contraire on écrit du silence.
// PARAMETRES: 			Aucune.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Se sert de la structure Sound pour savoir s'il y a un son à jouer.
////////////////////////////////////////////////////////////////////////////////
void ac97_ISR(void *CallBackRef);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		uart_plb_equipe_3_ISR
//						ISR de l'uart plb. Appelé lorsqu'un tranmission est terminée ou un caractère a été reçu.
//						Lors de la transmission, on effectue une attente active sur un flag mis-à-jour par ce ISR.
// PARAMETRES: 			Aucun.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Sert à mettre à jour controle_PushedButton avec le nouveau caractère et à transmattre des octets au rs232 pour le debbugage.
////////////////////////////////////////////////////////////////////////////////
void uart_plb_equipe_3_ISR(void *CallBackRef);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		tick_handler
//						Le Fit Timer génère une intérruption à tous les 250ms.
//						Gère cette inérruption (timer_callback du lwip, affichage temps réel etc).
// PARAMETRES: 			WAV_FILE_TYPE SoundType: Le type de son à être entendu.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Appelé dans l'ISR du ac97.
////////////////////////////////////////////////////////////////////////////////
void tick_handler(void *CallBackRef, u8 TmrCtrNumber);


////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION: 		setup_uart_plb_equipe_3
//						Active les inttérruptions de l'uart_plb_quipe_3 mets à jours ses variables de status pour la transmission/réception
// PARAMETRES: 			Aucune.
// VALEUR DE RETOUR:    Aucune.
// REMARQUE:            Doit être impéaitivement être appelé pour utiliser le matériel.
////////////////////////////////////////////////////////////////////////////////
void setup_uart_plb_equipe_3();

#endif /* __PLATFORM_H_ */

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
