/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
*                    配套 KST-51 单片机开发板 示例源代码
*
*         (c) 版权所有 2014 金沙滩工作室/清华大学出版社 保留所有权利
*                 获取更多资料请访问：http://www.kingst.org
*
* 文件名：PCF8591.c
* 描  述：AD/DA芯片PCF8591驱动模块的头文件
* 版本号：v1.0.0
* 备  注：
*******************************************************************************
*/

#ifndef _PCF8591_H
#define _PCF8591_H


#ifndef _PCF8591_C

#endif


uint8 GetADCValue(uint8 chn);
void SetDACOut(uint8 val);


#endif
