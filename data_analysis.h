#define BACKGROUND_COLOR RGB(0, 0, 0)

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <mmsystem.h>//播放音乐 


//draw.cpp
void drawView(int status);
void drawLeft();

void drawAVGInfo();//计算平均值导引界面 
void drawKRMInfo();//计算k阶原点矩的导引界面
void drawKCMInfo();//计算k阶中心矩的导引界面
void drawlRInfo();//计算最小二乘法线性拟合的斜率和截距
void drawHistory();
void drawMainInfo();//主界面 

void handle_AVG(MOUSEMSG m);//处理平均值计算 
void handle_KRM(MOUSEMSG m);//处理k阶原点矩界面 
void handle_KCM(MOUSEMSG m);// 处理k阶中心矩界面
void handle_lR(MOUSEMSG m);// 处理最小二乘法线性拟合的斜率和截距
void handle_his(MOUSEMSG m);//处理历史记录模块 

void menBtn(MOUSEMSG m, int* status);//控制导航栏按钮触发
void setUpButton(int index, int status);//按钮状态变更 

//calculate.cpp
double calculateMean(double data[], int size);
// 求k阶原点矩
double calculateRawMoment(double data[], int size, int k);
// 求k阶中心矩
double calculateCentralMoment(double data[], int size, int k);
// 最小二乘法线性拟合
void linearRegression(double x[], double y[], int size, double *slope, double *intercept);

//tool.cpp
bool isInteger(const char *str);
bool isFloat(const char *str);
bool isEmpty(const char *str);

void init_file();
void playMusic(); 
