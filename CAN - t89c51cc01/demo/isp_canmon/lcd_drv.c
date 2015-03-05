/*C*****************************************************************************
* FILE_NAME: LCD_DRV.C                                                             
*-------------------------------------------------------------------------------
* FILE_CREATED_BY: Eric TINLOT                                                         
* $Author: jberthy $
* $Revision: 1.1.1.1 $
* $Date: 2001/03/01 15:31:23 $
*-------------------------------------------------------------------------------
* FILE_PURPOSE:  DEMOBOARD LCD DRIVERS
* FILE_CONTENTS:                                                            
*******************************************************************************/

/* Includes     */

#include "config.h"
#include "lcd_drv.h"

/*  Defines     */
 
//#define TEMPO_15us (Uint32)(4 * FOSC) /12000 /* tempo duration of 15 us */
#define TEMPO_15us 3 


/* Declarations */
Uchar i;

/* Definitions  */

/* Prototypes   */

void lcd_tempo(void)
{
  for(i=0; i<TEMPO_15us; i++);
}

/**
** ----------------------------------------------------------------------------
** lcd_cmd_wr - write command to LCD
** ----------------------------------------------------------------------------
** Inputs: command
** Outputs: twice in 4 bit on LCD
** ----------------------------------------------------------------------------
** Comments: Use P3.2 and P3.4  to validate lcd  P1.6=R/W=0    P1.7=RS=0
** ----------------------------------------------------------------------------
*/
void lcd_cmd_wr(Uchar value)
{
  unsigned char a,b;

  a = (value >> 4) & 0x0F;              /* 4 highest bit of value + RS=RW=0 */
  b =        value & 0x0F;              /* 4 lowest  bit of value + RS=RW=0 */
        
  P1 = a;       		                                                 
  LCD_ENABLE;                  /* select  LCD with P3.2=0 and P3.4=0 */
  lcd_tempo();
  LCD_DISABLE;                /* Disable LCD with P3.2=1 and P3.4=1 */ 
  P1 = b;   		                    /* P1.7=0  --> Instruction data input */	
  LCD_ENABLE;                  /* select  LCD with P3.2=0 and P3.4=0 */
  P2_2 = 0;
  lcd_tempo();
  P2_2 = 1;

  LCD_DISABLE;                /* Disable LCD with P3.2=1 and P3.4=1 */ 
} 


/*
** ----------------------------------------------------------------------------
** lcd_cmd8_wr - write command to LCD in 8 bits (only 4 low bytes are send) 
** ----------------------------------------------------------------------------
** Inputs: command
** Outputs: none
** ----------------------------------------------------------------------------
** Comments: Use P3.2 and P3.4  to validate lcd  P1.6=R/W=0    P1.7=RS=0
** ----------------------------------------------------------------------------
*/
void lcd_cmd8_wr(Uchar value)
{
  P1= value & 0x3F;                         /* 4 low bit of value + RS=RW=0 */
  LCD_ENABLE;                  /* select  LCD with P3.2=0 and P3.4=0 */
  lcd_tempo();
  LCD_DISABLE;                /* Disable LCD with P3.2=1 and P3.4=1 */ 
} 



/*
** ----------------------------------------------------------------------------
** lcd_bf - look to see if lcd busy flag is OK
** ----------------------------------------------------------------------------
** Inputs: none
** Outputs: FALSE or TRUE
** ----------------------------------------------------------------------------
** Comments: Use P3.2 and P3.4  to validate lcd  P1.6=R/W=0    P1.7=RS=0
** ----------------------------------------------------------------------------
*/
Uchar lcd_bf(void)
{
  Uchar fct_return = FALSE;
  Uchar high,low;

  P1 = P1 & LCD_RD & LCD_DATA;     /* read busy flag command */
  LCD_ENABLE;                          /* enabled  LCD  */
  high  = P1 & LCD_BF;                 /* mask for Busy flag */ 
  LCD_DISABLE;                         /* Disable LCD  */ 
  lcd_tempo();
  LCD_ENABLE;
  low  = P1;                                    /* low 4 bit */
  LCD_DISABLE;
  if (high==0)
  { 
    fct_return = TRUE;
  }
  return(fct_return);  
}

/*****************************************************************************
* FUNCTION_NAME: lcd_data_wr                                                             
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: E.TINLOT                                                         
* FUNCTION_DATE: 06.10.1999                                                           
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: send a character to the current DDRAM ADRESS                                                          
* FUNCTION_INPUTS:  character                                                          
* FUNCTION_OUTPUTS: none                                                        
*****************************************************************************
* NOTE: 4 higest bit first then 4 lowest bit
*****************************************************************************/
void lcd_data_wr(Uchar charact)
{
    P1 = ((charact >> 4) & LCD_DATA) | LCD_RS;    /* 4 highest bit of charact */
    LCD_ENABLE;                                         /* Enabled LCD  */
    lcd_tempo();
    LCD_DISABLE;                                        /* Disable LCD  */ 
    P1 = (charact & LCD_DATA) | LCD_RS;            /* 4 lowest bit of charact */
    LCD_ENABLE;                          
    lcd_tempo();
    LCD_DISABLE;                
}


/*****************************************************************************
* FUNCTION_NAME: lcd_ddram_init                                                             
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: E.TINLOT                                                         
* FUNCTION_DATE: 06.10.1999                                                           
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: init ddram to adress                                                          
* FUNCTION_INPUTS:  adress to init                                                          
* FUNCTION_OUTPUTS: none                                                        
*****************************************************************************
* NOTE: 4 higest bit first then 4 lowest bit
*****************************************************************************/
void lcd_ddram_init(Uchar address)
{   
    P1 =  (address | LCD_DDRAM)>>4 ;              /* 4 highest bit of address */
    LCD_ENABLE;                                         /* Enabled LCD  */
    lcd_tempo();
    LCD_DISABLE;                                        /* Disable LCD  */ 
    P1 = address & 0x0F ;                          /* 4 lowest bit of address */
    LCD_ENABLE;                          
    lcd_tempo();
    LCD_DISABLE;                
}



