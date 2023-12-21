#include "data_analysis.h"

//��С���� 
#define windows_W 1000
#define windows_H 600

#define SIZE 30

IMAGE buffer(windows_W, windows_H);

const int BUTTON_WIDTH = 180;//��ť��� 
const int BUTTON_HEIGHT = 26;//��ť�߶� 
const int RET_BUTTON_WIDTH = 100;//���ذ�ť��� 


typedef struct Button {
    int x, y;  // ����
    char str[50];  // ��ť����
    COLORREF color[2];  // ��ť��ɫ ������״̬�İ�ť��ɫ 
    int status;// ��ť��״̬ 

} button;


//��๦�ܵ�����İ�ť 
//�����ҵĺ�����Button�Ľṹ�嶨��һ�� 
int btnNum = 6;// ��๦�ܵ�����İ�ť���� 
button btn[6] = {
	
    {0, 0, "ƽ��ֵ", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {0, 114, "k��ԭ���", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {0, 228, "k�����ľ�", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {0, 342, "��С���˷��������", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {0, 456, "�鿴��ʷ��¼", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
	{0, 570, "�˳�", {RGB(3,101,100), RGB(204, 213, 240)}, 0}               
};
//��ʷ��¼�İ�ť 
button his_btn[4] = {
	
    {200, 470, "ƽ��ֵ", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {400, 470, "k��ԭ���", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {600, 470, "k�����ľ�", {RGB(3,101,100), RGB(204, 213, 240)}, 0},
    {800, 470, "��С���˷��������", {RGB(3,101,100), RGB(204, 213, 240)}, 0}      
};

//���밴ť���������湲�� 
button input_btn = {450 ,470,"��ʼ",{RGB(3,101,100), RGB(204, 213, 240)}, 0};

//���ذ�ť���������湲�� 
button ret_btn = {220,10,"����",{RGB(3,101,100), RGB(204, 213, 240)}, 0}; 
 






// drawButton �������ڻ��ư�ť
// ������
//   - BTN: ��ʾ��ť�Ľṹ�壬������ť�����ꡢ�ı����ݡ���ɫ��״̬����Ϣ
//   - width: ��ť�Ŀ�ȣ�Ĭ��ֵΪ 160
//   - height: ��ť�ĸ߶ȣ�Ĭ��ֵΪ 30
void drawButton(button BTN, int width = 180, int height = 30) {
    setlinecolor(WHITE);  // ���ñ߿���ɫΪ��ɫ
    setfillcolor(BTN.color[BTN.status]);  // ���������ɫΪ��ť�ĵ�ǰ״̬��ɫ

    int x = BTN.x, y = BTN.y;  // ��ȡ��ť������
    fillroundrect(x, y, x + width, y + height, 10, 10);  // ���ƴ�Բ�ǵľ��ΰ�ť

    settextcolor(WHITE);  // �����ı���ɫΪ��ɫ 
    settextstyle(16, 0, _T("Consolas"));  // �����ı�����ʹ�С
    outtextxy(x + 28, y + 7, BTN.str);  // �ڰ�ť���Ļ����ı�
}

// drawLeft �������ڻ�����ߵĹ��ܿ�  ��600 �� 180 
void drawLeft() {
	//���õײ㱳��
	setfillcolor(RGB(39, 72, 98));
	// �����Σ���Ϊ�������ı���������(0,0) ����(180,600)  
	fillrectangle(0, 0, 180, 600);
	//������ť���飬���ư�ť 
	for (int i = 0; i < btnNum; i++) {
		drawButton(btn[i], BUTTON_WIDTH, BUTTON_HEIGHT);
	}
}



// drawView �������ڻ��ƽ������Ҫ��Ϣ
// ������
//   - status: ��ʾ��ǰ�����״̬�����ݲ�ͬ״̬���Ʋ�ͬ����Ϣ
void drawView(int status) {
    SetWorkingImage(&buffer);  // ���õ�ǰ��ͼ�豸Ϊ������
    cleardevice();  // ��ջ�����
    setbkmode(TRANSPARENT);  // ���ñ������ģʽΪ͸��
    setbkcolor(RGB(23,44,60));    // ���ñ�����ɫ 
    drawLeft();// ������๦�ܿ� 
    
    // ����״̬�����Ҳ���Ϣ
    switch (status) {
    	case 0:
			drawMainInfo();
			break; 
        case 1:
            //printf("����ƽ��ֵ"); 
            drawAVGInfo();
            break;
        case 2:
            //printf("����k��ԭ���");  
            drawKRMInfo();
            break;
        case 3:
            //printf("����k�����ľ�");  
            drawKCMInfo();
            break;
        case 4:
            //printf("��С���˷��������"); 
            drawlRInfo();
            break;
        case 5:
            //printf("�鿴��ʷ��¼");  
            drawHistory();
            break;
    	case 6:
    		break;
		}

    // ���û�ͼĿ��Ϊ��ͼ����
	SetWorkingImage();
	//�� buffer��ʾ�ڻ�ͼ������
    putimage(0, 0, &buffer);  
}


// setUpButton �����������ð�ť��״̬
// ������
//   - index: ָ����Ҫ����״̬�İ�ť����
//   - status: ָ����ť��״̬��0 ��ʾ����״̬��1 ��ʾ����״̬��-1 ��ʾȫ����ť�ָ�������״̬
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
//������ 
void drawMainInfo() {
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 64;
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	outtextxy(300, 50, "�������ݷ�����");


	settextstyle(18, 0, _T("����"));
	outtextxy(300, 160, _T("�����ݷ���������4������ģ�飬����๦������ʾ��������ʹ��˵����"));
	outtextxy(300, 200, _T("1��ƽ��ֵ������"));
	outtextxy(300, 220, _T("2������k��ԭ���"));
	outtextxy(300, 240, _T("3������k�����ľ�"));
	outtextxy(300, 260, _T("4����С���˷��������"));
	outtextxy(300, 280, _T("5���˳�"));
	
}


//����ƽ��ֵ��������  
void drawAVGInfo()
{	
	settextstyle(40, 0, _T("����"));
	outtextxy(400, 110, _T("ƽ��ֵ������"));
	settextstyle(20, 0, _T("����"));
	outtextxy(400, 180, _T("���ܣ�����һ������ƽ��ֵ"));
	outtextxy(400, 220, _T("���룺1.�����С 2. ����Ԫ�أ���������"));
	//����һ����ť���㰴ť�ſ�ʼ��������
	drawButton(input_btn, BUTTON_WIDTH, 30);//300 240
} 

//����k��ԭ��صĵ������� Raw Moment
void drawKRMInfo()
{
	settextstyle(40, 0, _T("����"));
	outtextxy(400, 110, _T("k��ԭ��ؼ�����"));
	settextstyle(20, 0, _T("����"));
	outtextxy(400, 180, _T("���ܣ�����һ������k��ԭ���"));
	outtextxy(400, 220, _T("���룺1.�����С 2.kֵ 3. ����Ԫ�أ���������"));
	//����һ����ť���㰴ť�ſ�ʼ��������
	drawButton(input_btn, BUTTON_WIDTH, 30);//300 240
	
} 


//����k�����ľصĵ������� Central Moment
void drawKCMInfo()
{
	settextstyle(40, 0, _T("����"));
	outtextxy(400, 110, _T("k�����ľؼ�����"));
	settextstyle(20, 0, _T("����"));
	outtextxy(400, 180, _T("���ܣ�����һ������k�����ľ�"));
	outtextxy(400, 220, _T("���룺1.�����С 2.kֵ 3. ����Ԫ�أ���������"));
	//����һ����ť���㰴ť�ſ�ʼ��������
	drawButton(input_btn, BUTTON_WIDTH, 30);//300 240
	
} 


//������С���˷�������ϵ�б�ʺͽؾ�
void drawlRInfo()
{
	settextstyle(40, 0, _T("����"));
	outtextxy(400, 110, _T("��С���˷��������"));
	settextstyle(20, 0, _T("����"));
	outtextxy(400, 180, _T("���ܣ�������С���˷�������ϵ�б�ʺͽؾ�"));
	outtextxy(400, 220, _T("���룺1.�����С(x��y��С���) 2. x��y�����Ԫ�أ���������"));
	//����һ����ť���㰴ť�ſ�ʼ��������
	drawButton(input_btn, BUTTON_WIDTH, 30);//300 240
	
} 

void drawHistory()
{	
	settextstyle(40, 0, _T("����"));
	outtextxy(400, 110, _T("��ʷ��¼"));
    for(int i=0;i<4;i++)
	{
		drawButton(his_btn[i], BUTTON_WIDTH, 30);//300 240	
	} 
} 



//��������ť����
void menBtn(MOUSEMSG m, int* status) {
	if (m.y >= 0 && m.y <= 26) {//����ƽ��ֵ 
		setUpButton(0, 1);
		*status = 1;
	}
	else if (m.y >= 114 && m.y <= 140) {//����k��ԭ��� 
		setUpButton(1, 1);
		*status = 2;
	}
	else if (m.y >= 228 && m.y <= 254) {//����k�����ľ� 
		setUpButton(2, 1);
		*status = 3;
	}
	else if (m.y >= 342 && m.y <= 368) {//��С���˷�������� 
		setUpButton(3, 1);
		*status = 4;
	}
	else if (m.y >= 456 && m.y <= 482) {//�鿴��ʷ��¼ 
		setUpButton(4, 1);
		*status = 5;
	}
	else if (m.y >= 570 && m.y <= 596) {//�˳� 
		setUpButton(5, 1);
		closegraph();
		exit(0);
	}
	
}

void handle_AVG(MOUSEMSG m)
{
	//���������Χ�ڱ�ʾ����䵽�����벿�ֵ����� 
	if (m.x >= 450 && m.x < 630) {
		if (m.y >= 470 && m.y <= 500) {
			input_btn.status = 1;
			// �ڴ�������ʾ�����
    		char inputBuffer[256];//�洢����� 
    		//printf("��������Ĵ�С (max 30): ");
    		//scanf("%d", &size);
			InputBox(inputBuffer,256, "��������Ĵ�С (max 30): ");
			//�ж����������ǲ��ǿ� 
			if(isEmpty(inputBuffer))
			{
				char text1[50] = {"�������ݲ���Ϊ��" }, text2[50] = {"�������" };
				MessageBox(GetHWnd(), text1, text2, 0);
				return ;
			}
    		double x[SIZE] = {0};
    		char str[SIZE];
    		
    		int size = atoi(inputBuffer);
    		//�����ж�
    		if(!isInteger(inputBuffer))
			{
				char text1[50] = {"�����С��Ϊ����" }, text2[50] = {"�������" };
				MessageBox(GetHWnd(), text1, text2, 0);
				return ;
			}
			// �����С�ж� 
    		if(size<0||size>30)
    		{
    			char text1[50] = {"��������ȷ�������С" }, text2[50] = {"�������" };
				MessageBox(GetHWnd(), text1, text2, 0);
				return ;
			}
    		
    		for (int i = 0; i < size; i++) {
    			sprintf(str, "�������%d����", i+1);
        		InputBox(inputBuffer,256,str);
        		if(!isInteger(inputBuffer)&&!isFloat(inputBuffer))
        		{
        			char text1[50] = {"��Ч������ֵ" }, text2[50] = {"�������" };
					MessageBox(GetHWnd(), text1, text2, 0);
					return ;
				}
				x[i] = strtod(inputBuffer,NULL);
    		}
    		
    		setfillcolor(RGB(204, 213, 240));
			fillrectangle(180, 0, 1000, 800);
			

    		double mean_x = calculateMean(x, size);
    		//system("pause");
    		
    		
    		SetWorkingImage(&buffer);  // ���õ�ǰ��ͼ�豸Ϊ������
    		cleardevice();  // ��ջ�����
    		setbkcolor(RGB(23,44,60));    // ���ñ���ɫ

   			// ������๦�ܰ�ť
    		drawLeft();
    
    		//������ 
    		
    		settextstyle(18, 0, _T("����"));
    		int begin_h = 160;
    		outtextxy(300, begin_h, "����Ϊ��");
    		int begin_w = 300;
    		int off = 0; 
    		begin_h += 20;
    		for (int i = 0; i < size; i++) {
				sprintf(str, "%lf", x[i]);
				outtextxy(begin_w+off, begin_h, str);
				off += 18 * strlen(str);
				//ÿ�ŷ��ĸ��� 
				if(i%4==3)
				{
					begin_w = 300;
					off = 0;
					begin_h += 20;
				} 
    		}
    		begin_h += 20;
    		sprintf(str, "%lf", mean_x);
    		outtextxy(300, begin_h, "ƽ�����������ǣ�");
    		begin_h += 20;
    		outtextxy(300, begin_h , str);
			// ���ļ���д������
    		FILE *file = fopen("avg_output.txt", "a");
    		if (file == NULL) {
        		return ;
    		}
    		// �����������д���ļ�
    		for (int i = 0; i < size; ++i) {
        		fprintf(file, "%lf ", x[i]);
    		}

    		// ��ƽ��ֵд���ļ�
    		fprintf(file, "\n%lf\n", mean_x);
    		// �ر��ļ�
    		fclose(file);
    		
    		//��һ�����ذ�ť
			drawButton(ret_btn, RET_BUTTON_WIDTH, 30);
			// ���û�ͼĿ��Ϊ��ͼ����
			SetWorkingImage();
			//�� buffer��ʾ�ڻ�ͼ������
    		putimage(0, 0, &buffer);  
			
    		bool flag = true;
    		while (flag) 
			{
				while (MouseHit())
				{
					m = GetMouseMsg();
					if (m.uMsg == WM_LBUTTONDOWN)
					{//�������
						if (m.x >= 220 && m.x <= 320 && m.y>=10 &&m.y<=40)
						{
							ret_btn.status = 1;
							flag = false;
					}
					}
					else if (m.uMsg == WM_LBUTTONUP)
					{//�������
					//���ð�ť״̬
						setUpButton(0, -1);
					}
				
				}
			} 
		}
	}
	
}





void handle_KRM(MOUSEMSG m)//����k��ԭ��ؽ��� 
{
	if (m.x >= 450 && m.x < 630) {
		if (m.y >= 470 && m.y <= 500) {
			input_btn.status = 1;
			//calculateRawMoment(double data[], int size, int k)  
			// �ڴ�������ʾ�����
    		char inputBuffer[256];//�洢����� 
			double x[SIZE] = {0};
    		char str[SIZE];
    		
			InputBox(inputBuffer, 256, "��������Ĵ�С (max 30): ");
    		//�����ж� 
			if(!isInteger(inputBuffer))
			{
				char text1[50] = {"�����С��Ϊ����" }, text2[50] = {"�������" };
				MessageBox(GetHWnd(), text1, text2, 0);
				return ;
			}
			int size = atoi(inputBuffer);
			// �����С�ж� 
    		if(size<0||size>30)
    		{
    			char text1[50] = {"��������ȷ�������С" }, text2[50] = {"�������" };
				MessageBox(GetHWnd(), text1, text2, 0);
				return ;
			}
			
    
    		InputBox(inputBuffer, 256, "����kֵ: ");
    		//�����ж� 
			if(!isInteger(inputBuffer))
			{
				char text1[50] = {"kֵ��Ϊ����" }, text2[50] = {"�������" };
				MessageBox(GetHWnd(), text1, text2, 0);
				return ;
			}
    		int k = atoi(inputBuffer);

    		//printf("������x,y��ֵ:\n");
    		for (int i = 0; i < size; i++) {
    			sprintf(str, "�������%d����", i+1);
        		InputBox(inputBuffer, 256, str);
        		if(!isInteger(inputBuffer)&&!isFloat(inputBuffer))
        		{
        			char text1[50] = {"��Ч������ֵ" }, text2[50] = {"�������" };
					MessageBox(GetHWnd(), text1, text2, 0);
					return ;
				}
				x[i] = strtod(inputBuffer,NULL);
    		}
 
   			double rawMoment_x = calculateRawMoment(x, size, k);
   			
   			// ���ļ���д������
    		FILE *file = fopen("krm_output.txt", "a");
    		if (file == NULL) {
        		return ;
    		}
    		 
    		// �����������д���ļ�
    		for (int i = 0; i < size; ++i) {
        		fprintf(file, "%lf ", x[i]);
    		}
    		//��kֵд���ļ�
    		fprintf(file, "\n%d ", k);
    		// �����д���ļ�
    		fprintf(file, "\n%lf\n", rawMoment_x);
    		// �ر��ļ�
    		fclose(file);
   			
   			SetWorkingImage(&buffer);  // ���õ�ǰ��ͼ�豸Ϊ������
    		cleardevice();  // ��ջ�����

    	
    		setbkcolor(RGB(23,44,60));    // ���ñ���ɫ

   			// ������๦�ܰ�ť
    		drawLeft();
    
    		//������ 
    		settextstyle(18, 0, _T("����"));
    		sprintf(str, "%lf", rawMoment_x);
    		outtextxy(300, 180, "����ǣ�");
    		outtextxy(300, 200, str);
    		
    		//��һ�����ذ�ť
			drawButton(ret_btn, RET_BUTTON_WIDTH, 30);
			// ���û�ͼĿ��Ϊ��ͼ����
			SetWorkingImage();
			//�� buffer��ʾ�ڻ�ͼ������
    		putimage(0, 0, &buffer);  
			
    		bool flag = true;
    		while (flag) {
				while (MouseHit()) {
				m = GetMouseMsg();
				if (m.uMsg == WM_LBUTTONDOWN)
				{//�������
					if (m.x >= 220 && m.x <= 320 && m.y>=10 &&m.y<=40) {
					ret_btn.status = 1;
					flag = false;
					}
				}
				else if (m.uMsg == WM_LBUTTONUP)
				{//�������
				//���ð�ť״̬
				setUpButton(0, -1);
				}
				
			}
			} 
    	
			}
	
}}

void handle_KCM(MOUSEMSG m)// ����k�����ľؽ���
{
	if (m.x >= 450 && m.x < 630) {
	if (m.y >= 470 && m.y <= 500) {
		//calculateCentralMoment  
		// �ڴ�������ʾ�����
    char inputBuffer[256];//�洢����� 
	InputBox(inputBuffer, 256, "��������Ĵ�С (max 30): ");
    double x[SIZE] = {0};
    char str[SIZE];
    
    //�����ж� 
	if(!isInteger(inputBuffer))
	{
		char text1[50] = {"�����С��Ϊ����" }, text2[50] = {"�������" };
			MessageBox(GetHWnd(), text1, text2, 0);
			return ;
	}
	int size = atoi(inputBuffer);
	// �����С�ж� 
    if(size<0||size>30)
    {
    	char text1[50] = {"��������ȷ�������С" }, text2[50] = {"�������" };
		MessageBox(GetHWnd(), text1, text2, 0);
		return ;
	}
    
    InputBox(inputBuffer, 256, "����kֵ: ");
    //�����ж� 
	if(!isInteger(inputBuffer))
	{
		char text1[50] = {"kֵ��Ϊ����" }, text2[50] = {"�������" };
		MessageBox(GetHWnd(), text1, text2, 0);
		return ;
	}
    int k = atoi(inputBuffer);

    //printf("������x,y��ֵ:\n");
    for (int i = 0; i < size; i++) 
	{
		sprintf(str, "�������%d����", i+1);
        InputBox(inputBuffer, 256, str);
		if(!isInteger(inputBuffer)&&!isFloat(inputBuffer))
        {
        	char text1[50] = {"��Ч������ֵ" }, text2[50] = {"�������" };
			MessageBox(GetHWnd(), text1, text2, 0);
			return ;
		}
		x[i] = strtod(inputBuffer,NULL);
    }
    double centralMoment_x = calculateCentralMoment(x, size, k);
    // ���ļ���д������
    FILE *file = fopen("kcm_output.txt", "a");
    if (file == NULL) {
        return ;
    }
    		 
    // �����������д���ļ�
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%lf ", x[i]);
    }
    //��kֵд���ļ�
    fprintf(file, "\n%d ", k);
    // �����д���ļ�
    fprintf(file, "\n%lf\n", centralMoment_x);
    // �ر��ļ�
    fclose(file);
    
    //system("pause");
    
    
    SetWorkingImage(&buffer);  // ���õ�ǰ��ͼ�豸Ϊ������
    cleardevice();  // ��ջ�����
    setbkcolor(RGB(23,44,60));    // ���ñ���ɫ

   	// ������๦�ܰ�ť
    drawLeft();
    
    //������ 
    settextstyle(18, 0, _T("����"));
    sprintf(str, "%lf", centralMoment_x);
    outtextxy(300, 180, "����ǣ�");
    outtextxy(300, 200, str);
    		
    //��һ�����ذ�ť
	drawButton(ret_btn, RET_BUTTON_WIDTH, 30);
	// ���û�ͼĿ��Ϊ��ͼ����
	SetWorkingImage();
	//�� buffer��ʾ�ڻ�ͼ������
    putimage(0, 0, &buffer);  
			
    bool flag = true;
    while (flag) 
	{
		while (MouseHit())
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{//�������
				if (m.x >= 220 && m.x <= 320 && m.y>=10 &&m.y<=40)
				{
					ret_btn.status = 1;
					flag = false;
				}
			}
			else if (m.uMsg == WM_LBUTTONUP)
			{//�������
			//���ð�ť״̬
				setUpButton(0, -1);
			}
				
		}
	} 
	}
	}


}

void handle_lR(MOUSEMSG m)// ����k�����ľؽ���
{
	if (m.x >= 450 && m.x < 630) {
	if (m.y >= 470 && m.y <= 500) {
		//calculateCentralMoment  
		// �ڴ�������ʾ�����
    char inputBuffer[256];//�洢����� 
	InputBox(inputBuffer, 256, "����x��y����Ĵ�С (max 30): ");
    double x[SIZE] = {0};
    double y[SIZE] = {0};
    char str[SIZE]; 
    //�����ж� 
	if(!isInteger(inputBuffer))
	{
		char text1[50] = {"�����С��Ϊ����" }, text2[50] = {"�������" };
			MessageBox(GetHWnd(), text1, text2, 0);
			return ;
	}
	int size = atoi(inputBuffer);
	// �����С�ж� 
    if(size<0||size>30)
    {
    	char text1[50] = {"��������ȷ�������С" }, text2[50] = {"�������" };
		MessageBox(GetHWnd(), text1, text2, 0);
		return ;
	}
    
    

    //printf("������x,y��ֵ:\n");
    for (int i = 0; i < size; i++) 
	{
		sprintf(str, "������x�ĵ�%d����", i+1);
        InputBox(inputBuffer, 256, str);
        if(!isInteger(inputBuffer)&&!isFloat(inputBuffer))
        {
        	char text1[50] = {"��Ч������ֵ" }, text2[50] = {"�������" };
			MessageBox(GetHWnd(), text1, text2, 0);
			return ;
		}
        x[i] = strtod(inputBuffer,NULL);
        
        sprintf(str, "������y�ĵ�%d����", i+1);
        InputBox(inputBuffer, 256, str);
        if(!isInteger(inputBuffer)&&!isFloat(inputBuffer))
        {
        	char text1[50] = {"��Ч������ֵ" }, text2[50] = {"�������" };
			MessageBox(GetHWnd(), text1, text2, 0);
			return ;
		}
        y[i] = strtod(inputBuffer,NULL);
    }
    
    double slope, intercept;
    linearRegression(x, y, size, &slope, &intercept);
    
    
    //system("pause");
    
    
    SetWorkingImage(&buffer);  // ���õ�ǰ��ͼ�豸Ϊ������
    cleardevice();  // ��ջ�����
    setbkcolor(RGB(23,44,60));    // ���ñ���ɫ

   	// ������๦�ܰ�ť
    drawLeft();
    
    //������ 
    settextstyle(18, 0, _T("����"));
    outtextxy(300, 180, "��ϵõ���б��Ϊ��");
    sprintf(str, "%lf", slope);
    outtextxy(300, 200, str);
    outtextxy(300, 220, "��ϵõ��Ľؾ�Ϊ��");
    sprintf(str, "%lf", intercept);
    outtextxy(300, 240, str);
    
    // ���ļ���д������
    FILE *file = fopen("lr_output.txt", "a");
    if (file == NULL) {
        return ;
    }
    		 
    // �����������д���ļ�
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%lf ", x[i]);
    }
    fprintf(file, "\n");
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%lf ", y[i]);
    }
    // �����д���ļ�
    fprintf(file, "\n%lf", slope);
    fprintf(file, "\n%lf\n", intercept);
    // �ر��ļ�
    fclose(file);
    		
    //��һ�����ذ�ť
	drawButton(ret_btn, RET_BUTTON_WIDTH, 30);
	// ���û�ͼĿ��Ϊ��ͼ����
	SetWorkingImage();
	//�� buffer��ʾ�ڻ�ͼ������
    putimage(0, 0, &buffer);  
			
    bool flag = true;
    while (flag) 
	{
		while (MouseHit())
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{//�������
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
	SetWorkingImage(&buffer);  // ���õ�ǰ��ͼ�豸Ϊ������
    cleardevice();  // ��ջ�����
    setbkcolor(RGB(23,44,60));    // ���ñ���ɫ

   	// ������๦�ܰ�ť
    drawLeft();
    char str[SIZE];
	if(m.x>=200&&m.x<=380&&m.y>=470&&m.y<=500)
	{
		//ƽ��ֵ��ʷ��¼��ť
		his_btn[0].status = 1;
		FILE *file = fopen("avg_output.txt", "r");
    	if (file == NULL)
    	{
    		char text1[50] = {"�Ҳ�����ʷ��¼�ļ���" }, text2[50] = {"�ļ�����" };
			MessageBox(GetHWnd(), text1, text2, 0);
    		return ;
		}
    

    	// �ļ��Ľṹ��ÿ�а���һЩ��������Ȼ����һ��ƽ��ֵ
    	int begin_h = 70;
    	char line[500]; 
    	bool line_avg = false;//ż�����ǽ�� 
    	// ���ж�ȡ�ļ�����
    	while (fgets(line, sizeof(line), file) != NULL) {
    		settextstyle(18, 0, _T("����"));
    		if(!line_avg){
    			outtextxy(220, begin_h, "���룺");
    		}
    		else
    		{
    			outtextxy(220, begin_h, "ƽ��ֵ��������");
    			
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
		//k��ԭ���
		his_btn[1].status = 1;
		//k��ԭ�����ʷ��¼��ť
		FILE *file = fopen("krm_output.txt", "r");
    	if (file == NULL)
    	{
    		char text1[50] = {"�Ҳ�����ʷ��¼�ļ���" }, text2[50] = {"�ļ�����" };
			MessageBox(GetHWnd(), text1, text2, 0);
    		return ;
		}
    

    	// �ļ��Ľṹ�ǵ�һ�У����븡�������ڶ��У�k�������У���� 
    	int begin_h = 70;
    	char line[500];  
    	int index = 0;//��Ƕ���ʲô���� 
		 
    	// ���ж�ȡ�ļ�����
    	while (fgets(line, sizeof(line), file) != NULL) {
    		settextstyle(18, 0, _T("����"));
    		if(index%3==0){
    			outtextxy(220, begin_h, "���룺");
    		}
    		else if(index%3==1)
    		{
    			outtextxy(220, begin_h, "k��");
			}
			else
			{
				outtextxy(220, begin_h, "k��ԭ��ؼ�������");
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
		//k�����ľ�
		his_btn[2].status = 1;
		//k�����ľ���ʷ��¼��ť
		FILE *file = fopen("kcm_output.txt", "r");
    	if (file == NULL)
    	{
    		char text1[50] = {"�Ҳ�����ʷ��¼�ļ���" }, text2[50] = {"�ļ�����" };
			MessageBox(GetHWnd(), text1, text2, 0);
    		return ;
		}
    

    	// �ļ��Ľṹ�ǵ�һ�У����븡�������ڶ��У�k�������У���� 
    	int begin_h = 70;
    	char line[500]; 
    	int index = 0;//��Ƕ���ʲô���� 
		 
    	// ���ж�ȡ�ļ�����
    	while (fgets(line, sizeof(line), file) != NULL) {
    		settextstyle(18, 0, _T("����"));
    		if(index%3==0){
    			outtextxy(220, begin_h, "���룺");
    		}
    		else if(index%3==1)
    		{
    			outtextxy(220, begin_h, "k��");
			}
			else
			{
				outtextxy(220, begin_h, "k��ԭ��ؼ�������");
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
		//��С���˷��������
		his_btn[3].status = 1;
		//k�����ľ���ʷ��¼��ť
		FILE *file = fopen("lr_output.txt", "r");
    	if (file == NULL)
    	{
    		char text1[50] = {"�Ҳ�����ʷ��¼�ļ���" }, text2[50] = {"�ļ�����" };
			MessageBox(GetHWnd(), text1, text2, 0);
    		return ;
		}
    

    	// �ļ��Ľṹ�ǵ�һ�У�x���ڶ��У�y,�����У�б�ʣ������У��ؾ� 
    	int begin_h = 70;
    	char line[500]; 
    	int index = 0;//��Ƕ���ʲô���� 
		 
    	// ���ж�ȡ�ļ�����
    	while (fgets(line, sizeof(line), file) != NULL) {
    		settextstyle(18, 0, _T("����"));
    		if(index%4==0){
    			outtextxy(220, begin_h, "x��");
    		}
    		else if(index%4==1)
    		{
    			outtextxy(220, begin_h, "y��");
			}
    		else if(index%4==2)
    		{
    			outtextxy(220, begin_h, "slope��");
			}
			else if(index%4==3)
			{
				outtextxy(220, begin_h, "intercept��");
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
    		
    //��һ�����ذ�ť
	drawButton(ret_btn, RET_BUTTON_WIDTH, 30);
	// ���û�ͼĿ��Ϊ��ͼ����
	SetWorkingImage();
	//�� buffer��ʾ�ڻ�ͼ������
    putimage(0, 0, &buffer);  
			
    bool flag = true;
    while (flag) 
	{
		while (MouseHit())
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{//�������
				if (m.x >= 220 && m.x <= 320 && m.y>=10 &&m.y<=40)
				{
					ret_btn.status = 1;
					flag = false;
				}
			}
			/*
			else if (m.uMsg == WM_LBUTTONUP)
			{//�������
			//���ð�ť״̬
				setUpButton(0, -1);
			}*/
			
			
		}
		setUpButton(0, -1);
		
	} 
	

	
	
	
}

 







