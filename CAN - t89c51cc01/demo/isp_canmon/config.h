/*H**************************************************************************
* NAME: config.h 
*----------------------------------------------------------------------------
* PURPOSE: 
*****************************************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

/*------ Include of file register */
#include "../../lib/compiler.h"
#include "../../lib/t89c51cc01.h"
#include "../../lib/can_lib.h"
#include "../../isp/can/flash_api/flash_api.h"

/*------ FOSC declaration in kHz */
#define FOSC 12000

/*------ SCHED_TIME_BASE declaration (if need) in ms */
#define BASE_TIME_SCHEDUL 2

/*------ Declaration for can it user function. */
#define USER_CAN_FCT_IT_RXOK
extern void can_fct_it_rxok (void);

#define USER_CAN_FCT_IT_TXOK
extern void can_fct_it_txok (void);

#undef USER_CAN_FCT_IT_ERROR    
#undef USER_CAN_FCT_IT_TIMOVF
#undef USER_CAN_FCT_IT_GEN

/*------- Prototype for interrupt function */
extern void fct_can_it     (void);
extern void fct_tim_ovf_it (void);
extern void fct_timer2_it  (void);


#endif /* _CONFIG_H_ */
