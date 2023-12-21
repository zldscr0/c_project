#include "data_analysis.h"
#define SIZE 30
#define K 2 
#define windows_W 1000
#define windows_H 600

int main() {
	

    initgraph(windows_W, windows_H);          // ���ô��ڵĴ�С��
    init_file();
    playMusic();
    //setbkcolor(BACKGROUND_COLOR); // ���ñ���ɫΪ��ɫ��
    
	MOUSEMSG m;
	
	int status = 0;
	int fixStatus = 0;
	FlushMouseMsgBuffer();
	while (true) {
		setUpButton(0, -1);
		while (MouseHit()) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {//�������
				if (m.x >= 0 && m.x <= 180) {
					menBtn(m, &status);
				} 
				else if (m.x > 180 && m.x < 1000) {
					switch (status) {
        				case 1: // ����ƽ��ֵ���� 
            				handle_AVG(m);  
            				break;
        				case 2:// ����k��ԭ��� 
        					handle_KRM(m); 
            				//printf("����k��ԭ���");  
            				break;
        				case 3:// ����k�����ľ� 
        					handle_KCM(m); 
            				//printf("����k�����ľ�");    
            				break;
        				case 4:// ��С���˷��������
        					handle_lR(m);
            				//printf("��С���˷��������");  
            				break;
            			case 5:// �鿴��ʷ��¼ 
            				handle_his(m);  
            				break;
    					}
				}
			}
			/*
			else if (m.uMsg == WM_LBUTTONUP) {//�������
				//���ð�ť״̬
				setUpButton(0, -1);
			}
			*/
			
		}
		drawView(status);
	}
	closegraph();//�ر�ͼ�δ��� 
	mciSendString(_T("close bkmusic"), NULL, 0, NULL);//�ر���Ƶ�ļ�
    return 0;
}
