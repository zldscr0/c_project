#include "data_analysis.h"

// calculateMean �������ڼ��������ƽ��ֵ
// ������
//   - data: �洢���ݵ�����
//   - size: ����Ĵ�С
// ����ֵ��
//   - ��������Ԫ�ص�ƽ��ֵ
double calculateMean(double data[], int size) {
    double sum = 0.0;  // �����ۼ������е�Ԫ��ֵ

    // �������飬�ۼ�Ԫ��ֵ
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }

    // ��������Ԫ�ص�ƽ��ֵ
    return sum / size;
}


// ��k��ԭ���
double calculateRawMoment(double data[], int size, int k) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += pow(data[i], k);
    }
    return sum / size;
}

// ��k�����ľ�
double calculateCentralMoment(double data[], int size, int k) {
    double sum = 0.0;
    double mean = calculateMean(data, size);
    for (int i = 0; i < size; i++) {
        sum += pow(data[i] - mean, k);
    }
    return sum / size;
}

// ��С���˷��������
// ������
//   x: ����� x ֵ����
//   y: ��Ӧ�� y ֵ����
//   size: ����Ĵ�С
//   slope: �����������ϵõ���б��
//   intercept: �����������ϵõ��Ľؾ�
void linearRegression(double x[], double y[], int size, double *slope, double *intercept) {
    // ��ʼ���ۼӱ���
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_xx = 0.0;

    // �������飬������ص��ۼӺ�
    for (int i = 0; i < size; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_xx += pow(x[i], 2);
    }

    // ������С���˷�������ϵ�б�ʺͽؾ�
    *slope = (size * sum_xy - sum_x * sum_y) / (size * sum_xx - pow(sum_x, 2));
    *intercept = (sum_y - *slope * sum_x) / size;
}

