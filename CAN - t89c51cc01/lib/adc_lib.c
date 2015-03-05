/*C*****************************************************************************
* FILE_NAME         : adc_lib.c                                             
*----------------------------------------------------------------------------
* FILE_CREATED_BY   : BERTHY JS                                             
* FILE_CREATION_DATE: 27/09/99                                              
*----------------------------------------------------------------------------
* FILE_PURPOSE: provide low level functions for ADC   
*
******************************************************************************/

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "compiler.h"
#include "config.h"
#include "adc_lib.h"

/*_____ G L O B A L S ________________________________________________________*/


/*_____ P R I V A T E - F U N C T I O N S - D E C L A R A T I O N ____________*/


/*_____ L O C A L S __________________________________________________________*/

/*_____ P U B L I C - F U N C T I O N S ______________________________________*/


/*_____ P R I V A T E - F U N C T I O N S ____________________________________*/

/*F****************************************************************************
* FUNCTION_NAME: adc_start_conv                                                 
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 9/05/00                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE:      
* FUNCTION_INPUTS : Uchar channel                                                          
* FUNCTION_OUTPUTS: Uint16 converted value                                                        
******************************************************************************/
Uint16 adc_start_conv(Uchar channel)
{
  ADCON &= ~MSK_ADCON_SCH;
  ADCON |= channel;
  ADCON |= MSK_ADCON_ADSST;

  while((ADCON & MSK_ADCON_ADEOC)!= MSK_ADCON_ADEOC);

  ADCON &= ~MSK_ADCON_ADEOC;
  
  return (ADDH << 2)+(ADDL);

}

/*F****************************************************************************
* FUNCTION_NAME: adc_start_convidle                                                 
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 9/05/00                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: Start conversion in idle mode.
*  The adc interrupt must be enable.     
* FUNCTION_INPUTS : Uchar channel                                                          
* FUNCTION_OUTPUTS: Uint16 converted value                                                        
******************************************************************************/
void adc_start_convidle(Uchar channel)
{
  EA = 1;
  ADC_IT_ENABLE;
  ADCON &= ~MSK_ADCON_SCH;
  ADCON |= channel;
  ADCON |= (MSK_ADCON_ADSST | MSK_ADCON_PSIDLE);

}











































