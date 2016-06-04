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
	const float MAX = 10; //最大训练次数
	const float COEF = 0.0035f; //网络的学习效率
	const float BCOEF = 0.001f;//网络的阀值调整效率
	const float ERROR = 0.002f; // 网络训练中的允许误差
	const float ACCURACY = 0.0005f;//网络要求精度
	double sample[H][W];
	double w[4][10][10], wc[4][10][10], b[4][10], bc[4][10];
public:
	double o[4][10], netin[4][10], d[4][10], differ;//单个样本的误差
	double is; //全体样本均方差
	int count, a;
public:
	BP(string src);
	void netout(int m, int n);//计算网络隐含层和输出层的输出
	void calculd(int m, int n); //计算网络的反向传播误差
	void calculwc(int m, int n);//计算网络权值的调整量
	void calculbc(int m, int n); //计算网络阀值的调整量
	void changew(int m, int n); //调整网络权值
	void changeb(int m, int n);//调整网络阀值
	void clearwc();//清除网络权值变化量wc
	void clearbc();//清除网络阀值变化量bc
	void initialw(void);//初始化NN网络权值W
	void initialb(void); //初始化NN网络阀值
	void calculdiffer(void);//计算NN网络单个样本误差
	void calculis(void);//计算NN网络全体样本误差
	void trainNN(void);//训练NN网络
};
