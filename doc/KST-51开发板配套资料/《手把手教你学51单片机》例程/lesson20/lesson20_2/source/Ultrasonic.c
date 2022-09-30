/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
*                    配套 KST-51 单片机开发板 示例源代码
*
*         (c) 版权所有 2016 金沙滩工作室/清华大学出版社 保留所有权利
*                 获取更多资料请访问：http://www.qdkingst.com
*
* 文件名：Ultrasonic.c
* 描  述：使用定时器1的门控模式测量超声波的回波信号，从而计算出距离
* 版本号：v1.0.0
* 备  注：开发板上T0的门控引脚P3.2被DS18B20占用，共用的话会相互影响；
          T1门控引脚P3.3与HS0038共用，在没有38K红外调制信号的环境下不会影响测量，
          所以本例选用T1来测量回波信号的脉冲宽度。
*******************************************************************************
*/

#include "Ultrasonic.h"

/*软件延时，延时时间（t*10)us*/
void DelayX10us(unsigned char t)
{
    do {
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    } while (--t);
}

/* 获取测量数据，返回值：以毫米为单位的距离值 */
unsigned int GetDistance()
{
    float time;
    float result;

    TH1 = 0;                  //定时器1清零，准备本次测距计数
    TL1 = 0;
    Trig = 1;                 //Trig输出高电平
    DelayX10us(2);            //延时20us
    Trig = 0;                 //Trig输出低电平，至此产生一个20us的脉冲信号以启动超声波模块
    while(!Echo);             //等待回波信号，回波信号自动使能T1计数
    while(Echo);              //等待回波信号结束，T1同时自动停止
    if (TF1 == 1)             //TF1为1时说明定时器溢出了
    {
        TF1 = 0;              //清除标志位
        time = 65535;         //溢出时，直接设置为最大计数值
    }
    else
    {
        time = TH1*256 + TL1; //未溢出时，读取其实际计数值
    }
    time = time * (12/11.0592) / 2;  //将计数周期转换为实际时间（us）；超声波测得的是来回距离，需要除以2得到单程距离所对应的时间
    result = (time/1000000) * 340;   //time(s)*速度 = 距离 ，340为声波在空气中的传播速度(m/s)
    if (result > 4.0)        //判断是否超出模块的测量范围
    {
        result = 4.0;        //超出上限4m则设置为4m
    }
    else if (result < 0.02)
    {
        result = 0.02;       //低于下限0.02m则设置为0.02m
    }
    return (unsigned int)(result*1000);   //以无符号整形数返回测量结果，乘1000使其单位变为毫米
}

/*初始化超声波模块*/
void InitUltrasonic()
{
    TMOD &= 0x0f;
    TMOD |= 0x90;  //设置T1为方式1，GATE=1启用门控模式；
    TH1 = 0;
    TL1 = 0;
    ET1 = 0;       //关闭T0中断
    TR1 = 1;       //使能定时器，预先打开定时器，启停将由INT1引脚控制
    Trig = 0;      //拉低模块触发引脚
}
