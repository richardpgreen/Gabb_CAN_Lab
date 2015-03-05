/*C*****************************************************************************
* FILE_NAME         : can_task.c                                             
*----------------------------------------------------------------------------
* FILE_CREATED_BY   : BERTHY JS                                             
* FILE_CREATION_DATE: 4/05/00                                              
*----------------------------------------------------------------------------
* FILE_PURPOSE:    
*
******************************************************************************/
/*_____ I N C L U D E - F I L E S ____________________________________________*/
#include "stdio.h"
#include "config.h"
#include "lcd_drv.h"
#include "io_task.h"

/*_____ P R I V A T E - F U N C T I O N S - D E C L A R A T I O N ____________*/

// Configuration for an oscillator of 12 MHZ
#define BRP_500k		0x00
#define SJW_500k    0x00
#define PRS_500k    0x02
#define PHS1_500k   0x03
#define PHS2_500k   0x03

#define TIM_10ms		2


/*_____ L O C A L S __________________________________________________________*/

can_data_t xdata data_200 = {0x53, 0x54, 0x41, 0x54, 0x49, 0x4F, 0x4E, 0x31};
can_data_t data_rx= {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
code can_msg_t can_200 = {STD_ID(0x001), CONF_NOIDE | CONF_DLC_8, data_200};

can_msg_t rx_data = {0x00, 0x00, data_rx};

Uchar task_state = 0x00;
Uchar debounce_bp = 0x00;

Uchar boot_cris;
Uchar boot_nnb;

/*_____ P U B L I C - F U N C T I O N S ______________________________________*/

Uchar dlc;     // DATA LENGTH FROM RX SIGNAL.
Uchar f_affichage =1;
Uchar f_start_bootloader;

Uchar f_barg;
Uchar barg_counter;
Uchar barg_io;

Uchar xdata line[2][17];   // DATA BUFFER FOR DISPLAY  - 2LINES. 17CHARS.

/*F**************************************************************************
* NAME: bin_to_ascii 
*----------------------------------------------------------------------------
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

/*_____ P R I V A T E - F U N C T I O N S ____________________________________*/


/*F**************************************************************************
* FUNCTION_NAME: can_task_init                                            
*-------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 4/05/00                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE:                          
* FUNCTION_INPUTS : void
* FUNCTION_OUTPUTS: void                                                                                                                 
******************************************************************************/
void can_task_init(void)
{
  f_start_bootloader = 0;

#ifndef DEBUG

	boot_cris  = __api_rd_CRIS();

	if (boot_cris == 0xFF)
	{
		boot_cris = 0x00;
	}
	boot_nnb   = __api_rd_NNB();

#endif

#ifdef DEBUG

	boot_cris  = 0x00;

	boot_nnb   = 0x02;

#endif
  CAN_CONTROLLER_RESET;     
  CAN_IT_DISABLE;
  CANTIM_IT_DISABLE;
  RazAllMailbox();
  CanSetBRP(BRP_500k);
  CanSetSJW(SJW_500k);
  CanSetPRS(PRS_500k);
  CanSetPHS1(PHS1_500k);
  CanSetPHS2(PHS2_500k);
  CAN_CONTROLLER_ENABLE;

  can_rx_filt.ext = 0x00;
  can_rx_msk.ext  = 0x00;
  conf_rx         = CONF_NOIDE|CONF_NOMSK_IDE|CONF_NOBUFFER;
  CAN_SET_CHANNEL(CHANNEL_0);
  CAN_CHANNEL_IT_ENABLE(CHANNEL_0);
  ConfChannel_Rx();


  CAN_IT_ENABLE;
  CAN_TX_IT_ENABLE;
  CAN_RX_IT_ENABLE
  task_state = 0x00;


//STRIP THE CODE BELOW TO YOUR OWN SCREEN LAYOUT 
  line[0][0] = 'A';
	line[0][1] = 'T';
 	line[0][2] = 'M';      
 	line[0][3] = 'E';
 	line[0][4] = 'L';      
 	line[0][5] = ' ';
  line[0][6] = 'W';      
  line[0][7] = 'i';
  line[0][8] = 'r';
	line[0][9] = 'e';
 	line[0][10] = 'l';      
 	line[0][11] = 'e';
 	line[0][12] = 's';      
 	line[0][13] = 's';      
 	line[0][14] = ' ';      
  line[0][15] = '&';
  line[1][0] = 'M';
	line[1][1] = 'i';
 	line[1][2] = 'c';      
 	line[1][3] = 'r';
 	line[1][4] = 'o';      
 	line[1][5] = 'C';
  line[1][6] = 'o';      
  line[1][7] = 'n';
  line[1][8] = 't';
	line[1][9] = 'r';
 	line[1][10] = 'o';      
 	line[1][11] = 'l';
 	line[1][12] = 'l';      
 	line[1][13] = 'e';      
 	line[1][14] = 'r';      
 	line[1][15] = 's';      

}
void display(void);
/*F**************************************************************************
* FUNCTION_NAME: can_task                                            
*-------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 4/05/00                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE:                          
* FUNCTION_INPUTS : void
* FUNCTION_OUTPUTS: void                                                                                                                 
******************************************************************************/
void can_task(void)
{
  if (f_start_bootloader)
  {
		TR2 = 0;
		ET2 = 0;
		__api_start_isp();
		while(1);
  }

	if (f_barg)
	{
		if(barg_counter++ == TIM_10ms)
    {
 			barg_counter = 0;
      barg_io >>= 1;
		  set_io_bg_value(barg_io);
		}
		if (barg_io == 0)
		{
			f_barg = 0;
		}
	}

  if (f_affichage == 1)
  {
    if(get_lcd_wr()==FALSE)
		{
	  	set_lcd_line(1, line[0]);
	  	f_affichage = 2;
		}
  }
  else if (f_affichage == 2)
  {
    if(get_lcd_wr()==FALSE)
		{
	  	set_lcd_line(2, line[1]);
	  	f_affichage = 0;
		}
  }

  switch (task_state)
  {
    case  0x00:
		{
      if (P3_3 == 0)
      { 
        debounce_bp++;
        if (debounce_bp == 50)
				{
		  		task_state = 1;
				}
      }
      break;
    }
    case  1:
		{
      CAN_SET_CHANNEL(CHANNEL_1);
      CAN_CHANNEL_IT_ENABLE(CHANNEL_1);
      can_tx_id     = can_200.id;
      conf_tx       = can_200.ctrl;
      pt_candata_tx = can_200.pt_donne;
      SendCanMsg();
      task_state = 2;
      break;
    }
    case  2:
	{
      debounce_bp = 0;
      break;
    }
  }
}

/****************************************************************************
* FUNCTION_NAME: can_fct_it_txok                                                
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  :                                                  
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE:                                   
* FUNCTION_INPUTS :                                                         
* FUNCTION_OUTPUTS:                                                         
******************************************************************************
* NOTE:                                                                      
******************************************************************************/
void can_fct_it_txok (void)
{
  channel_t channel;

  task_state  = 0;
  channel = CAN_GET_CHANNEL; 
  CAN_CHANNEL_IT_DISABLE(channel);  
}



void display(void)
{
	// DELETE LINE[0] AFTER TESTING? DISPLAY OWN SENSOR ELSEWHERE IN CODE (DIFF UPDATE TIME)
  line[0][0] = bin_to_ascii((can_tx_id.tab[0] & 0xF0)>>4);
	line[0][1] = bin_to_ascii(can_tx_id.tab[0] &0x0F);
 	line[0][2] = bin_to_ascii((can_tx_id.tab[1] & 0xF0)>>4);
 	line[0][3] = bin_to_ascii(can_tx_id.tab[1] &0x0F);      
  line[0][4] = ' ';
  line[0][5] = ' ';      
  line[0][6] = ' ';
  line[0][7] = ' ';      

  line[0][8] = ' ';
  line[0][9] = ' ';    
  line[0][10] = ' ';
  line[0][11] = ' ';      
  line[0][12] = ' '; 
  line[0][13] = ' ';       
  line[0][14] = bin_to_ascii((dlc & 0xF0)>>4); 
  line[0][15] = bin_to_ascii(dlc & 0x0F);       

// if statement needed to display each station  
		line[1][0] = data_rx[0];
  	line[1][1] = data_rx[1];
	  line[1][2] = data_rx[2];
	  line[1][3] = data_rx[3];
  	line[1][4] = data_rx[4];
  	line[1][5] = data_rx[5];
  	line[1][6] = data_rx[6];
  	line[1][7] = data_rx[7];
  	line[1][8] = data_rx[0];
  	line[1][9] = data_rx[1];
  	line[1][10] = data_rx[2];
  	line[1][11] = data_rx[3];
	  line[1][12] = data_rx[4];
	  line[1][13] = data_rx[5];
	  line[1][14] = data_rx[6];
	  line[1][15] = data_rx[7];
}

/****************************************************************************
* FUNCTION_NAME: can_fct_it_rxok                                                
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  :                                                  
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE:   TRANSMITTING CAN MESSAGE? OR LISTENING?                                
* FUNCTION_INPUTS :                                                         
* FUNCTION_OUTPUTS:                                                         
******************************************************************************
* NOTE:                                                                      
******************************************************************************/
void can_fct_it_rxok (void)
{
  Uchar i;

  dlc = CANCONCH & MSK_CTRL_DLC;  
  for (i=0; i<dlc; i++)
  {
    data_rx[i] = CANMSG;
  }
  can_tx_id.std = (CANIDT1 << 3) | (CANIDT2 >> 5);;

  CANSTCH  = 0x00;               

  if ((CANIDT1 == boot_cris)&&
      ((CANIDT2 & 0xE0) == 0x00     )  )
  {
	  if(boot_nnb == data_rx[0])
	  {
		  f_start_bootloader = 1;
	  }
  }
	f_barg  =1;
	set_io_bg_value(0x80);
	barg_io = 0x80;
	barg_counter = 0;

  display ();
  f_affichage = 1;
  ENABLE_CHANNEL_RX; /* Reception enabled.*/

}


