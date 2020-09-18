# RTOS_TaskScheduling

Project specification and description:

In this project we are designing a task scheduler in real time. This scheduler has many properties
in creating the tasks and running them in a preemption way.
• First a random integer number is generated between the range of 2 and the maximum
number of tasks that can be generated.
• Then, the program generates tasks that are equal to that random generated number.
• The scheduler operates in two modes: a safe mode and a no guarantee mode.
• Each task created has a few properties:
o A time at which the task arrives to the scheduler (Ta)
o A time of how long is the period of the task (Tp)
o A time of how much time will the task need to finish its computation (Tc)
After the tasks have been created, the program calculates each task’s CPU utilization and makes
a schedulability check for each task according to that CPU utilization and also calculates each
task’s rate.
The program then sorts the tasks giving each one of them a priority that is set according to their
periods and rates. After the tasks are sorted, the program starts acting like a scheduler and swaps
between the tasks so every task runs according to its period, priority and arrival times.
While the tasks are running, a random integer number is generated from an interval of the
number of tasks created. This number defines the number of the task that will be deleted
randomly during the runtime. After this task is deleted the scheduler continues swapping
between the remaining tasks after re-sorting them according to their periods and priorities once
again.
