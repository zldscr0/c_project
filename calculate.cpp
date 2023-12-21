#include "data_analysis.h"

// calculateMean 函数用于计算数组的平均值
// 参数：
//   - data: 存储数据的数组
//   - size: 数组的大小
// 返回值：
//   - 返回数组元素的平均值
double calculateMean(double data[], int size) {
    double sum = 0.0;  // 用于累加数组中的元素值

    // 遍历数组，累加元素值
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }

    // 返回数组元素的平均值
    return sum / size;
}


// 求k阶原点矩
double calculateRawMoment(double data[], int size, int k) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += pow(data[i], k);
    }
    return sum / size;
}

// 求k阶中心矩
double calculateCentralMoment(double data[], int size, int k) {
    double sum = 0.0;
    double mean = calculateMean(data, size);
    for (int i = 0; i < size; i++) {
        sum += pow(data[i] - mean, k);
    }
    return sum / size;
}

// 最小二乘法线性拟合
// 参数：
//   x: 输入的 x 值数组
//   y: 对应的 y 值数组
//   size: 数组的大小
//   slope: 输出参数，拟合得到的斜率
//   intercept: 输出参数，拟合得到的截距
void linearRegression(double x[], double y[], int size, double *slope, double *intercept) {
    // 初始化累加变量
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_xx = 0.0;

    // 遍历数组，计算相关的累加和
    for (int i = 0; i < size; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_xx += pow(x[i], 2);
    }

    // 计算最小二乘法线性拟合的斜率和截距
    *slope = (size * sum_xy - sum_x * sum_y) / (size * sum_xx - pow(sum_x, 2));
    *intercept = (sum_y - *slope * sum_x) / size;
}

