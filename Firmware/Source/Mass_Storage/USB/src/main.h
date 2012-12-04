#ifndef _MAIN_H_
 #define _MAIN_H_
 
 bool main_msc_enable(void);
 
 void main_msc_disable(void);
 
 void main_vbus_action(bool b_high);
 
 void main_sof_action(void);
 
 void main_suspend_action(void);
 
 void main_resume_action(void);
 
 void memories_initialization(long pba_hz);
 
 void main_remotewakeup_enable(void);
 
 void main_remotewakeup_disable(void);
 
 #endif // _MAIN_H_