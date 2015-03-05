/*H****************************************************************************
* FILE_NAME:    schedule_conf.h
*----------------------------------------------------------------------------
* FILE_CREATED_BY   : J.S. BERTHY                                           
* FILE_CREATION_DATE: 28/09/99                                              
*----------------------------------------------------------------------------
* FILE_PURPOSE:      
******************************************************************************/

#ifndef _SCHEDULE_CONF_H_
#define _SCHEDULE_CONF_H_


extern void task_lcd(void);
extern void task_lcd_init(void);
extern void can_task(void);
extern void can_task_init(void);
extern void task_io_init(void);
extern void task_io(void);

extern void default_schedule_fct(void);


#define TASK_1 	    task_lcd();
#define INIT_TASK_1 task_lcd_init();

#define TASK_2      can_task();
#define INIT_TASK_2 can_task_init();

#define TASK_3 	    task_io();
#define INIT_TASK_3 task_io_init();

#define TASK_4 	    default_schedule_fct();
#define INIT_TASK_4 default_schedule_fct();

#define TASK_5 	    default_schedule_fct();
#define INIT_TASK_5 default_schedule_fct();

#define TASK_6 	    default_schedule_fct();
#define INIT_TASK_6 default_schedule_fct();

#define TASK_7 	    default_schedule_fct();
#define INIT_TASK_7 default_schedule_fct();

#define TASK_8 	    default_schedule_fct();
#define INIT_TASK_8 default_schedule_fct();

#define TASK_9 	    default_schedule_fct();
#define INIT_TASK_9 default_schedule_fct();

#define TASK_10      default_schedule_fct();
#define INIT_TASK_10 default_schedule_fct();

#endif /* _SCHEDULE_CONF_H_ */
 
