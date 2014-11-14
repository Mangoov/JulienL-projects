///////////////////////////////////////////////////////////////////////////
/// @file uart_plb_equipe3.c
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


#include "uart_plb_equipe3.h"

typedef int bool;
enum { false, true };

///////////////////////////////////////////////////////////////////////////////
#define CYCLESBITS 	0x18
#define RX 			0x14
#define TX 			0x10
#define STATUS 		0x0c
#define CTRL 		0x08
#define STATSRX 	0x04
#define STATSTX 	0x00


///////////////////////////////////////////////////////////////////////////////
void uart_reset(void* base)
{
	XIo_Out32(base + CTRL, KU_CR_ENABLE_RST);
}


///////////////////////////////////////////////////////////////////////////////
void uart_write(void* base, u8 byte)
{
	XIo_Out32(base + TX, byte);
}


///////////////////////////////////////////////////////////////////////////////
u32 uart_read(void* base)
{
	return XIo_In32(base + RX);
}


///////////////////////////////////////////////////////////////////////////////
void uart_set_baud_rate(void* base, unsigned int baud_rate)
{
	char buffer[64] = {'\0'};
	u32 oldBaudRate, newBaudRate;
	oldBaudRate = XIo_In32(base + CYCLESBITS); // Debug
	bool bBaudRateTicks, bBaudRate = baud_rate == 2400 || baud_rate == 9600 || baud_rate == 14400 || baud_rate == 19200 || baud_rate == 28800 || baud_rate == 56000 || baud_rate == 115200;
	if(bBaudRate == true)
	{
		XIo_Out32(base + CYCLESBITS, (u32)baud_rate);
		newBaudRate = XIo_In32(base + CYCLESBITS);
		bBaudRateTicks = newBaudRate == 868 || newBaudRate == 1786 || newBaudRate == 3472 || newBaudRate == 5208 || newBaudRate == 6944 || newBaudRate == 10417 || newBaudRate == 41667;
		if(bBaudRateTicks == false)
		{
			sprintf(buffer, "Baud rate was not set to %u. The current value is %u.\n", baud_rate, (unsigned int)newBaudRate);
			stdout_write_char_array(buffer, strlen(buffer));
		}
	}
	else
	{
		sprintf(buffer, "%u is not a supported baud rate. Baud rate will be set by default to 9600.\n", baud_rate);
		stdout_write_char_array(buffer, strlen(buffer));
	}
}


