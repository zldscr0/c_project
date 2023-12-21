#include "data_analysis.h"
#define SIZE 30
#define K 2 
#define windows_W 1000
#define windows_H 600

int main() {
	

    initgraph(windows_W, windows_H);          // 设置窗口的大小；
    init_file();
    playMusic();
    //setbkcolor(BACKGROUND_COLOR); // 设置背景色为黑色；
    
	MOUSEMSG m;
	
	int status = 0;
	int fixStatus = 0;
	FlushMouseMsgBuffer();
	while (true) {
		setUpButton(0, -1);
		while (MouseHit()) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {//左键按下
				if (m.x >= 0 && m.x <= 180) {
					menBtn(m, &status);
				} 
				else if (m.x > 180 && m.x < 1000) {
					switch (status) {
        				case 1: // 计算平均值界面 
            				handle_AVG(m);  
            				break;
        				case 2:// 计算k阶原点矩 
        					handle_KRM(m); 
            				//printf("计算k阶原点矩");  
            				break;
        				case 3:// 计算k阶中心矩 
        					handle_KCM(m); 
            				//printf("计算k阶中心矩");    
            				break;
        				case 4:// 最小二乘法线性拟合
        					handle_lR(m);
            				//printf("最小二乘法线性拟合");  
            				break;
            			case 5:// 查看历史记录 
            				handle_his(m);  
            				break;
    					}
				}
			}
			/*
			else if (m.uMsg == WM_LBUTTONUP) {//左键弹起
				//重置按钮状态
				setUpButton(0, -1);
			}
			*/
			
		}
		drawView(status);
	}
	closegraph();//关闭图形窗口 
	mciSendString(_T("close bkmusic"), NULL, 0, NULL);//关闭音频文件
    return 0;
}
