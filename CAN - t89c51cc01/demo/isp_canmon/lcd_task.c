/*C*****************************************************************************
* FILE_NAME: lcd_task.c                                                            
*-------------------------------------------------------------------------------
* FILE_CREATED_BY: Eric TINLOT                                                         
* $Author: jberthy $
* $Revision: 1.1.1.1 $
* $Date: 2001/03/01 15:31:23 $
*-------------------------------------------------------------------------------
* FILE_PURPOSE:  DEMOBOARD LCD TASK
* FILE_CONTENTS:                                                            
*******************************************************************************/

/* Includes     */

#include "config.h"
#include "lcd_drv.h" 
#include "schedule.h"

/*  Defines     */


#define  LCD_TIMER_16MS 16/BASE_TIME_SCHEDUL  
#define  LCD_TIMER_6MS   6/BASE_TIME_SCHEDUL  

/* Declarations */

#ifdef MESURE_TASK_LCD
Uint16	valeur_debut, valeur_fin;
Uint16  valeur_max = 0;
#endif 

Uchar xdata state_lcd;
Uchar xdata lcd_buf_line[16];
Uchar xdata lcd_id_line;         

Uchar cpt_lcd;

Uchar lcd_wr;
Uchar state_return,state_lcd_wr;

/* Definitions  */
extern Uchar line[2][17];


/* Prototypes   */


void  lcd_cmd_wr(Uchar);
void  lcd_cmd8_wr(Uchar);
Uchar lcd_bf(void);  
void  lcd_data_wr(Uchar);
void  lcd_ddram_init(Uchar);
void  lcd_wr_line(void);
void  clr_lcd_wr(void);

/*
** ----------------------------------------------------------------------------
** task_lcd_init - initialisation of the task
** ----------------------------------------------------------------------------
** Inputs: none
** Outputs: none
** ----------------------------------------------------------------------------
*/
void task_lcd_init(void)
{
  state_lcd    = INIT_TEMPO_16MS;
  state_return = FALSE;
  state_lcd_wr = DDRAM_INIT; 
} 



/*
** ----------------------------------------------------------------------------
** task_lcd - task lcd init and update lcd display if needed
** ----------------------------------------------------------------------------
** Inputs: none 
** Outputs: none
** ----------------------------------------------------------------------------
** Comments: 
** ----------------------------------------------------------------------------
*/

void task_lcd(void)
{
static Uchar nb_8bit_mode;

#ifdef MESURE_TASK_LCD
  valeur_debut = (TH2 << 8) + TL2;
#endif
 
  switch(state_lcd)
  {

    case INIT_TEMPO_16MS: 
    { 
	  state_return = FALSE;
      cpt_lcd      = 0;
      state_lcd    = RUN_TEMPO_16MS;
      set_lcd_line(1," ATMEL WIRELESS ");
	  break;
    }
   
    case RUN_TEMPO_16MS:     
    {
	  cpt_lcd++;
      if( cpt_lcd > LCD_TIMER_16MS )     /*  waiting after lcd power supply = 4.5V for 16ms */    
      {
        state_lcd    = MODE_8_BIT; 
        nb_8bit_mode = 0;
      }
      break;
    }  

    case MODE_8_BIT:
    { 
      lcd_cmd8_wr(LCD_FCTSET8 | LCD_8BIT);                     /* in mode 8 bits */
      nb_8bit_mode++;
	  state_lcd = INIT_TEMPO_5MS; 
      
      if( nb_8bit_mode>=3 )      /* send 3 times same command to lcd */          
      {
        state_lcd = CONFIG_LCD; 
      }
      break;
    }
    
    case INIT_TEMPO_5MS: 
    { 
      cpt_lcd = 0;
      state_lcd = RUN_TEMPO_5MS;
      break;
    }

    case RUN_TEMPO_5MS:     
    {
	  cpt_lcd++;
      if( cpt_lcd > (LCD_TIMER_6MS) )      /* waiting after lcd Reset for 5 ms */          
      {
        state_lcd = MODE_8_BIT; 
      }
      break;
    }  

    case CONFIG_LCD: 
    { 
	  if(lcd_bf())
      {
        lcd_cmd8_wr(LCD_FCTSET8 | LCD_4BIT);                     /* in mode 8 bits */ 
    	state_lcd = MODE_4_BIT;
      }        
      break;
    }

    case MODE_4_BIT: 
    { 
	  if(lcd_bf())
      {
        lcd_cmd_wr(LCD_FCTSET  | LCD_4BIT | LCD_2_LINE | LCD_5_10DOTS);   
        /* 4 bit twice & 2lines & 5*10 dots */ 
	    state_lcd = LCD_DISPLAY_OFF;
      }        
      break;
    }

 
    case LCD_DISPLAY_OFF: 
    { 
	  if(lcd_bf())
      {
        lcd_cmd_wr(LCD_DISPLAY | LCD_DISP_OFF | LCD_CURS_OFF );   /* cursor off display on */
	    state_lcd = LCD_MODE;
      }        
      break;
    }
 
	
	case LCD_MODE: 
    { 
	  if(lcd_bf())
      {
        lcd_cmd_wr(LCD_SET | LCD_INC );  /* increment mode */
	    state_lcd = LCD_CURSOR;
      }        
      break;
    }
 	
	case LCD_CURSOR: 
    { 
	  if(lcd_bf())
      {
      	lcd_cmd_wr( LCD_CURS );    /* cursor shift to the left */
	    state_lcd = LCD_DISPLAY_ON;
      }        
      break;
    }

	case LCD_DISPLAY_ON: 
    { 
	  if(lcd_bf())
      {
        lcd_cmd_wr(LCD_DISPLAY | LCD_DISP_ON | LCD_CURS_OFF ); /* display & cursor off */
        state_lcd = LCD_CLEAR;
      }        
      break;
    }

	case LCD_CLEAR: 
    { 
	  if(lcd_bf())
      {
        lcd_cmd_wr(LCD_CLR);        /* CLEAR ALL DIPLAY with space characters */
        state_lcd = LCD_READY;
      }        
      break;
    }

	case LCD_READY: 
    { 
	  if(lcd_bf())
      {
       state_lcd = LCD_WR;
      }        
      break;
    }

    case LCD_WR:
	{
      if(get_lcd_wr())
      {
        lcd_wr_line();  
	  }        
      break;	
    }
    
    default:
	{
      state_lcd = INIT_TEMPO_16MS;
      break;	
    }
  }

#ifdef MESURE_TASK_LCD
  valeur_fin = (TH2 << 8) + TL2;
  if ((valeur_fin - valeur_debut) > valeur_max)
  {
    valeur_max = (valeur_fin - valeur_debut);
  }
#endif
}



          

