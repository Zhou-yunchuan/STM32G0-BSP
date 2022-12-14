
 
#include "bsp_time.h"
#include "main.h"      

typedef struct {
	__IO uint32_t tick;
	     uint32_t flag;
} Time;

static Time time = {0};
static uint32_t clock_ferq = 64;

void BSP_Time_Init(void)
{
	time.flag = 0;
	time.tick = 0;
}

void BSP_Time_IncTick(void)
{
	time.tick++;
}

int BSP_Time_CheckTick(void)
{
	int ret;
	if(time.flag != time.tick) 
	{
		time.flag = time.tick;	
		ret = 1;
	}
	else 
	{
		ret = 0;
	}
	return ret;
}

int BSP_Time_CheckSlice(int slice)
{
	int ret;
	if(time.flag % slice == 0) 
	{
		ret = 1;
	}
	else 
	{
		ret = 0;
	}
	return ret;
}

void BSP_Time_DelayUs(int us)
{
	uint32_t ticks;
	uint32_t t_old, t_now, t_cnt = 0;
	uint32_t reload = SysTick->LOAD;
	ticks = us*clock_ferq; 
	t_old = SysTick->VAL; 
	while(1)
	{
		t_now = SysTick->VAL;
		if(t_now!=t_old)
		{
			if(t_now<t_old) 
			{
				t_cnt += t_old-t_now;
			} 
			else 
			{
				t_cnt += reload+(t_old-t_now);
			}
			t_old = t_now;
			if(t_cnt>=ticks) 
			{
				break;
			}
		}
	}
}


void BSP_Time_DelayMs(int ms)
{
	uint32_t i;
	for(i=0;i<ms;i++)
	{
		BSP_Time_DelayUs(1000);
	}
}

