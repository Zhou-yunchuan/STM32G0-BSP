/**
  * @file  bsp_sys.c
  * @breif 系统相关板级支持包
	         提供常用的工具函数、数据类型
  * Copyright (c) 2022 Zhou Yunchuan
  */

#include "bsp_sys.h"

void generateRangeCycle(RangeCycle *rc, float start, float end, float step)
{
	if((rc->val)>=end)
	{
		rc->sign = -1;
	}
	if((rc->val)<=start) 
	{
		rc->sign = 1;
	}
	rc->val += step*(rc->sign);
}



