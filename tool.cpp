#include "data_analysis.h"
bool isInteger(const char *str) {
    // ���ÿ���ַ��Ƿ��������ַ�
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool isFloat(const char *str) {
    // ���ÿ���ַ��Ƿ��������ַ���С����
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
    return hasDot;  // ����������һ��С����
}

//�ж������Ƿ�Ϊ�� 
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

// ��������
void playMusic() {
    // �� "atomay.mp3" ��Ϊ��ȡ���� "bkmusic"
    mciSendString(_T("open atomay.mp3 alias bkmusic"), NULL, 0, NULL);

    // �����Ա��� "bkmusic" ��ʶ�������ļ���������Ϊѭ������
    mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
}
