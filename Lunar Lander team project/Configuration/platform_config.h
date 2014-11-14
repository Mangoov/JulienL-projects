///////////////////////////////////////////////////////////////////////////
/// @file platform_config.h
/// @author Chady El Feghaly 
/// @date 2013-10
/// @description Définitions des paramètres de la plateforme matérielle
/// @version 1.0
///
/// @addtogroup inf3995 INF3995-03
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __PLATFORM_CONFIG_H_
#define __PLATFORM_CONFIG_H_

#define MS 100000

#define STDOUT_IS_UARTLITE

#define PLATFORM_EMAC_BASEADDR XPAR_HARD_ETHERNET_MAC_CHAN_0_BASEADDR

//interrupt controller
#define PLATFORM_INTC_DEVICE_ID          XPAR_INTC_0_DEVICE_ID
#define PLATFORM_INTC_BASEADDR			 XPAR_INTC_0_BASEADDR

//uartlite
#define PLATFORM_UARTLITE_DEVICE_ID      XPAR_UARTLITE_1_DEVICE_ID
#define PLATFORM_UARTLITE_INT_IRQ_ID     XPAR_INTC_0_UARTLITE_1_VEC_ID

//xps timer0
#define PLATFORM_TMRCTR_0_DEVICE_ID	XPAR_TMRCTR_0_DEVICE_ID
#define PLATFORM_TMRCTR_0_BASEADDR	XPAR_XPS_TIMER_0_BASEADDR
#define PLATFORM_TMRCTR_0_INTERRUPT_ID	XPAR_INTC_0_TMRCTR_0_VEC_ID
#define PLATFORM_TMRCTR_0_INTERRUPT_MASK XPAR_XPS_TIMER_0_INTERRUPT_MASK
#define PLATFORM_TMRCTR_0	 0
#define PLATFORM_TMRCTR_0_RESET_VALUE	 (MS *(float)250)

#endif /* __PLATFORM_CONFIG_H_ */

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////