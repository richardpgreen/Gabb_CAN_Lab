/*C**************************************************************************
* NAME: test_api.c 
*----------------------------------------------------------------------------
* CREATED_BY:    Jean-Sebastien BERTHY
* CREATION_DATE: 15/01/2001 
* AUTHOR:        $Author: jberthy $
* REVISION       $Revision: 1.3 $
* DATE:          $Date: 2001/09/06 06:23:19 $
*----------------------------------------------------------------------------
* PURPOSE: 
*
*****************************************************************************/

/*_____ I N C L U D E S ____________________________________________________*/
#include "stdio.h"
#include "config.h"

/*_____ M A C R O S ________________________________________________________*/

/*_____ D E F I N I T I O N ________________________________________________*/
Uchar	xdata tab[256];
/*_____ D E C L A R A T I O N ______________________________________________*/


/*F**************************************************************************
* NAME: uart_init 
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebatien BERTHY 
*****************************************************************************/
void uart_init (void)
{
  SCON = 0x50;
  TMOD = TMOD | 0x20 ;      /*  Timer1 in mode 2 & not gated */
  TH1 = 0xF3;               /*  4800 bauds at 12 MHZ */
  TL1 = 0xF3; 
  PCON = PCON & 0X80;
  TCON |= 0x40;         
  TI=1;
}

/*F**************************************************************************
* NAME: bin_to_asc.        
* PARAMS:  
* to_convert: byte to parse in ascii
*----------------------------------------------------------------------------
* PURPOSE: This function return the ascii value
*****************************************************************************/
Uchar bin_to_ascii (Uchar to_convert)
{
  Uchar convert;

  if ((to_convert >= 0) &&
      (to_convert <= 9)   )
  {
    convert = to_convert + 0x30;
  }
  else
  {
    convert = to_convert + 0x37;
  }
  return (convert);
}

/*F**************************************************************************
* NAME: tx_data 
*----------------------------------------------------------------------------
* PARAMS:  
* data_to_tx: byte to transmit on the line
*----------------------------------------------------------------------------
* PURPOSE: This function send on UART the value
*****************************************************************************/
void tx_data (Uchar data_to_tx)
{
  while(!TI);
  TI = 0;
  SBUF = data_to_tx;
}

/*F**************************************************************************
* NAME: send_byte_ascii 
*----------------------------------------------------------------------------
* PARAMS:  
* byte_to_tx: byte to send on UART in ascii
*----------------------------------------------------------------------------
* PURPOSE: 
*****************************************************************************/
void send_byte_ascii(Uchar byte_to_tx)
{
  Uchar data_to_tx;

  data_to_tx = bin_to_ascii( byte_to_tx >> 4);
  tx_data(data_to_tx);
  data_to_tx = bin_to_ascii( byte_to_tx & 0x0F);
  tx_data(data_to_tx);
}

/*F**************************************************************************
* NAME: send_cr_lf 
*----------------------------------------------------------------------------
* PARAMS:  
*----------------------------------------------------------------------------
* PURPOSE: 
*****************************************************************************/
void send_cr_lf(void)
{
  tx_data(0x0D);
  tx_data(0x0A);
}

