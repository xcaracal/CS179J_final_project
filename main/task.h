#ifndef __TASK_H__
#define __TASK_H__

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

#endif //__TASK_H__