///////////////////////////////////////////////////////////////////////////////
void uart_set_enable_interrupts(void* base, int enable)
{
	char buffer[32] = {'\0'};
	u32 regValue, ctrlNew, ctrlOld = XIo_In32(base + CTRL);
	if(enable)
	{
		ctrlNew = (ctrlOld | KU_CR_GLOBAL_ENABLE_INTERRUPT) & KU_CR_DISABLE_RST;
		XIo_Out32(base + CTRL,  ctrlNew);
		regValue = XIo_In32(base + CTRL);
		if(regValue != ctrlNew && regValue != 0x8 && regValue != 0xA && regValue != 0xC && regValue != 0xE)
		{
			sprintf(buffer, "%u invalid global interrupt state (enable).\n", (unsigned int)regValue);
			stdout_write_char_array(buffer, strlen(buffer));
		}
	}
	else
	{
		ctrlNew = (ctrlOld | KU_CR_GLOBAL_DISABLE_INTERRUPT) & KU_CR_DISABLE_RST;
		XIo_Out32(base + CTRL,  ctrlNew);
		regValue = XIo_In32(base + CTRL);
		if(regValue != ctrlNew && regValue != 0x0 && regValue != 0x2 && regValue != 0x4 && regValue != 0x6)
		{
			sprintf(buffer, "%u invalid global interrupt control state (disable).\n", (unsigned int)regValue);
			stdout_write_char_array(buffer, strlen(buffer));
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
void uart_set_enable_rx_full_intr(void* base, int enable)
{
	char buffer[32] = {'\0'};
	u32 regValue, ctrlNew, ctrlOld = XIo_In32(base + CTRL);
	if(enable)
	{
		ctrlNew = (ctrlOld | KU_CR_RX_ENABLE_INTERRUPT) & KU_CR_DISABLE_RST;
		XIo_Out32(base + CTRL,  ctrlNew);
		regValue = XIo_In32(base + CTRL);
		if(regValue != ctrlNew && regValue != 0x2 && regValue != 0x6 && regValue != 0xA && regValue != 0xE)
		{
			sprintf(buffer, "%u invalid rx control state (enable).\n", (unsigned int)regValue);
			stdout_write_char_array(buffer, strlen(buffer));
		}
	}
	else
	{
		ctrlNew = (ctrlOld | KU_CR_RX_DISABLE_INTERRUPT) & KU_CR_DISABLE_RST;
		XIo_Out32(base + CTRL,  ctrlNew);
		regValue = XIo_In32(base + CTRL);
		if(regValue != ctrlNew && regValue != 0x0 && regValue != 0x4 && regValue != 0x8 && regValue != 0xC)
		{
			sprintf(buffer, "%u invalid rx control state (disable).\n", (unsigned int)regValue);
			stdout_write_char_array(buffer, strlen(buffer));
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
void uart_set_enable_tx_empty_intr(void* base, int enable)
{
	char buffer[32] = {'\0'};
	u32 regValue, ctrlNew, ctrlOld = XIo_In32(base + CTRL);
	if(enable)
	{
		ctrlNew = (ctrlOld | KU_CR_TX_ENABLE_INTERRUPT) & KU_CR_DISABLE_RST;
		XIo_Out32(base + CTRL,  ctrlNew);
		regValue = XIo_In32(base + CTRL);
		if(regValue != ctrlNew && regValue != 0x4 && regValue != 0x6 && regValue != 0xC && regValue != 0xE)
		{
			sprintf(buffer, "%u invalid tx control state (enable).\n", (unsigned int)regValue);
			stdout_write_char_array(buffer, strlen(buffer));
		}
	}
	else
	{
		ctrlNew = (ctrlOld | KU_CR_TX_DISABLE_INTERRUPT) & KU_CR_DISABLE_RST;
		XIo_Out32(base + CTRL,  ctrlNew);
		regValue = XIo_In32(base + CTRL);
		if(regValue != ctrlNew && regValue != 0x0 && regValue != 0x2 && regValue != 0x8 && regValue != 0xA)
		{
			sprintf(buffer, "%u invalid tx control state (disable).\n", (unsigned int)regValue);
			stdout_write_char_array(buffer, strlen(buffer));
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
u32 uart_read_status(void* base)
{
	return XIo_In32(base + STATUS);
}


///////////////////////////////////////////////////////////////////////////////
u32 uart_read_rx_stats(void* base)
{
	return XIo_In32(base + STATSRX);
}


///////////////////////////////////////////////////////////////////////////////
u32 uart_read_tx_stats(void* base)
{
	return XIo_In32(base + STATSTX);
}


////////////////////////////////////////////////////////////////////////
u32 stdin_read_char_array(char buf[], size_t size)
{
	u32 rx = '\0', i = 0;
	while(i < size - 1)
	{
		while(rx_state != 0x8 && rx != '\r' && rx != '\n')
		{
		}
		rx_state &= 0x7;
		rx = uart_read((void*)BASE);
		buf[i++] = rx;
	}
	buf[i] = '\0';
	return i;
}


////////////////////////////////////////////////////////////////////////
u8 stdin_read_char()
{
	while(rx_state != 0x8)
	{
	}
	rx_state &= 0x7;
	return rx;
}


////////////////////////////////////////////////////////////////////////
u32 stdout_write_char_array(char buf[], size_t size)
{
	u32 i = 0;
	while(i < size)
	{
		while(tx_state != 0x4)
		{
		}
		tx_state &= 0xb;
		uart_write((void*)BASE, buf[i++]);
	}
	return i;
}

void stdout_write_char(char buf)
{
	while(tx_state != 0x4)
	{
	}
	tx_state &= 0xb;
	uart_write((void*)BASE, buf);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
