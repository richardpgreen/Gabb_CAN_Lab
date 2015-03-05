	LCD_DISABLE;                /* Disable LCD with P3.2=1 and P3.4=1 */	
	
	/* configure channel P1.4(AN4) for ADC */ 

	ADCF = 0xC0;

	/* init prescaler for adc clock *//* Fadc = Fperiph/(2*(32-PRS)), PRS -> ADCLK[4:0] */ 

	ADCLK = 0x06; /* Fosc = 16 MHz, Fadsc = 153.8khz */ 
	ADCON = 0x20; /* Enable the ADC */

	EA = 1; /* enable interrupts */
	EADC = 1; /* enable ADC interrupt */

	while(1)
		{
		ADCON &= ~0x07; /* Clear the channel field ADCON[2:0] */
		ADCON |= 0x04; /* Select channel 4 */
		ADCON &= ~0x40; /* standard mode */
		ADCON |= 0x08; /* Start conversion */

		while(!end_of_convertion); /* wait end of convertion */
		end_of_convertion=0; /* clear software flag */
		value_AN4=value_converted; /* save converted value */
		}
	
	
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

	
	
	

	/*** FUNCTION_PURPOSE:Adc interrupt, save ADDH into an unsigned char
* FUNCTION_INPUTS:void
* FUNCTION_OUTPUTS:void
*/
void it_Adc(void) interrupt 8
{ 
ADCON &= ~0x10; /* Clear the End of conversion flag */
value_converted = ADDH<<2; /* save 8 msb bits */
//value_converted |= (ADDL & 0x03); /* save 2 lsb bits */
end_of_convertion=1; /* set flag */
}