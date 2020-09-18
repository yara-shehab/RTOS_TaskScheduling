#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
	float ta;
	float	tp;
	float tc;
	float cpu;
	float rate;
	int priority;
	int number;

}task;

#define N 5
#define tst 1
#define latest_arrival_time 15
#define maximum_computation_time 8
#define maximum_period_multiplier 17

int n, counter, inc =0 ; 
xTaskHandle xTask_Handle1[N];
xTaskHandle xTaskMas_Handle;
portBASE_TYPE xStatus;
task t[N];
int arr[N];
int dele[N];
int delecount=0;
char name[6]= "Task_";
int del_tasks[N];
int inc2=0; 
char id = '0';
int tempp=0;
int boolean=0;
void taskFunction();
void Task();
void insertionSort();
void ArrivalSort();
void vPeriodicTask( task *pvParameters );
void vTaskMaster();

int main( void )
{
	int i ,r , count ; 
  srand(567);
	Task();
	insertionSort();
	count = n+1 ; 
	counter = n+1;
		
	//Creating the tasks
	for(i=0; i<n; i++)
	{	

		if( (t[i].tp == t[i-1].tp) && i!=0)
		{
			
				
			t[i].priority = count;
			//xTaskCreate(vPeriodicTask , name ,240 ,&(t[i]) ,count ,NULL);	
			printf("Count %d \n", count);
		}
		else
		{
			count -= 1;
			t[i].priority = count;
			//xTaskCreate(vPeriodicTask , name ,240 ,&t[i] ,count ,NULL);
			printf("Count %d \n", count);
		}
			
	}
	
		ArrivalSort();
	  printf("AFTER ARRIVAL SORT \n");
	  for(i=0;i<n;i++)
	{
	  printf("Arrival %f \n", t[i].ta);
		printf("Computation %f \n" , t[i].tc);
		printf("Period %f \n" , t[i].tp);
		printf("CPU %f \n" , t[i].cpu);
		printf("Rate %f \n" , t[i].rate);
	}
	  
		arr[0] = t[0].ta; 
		for (i=1; i<n; i++)
		{
		 arr[i] = t[i].ta - t[i-1].ta;	
		}
		for (i=1; i<n; i++)
		{
			id=id+1;
			name[5]=id;
		 xTask_Handle1[i]=name;
		}
		id=0;
		for(i=0;i<n;i++)
		{
			dele[i]=n+1;
		}
		for(i=0 ; i<n ; i++)
	 {
		del_tasks[i] = n+1;
	 }
		xTaskCreate(vTaskMaster ,"MasterTask" ,240 ,NULL ,n+1 ,&xTaskMas_Handle);
		vTaskStartScheduler();
	
	
	for(;;);
}

void Task()
{
	
	int mode = 0; 
	int i ,j;
	float schedulability=0;
	n = 2 + rand()%4 ; //Number of tasks
	printf("tasks %d \n" , n);
	
	for(i=0; i<n; i++)
	{
   	 t[i].ta = (float) (0 + rand()% (latest_arrival_time + 1)) ;
		 t[i].tc = (float)(1 + rand()% (maximum_computation_time + 1)) ;
		 mode = 0 + rand()%2;
		 if(mode == 1) //No Guarantee mode
		 {
			t[i].tp = (float)(3*t[i].tc + rand()%10*t[i].tc + 1);
		 }
		 else //Safe Mode
		 {
			 t[i].tp = (float)(3*t[i].tc + rand()% maximum_period_multiplier*t[i].tc + 1) ;
		 }
		 t[i].cpu = (t[i].tc/t[i].tp);
		 t[i].rate = (1/t[i].tp);
		 
		printf("i= %d \n", i); 
		printf("Arrival %f \n", t[i].ta);
		printf("Computation %f \n" , t[i].tc);
		printf("Mode %d \n" , mode);
		printf("Period %f \n" , t[i].tp);
		printf("CPU %f \n" , t[i].cpu);
		printf("Rate %f \n" , t[i].rate);
	}
	for(j=0; j<n; j++)
	{
		schedulability = schedulability + t[j].cpu; 
	}
	
	if(schedulability < 0.7)
  {
	 printf("schedulability check is ok \n");
		
	}
	
}


