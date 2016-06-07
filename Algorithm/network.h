#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <math.h>

#define byte unsigned char
#define word unsigned short

#define threshold (double)(rand() % 99998 + 1) / 100000

class layer{
private:
	char name[20];
	double **data;
	double *bias;
	byte row, col;
public:
	layer(){
		strcpy_s(name, "temp");
		row = 1;
		col = 3;
		data = new double*[row];
		bias = new double[row];
		for (byte i = 0; i < row; i++){
			data[i] = new double[col];
			bias[i] = threshold;
			for (byte j = 0; j < col; j++){
				data[i][j] = 1;
			}
		}
	}
	layer(FILE *fp){
		fscanf_s(fp, "%d %d %s", &row, &col, name);
		data = new double*[row];
		bias = new double[row];
		for (byte i = 0; i < row; i++){
			data[i] = new double[col];
			bias[i] = threshold;
			for (byte j = 0; j < col; j++){
				fscanf_s(fp, "%lf", &data[i][j]);
			}
		}
	}
	layer(byte row, byte col){
		strcpy_s(name, "temp");
		this->row = row;
		this->col = col;
		this->data = new double*[row];
		this->bias = new double[row];
		for (byte i = 0; i < row; i++){
			data[i] = new double[col];
			bias[i] = threshold;
			for (byte j = 0; j < col; j++){
				data[i][j] = 1.0f;
			}
		}
	}
	layer(const layer &a){
		strcpy_s(name, a.name);
		row = a.row, col = a.col;
		data = new double*[row];
		bias = new double[row];
		for (byte i = 0; i < row; i++){
			data[i] = new double[col];
			bias[i] = a.bias[i];
			for (byte j = 0; j < col; j++){
				data[i][j] = a.data[i][j];
			}
		}
	}
	~layer(){
		// 删除原有数据
		for (byte i = 0; i < row; i++){
			delete[]data[i];
		}
		delete[]data;
	}
	layer& operator =(const layer &a){
		// 删除原有数据
		for (byte i = 0; i < row; i++){
			delete[]data[i];
		}
		delete[]data;
		delete[]bias;
		// 重新分配空间
		strcpy_s(name, a.name);
		row = a.row, col = a.col;
		data = new double*[row];
		bias = new double[row];
		for (byte i = 0; i < row; i++){
			data[i] = new double[col];
			bias[i] = a.bias[i];
			for (byte j = 0; j < col; j++){
				data[i][j] = a.data[i][j];
			}
		}
		return *this;
	}
	layer operator ~()const{
		layer arr(col, row);
		for (byte i = 0; i < row; i++){
			for (byte j = 0; j < col; j++){
				arr.data[j][i] = data[i][j];
			}
		}
		return arr;
	}
	layer operator *(const layer &b){
		layer arr(row, col);
		for (byte i = 0; i < row; i++){
			for (byte j = 0; j < col; j++){
				arr.data[i][j] = data[i][j] * b.data[i][j];
			}
		}
		return arr;
	}
	layer operator *(const int b){
		layer arr(row, col);
		for (byte i = 0; i < row; i++){
			for (byte j = 0; j < col; j++){
				arr.data[i][j] = b * data[i][j];
			}
		}
		return arr;
	}
	layer operator ()(const layer &b){
		layer arr(row, b.col);
		for (byte k = 0; k < b.col; k++){
			for (byte i = 0; i < row; i++){
				arr.bias[i] = bias[i];
				arr.data[i][k] = 0;
				for (byte j = 0; j < col; j++){
					arr.data[i][k] += data[i][j] * b.data[j][k];
				}
			}
		}
		return arr;
	}
	layer operator -(const layer &b){
		layer arr(row, col);
		for (byte i = 0; i < row; i++){
			for (byte j = 0; j < col; j++){
				arr.data[i][j] = data[i][j] - b.data[i][j];
			}
		}
		return arr;
	}
	layer operator +(const layer &b){
		layer arr(row, col);
		for (byte i = 0; i < row; i++){
			for (byte j = 0; j < col; j++){
				arr.data[i][j] = data[i][j] + b.data[i][j];
			}
		}
		return arr;
	}
	layer neg(){
		layer arr(row, col);
		for (byte i = 0; i < row; i++){
			for (byte j = 0; j < col; j++){
				arr.data[i][j] = -data[i][j];
			}
		}
		return arr;
	}
	bool operator ==(const layer &a){
		bool result = true;
		for (byte i = 0; i < row; i++){
			for (byte j = 0; j < col; j++){
				if (abs(data[i][j] - a.data[i][j]) > 10e-6){
					result = false;
					break;
				}
			}
		}
		return result;
	}
	void randomize(){
		for (byte i = 0; i < row; i++){
			for (byte j = 0; j < col; j++){
				data[i][j] = threshold;
			}
			bias[i] = threshold;
		}
	}
	void print(){
		for (byte i = 0; i < row; i++){
			for (byte j = 0; j < col; j++){
				printf("%lf ", data[i][j]);
			}
			printf("\n");
		}
	}
	friend class network;
};
class network{
	int iter;
	layer arr[5];
	layer data, target;
	layer& unit(layer &x){
		for (byte i = 0; i < x.row; i++){
			for (byte j = 0; j < x.col; j++){
				x.data[i][j] = i == j ? 1.0 : 0.0;
			}
		}
		return x;
	}
	layer& bias(layer &x){
		for (byte i = 0; i < x.row; i++){
			for (byte j = 0; j < x.col; j++){
				x.data[i][j] = 1 / (1 + exp(-x.data[i][j])); // 1/(1+exp(-z))
			}
		}
		return x;
	}
	layer nonlin(layer &x){
		layer e(x.row, x.col);
		e = x*(e - x);
		for (byte i = 0; i < x.row; i++){
			for (byte j = 0; j < x.col; j++){
				e.data[i][j] * x.bias[i];
			}
		}
		return e;// 误差函数
	}
public:
	network(FILE *fp){
		srand(time(0));
		fscanf_s(fp, "%d", &iter);
		data = layer(fp);
		for (byte i = 0; i < 5; i++){
			arr[i] = layer(fp);
			arr[i].randomize();
		}
		target = layer(fp);
	}
	void train(){
		int i = 0;
		printf("Training network\n");
		printf("Training...\n");
		for (i = 0; i < iter; i++){
			printf("Iterate:%4d\r", i);
			// 正向传播
			layer l0 = data;
			layer l1 = bias(arr[0](l0));
			layer l2 = bias(arr[1](l1));
			layer l3 = bias(arr[2](l2));
			layer l4 = bias(arr[3](l3));
			layer l5 = bias(arr[4](l4));
			if (l5 == target){
				printf("exit because taining results is equals to target.\n");
				break;
			}
			// 反向传播
			layer l5_error = (target - l5);// [1 8] = [1 8] - [1 8]
			layer l5_delta = l5_error * nonlin(l5);
			layer l4_error = (~arr[4])(l5_delta);// [4 8] = [4 1] . [1 8]
			layer l4_delta = l4_error * nonlin(l4);
			layer l3_error = (~arr[3])(l4_delta);// [5 8] = [5 4] . [4 8]
			layer l3_delta = l3_error * nonlin(l3);
			layer l2_error = (~arr[2])(l3_delta);// [6 8] = [6 5] . [5 8]
			layer l2_delta = l2_error * nonlin(l2);
			layer l1_error = (~arr[1])(l2_delta);// [5 8] = [5 6] . [6 8]
			layer l1_delta = l1_error * nonlin(l1);
			// 计算新的权值
			arr[4] = arr[4] + l5_delta(~l4);// [1 4] = [1 4] + [1 8](~[4 8])
			arr[3] = arr[3] + l4_delta(~l3);// [4 5] = [4 5] + [4 8](~[5 8])
			arr[2] = arr[2] + l3_delta(~l2);// [5 6] = [5 6] + [5 8](~[6 8])
			arr[1] = arr[1] + l2_delta(~l1);// [6 5] = [6 5] + [6 8](~[5 8])
			arr[0] = arr[0] + l1_delta(~l0);// [5 8] = [5 8] + [5 8](~[8 8])
		}
		printf("Iterate:%4d\n", i);
		printf("Training complete\n");
	}
	void selftest(){
		printf("network self test\n");
		printf("data:\n");
		data.print();
		// 正向传播
		layer l0 = data;
		layer l1 = bias(arr[0](l0));
		layer l2 = bias(arr[1](l1));
		layer l3 = bias(arr[2](l2));
		layer l4 = bias(arr[3](l3));
		layer l5 = bias(arr[4](l4));
		layer l5_error = (target - l5);// [1 8] = [1 8] - [1 8]
		layer l5_delta = l5_error * nonlin(l5);
		printf("target:\n");
		target.print();
		printf("result:\n");
		l5.print();
		printf("error:\n");
		l5_error.print();
		printf("delta:\n");
		l5_delta.print();
	}
	void test(layer &data){
		printf("test data\n");
		data.print();
		// 正向传播
		layer l0 = data;
		layer l1 = bias(arr[0](l0));
		layer l2 = bias(arr[1](l1));
		layer l3 = bias(arr[2](l2));
		layer l4 = bias(arr[3](l3));
		layer l5 = bias(arr[4](l4));
		printf("result:\n");
		l5.print();
	}
	void test(){
		printf("user test:\n");
		do{
			layer data(3, 1);
			for (byte i = 0; i < 3; i++){
				scanf_s("%lf", &data.data[i][0]);
			}
			test(data);
			printf("continue? [n]:\n");
		} while (getchar() == 'n');
	}
	void print(){
		printf("print network\n");
		data.print();
		for (byte i = 0; i < 5; i++){
			arr[i].print();
		}
		target.print();
	}
};