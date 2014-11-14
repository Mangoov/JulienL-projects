///////////////////////////////////////////////////////////////////////////
/// @file uartPilote.h
/// @author Chady El-Feghaly, Khalil Medawar
/// @date 2013-09
/// @version 1.0
///
/// @modified by Olivier Moussavou Cotte
/// @date 2013-10
/// @version 1.1
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef _PILOTE_H_
#define _PILOTE_H_

#include <xparameters.h> 	/* XPAR_KRAZY_UART_0_BASEADDR */
#include <xbasic_types.h>
#include <xio.h>
#include <stdio.h>			/* sprintf */
#include <string.h> 		/* memset, strlen */

/* adresse absolue choisie pour le bloc uart */ 
#define BASE XPAR_UART_PLB_EQUIPE_3_0_BASEADDR

///////////////////////////////////////////////////////////////////////////////
volatile u32 rx_state, tx_state;
volatile u8 rx;


/* Status Register bit positions */
#define KU_SR_RX_FULL		0x1	/* RX register full */
#define KU_SR_TX_EMPTY		0x2	/* TX register empty */
#define KU_SR_TX_ACTIVE		0x4	/* uart is transmiting */
#define KU_SR_RX_ACTIVE		0x8	/* uart is receiving */

/* Control Register bit positions */
#define KU_CR_ENABLE_RST				0x1
#define KU_CR_DISABLE_RST				0xE
#define KU_CR_GLOBAL_ENABLE_INTERRUPT	0x8
#define KU_CR_GLOBAL_DISABLE_INTERRUPT	0x6
#define KU_CR_TX_ENABLE_INTERRUPT		0x4
#define KU_CR_TX_DISABLE_INTERRUPT		0xA
#define KU_CR_RX_ENABLE_INTERRUPT		0x2
#define KU_CR_RX_DISABLE_INTERRUPT		0xC
#define KU_CR_ENABLE_STDIN_FLUSH		0X1E
#define KU_CR_DISABLE_STDIN_FLUSH		0XE


////////////////////////////////////////////////////////////////////////
///
/// @fn void uart_reset(void* base)
///
/// R�initialise (logiciel) le UART.
///
/// @param[in] base : Adresse m�moire de la base du p�riph�rique.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void uart_reset(void* base);


////////////////////////////////////////////////////////////////////////
///
/// @fn void uart_write(void* base, u8 byte)
///
/// Envoie un octet.
///
/// @param[in] base : Adresse m�moire de la base du p�riph�rique.
/// @param[in] byte : Byte � envoyer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void uart_write(void* base, u8 byte);


////////////////////////////////////////////////////////////////////////
///
/// @fn u8 uart_read(void* base)
///
/// Lit un octet re�u.
///
/// @param[in] base : Adresse m�moire de la base du p�riph�rique.
///
/// @return Byte lu.
///
////////////////////////////////////////////////////////////////////////
u32 uart_read(void* base);


////////////////////////////////////////////////////////////////////////
///
/// @fn void uart_set_baud_rate(void* base, unsigned int baud_rate)
///
/// Ajuste le baud rate.
///
/// @param[in] bass 		: Adresse m�moire de la base du p�riph�rique.
/// @param[in] baud_rate 	: Nouveau baud rate.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void uart_set_baud_rate(void* base, unsigned int baud_rate);


////////////////////////////////////////////////////////////////////////
///
/// @fn void uart_set_enable_interrupts(void* base, int enable)
///
/// active/d�sactive les interruptions globalement
///
/// @param[in] base : Adresse m�moire de la base du p�riph�rique..
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void uart_set_enable_interrupts(void* base, int enable);


////////////////////////////////////////////////////////////////////////
///
/// @fn void uart_set_enable_rx_full_intr(void* base, int enable)
///
/// active/d�sactive l�interruption de r�ception pleine.
///
/// @param[in] base 	: Adresse m�moire de la base du p�riph�rique.
/// @param[in] enable 	: flag qui permet de savoir si on veut enable/disable les interruptions de r�ception pleine.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void uart_set_enable_rx_full_intr(void* base, int enable);


////////////////////////////////////////////////////////////////////////
///
/// @fn void uart_set_enable_tx_empty_intr(void* base, int enable)
///
/// active/d�sactive l�interruption de transmission vide.
///
/// @param[in] base 	: Adresse m�moire de la base du p�riph�rique.
/// @param[in] enable 	: flag qui permet de savoir si on veut enable/disable les interruptions de transmission vide.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void uart_set_enable_tx_empty_intr(void* base, int enable);


////////////////////////////////////////////////////////////////////////
///
/// @fn u32 uart_read_status(void* base)
///
/// Lit le registre de statut.
///
/// @param[in] base : Adresse m�moire de la base du p�riph�rique.
///
/// @return Les 4 bit du registres de status dans une 32 bits.
///
////////////////////////////////////////////////////////////////////////
u32 uart_read_status(void* base);


////////////////////////////////////////////////////////////////////////
///
/// @fn u32 uart_read_rx_stats(void* base)
///
/// R�cup�re les statistiques de r�ception.
///
/// @param[in] base : Adresse m�moire de la base du p�riph�rique.
///
/// @return Les statistiques de r�ception.
///
////////////////////////////////////////////////////////////////////////
u32 uart_read_rx_stats(void* base);


////////////////////////////////////////////////////////////////////////
///
/// @fn u32 uart_read_tx_stats(void* base)
///
/// R�cup�re les statistiques de transmission.
///
/// @param[in] base : Adresse m�moire de la base du p�riph�rique.
///
/// @return Les statistiques de transmission.
///
////////////////////////////////////////////////////////////////////////
u32 uart_read_tx_stats(void* base);


////////////////////////////////////////////////////////////////////////
///
/// @fn void stdin_read_char(char *buf, size_t size)
///
/// r�cup�re de l'entr�e standard un caract�re jusqu'� tant que le buffer buf soit plein
/// ou que le caract�re \n soit rencontr�e
///
/// @param[inout] buf 	: tampon o� l'on stocke les caract�res lus de l'entr�e standard.
/// @param[in] size 	: taile du tampon.
///
/// @return Nombre d'octets lus.
///
////////////////////////////////////////////////////////////////////////
u32 stdin_read_char_array(char buf[], size_t size);
u8 stdin_read_char();

////////////////////////////////////////////////////////////////////////
///
/// @fn void stdout_write_char(char *buf, size_t size)
///
/// r�cup�re les statistiques de transmission
///
/// @param[inout] buf 	: tampon o� l'on lits les caract�res dirig�s vers la sortie standard.
/// @param[in] size 	: taile du tampon.
///
/// @return Nombre d'octets �crit.
///
////////////////////////////////////////////////////////////////////////
u32 stdout_write_char_array(char buf[], size_t size);

void stdout_write_char(char buf);

#endif /* _PILOTE_H_ */

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
