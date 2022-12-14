/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
*                    配套 KST-51 单片机开发板 示例源代码
*
*         (c) 版权所有 2014 金沙滩工作室/清华大学出版社 保留所有权利
*                 获取更多资料请访问：http://www.kingst.org
*
* 文件名：main.c
* 描  述：第7章 作业题4 
* 版本号：v1.0.0
* 备  注：lesson7_7的向左移动改为向右移动
*******************************************************************************
*/

#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code image[30][8] = {
    {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    {0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE},
    {0xFF,0xFC,0xFE,0xFE,0xFE,0xFE,0xFE,0xFC},
    {0xFF,0xF8,0xFC,0xFC,0xFC,0xFC,0xFC,0xF8},
    {0xFF,0xF0,0xF9,0xF9,0xF9,0xF9,0xF9,0xF0},
    {0xFF,0xE1,0xF3,0xF3,0xF3,0xF3,0xF3,0xE1},
    {0xFF,0xC3,0xE7,0xE7,0xE7,0xE7,0xE7,0xC3},
    {0xFF,0x87,0xCE,0xCE,0xCE,0xCF,0xCF,0x87},
    {0xFF,0x0E,0x9C,0x9C,0x9C,0x9E,0x9F,0x0F},
    {0xFF,0x1C,0x38,0x38,0x38,0x3C,0x3E,0x1F},
    {0xFF,0x39,0x70,0x70,0x70,0x78,0x7C,0x3E}, 
    {0xFF,0x73,0xE0,0xE0,0xE0,0xF0,0xF8,0x7C},
    {0xFF,0xE6,0xC0,0xC0,0xC0,0xE0,0xF0,0xF9},
    {0xFF,0xCC,0x80,0x80,0x80,0xC0,0xE1,0xF3},
    {0xFF,0x99,0x00,0x00,0x00,0x81,0xC3,0xE7},
    {0xFF,0x33,0x01,0x01,0x01,0x03,0x87,0xCF},
    {0xFF,0x67,0x03,0x03,0x03,0x07,0x0F,0x9F},
    {0xFF,0xCE,0x06,0x06,0x06,0x0E,0x1E,0x3F},
    {0xFF,0x9C,0x0C,0x0C,0x0C,0x1C,0x3C,0x7E},
    {0xFF,0x39,0x19,0x19,0x19,0x39,0x78,0xFC},
    {0xFF,0x73,0x33,0x33,0x33,0x73,0xF0,0xF8},
    {0xFF,0xE6,0x66,0x66,0x66,0xE6,0xE0,0xF0},
    {0xFF,0xCC,0xCC,0xCC,0xCC,0xCC,0xC0,0xE1},
    {0xFF,0x99,0x99,0x99,0x99,0x99,0x81,0xC3},
    {0xFF,0x33,0x33,0x33,0x33,0x33,0x03,0x87},
    {0xFF,0x67,0x67,0x67,0x67,0x67,0x07,0x0F},
    {0xFF,0xCF,0xCF,0xCF,0xCF,0xCF,0x0F,0x1F},
    {0xFF,0x9F,0x9F,0x9F,0x9F,0x9F,0x1F,0x3F},
    {0xFF,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x7F},
    {0xFF,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0xFF},
};

void main()
{
    EA = 1;       //使能总中断
    ENLED = 0;    //使能U4，选择LED点阵
    ADDR3 = 0;
    TMOD = 0x01;  //设置T0为模式1
    TH0  = 0xFC;  //为T0赋初值0xFC67，定时1ms
    TL0  = 0x67;
    ET0  = 1;     //使能T0中断
    TR0  = 1;     //启动T0
    while (1);
}
/* 定时器0中断服务函数 */
void InterruptTimer0() interrupt 1
{
    static unsigned char i = 0;  //动态扫描的索引
    static unsigned char tmr = 0;  //250ms软件定时器
    static unsigned char index = 0;  //图片刷新索引

    TH0 = 0xFC;  //重新加载初值
    TL0 = 0x67;
    //以下代码完成LED点阵动态扫描刷新
    P0 = 0xFF;   //显示消隐
    switch (i)
    {
        case 0: ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=image[index][0]; break;
        case 1: ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=image[index][1]; break;
        case 2: ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=image[index][2]; break;
        case 3: ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=image[index][3]; break;
        case 4: ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=image[index][4]; break;
        case 5: ADDR2=1; ADDR1=0; ADDR0=1; i++; P0=image[index][5]; break;
        case 6: ADDR2=1; ADDR1=1; ADDR0=0; i++; P0=image[index][6]; break;
        case 7: ADDR2=1; ADDR1=1; ADDR0=1; i=0; P0=image[index][7]; break;
        default: break;
    }
    //以下代码完成每250ms改变一帧图像
    tmr++;
    if (tmr >= 250)  //达到250ms时改变一次图片索引
    {
        tmr = 0;
        index++;
        if (index >= 30)  //图片索引达到30后归零
        {
            index = 0;
        }
    }
}
