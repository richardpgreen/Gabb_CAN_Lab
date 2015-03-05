/******************************************************************************/
/* @FILE_NAME:    LCD_DRV.H                                                       */
/*----------------------------------------------------------------------------*/
/* @FILE_CREATED_BY   : Eric TINLOT                                           */
/* @FILE_CREATION_DATE: 05/10/99                                              */
/*----------------------------------------------------------------------------*/
/* @FILE_PURPOSE: This file contains all prototypes and macros exported.      */
/******************************************************************************/

#ifndef _LCD_DRV_H_
#define _LCD_DRV_H_



/* ___________________________________________________________________________*/
/**
** Comments:  LCD in 4 bit mode only		
** Interconnexion between LCD and Microcontroler
**
** E     --------  P3.2=0 & P3.4=0
** R/W   --------  P1.6    
** RS    --------  P1.7    
** D4    --------  P1.0    
** D5    --------  P1.1  
** D6    --------  P1.2 
** D7    --------  P1.3 
** ___________________________________________________________________________*/



#define LCD_E        0xEB    /* Lcd enable  */
#define LCD_DIS      0x14    /* Lcd Disable */

#define LCD_RS       0x80    /* Register selection :data input */
#define LCD_RD       0x40    /* Read/Write  Read=1 */
         
#define LCD_4BIT     0x00    /* command for 4 bit mode */
#define LCD_8BIT     0x01    /* command for 8 bit mode */
#define LCD_CLR      0x01    /* Clear entire display */
#define LCD_HOME     0x02    /* Cursor back to home position */
#define LCD_SET      0x04    /* Set cursor move direction and specifies shift or display */
#define LCD_DISPLAY  0x08    /* Control Display,cursor,blink - ON / OFF */
#define LCD_CURS     0x10    /* Move Cursor and shift display */
#define LCD_FCTSET8  0x02 
#define LCD_FCTSET   0x20    /* Set: 4 bits mode , nb of lines, nb of dot matrix */
#define LCD_CGRAM    0x40    /* Set CG RAM address */
#define LCD_DDRAM    0x80    /* Set DD RAM adresse */
#define LCD_2_LINE   0x08    /* set in 2 Line mode */
#define LCD_5_10DOTS 0x04    /* set in 5*10 dots   */
#define LCD_BF       0x08    /* busy flag */
#define LCD_DISP_ON  0x04    /* Display ON */
#define LCD_CURS_ON  0x02    /* Cursor ON */
#define LCD_BLINK_ON 0x01    /* Blink ON */
#define LCD_SHIFT    0x01    /* shift ON */
#define LCD_INC      0x02    /* inc ON */
#define LCD_DATA     0x0F    /* data mask on 4 bit  */
#define LCD_LINE_1   0x00    /* addr of 1st line  */
#define LCD_LINE_2   0x40    /* addr of 2nd line  */
#define LCD_DISP_OFF 0x00
#define LCD_CURS_OFF 0x00
#define LCD_CURS_SHT 0x08    /* display shift */
#define LCD_CURS_RIG 0x04    /* display shift right*/
#define LCD_CURS_LEF 0x00    /* display shift left*/


/* Define for state machine of lcd_init function */

#define INIT_TEMPO_16MS 0x01
#define RUN_TEMPO_16MS  0x02
#define MODE_8_BIT      0x03
#define INIT_TEMPO_5MS  0x04
#define RUN_TEMPO_5MS   0x05
#define CONFIG_LCD      0x06
#define MODE_4_BIT      0x07
#define LCD_DISPLAY_OFF 0x08
#define LCD_MODE        0x09
#define LCD_CURSOR      0x0A
#define LCD_DISPLAY_ON  0x0B
#define LCD_CLEAR       0x0C
#define LCD_READY       0x0D
#define LCD_WR			0x0E

/* Define for state machine of lcd_wr_line function */

#define DDRAM_INIT      0x01
#define WR_CHAR         0x02


/*_____ T Y P E D E F - D E C L A R A T I O N ________________________________*/

#define LCD_ENABLE		P3 = (P3 & LCD_E)
#define LCD_DISABLE		P3 = (P3 | LCD_DIS)

/*_____ P R O T O T Y P E S - D E C L A R A T I O N __________________________*/


Uchar get_lcd_wr(void);
void  set_lcd_line(Uchar,Uchar*);
  
#endif /* _LCD_DRV_H_ */

