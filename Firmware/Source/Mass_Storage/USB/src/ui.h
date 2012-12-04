 #ifndef _UI_H_
 #define _UI_H_
 
 void ui_init(void);
 
 void ui_powerdown(void);
 
 void ui_wakeup(void);
 
 void ui_start_read(void);
 void ui_stop_read(void);
 void ui_start_write(void);
 void ui_stop_write(void);
 
 void ui_process(uint16_t framenumber);
 
 #endif // _UI_H_