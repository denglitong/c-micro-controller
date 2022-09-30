/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
*                    配套 KST-51 单片机开发板 示例源代码
*
*         (c) 版权所有 2014 金沙滩工作室/清华大学出版社 保留所有权利
*                 获取更多资料请访问：http://www.kingst.org
*
* 文件名：main.c
* 描  述：第9章 步进电机驱动的基础示例
* 版本号：v1.0.0
* 备  注：详情见第9章9.3.3节，此为针对STC12系列单片机修改的代码
*******************************************************************************
*/

#include <reg52.h>

unsigned char code BeatCode[8] = {  //步进电机节拍对应的IO控制代码
    0xE, 0xC, 0xD, 0x9, 0xB, 0x3, 0x7, 0x6
};

void delay();

void main()
{
    unsigned char tmp;  //定义一个临时变量
    unsigned char index = 0;  //定义节拍输出索引
    
	while (1)
    {
        tmp = P1;                    //用tmp把P1口当前值暂存
        tmp = tmp & 0xF0;            //用&操作清零低4位
        tmp = tmp | BeatCode[index]; //用|操作把节拍代码写到低4位
        P1  = tmp;                   //把低4位的节拍代码和高4位的原值送回P1
        index++;                     //节拍输出索引递增
        index = index & 0x07;        //用&操作实现到8归零
        delay();                     //延时2ms，即2ms执行一拍
    }
}
/* 软件延时函数，延时约2ms */
void delay()
{
    unsigned int i = 1400;
	
    while (i--);
}