/*
****************************************************************************
* FUNCTION_NAME: lcd_wr_line                                                             
*---------------------------------------------------------------------------
* FUNCTION_AUTHOR: E.TINLOT                                                         
* FUNCTION_DATE: 06.10.1999                                                           
*---------------------------------------------------------------------------
* FUNCTION_PURPOSE: send a string of 16 characters (one line) on LCD                                                          
* FUNCTION_INPUTS:                                                             
* FUNCTION_OUTPUTS: False or True                                                        
****************************************************************************
*/
void lcd_wr_line(void)
{
static Uchar nb_char;     

  switch (state_lcd_wr)
  {  
    case DDRAM_INIT:    
    {  
      if (lcd_id_line==1)                  /* first line */
      {
        lcd_ddram_init(LCD_LINE_1); 
      }
      else   
      {  
        lcd_ddram_init(LCD_LINE_2);     /* second line */
      }
      nb_char = 0;
      state_lcd_wr = WR_CHAR;
      break;
    }

	case WR_CHAR: 
    { 
	  if(lcd_bf())
      {
        lcd_data_wr(lcd_buf_line[nb_char]);  
        nb_char++;
        if ( nb_char>15 )
        {      
          clr_lcd_wr();
	      state_lcd_wr = DDRAM_INIT;  
        }
      }
      break;
    }
	
	default:
	{
	  state_lcd_wr = DDRAM_INIT; 
	  break;
	}
  }
}

 

/*
** ----------------------------------------------------------------------------
** clr_lcd_wr / nothing to print on LCD
** ----------------------------------------------------------------------------
** Inputs: none
** Outputs: none 
** ----------------------------------------------------------------------------
*/
void clr_lcd_wr(void)
{
  lcd_wr = FALSE; 
} 
  

  
/*
** ----------------------------------------------------------------------------
** get_lcd_wr  /  allow to know if there is something to write on LCD
** ----------------------------------------------------------------------------
** Inputs: none
** Outputs:False or TRUE 
** ----------------------------------------------------------------------------
*/
Uchar get_lcd_wr(void)
{
  return(lcd_wr);
}

/*
** ----------------------------------------------------------------------------
** set_lcd_line  /  write line into buffer , set flag for print 
** ----------------------------------------------------------------------------
** Inputs: line one or two, and string to print
** Outputs:none 
** ----------------------------------------------------------------------------
*/
void set_lcd_line(Uchar line,Uchar *string)
{
  int h;

  for (h=0 ; h<16 ; h++)
  {
    lcd_buf_line[h] = string[h];
  }
  lcd_id_line  = line;   
  lcd_wr = TRUE; 
}  
