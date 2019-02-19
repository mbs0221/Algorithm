#include "bp_network.h"

BP::BP(string src)
{
	ifstream inf(src);
	if (!inf.is_open())
	{
		printf("open %s failed.", src);
		return;
	}
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			inf >> sample[i][j];
		}
	}
	inf.close();
}
void BP::netout(int m, int n)
{
	int i, j, k;

	//隐含层各节点的的输出
	for (j = 1, i = 2; j <= m; j++) //m为隐含层节点个数
	{
		netin[i][j] = 0.0;
		for (k = 1; k <= 3; k++)//隐含层的每个节点均有三个输入变量
			netin[i][j] = netin[i][j] + o[i - 1][k] * w[i][k][j];
		netin[i][j] = netin[i][j] - b[i][j];
		o[i][j] = A / (1 + exp(-netin[i][j] / B));
	}

	//输出层各节点的输出
	for (j = 1, i = 3; j <= n; j++)
	{
		netin[i][j] = 0.0;
		for (k = 1; k <= m; k++)
			netin[i][j] = netin[i][j] + o[i - 1][k] * w[i][k][j];
		netin[i][j] = netin[i][j] - b[i][j];
		o[i][j] = A / (1 + exp(-netin[i][j] / B));
	}
}
void BP::calculd(int m, int n)
{
	int i, j, k;
	double t;
	a = count - 1;
	d[3][1] = (o[3][1] - sample[a][3])*(A / B)*exp(-netin[3][1] / B) / pow(1 + exp(-netin[3][1] / B), 2);

	//隐含层的误差
	for (j = 1, i = 2; j <= m; j++)
	{
		t = 0.00;
		for (k = 1; k <= n; k++)
			t = t + w[i + 1][j][k] * d[i + 1][k];
		d[i][j] = t*(A / B)*exp(-netin[i][j] / B) / pow(1 + exp(-netin[i][j] / B), 2);
	}
}
void BP::calculwc(int m, int n)
{
	int i, j, k;

	// 输出层（第三层）与隐含层（第二层）之间的连接权值的调整
	for (i = 1, k = 3; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			wc[k][i][j] = -COEF*d[k][j] * o[k - 1][i] + 0.5*wc[k][i][j];
		}
	}
	//隐含层与输入层之间的连接权值的调整
	for (i = 1, k = 2; i <= m; i++)
	{
		for (j = 1; j <= m; j++)
		{
			wc[k][i][j] = -COEF*d[k][j] * o[k - 1][i] + 0.5*wc[k][i][j];
		}
	}

}
void BP::calculbc(int m, int n)
{
	int j;

	for (j = 1; j <= m; j++)
	{
		bc[2][j] = BCOEF*d[2][j];
	}

	for (j = 1; j <= n; j++)
	{
		bc[3][j] = BCOEF*d[3][j];
	}
}
void BP::changew(int m, int n)
{
	int i, j;
	for (i = 1; i <= 3; i++)
	for (j = 1; j <= m; j++)
	{
		w[2][i][j] = 0.9*w[2][i][j] + wc[2][i][j];
		//为了保证系统有较好的鲁棒性，计算权值时乘惯性系数0.9
		//		printf("w[2][%d][%d]=%f\n", i, j, w[2][i][j]);
	}
	for (i = 1; i <= m; i++)
	for (j = 1; j <= n; j++)
	{
		w[3][i][j] = 0.9*w[3][i][j] + wc[3][i][j];
		//		printf("w[3][%d][%d]=%f\n", i, j, w[3][i][j]);
	}
}
void BP::changeb(int m, int n)
{
	int j;

	for (j = 1; j <= m; j++)
		b[2][j] = b[2][j] + bc[2][j];
	for (j = 1; j <= n; j++)
		b[3][j] = b[3][j] + bc[3][j];
}
void BP::clearwc(void)
{
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 10; j++)
	for (int k = 0; k < 10; k++)
		wc[i][j][k] = 0.00;
}
void BP::clearbc(void)
{
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 10; j++)
		bc[i][j] = 0.00;
}
void BP::initialw(void)
{
	int i, j, k, x;
	double weight;
	for (i = 0; i < 4; i++)
	for (j = 0; j < 10; j++)
	for (k = 0; k < 10; k++)
	{
		srand(clock());
		x = 100 + rand() % 400;
		weight = (double)x / 5000.00;
		w[i][j][k] = weight;
	}
}
void BP::initialb(void)
{
	int i, j, x;
	double fazhi;
	for (i = 0; i < 4; i++)
	for (j = 0; j < 10; j++)
	{
		srand(clock());
		for (int k = 0; k < 12; k++)
		{
			x = 100 + rand() % 400;
		}
		fazhi = (double)x / 50000.00;
		b[i][j] = fazhi;
	}
}
void BP::calculdiffer(void)
{
	a = count - 1;
	differ = 0.5*(o[3][1] - sample[a][3])*(o[3][1] - sample[a][3]);
}
void BP::calculis(void)
{
	int i;
	is = 0.0;

	for (i = 0; i <= 60; i++)
	{
		o[1][1] = sample[i][0];
		o[1][2] = sample[i][1];
		o[1][3] = sample[i][2];
		netout(8, 1);
		is = is + (o[3][1] - sample[i][3])*(o[3][1] - sample[i][3]);
	}
	is = is / 60;
}
void BP::trainNN(void)
{
	long int time;
	initialw();
	initialb();

	for (time = 1; time <= MAX; time++)
	{
		count = 0;
		while (count <= 60)
		{
			o[1][1] = sample[count][0];
			o[1][2] = sample[count][1];
			o[1][3] = sample[count][2];

			count = count + 1;
			clearwc();
			clearbc();
			netout(8, 1);
			calculdiffer();
			while (differ > ERROR)
			{
				calculd(8, 1);
				calculwc(8, 1);
				calculbc(8, 1);
				changew(8, 1);
				changeb(8, 1);
				netout(8, 1);
				calculdiffer();
			}
		}
		printf("This is %d times training NN...\n", time);
		calculis();
		printf("is==%f\n", is);
		if (is < ACCURACY) break;
	}
}
