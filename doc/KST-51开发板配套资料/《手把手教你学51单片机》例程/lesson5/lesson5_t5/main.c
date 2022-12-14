/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
*                    配套 KST-51 单片机开发板 示例源代码
*
*         (c) 版权所有 2014 金沙滩工作室/清华大学出版社 保留所有权利
*                 获取更多资料请访问：http://www.kingst.org
*
* 文件名：main.c
* 描  述：第5章 作业题5
* 版本号：v1.0.0
* 备  注：变更lesson5_3的正计数为倒计数
*******************************************************************************
*/

#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

//用数组来存储数码管的真值表，数组将在下一章详细介绍
unsigned char code LedChar[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};

void main()
{
    unsigned char cnt = 0;  //记录T0中断次数
    unsigned char sec = 0x0F;  //记录经过的秒数，倒计时初值0x0F(15)

    ENLED = 0;    //使能U3，选择数码管DS1
    ADDR3 = 1;
    ADDR2 = 0;
    ADDR1 = 0;
    ADDR0 = 0;
    TMOD = 0x01;  //设置T0为模式1
    TH0  = 0xB8;  //为T0赋初值0xB800
    TL0  = 0x00;
    TR0  = 1;     //启动T0
    
    while (1)
    {
        if (TF0 == 1)        //判断T0是否溢出
        {
            TF0 = 0;         //T0溢出后，清零中断标志
            TH0 = 0xB8;      //并重新赋初值
            TL0 = 0x00;
            cnt++;           //计数值自加1
            if (cnt >= 50)   //判断T0溢出是否达到50次
            {
                cnt = 0;            //达到50次后计数值清零
                P0 = LedChar[sec];  //当前秒数对应的真值表中的值送到P0口
                if (sec > 0)        //当秒数大于0时，减1
                {
                    sec--;
                }
                else                //当秒数等于0时，重新赋初值0x0F
                {
                    sec = 0x0F;
                }
            }
        }
    }
}