void insertionSort()  
{  
    int i, j, r; 
		float key;
		task temp;
	  int x = n*28 / sizeof(t[0]);
	
    for (i = 1; i < x; i++) 
    {  
        key = t[i].tp;  
				temp = t[i];
        j = i - 1;  
  
        while (j >= 0 && t[j].tp > key) 
        {  
            t[j + 1] = t[j];  
            j = j - 1;  
        }  
        t[j + 1] = temp;  
    }  	
			
}


 
void ArrivalSort()
{
		int i, j, r; 
		float key;
		task temp;
	  int x = n*28 / sizeof(t[0]);
	
    for (i = 1; i < x; i++) 
    {  
        key = t[i].ta;  
				temp = t[i];
        j = i - 1;  
  
        while (j >= 0 && t[j].ta > key) 
        {  
            t[j + 1] = t[j];  
            j = j - 1;  
        }  
        t[j + 1] = temp;  
    }  
		  
}

static void vPeriodicTask( task *pvParameters )
{
	portTickType xLastWakeTime;
	task pcTask;
	int i, temp, bol=0, j, check = 0;

	int rnd = 0 + rand()% n ;
	int boo = 0 + rand()% 20 ;
	pcTask = *pvParameters;
	xLastWakeTime = xTaskGetTickCount();

  
	
	for( ;; )
	{
		
		printf("ARRIVAL TIME %d \n", (int)pcTask.ta);
		printf("At time %d Task %d is runing \n", (int)xLastWakeTime, pcTask.number );
		
		//for (i=0; i< pcTask.tc*1000; i++);
		
		if(boo < 5 && boolean == 1)
		{
			
			
			//If the task was deleted before
			for (i=0 ; i<n ; i++)
			{
			  if(del_tasks[i] == rnd)
				{
					bol = 1;	
					break;
				}
			}
			if(bol == 0)
			{
				vTaskSuspendAll();
				printf("Task is about delete: %d \n", rnd+1);	
				vTaskDelete( xTask_Handle1[rnd] );
				insertionSort();
				counter -= 1;
				temp = counter;
				del_tasks[inc2] = rnd;
				inc2 += 1;	
					for(i=0; i<n; i++)
					{	
						for(j=0; j<n; j++)
						{
							if(t[i].number == del_tasks[j]+1)
							{
							 check = 1;
							}
						}
						//Setting priorities of other running tasks
						if( t[i].number != rnd+1  && check == 0)
							{
								
								if( (t[i].tp == t[i-1].tp) && i!=0 )
									{
										vTaskPrioritySet(xTask_Handle1[t[i].number-1] , counter);	
										t[i].priority = counter;
									}
									
								else
									{
										counter -= 1;
										vTaskPrioritySet(xTask_Handle1[t[i].number-1], counter);
										t[i].priority = counter;
									}
							}
							check = 0;
					}
					counter = temp;
					ArrivalSort();
					xTaskResumeAll();
		}
		 boo = 0;	
	}
		
		vTaskDelayUntil( &xLastWakeTime, ( (int)pcTask.tp / portTICK_RATE_MS ) );
		
   }
}



static void vTaskMaster(void *pvParameters)
{
		portTickType xLastWakeTime;
		xLastWakeTime = xTaskGetTickCount();
		for(;;)
		{
			vTaskDelayUntil( &xLastWakeTime, ( arr[inc]/ portTICK_RATE_MS ) );
			t[inc].number = inc+1;	
			id=id+1;
			name[5]=id;
			xTaskCreate(vPeriodicTask, name, 120, &t[inc], t[inc].priority,& xTask_Handle1[inc]);
			
			inc += 1;
			if (inc == n )
			{
				printf("MASTER IS ABOUT TO DELETE \n");
				boolean=1;
				//tempp=1;
				vTaskDelete(xTaskMas_Handle); 	
			}
			 
		}

}