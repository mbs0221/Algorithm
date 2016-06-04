#include <iomanip>
#include <iostream>

using namespace std;

void knap_sack(int N, int capacity)//N为物品数，capacity为背包容量
{
	int *weight = new int[N];//每件物品重量
	int *value = new int[N];//每件物品价值
	int **C = new int*[N + 1];//最优值数组
	int *select = new int[N];//各物品装的状态
	cout << "N:" << N << ",capacity:" << capacity << endl;
	for (int i = 0; i < N; i++)//初始化每件物品重量，价值
	{
		weight[i] = rand() % N + 1;
		value[i] = rand() % N + 1;
		cout << setw(2) << i + 1 << " w:" << weight[i] << " v:" << value[i] << endl;
	}
	for (int i = 0; i <= N; i++)//初始化最优值数组和重量为0时的价值
	{
		C[i] = new int[capacity + 1];
		C[i][0] = 0;
	}
	for (int i = 0; i <= capacity; i++)//初始化选0个物品
	{
		C[0][i] = 0;
	}
	for (int i = 1; i <= N; i++)//构造最优解
	{
		for (int j = 1; j <= capacity; j++)//j为当前容量最大值
		{
			if (weight[i - 1] <= j)//和装第一个物品一样，为了求得第i个物品的weight和value，i应该-1
			{
				if (C[i - 1][j - weight[i - 1]] + value[i - 1] > C[i - 1][j])
				{
					C[i][j] = C[i - 1][j - weight[i - 1]] + value[i - 1];
				}
				else
				{
					C[i][j] = C[i - 1][j];
				}
			}
			else//除去i物品的重量的价值和加上i物品重量的价值比较
			{
				C[i][j] = C[i - 1][j];
			}
		}
	}
	//输出列标
	cout << " C";
	for (int i = 0; i <= capacity; i++)
		cout << setw(3) << i;
	cout << endl;
	//输出列表
	for (int i = 0; i <= N; i++)
	{
		cout << setw(2) << i << ":";
		for (int j = 0; j <= capacity; j++)
		{
			cout << setw(2) << C[i][j] << " ";
		}
		cout << endl;
	}
	//计算是否装入第i个物品
	int j = capacity;
	for (int i = N; i > 0; i--)
	{
		if (C[i][j] > C[i - 1][j])//装入i提升了价值，装！
		{
			select[i - 1] = 1;
			j -= weight[i - 1];
		}
		else//价值没有提升，不装！
		{
			select[i - 1] = 0;
		};
	}
	//输出0-1选择状态
	cout << "select:";
	for (int i = 0; i < N; i++)
	{
		cout << setw(2) << select[i] << " ";
	}
	cout << endl;
}

void gena_knap_sack(int N, int capacity)
{
	int *weight = new int[N];//每件物品重量
	int *value = new int[N];//每件物品价值
	int **C = new int*[N + 1];//最优值数组
	int *select = new int[N];//各物品装的状态
	cout << "N:" << N << ",capacity:" << capacity << endl;
	for (int i = 0; i < N; i++)//初始化每件物品重量，价值
	{
		weight[i] = rand() % N + 1;
		value[i] = rand() % N + 1;
		select[i] = 0;
		cout << setw(2) << i + 1 << " w:" << weight[i] << " v:" << value[i] << endl;
	}
	for (int i = 0; i <= N; i++)//初始化最优值数组和重量为0时的价值
	{
		C[i] = new int[capacity + 1];
		C[i][0] = 0;
	}
	for (int i = 0; i <= capacity; i++)//初始化选0个物品
	{
		C[0][i] = 0;
	}
	for (int i = 1; i <= N; i++)//构造最优解
	{
		for (int j = 1; j <= capacity; j++)//j为当前容量最大值
		{
			if (weight[i - 1] <= j)
			{
				if (C[i - 1][j - weight[i - 1]] + value[i - 1] > C[i - 1][j])
				{
					//C[i][j] = C[i - 1][j - weight[i - 1]] + value[i - 1];0-1背包问题
					C[i][j] = C[i][j - weight[i - 1]] + value[i - 1];
				}
				else
				{
					C[i][j] = C[i - 1][j];
				}
			}
			else
			{
				C[i][j] = C[i - 1][j];
			}
		}
	}
	//输出列标
	cout << " C";
	for (int i = 0; i <= capacity; i++)
		cout << setw(3) << i;
	cout << endl;
	//输出列表
	for (int i = 0; i <= N; i++)
	{
		cout << setw(2) << i << ":";
		for (int j = 0; j <= capacity; j++)
		{
			cout << setw(2) << C[i][j] << " ";
		}
		cout << endl;
	}
	//计算是否装入第i个物品
	int j = capacity;
	for (int i = N; i > 0; i--)
	{
		while (C[i][j] > C[i - 1][j])//装入i提升了价值，装！
		{
			select[i - 1]++;//累计i物品
			j -= weight[i - 1];//减去同等物品的重量
		}
	}
	//输出0-1选择状态
	cout << "select:";
	for (int i = 0; i < N; i++)
	{
		cout << setw(2) << select[i] << " ";
	}
	cout << endl;
}