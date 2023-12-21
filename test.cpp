#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

#define SIZE 30 // 数据组数
#define K 2    // k阶矩的阶数

// 求平均值
double calculateMean(double data[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
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
void linearRegression(double x[], double y[], int size, double *slope, double *intercept) {
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_xx = 0.0;

    for (int i = 0; i < size; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_xx += pow(x[i], 2);
    }

    *slope = (size * sum_xy - sum_x * sum_y) / (size * sum_xx - pow(sum_x, 2));
    *intercept = (sum_y - *slope * sum_x) / size;
}

int main() {
    initgraph(800, 600); // 初始化图形窗口

    int size;
    printf("输入数组的大小 (max 30): ");
    scanf("%d", &size);

    if (size > SIZE) {
        printf("Error: Array size too large.\n");
        return 1;
    }

    double x[SIZE] = {0};
    double y[SIZE] = {0};

    printf("请输入x,y的值:\n");
    for (int i = 0; i < size; i++) {
        scanf("%lf %lf", &x[i], &y[i]);
    }

    double mean_x = calculateMean(x, size);
    double mean_y = calculateMean(y, size);

    double rawMoment_x = calculateRawMoment(x, size, K);
    double rawMoment_y = calculateRawMoment(y, size, K);

    double centralMoment_x = calculateCentralMoment(x, size, K);
    double centralMoment_y = calculateCentralMoment(y, size, K);

    double slope, intercept;
    linearRegression(x, y, size, &slope, &intercept);

    // 显示结果
    outtextxy(10, 10, "计算结果:");
    char result[100];
    sprintf(result, "x的平均值: %.2f", mean_x);
    outtextxy(10, 30, result);
    sprintf(result, "y的平均值: %.2f", mean_y);
    outtextxy(10, 50, result);
    sprintf(result, "x的K阶原点矩: %.2f", rawMoment_x);
    outtextxy(10, 70, result);
    sprintf(result, "y的K阶原点矩: %.2f", rawMoment_y);
    outtextxy(10, 90, result);
    sprintf(result, "x的k阶中心矩: %.2f", centralMoment_x);
    outtextxy(10, 110, result);
    sprintf(result, "y的k阶中心矩: %.2f", centralMoment_y);
    outtextxy(10, 130, result);
    sprintf(result, "线性回归方程: y = %.2f * x + %.2f", slope, intercept);
    outtextxy(10, 150, result);

    // 等待键盘输入，结束程序
    getch();
    closegraph(); // 关闭图形窗口
    return 0;
}

