#include "stm32f4xx.h"
#include "bsp.h"
#include "includes.h"

#define  TEST_TASK_STK_SIZE     512
#define  TEST_Idle_STK_SIZE     512
#define  OSTASK_TEST_PRIO       3
#define  OSTASK_Idle_PRIO       5

static void  Test_Task(void *p_arg);
static void  Test_Idle(void *p_arg);

// 任务控制块
static  OS_TCB   Test_Task_TCB;
static  OS_TCB   Test_Idle_TCB;

// 任务堆栈的大小为数组所占空间的大小 32位整型*256 = 1024
static  CPU_STK  Test_Task_STK[TEST_TASK_STK_SIZE];
static  CPU_STK  Test_Idle_STK[TEST_TASK_STK_SIZE];

void TaskCreateAppTask(void);

static void Test_Task(void *p_arg)
{
	OS_ERR  err;
	(void)p_arg;

    /*
        (a) HAL_Init();
        (b) SystemClock_Config();
        (c) SysTick_init();
        (d) Bsp_Led_Init();
    */
	Bsp_Init(); // Initialize the Board Support Package (BSP).

    // Bsp_Tick_init(); // Configure and Initialize the OS Tick Services (SysTick).
	TaskCreateAppTask();
	#if OS_CFG_STAT_TASK_EN > 0u
        OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
    #endif

    #ifdef CPU_CFG_INT_DIS_MEAS_EN
        CPU_IntDisMeasMaxCurReset();
    #endif

	while(1) 
	{
        Led_On();
        //精确延时 时， 分， 秒， 毫秒
        OSTimeDlyHMSM(0, 0,1, 0,OS_OPT_TIME_HMSM_STRICT,&err);
        Led_Off();
        OSTimeDlyHMSM(0, 0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
        // printf("Working in Led Blink-----");
	}
}

static void Test_Idle(void *p_arg)
{
	OS_ERR  err;
	(void)p_arg;

	while(1) 
	{
        //精确延时 时， 分， 秒， 毫秒
        OSTimeDlyHMSM(0, 0, 1,0,OS_OPT_TIME_HMSM_STRICT,&err);
        // printf("Working in Idle-----");
	}
}

void TaskCreateAppTask(void)
{
    OS_ERR  err;

/* 
    uC/OS-II有两个用来创建任务的函数:OSTaskCreate()和OSTaskCreateExt()
    OSTaskCreate ()函数主要完成3项工作:
        1. 任务堆栈的初始化
        2. 任务控制块的初始化
        3. 任务调度
    任务代码的指针并不是存放在任务控制块中的,而是存放在任务堆栈里面
*/

    OSTaskCreate((OS_TCB       *)&Test_Idle_TCB,              /* Create the start task                                */
                    (CPU_CHAR     *)"Idle",
                    (OS_TASK_PTR   )Test_Idle,
                    (void         *)0u,
                    (OS_PRIO       )OSTASK_Idle_PRIO,
                    (CPU_STK      *)&Test_Idle_STK[0u],
                    (CPU_STK_SIZE  )Test_Idle_STK[TEST_Idle_STK_SIZE / 10u],
                    (CPU_STK_SIZE  )TEST_Idle_STK_SIZE,
                    (OS_MSG_QTY    )0u,
                    (OS_TICK       )0u,
                    (void         *)0u,
                    (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                    (OS_ERR       *)&err);

}

void TaskCreate(void)
{
    OS_ERR  err;
					 
    OSTaskCreate((OS_TCB       *)&Test_Task_TCB,              /* Create the start task                                */
                 (CPU_CHAR     *)"TEST",
                 (OS_TASK_PTR   )Test_Task,
                 (void         *)0u,
                 (OS_PRIO       )OSTASK_TEST_PRIO,
                 (CPU_STK      *)&Test_Task_STK[0u],
                 (CPU_STK_SIZE  )Test_Task_STK[TEST_TASK_STK_SIZE / 10u],
                 (CPU_STK_SIZE  )TEST_TASK_STK_SIZE,
                 (OS_MSG_QTY    )0u,
                 (OS_TICK       )0u,
                 (void         *)0u,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

}


int main(){
	OS_ERR  err;

    // Bsp_Init();
    CPU_IntDis(); //关中断
    /*
        (a) Initialize CPU timestamps
        (b) Initialize CPU interrupts disabled time measurements
        (c) Initialize CPU host name
    */   
    CPU_Init();

    Mem_Init();
    /*
        OSInit工作
        (a) 基础参数初始化 Initialize miscellaneous(混杂的,各种各样的) variables 
        (b) 初始化任务就绪表 Initialize the Ready List 
        (c) 初始化任务控制块 Initialize the free list of OS_TCBs 
        (d) 初始化事件控制块 Initialize the free list of OS_EVENTs 
    */
	OSInit(&err); 

	/* 
        Create the start task 
        创建启动任务
    */
	TaskCreate();

    /*  
        OSStart工作
        (a) 该函数由SStart()函数调用
        (b) 功能是运行优先级最高的就绪任务
        (c) 在调用OSStart()之前,用户必须先调用OSInit()，并且已经至少创建了一个任务.
    */
	OSStart(&err);
	(void)&err;
	return (0u);
}
