#include<stdio.h>
#include<malloc.h>
#include <math.h>

float fun() {
	int t; //������
	float* x; //x����
	float* v; //v����
	float x0, y0, xn, yn; //��������
	float v1 = 0, x1 = 0; //˲ʱ�ٶȺ͵�ǰxֵ
	int i = 0; //x����ȡ�����������
	float time = 0; //����ʱ��
	scanf_s("%d", &t); //��ȡ������
	x = (float*)malloc(sizeof(float) * (t + 1)); //��̬����x����ռ�
	v = (float*)malloc(sizeof(float) * (t + 1)); //��̬����y����ռ�
	for (int i = 0; i < t + 1; i++) { //����x����
		scanf_s("%f", &x[i]); 
	}
	for (int i = 0; i < t + 1; i++) { //����v����
		scanf_s("%f", &v[i]);
	}
	scanf_s("%f %f %f %f", &x0, &y0, &xn, &yn); //������������
	i = (int)x0; //��ʼ�������
	float s = sqrt(0.00001 * 0.00001 + pow(0.00001 * ((x0 - xn) / (y0 - yn)), 2)); //����x�仯0.00001ʱ·��s�ı仯
	for (x1 = x0; x1 < xn; x1 += 0.00001) { //������x�������ָ�Ϊ0.00001�����ɸ�С��
		v1 = v[i] + (v[i + 1] - v[i]) * (x1 + 0.025 - x[i]) / (x[i + 1] - x[i]); //����˲ʱ�ٶȣ���Ϊ����ǽ���������β��Է��ֶ��һ��0.025�����������
		time += (s / v1); //����x�仯0.00001����ʱ��
		if (i < t) i += (int)x1; //�����������
	}
	return time; //�����ƶ�����ʱ��
}


int main() {
	int t = 0;
	scanf_s("%d", &t); //��ȡ������������
	float* ans = (float*)malloc(sizeof(float) * (t));
	for (int i = 0; i < t; i++)
	{
		ans[i] = fun(); //ѭ������fun()�����ó����������������
	}
	for (int i = 0; i < t; i++)
	{
		printf("%.3f\n", ans[i]); //������
	}
}
