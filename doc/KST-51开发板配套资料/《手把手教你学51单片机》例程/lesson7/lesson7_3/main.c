/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
*                    配套 KST-51 单片机开发板 示例源代码
*
*         (c) 版权所有 2014 金沙滩工作室/清华大学出版社 保留所有权利
*                 获取更多资料请访问：http://www.kingst.org
*
* 文件名：main.c
* 描  述：第7章 点亮LED点阵上的一行
* 版本号：v1.0.0
* 备  注：详情见第7章7.3节
*******************************************************************************
*/

#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
    ENLED = 0;   //U3、U4两片74HC138总使能
    ADDR3 = 0;   //使能U4使之正常输出
    ADDR2 = 0;   //经U4的Y1输出开启三极管Q11
    ADDR1 = 0;
    ADDR0 = 1;
    P0 = 0x00;    //向P0写入0来点亮一行
    while(1);     //程序停止在这里
}
