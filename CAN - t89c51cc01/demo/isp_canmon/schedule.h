/*H****************************************************************************
* FILE_NAME:    schedule.h
*----------------------------------------------------------------------------
* FILE_CREATED_BY   : J.S. BERTHY                                           
* FILE_CREATION_DATE: 28/09/99                                              
*----------------------------------------------------------------------------
* FILE_PURPOSE:      
******************************************************************************/

#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

/*_____ I N C L U D E - F I L E S ____________________________________________*/

/*_____ C O N S T A N T E S - D E F I N I T I O N  ___________________________*/



#define SCHED_TASK_1	1
#define SCHED_TASK_2	2
#define SCHED_TASK_3	3	
#define SCHED_TASK_4	4
#define SCHED_TASK_5	5
#define SCHED_TASK_6	6
#define SCHED_TASK_7	7
#define SCHED_TASK_8	8
#define SCHED_TASK_9	9
#define SCHED_TASK_10	10


/*_____ M A C R O S - DE C L A R A T I O N ___________________________________*/

/*_____ T Y P E D E F - D E C L A R A T I O N ________________________________*/

/*_____ P R O T O T Y P E S - D E C L A R A T I O N __________________________*/

extern void schedule_init(void);
extern void schedule(void);
extern void activate_new_schedul(void);

#endif /* _SCHEDULE_H_ */
