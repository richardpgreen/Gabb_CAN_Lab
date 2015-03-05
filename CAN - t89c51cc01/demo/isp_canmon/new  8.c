void main(void)
{

{ 

//if(lcd_bf())
//      {
        lcd_cmd_wr(LCD_DISPLAY | LCD_DISP_ON | LCD_CURS_OFF ); /* display & cursor off */
        
//      } 

// if(lcd_bf())
//      {
        lcd_cmd_wr(LCD_CLR);        /* CLEAR ALL DIPLAY with space characters */
 //     }        

//if(lcd_bf())
//      {
		if(get_lcd_wr())
		{
        lcd_wr_line();  
		}   
//	}
	  
}	  
void lcd_wr_line(void)
{
      if (lcd_id_line==1)                  /* first line */
      {
        lcd_ddram_init(LCD_LINE_1); 
      }
      else   
      {  
        lcd_ddram_init(LCD_LINE_2);     /* second line */
      }
}