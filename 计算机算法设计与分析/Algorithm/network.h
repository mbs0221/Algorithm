#define _EDG_ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <easyx.h>
#include <graphics.h>

#define uint unsigned short
#define real double

#define threshold (real)(rand() % 99998 + 1) / 100000

class layer{
private:
	char name[20];
	uint row, col;
	real **data;
	real *bias;
public:
	layer(){
		strcpy_s(name, "temp");
		row = 1;
		col = 3;
		data = new real*[row];
		bias = new real[row];
		for (uint i = 0; i < row; i++){
			data[i] = new real[col];
			bias[i] = threshold;
			for (uint j = 0; j < col; j++){
				data[i][j] = 1;
			}
		}
	}
	layer(FILE *fp){
		fscanf_s(fp, "%d %d %s", &row, &col, name);
		data = new real*[row];
		bias = new real[row];
		for (uint i = 0; i < row; i++){
			data[i] = new real[col];
			bias[i] = threshold;
			for (uint j = 0; j < col; j++){
				fscanf_s(fp, "%lf", &data[i][j]);
			}
		}
	}
	layer(uint row, uint col){
		strcpy_s(name, "temp");
		this->row = row;
		this->col = col;
		this->data = new real*[row];
		this->bias = new real[row];
		for (uint i = 0; i < row; i++){
			data[i] = new real[col];
			bias[i] = threshold;
			for (uint j = 0; j < col; j++){
				data[i][j] = 1.0f;
			}
		}
	}
	layer(const layer &a){
		strcpy_s(name, a.name);
		row = a.row, col = a.col;
		data = new real*[row];
		bias = new real[row];
		for (uint i = 0; i < row; i++){
			data[i] = new real[col];
			bias[i] = a.bias[i];
			for (uint j = 0; j < col; j++){
				data[i][j] = a.data[i][j];
			}
		}
	}
	~layer(){
		// 删除原有数据
		for (uint i = 0; i < row; i++){
			delete[]data[i];
		}
		delete[]data;
	}
	layer& operator =(const layer &a){
		// 删除原有数据
		for (uint i = 0; i < row; i++){
			delete[]data[i];
		}
		delete[]data;
		delete[]bias;
		// 重新分配空间
		strcpy_s(name, a.name);
		row = a.row, col = a.col;
		data = new real*[row];
		bias = new real[row];
		for (uint i = 0; i < row; i++){
			data[i] = new real[col];
			bias[i] = a.bias[i];
			for (uint j = 0; j < col; j++){
				data[i][j] = a.data[i][j];
			}
		}
		return *this;
	}
	layer operator ~()const{
		layer arr(col, row);
		for (uint i = 0; i < row; i++){
			for (uint j = 0; j < col; j++){
				arr.data[j][i] = data[i][j];
			}
		}
		return arr;
	}
	layer operator *(const layer &b){
		layer arr(row, col);
		for (uint i = 0; i < row; i++){
			for (uint j = 0; j < col; j++){
				arr.data[i][j] = data[i][j] * b.data[i][j];
			}
		}
		return arr;
	}
	layer operator *(const int b){
		layer arr(row, col);
		for (uint i = 0; i < row; i++){
			for (uint j = 0; j < col; j++){
				arr.data[i][j] = b * data[i][j];
			}
		}
		return arr;
	}
	layer operator ()(const layer &b){
		layer arr(row, b.col);
		for (uint k = 0; k < b.col; k++){
			for (uint i = 0; i < row; i++){
				arr.bias[i] = bias[i];
				arr.data[i][k] = 0;
				for (uint j = 0; j < col; j++){
					arr.data[i][k] += data[i][j] * b.data[j][k];
				}
			}
		}
		return arr;
	}
	layer operator -(const layer &b){
		layer arr(row, col);
		for (uint i = 0; i < row; i++){
			for (uint j = 0; j < col; j++){
				arr.data[i][j] = data[i][j] - b.data[i][j];
			}
		}
		return arr;
	}
	layer operator +(const layer &b){
		layer arr(row, col);
		for (uint i = 0; i < row; i++){
			for (uint j = 0; j < col; j++){
				arr.data[i][j] = data[i][j] + b.data[i][j];
			}
		}
		return arr;
	}
	layer neg(){
		layer arr(row, col);
		for (uint i = 0; i < row; i++){
			for (uint j = 0; j < col; j++){
				arr.data[i][j] = -data[i][j];
			}
		}
		return arr;
	}
	bool operator ==(const layer &a){
		bool result = true;
		for (uint i = 0; i < row; i++){
			for (uint j = 0; j < col; j++){			
				if (fabs(data[i][j] - a.data[i][j]) > 10e-6){
					result = false;
					break;
				}
			}
		}
		return result;
	}
	void randomize(){
		for (uint i = 0; i < row; i++){
			for (uint j = 0; j < col; j++){
				data[i][j] = threshold;
			}
			bias[i] = 0.3;
		}
	}
	void print(){
		printf("matrix:%s\n", name);
		for (uint i = 0; i < row; i++){
			for (uint j = 0; j < col; j++){
				printf("%.6f\t", data[i][j]);
			}
			printf("\n");
		}
	}
	void save(FILE *fp){
		fprintf_s(fp, "%d %d %s\n", row, col, name);
		for (uint i = 0; i < row; i++){
			for (uint j = 0; j < col; j++){
				fprintf_s(fp, "%lf ", data[i][j]);
			}
			fprintf_s(fp, "\n");
		}
	}
	friend class network;
	friend layer operator *(const double a, const layer &b);
};

