#include <stdio.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include <omp.h>

using namespace std;

#pragma hdrstop

class BP{
private:
	static const int W = 4;
	static const int H = 20;
	const float A = 30.0;
	const float B = 10.0;
	const float MAX = 10; //���ѵ������
	const float COEF = 0.0035f; //�����ѧϰЧ��
	const float BCOEF = 0.001f;//����ķ�ֵ����Ч��
	const float ERROR = 0.002f; // ����ѵ���е��������
	const float ACCURACY = 0.0005f;//����Ҫ�󾫶�
	double sample[H][W];
	double w[4][10][10], wc[4][10][10], b[4][10], bc[4][10];
public:
	double o[4][10], netin[4][10], d[4][10], differ;//�������������
	double is; //ȫ������������
	int count, a;
public:
	BP(string src);
	void netout(int m, int n);//������������������������
	void calculd(int m, int n); //��������ķ��򴫲����
	void calculwc(int m, int n);//��������Ȩֵ�ĵ�����
	void calculbc(int m, int n); //�������緧ֵ�ĵ�����
	void changew(int m, int n); //��������Ȩֵ
	void changeb(int m, int n);//�������緧ֵ
	void clearwc();//�������Ȩֵ�仯��wc
	void clearbc();//������緧ֵ�仯��bc
	void initialw(void);//��ʼ��NN����ȨֵW
	void initialb(void); //��ʼ��NN���緧ֵ
	void calculdiffer(void);//����NN���絥���������
	void calculis(void);//����NN����ȫ���������
	void trainNN(void);//ѵ��NN����
};
