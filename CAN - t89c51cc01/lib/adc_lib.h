/*H***************************************************************************
* FILE_NAME:    adc_lib.
*----------------------------------------------------------------------------
* FILE_CREATED_BY   : J.S. BERTHY                                           
* FILE_CREATION_DATE: 9/05/00                                              
*----------------------------------------------------------------------------
* FILE_PURPOSE: This file contains all prototypes and macros exported.      
******************************************************************************/

#ifndef _ADC_LIB_H_
#define _ADC_LIB_H_

/*_____ I N C L U D E - F I L E S ____________________________________________*/

/*_____ C O N S T A N T E S - D E F I N I T I O N  ___________________________*/

#define ADC_CH_0 0
#define ADC_CH_1 1
#define ADC_CH_2 2
#define ADC_CH_3 3
#define ADC_CH_4 4
#define ADC_CH_5 5
#define ADC_CH_6 6
#define ADC_CH_7 7

#define ADC_MAX_VALUE 0x3FF
#define ADC_IT_ENABLE EADC = 1
#define ADC_IT_DISABLE EADC = 0
/*_____ M A C R O S - DE C L A R A T I O N ___________________________________*/


/*_____ T Y P E D E F - D E C L A R A T I O N ________________________________*/

/*_____ P R O T O T Y P E S - D E C L A R A T I O N __________________________*/

Uint16 adc_start_conv(Uchar channel);
void adc_start_convidle(Uchar channel);

#endif /* _ADC_LIB_H_ */


