layer operator *(const double a, const layer &b){
	layer arr(b.row, b.col);
	for (uint i = 0; i < arr.row; i++){
		for (uint j = 0; j < arr.col; j++){
			arr.data[i][j] = a * b.data[i][j];
		}
	}
	return arr;
}

// 神经网络
class network{
	int iter;
	double learn;
	layer arr[3];
	layer data, target, test;
	layer& unit(layer &x){
		for (uint i = 0; i < x.row; i++){
			for (uint j = 0; j < x.col; j++){
				x.data[i][j] = i == j ? 1.0 : 0.0;
			}
		}
		return x;
	}
	layer& bias(layer &x){
		for (uint i = 0; i < x.row; i++){
			for (uint j = 0; j < x.col; j++){
				//x.data[i][j] = (exp(x.data[i][j]) - exp(-x.data[i][j])) / ((exp(x.data[i][j])) + exp(-x.data[i][j]));
				x.data[i][j] = 1 / (1 + exp(-x.data[i][j]));// x = 1 / (1 + exp(-z))
			}
		}
		return x;
	}
	layer nonlin(layer &x){
		layer e(x.row, x.col);
		e = x*(e - x);// O[j]*(1-O[j])
		return e;// 误差函数
	}
public:
	network(FILE *fp){
		fscanf_s(fp, "%d %lf", &iter, &learn);
		// 输入数据
		data = layer(fp);
		for (uint i = 0; i < 3; i++){
			arr[i] = layer(fp);
			arr[i].randomize();
		}
		target = layer(fp);
		// 初始化
		for (uint i = 0; i < data.col; i++){
			data.data[0][i] = (double)i / data.col;
			data.data[1][i] = (double)i / data.col;
			target.data[0][i] = sin(data.data[0][i]) + cos(data.data[1][i]);
		}
		// 测试数据
		test = layer(2, 40000);
		for (uint i = 0; i < 40000; i++){
			test.data[0][i] = (double)i / 200;
			test.data[1][i] = i % 200;
		}
	}
	void train(){
		int i = 0;
		char str[20];
		data.print();
		target.print();
		for (i = 0; i < iter; i++){
			sprintf_s(str, "Iterate:%d", i);
			// 正向传播
			layer l0 = data;
			layer l1 = bias(arr[0](l0));
			layer l2 = bias(arr[1](l1));
			layer l3 = bias(arr[2](l2));
			// 显示输出结果
			//l1.print();
			//l2.print();
			//l3.print();
			if (l3 == target){
				break;
			}
			// 反向传播
			layer l3_delta = (target - l3) * nonlin(l3);// Err[j] = (T[j]-O[j]) * O[j]*(1-O[j])
			layer l2_delta = (~arr[2])(l3_delta) * nonlin(l2);// [W[j][j+1]]^-1 * Err[j+1] * O[j]*(1-O[j])
			layer l1_delta = (~arr[1])(l2_delta) * nonlin(l1);// [W[j][j+1]]^-1 * Err[j+1] * O[j]*(1-O[j])
			// 计算新的权值
			arr[2] = arr[2] + learn * l3_delta(~l2);// [5 6] = [5 6] + [5 8](~[6 8]) // learn * Err3 * O2
			arr[1] = arr[1] + learn * l2_delta(~l1);// [6 5] = [6 5] + [6 8](~[5 8]) // learn * Err2 * O1
			arr[0] = arr[0] + learn * l1_delta(~l0);// [5 8] = [5 8] + [5 8](~[8 8]) // learn * Err1 * O0
		}
		sprintf_s(str, "Iterate:%d", i);
		// 测试输出
		selftest();
	}
	void selftest(){
		// 测试
		layer l0 = test;
		layer l1 = bias(arr[0](l0));
		layer l2 = bias(arr[1](l1));
		layer l3 = bias(arr[2](l2));
		// 测试例
		for (uint j = 0; j < test.col; j++){
			//COLORREF Col = HSLtoRGB(l3.data[0][j], 1, 1);
			//putpixel((int)(test.data[0][j] * 200) + 400, (int)(test.data[1][j] * 200) + 30, Col);

		}
		// 标准例
		for (uint j = 0; j < target.col; j++){
			//COLORREF Col = HSLtoRGB(target.data[0][j], 1, 1);
			//putpixel((int)(test.data[0][j] * 200) + 400, (int)(test.data[1][j] * 200) + 30, Col);
		}
		//setlinecolor(WHITE);
		//line(400, 30, 400, 230);
		//line(400, 30, 600, 30);
	}
	void save(FILE *fp){
		fprintf_s(fp, "%d %lf\n", iter, learn);
		data.save(fp);
		for (uint i = 0; i < 3; i++){
			arr[i].save(fp);
		}
		target.save(fp);
	}
	static void test() {
		FILE file;
		FILE *fp = &file;
		fopen_s(&fp, "Text.txt", "r");
		network net(fp);
		net.train();
		net.selftest();
		net.save(fp);
		fclose(fp);
	}
};