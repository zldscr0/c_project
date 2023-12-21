#include "data_analysis.h"

//大小界面 
#define windows_W 1000
#define windows_H 600

#define SIZE 30

IMAGE buffer(windows_W, windows_H);

const int BUTTON_WIDTH = 180;//按钮宽度 
const int BUTTON_HEIGHT = 26;//按钮高度 
const int RET_BUTTON_WIDTH = 100;//返回按钮宽度 


typedef struct Button {
    int x, y;  // 坐标
    char str[50];  // 按钮内容
    COLORREF color[2];  // 按钮颜色 共两个状态的按钮颜色 
    int status;// 按钮的状态 

} button;


//左侧功能导航框的按钮 
//从左到右的含义与Button的结构体定义一致 
int btnNum = 6;// 左侧功能导航框的按钮数量 
button btn[6] = {
	
    {0, 0, "平均值", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {0, 114, "k阶原点矩", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {0, 228, "k阶中心矩", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {0, 342, "最小二乘法线性拟合", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {0, 456, "查看历史记录", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
	{0, 570, "退出", {RGB(3,101,100), RGB(204, 213, 240)}, 0}               
};
//历史记录的按钮 
button his_btn[4] = {
	
    {200, 470, "平均值", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {400, 470, "k阶原点矩", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {600, 470, "k阶中心矩", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {800, 470, "最小二乘法线性拟合", {RGB(3,101,100), RGB(204, 213, 240)}, 0}      
};

//输入按钮（几个界面共用 
button input_btn = {450 ,470,"开始",{RGB(3,101,100), RGB(204, 213, 240)}, 0};

//返回按钮（几个界面共用 
button ret_btn = {220,10,"返回",{RGB(3,101,100), RGB(204, 213, 240)}, 0}; 
 






// drawButton 函数用于绘制按钮
// 参数：
//   - BTN: 表示按钮的结构体，包含按钮的坐标、文本内容、颜色和状态等信息
//   - width: 按钮的宽度，默认值为 160
//   - height: 按钮的高度，默认值为 30
void drawButton(button BTN, int width = 180, int height = 30) {
    setlinecolor(WHITE);  // 设置边框颜色为白色
    setfillcolor(BTN.color[BTN.status]);  // 设置填充颜色为按钮的当前状态颜色

    int x = BTN.x, y = BTN.y;  // 获取按钮的坐标
    fillroundrect(x, y, x + width, y + height, 10, 10);  // 绘制带圆角的矩形按钮

    settextcolor(WHITE);  // 设置文本颜色为白色 
    settextstyle(16, 0, _T("Consolas"));  // 设置文本字体和大小
    outtextxy(x + 28, y + 7, BTN.str);  // 在按钮中心绘制文本
}

// drawLeft 函数用于绘制左边的功能框  高600 宽 180 
void drawLeft() {
	//设置底层背景
	setfillcolor(RGB(39, 72, 98));
	// 填充矩形，作为左侧区域的背景，左上(0,0) 右下(180,600)  
	fillrectangle(0, 0, 180, 600);
	//遍历按钮数组，绘制按钮 
	for (int i = 0; i < btnNum; i++) {
		drawButton(btn[i], BUTTON_WIDTH, BUTTON_HEIGHT);
	}
}



// drawView 函数用于绘制界面的主要信息
// 参数：
//   - status: 表示当前界面的状态，根据不同状态绘制不同的信息
void drawView(int status) {
    SetWorkingImage(&buffer);  // 设置当前绘图设备为缓冲区
    cleardevice();  // 清空缓冲区
    setbkmode(TRANSPARENT);  // 设置背景混合模式为透明
    setbkcolor(RGB(23,44,60));    // 设置背景颜色 
    drawLeft();// 绘制左侧功能框 
    
    // 根据状态绘制右侧信息
    switch (status) {
    	case 0:
			drawMainInfo();
			break; 
        case 1:
            //printf("计算平均值"); 
            drawAVGInfo();
            break;
        case 2:
            //printf("计算k阶原点矩");  
            drawKRMInfo();
            break;
        case 3:
            //printf("计算k阶中心矩");  
            drawKCMInfo();
            break;
        case 4:
            //printf("最小二乘法线性拟合"); 
            drawlRInfo();
            break;
        case 5:
            //printf("查看历史记录");  
            drawHistory();
            break;
    	case 6:
    		break;
		}

    // 设置绘图目标为绘图窗口
	SetWorkingImage();
	//将 buffer显示在绘图窗口中
    putimage(0, 0, &buffer);  
}


// setUpButton 函数用于设置按钮的状态
// 参数：
//   - index: 指定需要设置状态的按钮索引
//   - status: 指定按钮的状态，0 表示正常状态，1 表示激活状态，-1 表示全部按钮恢复到正常状态
void setUpButton(int index, int status) {
        
    if(status==-1){
        for (int i = 0; i < btnNum; i++) {
            btn[i].status = 0;
        }
        for (int i = 0; i < 4; i++) {
            his_btn[i].status = 0;
        }
        
    	input_btn.status = 0;
    	ret_btn.status = 0;
    }
    else
    {
    	btn[index].status = status;
	}
}
//主界面 
void drawMainInfo() {
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 64;
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	outtextxy(300, 50, "简易数据分析器");


	settextstyle(18, 0, _T("仿宋"));
	outtextxy(300, 160, _T("本数据分析器设有4个功能模块，如左侧功能区所示，以下是使用说明："));
	outtextxy(300, 200, _T("1、平均值计算器"));
	outtextxy(300, 220, _T("2、计算k阶原点矩"));
	outtextxy(300, 240, _T("3、计算k阶中心矩"));
	outtextxy(300, 260, _T("4、最小二乘法线性拟合"));
	outtextxy(300, 280, _T("5、退出"));
	
}


//计算平均值导引界面  
void drawAVGInfo()
{	
	settextstyle(40, 0, _T("仿宋"));
	outtextxy(400, 110, _T("平均值计算器"));
	settextstyle(20, 0, _T("仿宋"));
	outtextxy(400, 180, _T("功能：计算一组数的平均值"));
	outtextxy(400, 220, _T("输入：1.数组大小 2. 数组元素（浮点数）"));
	//加入一个按钮，点按钮才开始输入数据
	drawButton(input_btn, BUTTON_WIDTH, 30);//300 240
} 

//计算k阶原点矩的导引界面 Raw Moment
void drawKRMInfo()
{
	settextstyle(40, 0, _T("仿宋"));
	outtextxy(400, 110, _T("k阶原点矩计算器"));
	settextstyle(20, 0, _T("仿宋"));
	outtextxy(400, 180, _T("功能：计算一组数的k阶原点矩"));
	outtextxy(400, 220, _T("输入：1.数组大小 2.k值 3. 数组元素（浮点数）"));
	//加入一个按钮，点按钮才开始输入数据
	drawButton(input_btn, BUTTON_WIDTH, 30);//300 240
	
} 


//计算k阶中心矩的导引界面 Central Moment
void drawKCMInfo()
{
	settextstyle(40, 0, _T("仿宋"));
	outtextxy(400, 110, _T("k阶中心矩计算器"));
	settextstyle(20, 0, _T("仿宋"));
	outtextxy(400, 180, _T("功能：计算一组数的k阶中心矩"));
	outtextxy(400, 220, _T("输入：1.数组大小 2.k值 3. 数组元素（浮点数）"));
	//加入一个按钮，点按钮才开始输入数据
	drawButton(input_btn, BUTTON_WIDTH, 30);//300 240
	
} 


//计算最小二乘法线性拟合的斜率和截距
void drawlRInfo()
{
	settextstyle(40, 0, _T("仿宋"));
	outtextxy(400, 110, _T("最小二乘法线性拟合"));
	settextstyle(20, 0, _T("仿宋"));
	outtextxy(400, 180, _T("功能：计算最小二乘法线性拟合的斜率和截距"));
	outtextxy(400, 220, _T("输入：1.数组大小(x和y大小相等) 2. x与y数组的元素（浮点数）"));
	//加入一个按钮，点按钮才开始输入数据
	drawButton(input_btn, BUTTON_WIDTH, 30);//300 240
	
} 

void drawHistory()
{	
	settextstyle(40, 0, _T("仿宋"));
	outtextxy(400, 110, _T("历史记录"));
    for(int i=0;i<4;i++)
	{
		drawButton(his_btn[i], BUTTON_WIDTH, 30);//300 240	
	} 
} 



//导航栏按钮触发
void menBtn(MOUSEMSG m, int* status) {
	if (m.y >= 0 && m.y <= 26) {//计算平均值 
		setUpButton(0, 1);
		*status = 1;
	}
	else if (m.y >= 114 && m.y <= 140) {//计算k阶原点矩 
		setUpButton(1, 1);
		*status = 2;
	}
	else if (m.y >= 228 && m.y <= 254) {//计算k阶中心距 
		setUpButton(2, 1);
		*status = 3;
	}
	else if (m.y >= 342 && m.y <= 368) {//最小二乘法线性拟合 
		setUpButton(3, 1);
		*status = 4;
	}
	else if (m.y >= 456 && m.y <= 482) {//查看历史记录 
		setUpButton(4, 1);
		*status = 5;
	}
	else if (m.y >= 570 && m.y <= 596) {//退出 
		setUpButton(5, 1);
		closegraph();
		exit(0);
	}
	
}

void handle_AVG(MOUSEMSG m)
{
	//落在这个范围内表示鼠标落到了输入部分的区域 
	if (m.x >= 450 && m.x < 630) {
		if (m.y >= 470 && m.y <= 500) {
			input_btn.status = 1;
			// 在窗口中显示输入框
    		char inputBuffer[256];//存储输入框 
    		//printf("输入数组的大小 (max 30): ");
    		//scanf("%d", &size);
			InputBox(inputBuffer,256, "输入数组的大小 (max 30): ");
			//判断输入内容是不是空 
			if(isEmpty(inputBuffer))
			{
				char text1[50] = {"输入内容不可为空" }, text2[50] = {"输入错误" };
				MessageBox(GetHWnd(), text1, text2, 0);
				return ;
			}
    		double x[SIZE] = {0};
    		char str[SIZE];
    		
    		int size = atoi(inputBuffer);
    		//整数判断
    		if(!isInteger(inputBuffer))
			{
				char text1[50] = {"数组大小需为整数" }, text2[50] = {"输入错误" };
				MessageBox(GetHWnd(), text1, text2, 0);
				return ;
			}
			// 数组大小判断 
    		if(size<0||size>30)
    		{
    			char text1[50] = {"请输入正确的数组大小" }, text2[50] = {"输入错误" };
				MessageBox(GetHWnd(), text1, text2, 0);
				return ;
			}
    		
    		for (int i = 0; i < size; i++) {
    			sprintf(str, "请输入第%d个数", i+1);
        		InputBox(inputBuffer,256,str);
        		if(!isInteger(inputBuffer)&&!isFloat(inputBuffer))
        		{
        			char text1[50] = {"无效的输入值" }, text2[50] = {"输入错误" };
					MessageBox(GetHWnd(), text1, text2, 0);
					return ;
				}
				x[i] = strtod(inputBuffer,NULL);
    		}
    		
    		setfillcolor(RGB(204, 213, 240));
			fillrectangle(180, 0, 1000, 800);
			

    		double mean_x = calculateMean(x, size);
    		//system("pause");
    		
    		
    		SetWorkingImage(&buffer);  // 设置当前绘图设备为缓冲区
    		cleardevice();  // 清空缓冲区
    		setbkcolor(RGB(23,44,60));    // 设置背景色

   			// 绘制左侧功能按钮
    		drawLeft();
    
    		//输出结果 
    		
    		settextstyle(18, 0, _T("仿宋"));
    		int begin_h = 160;
    		outtextxy(300, begin_h, "输入为：");
    		int begin_w = 300;
    		int off = 0; 
    		begin_h += 20;
    		for (int i = 0; i < size; i++) {
				sprintf(str, "%lf", x[i]);
				outtextxy(begin_w+off, begin_h, str);
				off += 18 * strlen(str);
				//每排放四个数 
				if(i%4==3)
				{
					begin_w = 300;
					off = 0;
					begin_h += 20;
				} 
    		}
    		begin_h += 20;
    		sprintf(str, "%lf", mean_x);
    		outtextxy(300, begin_h, "平均数计算结果是：");
    		begin_h += 20;
    		outtextxy(300, begin_h , str);
			// 打开文件以写入数据
    		FILE *file = fopen("avg_output.txt", "a");
    		if (file == NULL) {
        		return ;
    		}
    		// 将数组的内容写入文件
    		for (int i = 0; i < size; ++i) {
        		fprintf(file, "%lf ", x[i]);
    		}

    		// 将平均值写入文件
    		fprintf(file, "\n%lf\n", mean_x);
    		// 关闭文件
    		fclose(file);
    		
    		//画一个返回按钮
			drawButton(ret_btn, RET_BUTTON_WIDTH, 30);
			// 设置绘图目标为绘图窗口
			SetWorkingImage();
			//将 buffer显示在绘图窗口中
    		putimage(0, 0, &buffer);  
			
    		bool flag = true;
    		while (flag) 
			{
				while (MouseHit())
				{
					m = GetMouseMsg();
					if (m.uMsg == WM_LBUTTONDOWN)
					{//左键按下
						if (m.x >= 220 && m.x <= 320 && m.y>=10 &&m.y<=40)
						{
							ret_btn.status = 1;
							flag = false;
					}
					}
					else if (m.uMsg == WM_LBUTTONUP)
					{//左键弹起
					//重置按钮状态
						setUpButton(0, -1);
					}
				
				}
			} 
		}
	}
	
}





void handle_KRM(MOUSEMSG m)//处理k阶原点矩界面 
{
	if (m.x >= 450 && m.x < 630) {
		if (m.y >= 470 && m.y <= 500) {
			input_btn.status = 1;
			//calculateRawMoment(double data[], int size, int k)  
			// 在窗口中显示输入框
    		char inputBuffer[256];//存储输入框 
			double x[SIZE] = {0};
    		char str[SIZE];
    		
			InputBox(inputBuffer, 256, "输入数组的大小 (max 30): ");
    		//整数判断 
			if(!isInteger(inputBuffer))
			{
				char text1[50] = {"数组大小需为整数" }, text2[50] = {"输入错误" };
				MessageBox(GetHWnd(), text1, text2, 0);
				return ;
			}
			int size = atoi(inputBuffer);
			// 数组大小判断 
    		if(size<0||size>30)
    		{
    			char text1[50] = {"请输入正确的数组大小" }, text2[50] = {"输入错误" };
				MessageBox(GetHWnd(), text1, text2, 0);
				return ;
			}
			
    
    		InputBox(inputBuffer, 256, "输入k值: ");
    		//整数判断 
			if(!isInteger(inputBuffer))
			{
				char text1[50] = {"k值需为整数" }, text2[50] = {"输入错误" };
				MessageBox(GetHWnd(), text1, text2, 0);
				return ;
			}
    		int k = atoi(inputBuffer);

    		//printf("请输入x,y的值:\n");
    		for (int i = 0; i < size; i++) {
    			sprintf(str, "请输入第%d个数", i+1);
        		InputBox(inputBuffer, 256, str);
        		if(!isInteger(inputBuffer)&&!isFloat(inputBuffer))
        		{
        			char text1[50] = {"无效的输入值" }, text2[50] = {"输入错误" };
					MessageBox(GetHWnd(), text1, text2, 0);
					return ;
				}
				x[i] = strtod(inputBuffer,NULL);
    		}
 
   			double rawMoment_x = calculateRawMoment(x, size, k);
   			
   			// 打开文件以写入数据
    		FILE *file = fopen("krm_output.txt", "a");
    		if (file == NULL) {
        		return ;
    		}
    		 
    		// 将数组的内容写入文件
    		for (int i = 0; i < size; ++i) {
        		fprintf(file, "%lf ", x[i]);
    		}
    		//将k值写入文件
    		fprintf(file, "\n%d ", k);
    		// 将结果写入文件
    		fprintf(file, "\n%lf\n", rawMoment_x);
    		// 关闭文件
    		fclose(file);
   			
   			SetWorkingImage(&buffer);  // 设置当前绘图设备为缓冲区
    		cleardevice();  // 清空缓冲区

    	
    		setbkcolor(RGB(23,44,60));    // 设置背景色

   			// 绘制左侧功能按钮
    		drawLeft();
    
    		//输出结果 
    		settextstyle(18, 0, _T("仿宋"));
    		sprintf(str, "%lf", rawMoment_x);
    		outtextxy(300, 180, "结果是：");
    		outtextxy(300, 200, str);
    		
    		//画一个返回按钮
			drawButton(ret_btn, RET_BUTTON_WIDTH, 30);
			// 设置绘图目标为绘图窗口
			SetWorkingImage();
			//将 buffer显示在绘图窗口中
    		putimage(0, 0, &buffer);  
			
    		bool flag = true;
    		while (flag) {
				while (MouseHit()) {
				m = GetMouseMsg();
				if (m.uMsg == WM_LBUTTONDOWN)
				{//左键按下
					if (m.x >= 220 && m.x <= 320 && m.y>=10 &&m.y<=40) {
					ret_btn.status = 1;
					flag = false;
					}
				}
				else if (m.uMsg == WM_LBUTTONUP)
				{//左键弹起
				//重置按钮状态
				setUpButton(0, -1);
				}
				
			}
			} 
    	
			}
	
}}

void handle_KCM(MOUSEMSG m)// 处理k阶中心矩界面
{
	if (m.x >= 450 && m.x < 630) {
	if (m.y >= 470 && m.y <= 500) {
		//calculateCentralMoment  
		// 在窗口中显示输入框
    char inputBuffer[256];//存储输入框 
	InputBox(inputBuffer, 256, "输入数组的大小 (max 30): ");
    double x[SIZE] = {0};
    char str[SIZE];
    
    //整数判断 
	if(!isInteger(inputBuffer))
	{
		char text1[50] = {"数组大小需为整数" }, text2[50] = {"输入错误" };
			MessageBox(GetHWnd(), text1, text2, 0);
			return ;
	}
	int size = atoi(inputBuffer);
	// 数组大小判断 
    if(size<0||size>30)
    {
    	char text1[50] = {"请输入正确的数组大小" }, text2[50] = {"输入错误" };
		MessageBox(GetHWnd(), text1, text2, 0);
		return ;
	}
    
    InputBox(inputBuffer, 256, "输入k值: ");
    //整数判断 
	if(!isInteger(inputBuffer))
	{
		char text1[50] = {"k值需为整数" }, text2[50] = {"输入错误" };
		MessageBox(GetHWnd(), text1, text2, 0);
		return ;
	}
    int k = atoi(inputBuffer);

    //printf("请输入x,y的值:\n");
    for (int i = 0; i < size; i++) 
	{
		sprintf(str, "请输入第%d个数", i+1);
        InputBox(inputBuffer, 256, str);
		if(!isInteger(inputBuffer)&&!isFloat(inputBuffer))
        {
        	char text1[50] = {"无效的输入值" }, text2[50] = {"输入错误" };
			MessageBox(GetHWnd(), text1, text2, 0);
			return ;
		}
		x[i] = strtod(inputBuffer,NULL);
    }
    double centralMoment_x = calculateCentralMoment(x, size, k);
    // 打开文件以写入数据
    FILE *file = fopen("kcm_output.txt", "a");
    if (file == NULL) {
        return ;
    }
    		 
    // 将数组的内容写入文件
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%lf ", x[i]);
    }
    //将k值写入文件
    fprintf(file, "\n%d ", k);
    // 将结果写入文件
    fprintf(file, "\n%lf\n", centralMoment_x);
    // 关闭文件
    fclose(file);
    
    //system("pause");
    
    
    SetWorkingImage(&buffer);  // 设置当前绘图设备为缓冲区
    cleardevice();  // 清空缓冲区
    setbkcolor(RGB(23,44,60));    // 设置背景色

   	// 绘制左侧功能按钮
    drawLeft();
    
    //输出结果 
    settextstyle(18, 0, _T("仿宋"));
    sprintf(str, "%lf", centralMoment_x);
    outtextxy(300, 180, "结果是：");
    outtextxy(300, 200, str);
    		
    //画一个返回按钮
	drawButton(ret_btn, RET_BUTTON_WIDTH, 30);
	// 设置绘图目标为绘图窗口
	SetWorkingImage();
	//将 buffer显示在绘图窗口中
    putimage(0, 0, &buffer);  
			
    bool flag = true;
    while (flag) 
	{
		while (MouseHit())
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{//左键按下
				if (m.x >= 220 && m.x <= 320 && m.y>=10 &&m.y<=40)
				{
					ret_btn.status = 1;
					flag = false;
				}
			}
			else if (m.uMsg == WM_LBUTTONUP)
			{//左键弹起
			//重置按钮状态
				setUpButton(0, -1);
			}
				
		}
	} 
	}
	}


}

void handle_lR(MOUSEMSG m)// 处理k阶中心矩界面
{
	if (m.x >= 450 && m.x < 630) {
	if (m.y >= 470 && m.y <= 500) {
		//calculateCentralMoment  
		// 在窗口中显示输入框
    char inputBuffer[256];//存储输入框 
	InputBox(inputBuffer, 256, "输入x与y数组的大小 (max 30): ");
    double x[SIZE] = {0};
    double y[SIZE] = {0};
    char str[SIZE]; 
    //整数判断 
	if(!isInteger(inputBuffer))
	{
		char text1[50] = {"数组大小需为整数" }, text2[50] = {"输入错误" };
			MessageBox(GetHWnd(), text1, text2, 0);
			return ;
	}
	int size = atoi(inputBuffer);
	// 数组大小判断 
    if(size<0||size>30)
    {
    	char text1[50] = {"请输入正确的数组大小" }, text2[50] = {"输入错误" };
		MessageBox(GetHWnd(), text1, text2, 0);
		return ;
	}
    
    

    //printf("请输入x,y的值:\n");
    for (int i = 0; i < size; i++) 
	{
		sprintf(str, "请输入x的第%d个数", i+1);
        InputBox(inputBuffer, 256, str);
        if(!isInteger(inputBuffer)&&!isFloat(inputBuffer))
        {
        	char text1[50] = {"无效的输入值" }, text2[50] = {"输入错误" };
			MessageBox(GetHWnd(), text1, text2, 0);
			return ;
		}
        x[i] = strtod(inputBuffer,NULL);
        
        sprintf(str, "请输入y的第%d个数", i+1);
        InputBox(inputBuffer, 256, str);
        if(!isInteger(inputBuffer)&&!isFloat(inputBuffer))
        {
        	char text1[50] = {"无效的输入值" }, text2[50] = {"输入错误" };
			MessageBox(GetHWnd(), text1, text2, 0);
			return ;
		}
        y[i] = strtod(inputBuffer,NULL);
    }
    
    double slope, intercept;
    linearRegression(x, y, size, &slope, &intercept);
    
    
    //system("pause");
    
    
    SetWorkingImage(&buffer);  // 设置当前绘图设备为缓冲区
    cleardevice();  // 清空缓冲区
    setbkcolor(RGB(23,44,60));    // 设置背景色

   	// 绘制左侧功能按钮
    drawLeft();
    
    //输出结果 
    settextstyle(18, 0, _T("仿宋"));
    outtextxy(300, 180, "拟合得到的斜率为：");
    sprintf(str, "%lf", slope);
    outtextxy(300, 200, str);
    outtextxy(300, 220, "拟合得到的截距为：");
    sprintf(str, "%lf", intercept);
    outtextxy(300, 240, str);
    
    // 打开文件以写入数据
    FILE *file = fopen("lr_output.txt", "a");
    if (file == NULL) {
        return ;
    }
    		 
    // 将数组的内容写入文件
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%lf ", x[i]);
    }
    fprintf(file, "\n");
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%lf ", y[i]);
    }
    // 将结果写入文件
    fprintf(file, "\n%lf", slope);
    fprintf(file, "\n%lf\n", intercept);
    // 关闭文件
    fclose(file);
    		
    //画一个返回按钮
	drawButton(ret_btn, RET_BUTTON_WIDTH, 30);
	// 设置绘图目标为绘图窗口
	SetWorkingImage();
	//将 buffer显示在绘图窗口中
    putimage(0, 0, &buffer);  
			
    bool flag = true;
    while (flag) 
	{
		while (MouseHit())
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{//左键按下
				if (m.x >= 220 && m.x <= 320 && m.y>=10 &&m.y<=40)
				{
					ret_btn.status = 1;
					flag = false;
				}
			}
		}
		setUpButton(0, -1);
		
	} 
	}
	}


}

void handle_his(MOUSEMSG m)
{
	SetWorkingImage(&buffer);  // 设置当前绘图设备为缓冲区
    cleardevice();  // 清空缓冲区
    setbkcolor(RGB(23,44,60));    // 设置背景色

   	// 绘制左侧功能按钮
    drawLeft();
    char str[SIZE];
	if(m.x>=200&&m.x<=380&&m.y>=470&&m.y<=500)
	{
		//平均值历史记录按钮
		his_btn[0].status = 1;
		FILE *file = fopen("avg_output.txt", "r");
    	if (file == NULL)
    	{
    		char text1[50] = {"找不到历史记录文件！" }, text2[50] = {"文件错误" };
			MessageBox(GetHWnd(), text1, text2, 0);
    		return ;
		}
    

    	// 文件的结构是每行包含一些浮点数，然后是一个平均值
    	int begin_h = 70;
    	char line[500]; 
    	bool line_avg = false;//偶数行是结果 
    	// 逐行读取文件内容
    	while (fgets(line, sizeof(line), file) != NULL) {
    		settextstyle(18, 0, _T("仿宋"));
    		if(!line_avg){
    			outtextxy(220, begin_h, "输入：");
    		}
    		else
    		{
    			outtextxy(220, begin_h, "平均值计算结果：");
    			
			}
			begin_h+=20;
			line_avg = !line_avg;
    		outtextxy(220, begin_h, line);
    		begin_h+=20;
    		if(begin_h>=windows_H)
    		{
    			begin_h = 0;
			}
		} 
    	fclose(file);
	} 
	else if(m.x>=400&&m.x<=580&&m.y>=470&&m.y<=500)
	{
		//k阶原点矩
		his_btn[1].status = 1;
		//k阶原点矩历史记录按钮
		FILE *file = fopen("krm_output.txt", "r");
    	if (file == NULL)
    	{
    		char text1[50] = {"找不到历史记录文件！" }, text2[50] = {"文件错误" };
			MessageBox(GetHWnd(), text1, text2, 0);
    		return ;
		}
    

    	// 文件的结构是第一行：输入浮点数，第二行：k，第三行：结果 
    	int begin_h = 70;
    	char line[500];  
    	int index = 0;//标记读到什么内容 
		 
    	// 逐行读取文件内容
    	while (fgets(line, sizeof(line), file) != NULL) {
    		settextstyle(18, 0, _T("仿宋"));
    		if(index%3==0){
    			outtextxy(220, begin_h, "输入：");
    		}
    		else if(index%3==1)
    		{
    			outtextxy(220, begin_h, "k：");
			}
			else
			{
				outtextxy(220, begin_h, "k阶原点矩计算结果：");
			}
			index ++;
			begin_h+=20;
    		outtextxy(220, begin_h, line);
    		begin_h+=20;
    		if(begin_h>=windows_H)
    		{
    			begin_h = 0;
			}
		} 
    	fclose(file);	 
	} 
	else if(m.x>=600&&m.x<=780&&m.y>=470&&m.y<=500)
	{
		//k阶中心矩
		his_btn[2].status = 1;
		//k阶中心矩历史记录按钮
		FILE *file = fopen("kcm_output.txt", "r");
    	if (file == NULL)
    	{
    		char text1[50] = {"找不到历史记录文件！" }, text2[50] = {"文件错误" };
			MessageBox(GetHWnd(), text1, text2, 0);
    		return ;
		}
    

    	// 文件的结构是第一行：输入浮点数，第二行：k，第三行：结果 
    	int begin_h = 70;
    	char line[500]; 
    	int index = 0;//标记读到什么内容 
		 
    	// 逐行读取文件内容
    	while (fgets(line, sizeof(line), file) != NULL) {
    		settextstyle(18, 0, _T("仿宋"));
    		if(index%3==0){
    			outtextxy(220, begin_h, "输入：");
    		}
    		else if(index%3==1)
    		{
    			outtextxy(220, begin_h, "k：");
			}
			else
			{
				outtextxy(220, begin_h, "k阶原点矩计算结果：");
			}
			index ++;
			begin_h+=20;
    		outtextxy(220, begin_h, line);
    		begin_h+=20;
    		if(begin_h>=windows_H)
    		{
    			begin_h = 0;
			}
		} 
    	fclose(file);	 
		
	}
	else if(m.x>=800&&m.x<=980&&m.y>=470&&m.y<=500)
	{
		//最小二乘法线性拟合
		his_btn[3].status = 1;
		//k阶中心矩历史记录按钮
		FILE *file = fopen("lr_output.txt", "r");
    	if (file == NULL)
    	{
    		char text1[50] = {"找不到历史记录文件！" }, text2[50] = {"文件错误" };
			MessageBox(GetHWnd(), text1, text2, 0);
    		return ;
		}
    

    	// 文件的结构是第一行：x，第二行：y,第三行：斜率，第四行：截距 
    	int begin_h = 70;
    	char line[500]; 
    	int index = 0;//标记读到什么内容 
		 
    	// 逐行读取文件内容
    	while (fgets(line, sizeof(line), file) != NULL) {
    		settextstyle(18, 0, _T("仿宋"));
    		if(index%4==0){
    			outtextxy(220, begin_h, "x：");
    		}
    		else if(index%4==1)
    		{
    			outtextxy(220, begin_h, "y：");
			}
    		else if(index%4==2)
    		{
    			outtextxy(220, begin_h, "slope：");
			}
			else if(index%4==3)
			{
				outtextxy(220, begin_h, "intercept：");
			}
			index ++;
			begin_h+=20;
    		outtextxy(220, begin_h, line);
    		begin_h+=20;
    		if(begin_h>=windows_H)
    		{
    			begin_h = 0;
			}
		} 
    	fclose(file);	 
		
	}
    		
    //画一个返回按钮
	drawButton(ret_btn, RET_BUTTON_WIDTH, 30);
	// 设置绘图目标为绘图窗口
	SetWorkingImage();
	//将 buffer显示在绘图窗口中
    putimage(0, 0, &buffer);  
			
    bool flag = true;
    while (flag) 
	{
		while (MouseHit())
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{//左键按下
				if (m.x >= 220 && m.x <= 320 && m.y>=10 &&m.y<=40)
				{
					ret_btn.status = 1;
					flag = false;
				}
			}
			/*
			else if (m.uMsg == WM_LBUTTONUP)
			{//左键弹起
			//重置按钮状态
				setUpButton(0, -1);
			}*/
			
			
		}
		setUpButton(0, -1);
		
	} 
	

	
	
	
}

 







