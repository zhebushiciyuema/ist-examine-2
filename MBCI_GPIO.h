/**
 * @file MBCI_GPIO.h
 * @author YuLin Wang (2677657424@qq.com)
 * @brief GPIO 设备的抽象，用于一般场景下的 GPIO 操作
 * @version 0.1
 * @date 2023-10-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "cw32f030.h"
#include "base_types.h"

#ifndef __MBCI_GPIO_H__
#define __MBCI_GPIO_H__

#define MBCI_IO_HIGH 1
#define MBCI_IO_LOW 0

#define GPIO_REG_A      ((GPIO_TypeDef*)0x48000000)
#define GPIO_REG_B      ((GPIO_TypeDef*)0x48000400)
#define GPIO_REG_C      ((GPIOC_TypeDef*)0x48000800)
#define GPIO_REG_F      ((GPIOF_TypeDef*)0x48001400)

#define GPIO_PIN   (((uint16_t)name[3])*10+(uint16_t)name[4])

/**
 * @brief GPIO 输入输出模式
 * 
 */
enum mbci_gpio_mode
{
    /**
     * @brief 浮空输入。I/O 电平信号直接输入到寄存器，内部无上下拉电阻。如果在外部电路中没有上下拉电阻，那么输入信号将是不确定的。
     *
     */
    MBCI_GPIO_IN_FLOATING = 0x00,
    /**
     * @brief 上拉输入。内部连接上拉电阻，在引脚浮空时，输入信号将被读取为高电平。
     * 
     */
    MBCI_GPIO_IN_PULL_UP = 0x01,
    /**
     * @brief 下拉输入。内部连接下拉电阻，在引脚浮空时，输入信号将被读取为低电平。
     * 
     */
    MBCI_GPIO_IN_PULL_DOWN = 0x02,
    /**
     * @brief 推挽输出。当设置输出为高电平时，引脚输出高电平；当设置输出为低电平时，引脚输出低电平。
     * 
     */
    MBCI_GPIO_OUT_PP = 0x10,
    /**
     * @brief 开漏输出。当设置输出为高电平时，引脚为高阻状态，由外部电路决定状态；当设置输出为低电平时，引脚将拉低电平。
     * 
     */
    MBCI_GPIO_OUT_OD = 0x11,
};

/**
 * @brief 初始化指定的 GPIO 引脚
 * 
 * @param name 引脚名称，必须以P开头，且后面跟着引脚编号。引脚编号的规则如下: 引脚编号应该由端口号和引脚号组成,并通过`.`分隔，端口号为 0~7 或者 A-Z，引脚号为 00~99。例如 P1.01 表示端口 1 的第 1 号引脚。端口号可以是一个数字，也可是一个字母。由具体的芯片决定。引脚号必须是两位数的数字。
 * @param dir 引脚的输入输出模式，参见 enum mbci_gpio_mode
 */
