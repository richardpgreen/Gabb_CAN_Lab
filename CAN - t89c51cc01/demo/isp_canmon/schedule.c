/*C*****************************************************************************
* FILE_NAME         : scheduler.c                                             
*----------------------------------------------------------------------------
* FILE_CREATED_BY   : BERTHY JS                                             
* FILE_CREATION_DATE: 4/05/00                                              
*----------------------------------------------------------------------------
* FILE_PURPOSE:    
*
******************************************************************************/
/*_____ I N C L U D E - F I L E S ____________________________________________*/
#include "config.h"
#include "schedule.h"
#include "schedule_conf.h"

/*_____ P R I V A T E - F U N C T I O N S - D E C L A R A T I O N ____________*/
void call_next_task(void);


/*_____ L O C A L S __________________________________________________________*/

Uchar task_in_progress; 


/*_____ P U B L I C - F U N C T I O N S ______________________________________*/


/*F**************************************************************************
* FUNCTION_NAME: schedule                                             
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  :                                                  
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE:                          
* FUNCTION_INPUTS : 
* FUNCTION_OUTPUTS:                                                    
*----------------------------------------------------------------------------
* GLOBAL VARIABLES USED :
******************************************************************************
* NOTE:                                                                      
******************************************************************************/
void schedule(void)
{
  switch(task_in_progress)
  {
    case SCHED_TASK_1:
	{
	  TASK_1;
	  call_next_task();
	  break;
	}
    case SCHED_TASK_2:
	{
	  TASK_2;
	  call_next_task();
	  break;
	}
    case SCHED_TASK_3:
	{
	  TASK_3;
	  call_next_task();
	  break;
	}
    case SCHED_TASK_4:
	{
	  TASK_4;
	  call_next_task();
	  break;
	}
    case SCHED_TASK_5:
	{
	  TASK_5;
	  call_next_task();
	  break;
	}
    case SCHED_TASK_6:
	{
	  TASK_6;
	  call_next_task();
	  break;
	}
    case SCHED_TASK_7:
	{
	  TASK_7;
	  call_next_task();
	  break;
	}
    case SCHED_TASK_8:
	{
	  TASK_8;
	  call_next_task();
	  break;
	}
    case SCHED_TASK_9:
	{
	  TASK_9;
	  call_next_task();
	  break;
	}
    case SCHED_TASK_10:
	{
	  TASK_10;
	  call_next_task();
	  break;
	}
    default:
	{
	  break;
	}
  }
}

/*F**************************************************************************
* FUNCTION_NAME: schedule_init                                             
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 4/05/00                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE:                          
* FUNCTION_INPUTS : void
* FUNCTION_OUTPUTS: void                                                                                                                 
******************************************************************************/
void schedule_init(void)
{
  task_in_progress = SCHED_TASK_1;
  INIT_TASK_1;  
  INIT_TASK_2;  
  INIT_TASK_3;  
  INIT_TASK_4;  
  INIT_TASK_5;  
  INIT_TASK_6;  
  INIT_TASK_7;  
  INIT_TASK_8;  
  INIT_TASK_9;  
  INIT_TASK_10;  
}

/*F**************************************************************************
* FUNCTION_NAME: activate_new_schedul                                             
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 4/05/00                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE:                          
* FUNCTION_INPUTS : void
* FUNCTION_OUTPUTS: void                                                                                                                 
******************************************************************************/
void activate_new_schedul(void)
{
  task_in_progress = SCHED_TASK_1;
}


/*_____ P R I V A T E - F U N C T I O N S ____________________________________*/


/*F**************************************************************************
* FUNCTION_NAME: call_next_task                                             
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 4/05/00                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE:                          
* FUNCTION_INPUTS : void
* FUNCTION_OUTPUTS: void                                                                                                                 
******************************************************************************/
void call_next_task(void)
{
  EA = 0;
  task_in_progress++;
  EA = 1;
}

/*F**************************************************************************
* FUNCTION_NAME: default_schedul_fct                                             
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 4/05/00                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE:                          
* FUNCTION_INPUTS : void
* FUNCTION_OUTPUTS: void                                                                                                                 
******************************************************************************/
void default_schedule_fct(void)
{
 
}


