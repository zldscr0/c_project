#define BACKGROUND_COLOR RGB(0, 0, 0)

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <mmsystem.h>//�������� 


//draw.cpp
void drawView(int status);
void drawLeft();

void drawAVGInfo();//����ƽ��ֵ�������� 
void drawKRMInfo();//����k��ԭ��صĵ�������
void drawKCMInfo();//����k�����ľصĵ�������
void drawlRInfo();//������С���˷�������ϵ�б�ʺͽؾ�
void drawHistory();
void drawMainInfo();//������ 

void handle_AVG(MOUSEMSG m);//����ƽ��ֵ���� 
void handle_KRM(MOUSEMSG m);//����k��ԭ��ؽ��� 
void handle_KCM(MOUSEMSG m);// ����k�����ľؽ���
void handle_lR(MOUSEMSG m);// ������С���˷�������ϵ�б�ʺͽؾ�
void handle_his(MOUSEMSG m);//������ʷ��¼ģ�� 

void menBtn(MOUSEMSG m, int* status);//���Ƶ�������ť����
void setUpButton(int index, int status);//��ť״̬��� 

//calculate.cpp
double calculateMean(double data[], int size);
// ��k��ԭ���
double calculateRawMoment(double data[], int size, int k);
// ��k�����ľ�
double calculateCentralMoment(double data[], int size, int k);
// ��С���˷��������
void linearRegression(double x[], double y[], int size, double *slope, double *intercept);

//tool.cpp
bool isInteger(const char *str);
bool isFloat(const char *str);
bool isEmpty(const char *str);

void init_file();
void playMusic(); 