void mbci_gpio_init(char *name, enum mbci_gpio_mode dir)
{
	if(name[1] == 'A')
	{
		GPIO_TypeDef *GPIO_Reg_A = GPIO_REG_A;
		if (dir == (MBCI_GPIO_IN_FLOATING | MBCI_GPIO_IN_PULL_UP | MBCI_GPIO_IN_PULL_DOWN))   //输入模式
		{
			REGBITS_SET(GPIO_Reg_A->DIR, (uint16_t)0x0001<<GPIO_PIN);
			if (dir == MBCI_GPIO_IN_FLOATING) 
			{
				 REGBITS_SET(GPIO_Reg_A->PUR, (uint16_t)0x0001<<GPIO_PIN);
				 REGBITS_CLR(GPIO_Reg_A->PDR, (uint16_t)0x0001<<GPIO_PIN);
			}
			if (dir == MBCI_GPIO_IN_PULL_UP)
			{
				 REGBITS_SET(GPIO_Reg_A->PUR, (uint16_t)0x0001<<GPIO_PIN);
				 REGBITS_CLR(GPIO_Reg_A->PDR, (uint16_t)0x0001<<GPIO_PIN);
			}
			if (dir == MBCI_GPIO_IN_PULL_DOWN)
			{
				 REGBITS_SET(GPIO_Reg_A->PDR, (uint16_t)0x0001<<GPIO_PIN);
				 REGBITS_CLR(GPIO_Reg_A->PUR, (uint16_t)0x0001<<GPIO_PIN);
			}
		}
		else                                                           //输出模式
		{
			REGBITS_CLR(GPIO_Reg_A->DIR, (uint16_t)0x0001<<GPIO_PIN);
			if (dir == MBCI_GPIO_OUT_PP)
			{
				 REGBITS_CLR(GPIO_Reg_A->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
			else
			{
				 REGBITS_SET(GPIO_Reg_A->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
			if (dir == MBCI_GPIO_OUT_OD)
			{
				 REGBITS_SET(GPIO_Reg_A->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
			else
			{
				 REGBITS_CLR(GPIO_Reg_A->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
		}
	}
	if(name[1] == 'B')
	{
		GPIO_TypeDef *GPIO_Reg_B = GPIO_REG_B;
		if (dir == (MBCI_GPIO_IN_FLOATING | MBCI_GPIO_IN_PULL_UP | MBCI_GPIO_IN_PULL_DOWN))   //输入模式
		{
			REGBITS_SET(GPIO_Reg_B->DIR, (uint16_t)0x0001<<GPIO_PIN);
			if (dir == MBCI_GPIO_IN_FLOATING) 
			{
				 REGBITS_SET(GPIO_Reg_B->PUR, (uint16_t)0x0001<<GPIO_PIN);
				 REGBITS_CLR(GPIO_Reg_B->PDR, (uint16_t)0x0001<<GPIO_PIN);
			}
			if (dir == MBCI_GPIO_IN_PULL_UP)
			{
				 REGBITS_SET(GPIO_Reg_B->PUR, (uint16_t)0x0001<<GPIO_PIN);
				 REGBITS_CLR(GPIO_Reg_B->PDR, (uint16_t)0x0001<<GPIO_PIN);
			}
			if (dir == MBCI_GPIO_IN_PULL_DOWN)
			{
				 REGBITS_SET(GPIO_Reg_B->PDR, (uint16_t)0x0001<<GPIO_PIN);
				 REGBITS_CLR(GPIO_Reg_B->PUR, (uint16_t)0x0001<<GPIO_PIN);
			}
		}
		else                                                           //输出模式
		{
			REGBITS_CLR(GPIO_Reg_B->DIR, (uint16_t)0x0001<<GPIO_PIN);
			if (dir == MBCI_GPIO_OUT_PP)
			{
				 REGBITS_CLR(GPIO_Reg_B->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
			else
			{
				 REGBITS_SET(GPIO_Reg_B->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
			if (dir == MBCI_GPIO_OUT_OD)
			{
				 REGBITS_SET(GPIO_Reg_B->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
			else
			{
				 REGBITS_CLR(GPIO_Reg_B->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
		}
	}
	if(name[1] == 'C')
	{
		GPIOC_TypeDef *GPIO_Reg_C = GPIO_REG_C;
		if (dir == (MBCI_GPIO_IN_FLOATING | MBCI_GPIO_IN_PULL_UP | MBCI_GPIO_IN_PULL_DOWN))   //输入模式
		{
			REGBITS_SET(GPIO_Reg_C->DIR, (uint16_t)0x0001<<GPIO_PIN);
			if (dir == MBCI_GPIO_IN_FLOATING) 
			{
				 REGBITS_SET(GPIO_Reg_C->PUR, (uint16_t)0x0001<<GPIO_PIN);
				 REGBITS_CLR(GPIO_Reg_C->PDR, (uint16_t)0x0001<<GPIO_PIN);
			}
			if (dir == MBCI_GPIO_IN_PULL_UP)
			{
				 REGBITS_SET(GPIO_Reg_C->PUR, (uint16_t)0x0001<<GPIO_PIN);
				 REGBITS_CLR(GPIO_Reg_C->PDR, (uint16_t)0x0001<<GPIO_PIN);
			}
			if (dir == MBCI_GPIO_IN_PULL_DOWN)
			{
				 REGBITS_SET(GPIO_Reg_C->PDR, (uint16_t)0x0001<<GPIO_PIN);
				 REGBITS_CLR(GPIO_Reg_C->PUR, (uint16_t)0x0001<<GPIO_PIN);
			}
		}
		else                                                           //输出模式
		{
			REGBITS_CLR(GPIO_Reg_C->DIR, (uint16_t)0x0001<<GPIO_PIN);
			if (dir == MBCI_GPIO_OUT_PP)
			{
				 REGBITS_CLR(GPIO_Reg_C->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
			else
			{
				 REGBITS_SET(GPIO_Reg_C->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
			if (dir == MBCI_GPIO_OUT_OD)
			{
				 REGBITS_SET(GPIO_Reg_C->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
			else
			{
				 REGBITS_CLR(GPIO_Reg_C->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
		}
	}
	if(name[1] == 'F')
	{
		GPIOF_TypeDef *GPIO_Reg_F = GPIO_REG_F;
		if (dir == (MBCI_GPIO_IN_FLOATING | MBCI_GPIO_IN_PULL_UP | MBCI_GPIO_IN_PULL_DOWN))   //输入模式
		{
			REGBITS_SET(GPIO_Reg_F->DIR, (uint16_t)0x0001<<GPIO_PIN);
			if (dir == MBCI_GPIO_IN_FLOATING) 
			{
				 REGBITS_SET(GPIO_Reg_F->PUR, (uint16_t)0x0001<<GPIO_PIN);
				 REGBITS_CLR(GPIO_Reg_F->PDR, (uint16_t)0x0001<<GPIO_PIN);
			}
			if (dir == MBCI_GPIO_IN_PULL_UP)
			{
				 REGBITS_SET(GPIO_Reg_F->PUR, (uint16_t)0x0001<<GPIO_PIN);
				 REGBITS_CLR(GPIO_Reg_F->PDR, (uint16_t)0x0001<<GPIO_PIN);
			}
			if (dir == MBCI_GPIO_IN_PULL_DOWN)
			{
				 REGBITS_SET(GPIO_Reg_F->PDR, (uint16_t)0x0001<<GPIO_PIN);
				 REGBITS_CLR(GPIO_Reg_F->PUR, (uint16_t)0x0001<<GPIO_PIN);
			}
		}
		else                                                           //输出模式
		{
			REGBITS_CLR(GPIO_Reg_F->DIR, (uint16_t)0x0001<<GPIO_PIN);
			if (dir == MBCI_GPIO_OUT_PP)
			{
				 REGBITS_CLR(GPIO_Reg_F->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
			else
			{
				 REGBITS_SET(GPIO_Reg_F->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
			if (dir == MBCI_GPIO_OUT_OD)
			{
				 REGBITS_SET(GPIO_Reg_F->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
			else
			{
				 REGBITS_CLR(GPIO_Reg_F->OPENDRAIN, (uint16_t)0x0001<<GPIO_PIN);
			}
		}
	}
}

/**
 * @brief 对指定的 GPIO 引脚的输出进行设置
 * 
 * @param name 引脚名称。规则同 mbci_gpio_init
 * @param value 输出的电平，参见 MBCI_IO_HIGH 和 MBCI_IO_LOW
 */
void mbci_gpio_set(char *name, int value)
{
	if(name[1] == 'A')
	{
		GPIO_TypeDef *GPIO_Reg_A = GPIO_REG_A;
		if (value == MBCI_IO_HIGH)
		{
			GPIO_Reg_A->BSRR = (uint16_t)0x0001<<GPIO_PIN;
		}
		else
		{
			GPIO_Reg_A->BRR = (uint16_t)0x0001<<GPIO_PIN;
		}
	}
	if(name[1] == 'B')
	{
		GPIO_TypeDef *GPIO_Reg_B = GPIO_REG_B;
		if (value == MBCI_IO_HIGH)
		{
			GPIO_Reg_B->BSRR = (uint16_t)0x0001<<GPIO_PIN;
		}
		else
		{
			GPIO_Reg_B->BRR = (uint16_t)0x0001<<GPIO_PIN;
		}
	}
	if(name[1] == 'C')
	{
		GPIOC_TypeDef *GPIO_Reg_C = GPIO_REG_C;
		if (value == MBCI_IO_HIGH)
		{
			GPIO_Reg_C->BSRR = (uint16_t)0x0001<<GPIO_PIN;
		}
		else
		{
			GPIO_Reg_C->BRR = (uint16_t)0x0001<<GPIO_PIN;
		}
	}
	if(name[1] == 'F')
	{
		GPIOF_TypeDef *GPIO_Reg_F = GPIO_REG_F;
		if (value == MBCI_IO_HIGH)
		{
			GPIO_Reg_F->BSRR = (uint16_t)0x0001<<GPIO_PIN;
		}
		else
		{
			GPIO_Reg_F->BRR = (uint16_t)0x0001<<GPIO_PIN;
		}
	}
}

/**
 * @brief 读取指定的 GPIO 引脚的输入
 * 
 * @param name 引脚名称。规则同 mbci_gpio_init
 * @return int 输入的电平，参见 MBCI_IO_HIGH 和 MBCI_IO_LOW
 */
int mbci_gpio_get(char *name)
{
   if(name[1] == 'A')
   {
	   GPIO_TypeDef *GPIO_Reg_A = GPIO_REG_A;
	   if (GPIO_Reg_A->IDR & (uint16_t)0x0001<<GPIO_PIN)
	   {
		  return (MBCI_IO_HIGH);
	   }
	   return (MBCI_IO_LOW);
	}
	else if(name[1] == 'B')
   {
	   GPIO_TypeDef *GPIO_Reg_B = GPIO_REG_B;
	   if (GPIO_Reg_B->IDR & (uint16_t)0x0001<<GPIO_PIN)
	   {
		  return (MBCI_IO_HIGH);
	   }
	   return (MBCI_IO_LOW);
	}
	else if(name[1] == 'C')
   {
	   GPIOC_TypeDef *GPIO_Reg_C = GPIO_REG_C;
	   if (GPIO_Reg_C->IDR & (uint16_t)0x0001<<GPIO_PIN)
	   {
		  return (MBCI_IO_HIGH);
	   }
	   return (MBCI_IO_LOW);
	}
	else if(name[1] == 'F')
   {
	   GPIOF_TypeDef *GPIO_Reg_F = GPIO_REG_F;
	   if (GPIO_Reg_F->IDR & (uint16_t)0x0001<<GPIO_PIN)
	   {
		  return (MBCI_IO_HIGH);
	   }
	   return (MBCI_IO_LOW);
	}
}

#endif // __MBCI_GPIO_H__