/*F**************************************************************************
* NAME: main 
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebatien BERTHY 
*****************************************************************************/
void main (void)
{
	Uint16 cpt;
  Uchar	value;
  
	uart_init();


/*---- Test BSB ------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

// Read BSB
	printf("BSB = ");	
	value = __api_rd_BSB ();
	send_byte_ascii(value);
	send_cr_lf();
// Write BSB
	printf("Write BSB = 0x55");	
	value = __api_wr_BSB (0x55);
	send_cr_lf();
// Read BSB
	printf("BSB = ");	
	value = __api_rd_BSB ();
	send_byte_ascii(value);
	send_cr_lf();
// Write BSB
	printf("Write BSB = 0xFF");	
	value = __api_wr_BSB (0xFF);
	send_cr_lf();
// Read BSB
	printf("BSB = ");	
	value = __api_rd_BSB ();
	send_byte_ascii(value);
	send_cr_lf();

/*---- Test SBV ------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

// Read SBV
	printf("SBV = ");	
	value = __api_rd_SBV ();
	send_byte_ascii(value);
	send_cr_lf();
// Write SBV
	printf("Write SBV = 0xAA");	
	value = __api_wr_SBV (0xAA);
	send_cr_lf();
// Read SBV
	printf("SBV = ");	
	value = __api_rd_SBV ();
	send_byte_ascii(value);
	send_cr_lf();
// Erase SBV
	printf("Erase SBV");	
	value = __api_erase_SBV ();
	send_cr_lf();
// Read SBV
	printf("SBV = ");	
	value = __api_rd_SBV ();
	send_byte_ascii(value);
	send_cr_lf();

/*---- Test SSB ------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

// Read SSB
	printf("SSB = ");	
	value = __api_rd_SSB ();
	send_byte_ascii(value);
	send_cr_lf();
// Write SSB
	printf("Write SSB = no_security");	
	value = __api_wr_SSB (NO_SECURITY);
	send_cr_lf();
// Read SSB
	printf("SSB = ");	
	value = __api_rd_SSB ();
	send_byte_ascii(value);
	send_cr_lf();
// Write SSB
	printf("Write SSB = wr_security");	
	value = __api_wr_SSB (WR_SECURITY);
	send_cr_lf();
// Read SSB
	printf("SSB = ");	
	value = __api_rd_SSB ();
	send_byte_ascii(value);
	send_cr_lf();
// Write SSB
	printf("Write SSB = rd_wr_security");	
	value = __api_wr_SSB (RD_WR_SECURITY);
	send_cr_lf();
// Read SSB
	printf("SSB = ");	
	value = __api_rd_SSB ();
	send_byte_ascii(value);
	send_cr_lf();
// Write SSB
	printf("Write SSB = no_security");	
	value = __api_wr_SSB (NO_SECURITY);
	send_cr_lf();
// Read SSB
	printf("SSB = ");	
	value = __api_rd_SSB ();
	send_byte_ascii(value);
	send_cr_lf();

/*---- Test EB ------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

// Read EB
	printf("EB = ");	
	value = __api_rd_EB ();
	send_byte_ascii(value);
	send_cr_lf();
// Write EB
	printf("Write EB = 5A");	
	value = __api_wr_EB (0x5A);
	send_cr_lf();
// Read EB
	printf("EB = ");	
	value = __api_rd_EB ();
	send_byte_ascii(value);
	send_cr_lf();
// Write EB
	printf("Write EB = FF");	
	value = __api_wr_EB (0xFF);
	send_cr_lf();
// Read EB
	printf("EB = ");	
	value = __api_rd_EB ();
	send_byte_ascii(value);
	send_cr_lf();

/*---- Test special read  --------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// Read manufacturer
	printf("manufacturer = ");	
	value = __api_rd_manufacturer();
	send_byte_ascii(value);
	send_cr_lf();
// Read device id1
	printf("device id1 = ");	
	value = __api_rd_device_id1();
	send_byte_ascii(value);
	send_cr_lf();
// Read device id2
	printf("device id2 = ");	
	value = __api_rd_device_id2();
	send_byte_ascii(value);
	send_cr_lf();
// Read device id3
	printf("device id3 = ");	
	value = __api_rd_device_id3();
	send_byte_ascii(value);
	send_cr_lf();
// Read device boot version
	printf(" boot version = ");	
	value = __api_rd_bootloader_version ();
	send_byte_ascii(value);
	send_cr_lf();

/*---- Test Fuse  ----------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// Read fuse bits
	printf("HSB = ");	
	value = __api_rd_HSB();
	send_byte_ascii(value);
	send_cr_lf();
// Write fuse bit X2
	printf("set bit X2 ");	
	value = __api_set_X2();
	send_cr_lf();
// Read fuse bits
	printf("HSB = ");	
	value = __api_rd_HSB();
	send_byte_ascii(value);
	send_cr_lf();
// Clear fuse bit X2
	printf("clear bit X2 ");	
	value = __api_clr_X2();
	send_cr_lf();
// Read fuse bits
	printf("HSB = ");	
	value = __api_rd_HSB();
	send_byte_ascii(value);
	send_cr_lf();
// Write fuse bit BLJB
	printf("set bit BLJB ");	
	value = __api_set_BLJB();
	send_cr_lf();
// Read fuse bits
	printf("HSB = ");	
	value = __api_rd_HSB();
	send_byte_ascii(value);
	send_cr_lf();
// Clear fuse bit BLJB
	printf("clear bit BLJB ");	
	value = __api_clr_BLJB();
	send_cr_lf();
// Read fuse bits
	printf("HSB = ");	
	value = __api_rd_HSB();
	send_byte_ascii(value);
	send_cr_lf();
// Write fuse bit BLJB
	printf("set bit BLJB ");	
	value = __api_set_BLJB();
	send_cr_lf();
// Read fuse bits
	printf("HSB = ");	
	value = __api_rd_HSB();
	send_byte_ascii(value);
	send_cr_lf();
// Write fuse bit X2
	printf("set bit X2 ");	
	value = __api_set_X2();
	send_cr_lf();
// Read fuse bits
	printf("HSB = ");	
	value = __api_rd_HSB();
	send_byte_ascii(value);
	send_cr_lf();

/*---- Test CAN config  ----------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// Read CANBTC1
	printf("BTC_1 = ");	
	value = __api_rd_BTC_1 ();
	send_byte_ascii(value);
	send_cr_lf();
// Write CANBTC_1
	printf("Write BTC_1 = 00");	
	value = __api_wr_BTC_1 (0x00);
	send_cr_lf();
// Read CANBTC_1
	printf("BTC_1 = ");	
	value = __api_rd_BTC_1 ();
	send_byte_ascii(value);
	send_cr_lf();

// Read CANBTC2
	printf("BTC_2 = ");	
	value = __api_rd_BTC_2 ();
	send_byte_ascii(value);
	send_cr_lf();
// Write CANBTC_2
	printf("Write BTC_2 = 0x04");	
	value = __api_wr_BTC_2 (0x04);
	send_cr_lf();
// Read CANBTC_2
	printf("BTC_2 = ");	
	value = __api_rd_BTC_2 ();
	send_byte_ascii(value);
	send_cr_lf();

// Read CANBTC3
	printf("BTC_3 = ");	
	value = __api_rd_BTC_3 ();
	send_byte_ascii(value);
	send_cr_lf();
// Write CANBTC_3
	printf("Write BTC_3 = 0x36");	
	value = __api_wr_BTC_3 (0x36);
	send_cr_lf();
// Read CANBTC_3
	printf("BTC_3 = ");	
	value = __api_rd_BTC_3 ();
	send_byte_ascii(value);
	send_cr_lf();

// Read NNB
	printf("NNB = ");	
	value = __api_rd_NNB ();
	send_byte_ascii(value);
	send_cr_lf();
// Write NNB
	printf("Write NNB = 0x00");	
	value = __api_wr_NNB (0x00);
	send_cr_lf();
// Read NNB
	printf("NNB = ");	
	value = __api_rd_NNB ();
	send_byte_ascii(value);
	send_cr_lf();

// Read CRIS
	printf("CRIS = ");	
	value = __api_rd_CRIS ();
	send_byte_ascii(value);
	send_cr_lf();
// Write CRIS
	printf("Write CRIS = 0x00");	
	value = __api_wr_CRIS (0x00);
	send_cr_lf();
// Read CRIS
	printf("CRIS = ");	
	value = __api_rd_CRIS ();
	send_byte_ascii(value);
	send_cr_lf();


/*---- Test FLASH  ---------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

// Read data address 0x7F00
	printf("read data at 0x7F00 : ");	
	value = __api_rd_code_byte (0x7F00);
	send_byte_ascii(value);
	send_cr_lf();
// Write data at address 0x7F00 = 0xAA
	printf("Write Data at add 0x7F00 the value 0xAA \n");	
	__api_wr_code_byte(0x7F00, 0xAA);

// Read data address 0x7F00
	printf("read data at 0x7F00 : ");	
	value = __api_rd_code_byte(0x7F00);
	send_byte_ascii(value);
	send_cr_lf();

	for (cpt = 0; cpt< 0x10; cpt++)
	{
		tab[cpt] = 0x55;
	} 

// Write data at address 0x1000 = 0x55
	printf("Write Data page at 0x1000 = 0x55 \n");	

	__api_wr_code_page(0x1000, tab ,0x10);

// Read data address 0x1000
	printf("read data at 0x1000-0x1010 : \n");	
	for (cpt = 0x1000; cpt< 0x1010; cpt++)
	{
		value = __api_rd_code_byte(cpt);
		send_byte_ascii(value);
	}
	send_cr_lf();

/*---- Test EEPROM ---------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

// Read EEPROM
	printf("Read EEPROM from 0x00 to 0x10 \n");
	if (!__api_eeprom_busy())
	{
		for (cpt = 0; cpt< 0x10; cpt++)
		{
      value = __api_rd_eeprom_byte(cpt);
			send_byte_ascii(value);
			printf(" ");
		}
	}
	else
	{
		printf("Error busy");
	}		
	send_cr_lf();

// Fill EEPROM
	printf("Fill EEPROM 0x55\n");
	for (cpt = 0; cpt< 0x10; cpt++)
	{
    value = __api_wr_eeprom_byte(cpt,0x55);
		while(__api_eeprom_busy());
	}		

// Read EEPROM
	printf("Read EEPROM from 0x00 to 0x10 \n");
	if (!__api_eeprom_busy())
	{
		for (cpt = 0; cpt< 0x10; cpt++)
		{
      value = __api_rd_eeprom_byte(cpt);
			send_byte_ascii(value);
			printf(" ");
		}
	}
	else
	{
		printf("Error busy");
	}		
	send_cr_lf();

	while(1);

}























