#include <T89C51CC01.h>

//unsigned int value_converted=0x0000; /* converted value */
//unsigned char value_AN4=0x0000; /* converted AN4 value */
//bit end_of_convertion=0; /* software flag */

int result,i,j;

void main(void)
	
{


	while(1)
   {
	 ///
		
		 /*Set Pins 3.2 and 3.4 for ADC*/
	  P3_2 = 1;
	  P3_4 = 1;
	ADCLK &= 0xFE; //adc clock
    ADCF = 0x10; //p1.4		
    ADCON = 0x24; //enable adc and use p1.4
    //ADCON &= ~0xF8; /* Clear the channel field ADCON[2:0] */
    //ADCON |= 0x04; /* Select channel 4 */
    ADCON |= 0x08; /* Start conversion */
    while((ADCON & 0x10)!= 0x10);         //Wait for conversion to end
    result = ADDH; //result stored here
	ADCON &= 0xEF; // clear the adeoc for next conversion
    //value_AN4 = (ADDH << 2);
		 
    ADCON = 0x00; //disable adc

		
		if(result > 128)
								P1 = 0x80;
			else
								P1 = 0x08;
			
			
		
	  P3_2 = 0;
	  // you need a delay loop to actually see the leds, otherwise it will quickly move to the adc again
	for(i=0;i<3000;i++)
    {
        for(j=0;j<100;j++)
        {
        }
    }		
	 }
	
		
	}
