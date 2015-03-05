/*C*****************************************************************************
* FILE_NAME: TASK_IO.C                                                             
*-------------------------------------------------------------------------------
* FILE_CREATED_BY: Eric TINLOT                                                         
* $Author: jberthy $
* $Revision: 1.1.1.1 $
* $Date: 2001/04/30 14:53:59 $
*-------------------------------------------------------------------------------
* FILE_PURPOSE:  DEMOBOARD IO TASK
* FILE_CONTENTS:                                                            
*******************************************************************************/

/* Includes     */

#include "config.h"
#include "io_task.h" 
#include "schedule.h"



Uchar state_io;
Uchar io_bg_value;
Uchar io_sw_value;
Uchar io_sw_flag;

/* Definitions  */



/* Prototypes   */

void io_tempo(void);
void set_io_sw_flag(void);

/*
** ----------------------------------------------------------------------------
** task_io_init  
** ----------------------------------------------------------------------------
** Inputs: none
** Outputs: none 
** ----------------------------------------------------------------------------
*/

void task_io_init(void)
{
  state_io = IO_WRITE_BARGRAPH;
  io_bg_value = 0;
  clr_io_sw_flag();
} 


/*
** ----------------------------------------------------------------------------
** task_io 
** ----------------------------------------------------------------------------
** Inputs: none 
** Outputs: none
** ----------------------------------------------------------------------------
** Comments: 
** ----------------------------------------------------------------------------
*/

void task_io(void)
{
  switch(state_io)
  {

    case IO_WRITE_BARGRAPH:
    { 
	  	P1 = io_bg_value;  
      BARGRAPH_ENABLE;	 
      io_tempo();
      BARGRAPH_DISABLE;
      break;
    }
   
    default:
		{
      state_io = IO_WRITE_BARGRAPH;
      break;	
    }
  }

}



void io_tempo(void)
{
  Uchar i;
  for(i=0; i<TEMPO_IO_15us; i++);
}

          

 


/*
** ----------------------------------------------------------------------------
** clr_io_sw_flag / set that there is not to read switchs
** ----------------------------------------------------------------------------
** Inputs: none
** Outputs: none 
** ----------------------------------------------------------------------------
*/
void clr_io_sw_flag(void)
{
  io_sw_flag = FALSE; 
} 
  


/*
** ----------------------------------------------------------------------------
** set_io_sw_flag  / set flag for switch to read
** ----------------------------------------------------------------------------
** Inputs: none
** Outputs: None
** ----------------------------------------------------------------------------
*/
void set_io_sw_flag(void)
{
  io_sw_flag = TRUE; 
} 







/*
** ----------------------------------------------------------------------------
** set_io_bg_value
** ----------------------------------------------------------------------------
** Inputs: data to send to bargraph
** Outputs: None
** ----------------------------------------------------------------------------
*/
void set_io_bg_value(Uchar value)
{
  io_bg_value = value;  
}

 

