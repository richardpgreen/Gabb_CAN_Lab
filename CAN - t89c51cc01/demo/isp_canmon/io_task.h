/******************************************************************************/
/* @FILE_NAME:    io_task  .h                                                */
/*----------------------------------------------------------------------------*/
/* @FILE_CREATED_BY   : E. TINLOT                                             */
/* @FILE_CREATION_DATE: 05/10/99                                              */
/*----------------------------------------------------------------------------*/
/* @FILE_PURPOSE: This file contains all prototypes and macros exported.      */
/******************************************************************************/

#ifndef _IO_TASK_H_
#define _IO_TASK_H_

/*_____ I N C L U D E - F I L E S ____________________________________________*/



/*_____ C O N S T A N T S - D E F I N I T I O N  ___________________________*/


#define BARGRAPH_E     0xFB    /* bargraph enable with P3.2=0  P3.4=1 */
#define BARGRAPH_DIS   0x04    /* bargraph Disable with P3.2=1 P3.4=1 */
#define SWITCH_E       0xEF    /* switch enable with P3.2=1   P3.4=0  */
#define SWITCH_DIS     0x10    /* switch Disable with P3.2=1  P3.4=1  */



#define BARGRAPH_ENABLE		P3 = P3 & BARGRAPH_E
#define BARGRAPH_DISABLE	P3 = P3 | BARGRAPH_DIS
#define SWITCH_ENABLE	    P3 = P3 & SWITCH_E
#define SWITCH_DISABLE	    P3 = P3 | SWITCH_DIS


/*_____ T Y P E D E F - D E C L A R A T I O N ________________________________*/


/* delcaration for task state machine  */

#define IO_WRITE_BARGRAPH  0x01
#define IO_INT1_PB         0x02
#define IO_READ_SWITCHS    0x03




/*  define hardware temporisation */

#define TEMPO_IO_15us      0x03

/*_____ P R O T O T Y P E S - D E C L A R A T I O N __________________________*/

void  clr_io_sw_flag(void);
Uchar get_io_sw_flag(void);
Uchar get_io_sw_value(void);
void  set_io_bg_value(Uchar value);

#endif /* _IO_TASK_H_ */




