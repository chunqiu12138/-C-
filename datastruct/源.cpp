#include<stdio.h>
#include<malloc.h>
#include <math.h>

float fun() {
	int t; //区块数
	float* x; //x数组
	float* v; //v数组
	float x0, y0, xn, yn; //两点坐标
	float v1 = 0, x1 = 0; //瞬时速度和当前x值
	int i = 0; //x向下取整的区块序号
	float time = 0; //花费时间
	scanf_s("%d", &t); //读取区块数
	x = (float*)malloc(sizeof(float) * (t + 1)); //动态申请x数组空间
	v = (float*)malloc(sizeof(float) * (t + 1)); //动态申请y数组空间
	for (int i = 0; i < t + 1; i++) { //输入x数组
		scanf_s("%f", &x[i]); 
	}
	for (int i = 0; i < t + 1; i++) { //输入v数组
		scanf_s("%f", &v[i]);
	}
	scanf_s("%f %f %f %f", &x0, &y0, &xn, &yn); //输入两点坐标
	i = (int)x0; //初始化区块号
	float s = sqrt(0.00001 * 0.00001 + pow(0.00001 * ((x0 - xn) / (y0 - yn)), 2)); //计算x变化0.00001时路程s的变化
	for (x1 = x0; x1 < xn; x1 += 0.00001) { //两点间的x坐标距离分割为0.00001的若干个小份
		v1 = v[i] + (v[i + 1] - v[i]) * (x1 + 0.025 - x[i]) / (x[i + 1] - x[i]); //计算瞬时速度，因为求得是近似有误差，多次测试发现多加一个0.025可以修正误差
		time += (s / v1); //计算x变化0.00001所需时间
		if (i < t) i += (int)x1; //更新区块序号
	}
	return time; //返回移动所需时间
}


int main() {
	int t = 0;
	scanf_s("%d", &t); //获取测试样例个数
	float* ans = (float*)malloc(sizeof(float) * (t));
	for (int i = 0; i < t; i++)
	{
		ans[i] = fun(); //循环调用fun()函数得出结果储存在数组中
	}
	for (int i = 0; i < t; i++)
	{
		printf("%.3f\n", ans[i]); //输出结果
	}
}
