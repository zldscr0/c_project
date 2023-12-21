#include "data_analysis.h"
bool isInteger(const char *str) {
    // 检查每个字符是否是数字字符
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool isFloat(const char *str) {
    // 检查每个字符是否是数字字符或小数点
    bool hasDot = false;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            if (str[i] == '.' && !hasDot) {
                hasDot = true;
            } else {
                return false;
            }
        }
    }
    return hasDot;  // 必须至少有一个小数点
}

//判断输入是否为空 
bool isEmpty(const char *str)
{
	return strlen(str)==0;
}


void init_file()
{
	const char* files[] = {"avg_output.txt", "krm_output.txt", "kcm_output.txt", "lr_output.txt"};

	for(int i=0;i<4;i++)
	{
		FILE* file = fopen(files[i], "w");
		fclose(file);
	}	
}

// 播放音乐
void playMusic() {
    // 打开 "atomay.mp3" 并为其取别名 "bkmusic"
    mciSendString(_T("open atomay.mp3 alias bkmusic"), NULL, 0, NULL);

    // 播放以别名 "bkmusic" 标识的音乐文件，并设置为循环播放
    mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
}
