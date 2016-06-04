#include <iomanip>
#include <iostream>

using namespace std;

void knap_sack(int N, int capacity)//NΪ��Ʒ����capacityΪ��������
{
	int *weight = new int[N];//ÿ����Ʒ����
	int *value = new int[N];//ÿ����Ʒ��ֵ
	int **C = new int*[N + 1];//����ֵ����
	int *select = new int[N];//����Ʒװ��״̬
	cout << "N:" << N << ",capacity:" << capacity << endl;
	for (int i = 0; i < N; i++)//��ʼ��ÿ����Ʒ��������ֵ
	{
		weight[i] = rand() % N + 1;
		value[i] = rand() % N + 1;
		cout << setw(2) << i + 1 << " w:" << weight[i] << " v:" << value[i] << endl;
	}
	for (int i = 0; i <= N; i++)//��ʼ������ֵ���������Ϊ0ʱ�ļ�ֵ
	{
		C[i] = new int[capacity + 1];
		C[i][0] = 0;
	}
	for (int i = 0; i <= capacity; i++)//��ʼ��ѡ0����Ʒ
	{
		C[0][i] = 0;
	}
	for (int i = 1; i <= N; i++)//�������Ž�
	{
		for (int j = 1; j <= capacity; j++)//jΪ��ǰ�������ֵ
		{
			if (weight[i - 1] <= j)//��װ��һ����Ʒһ����Ϊ����õ�i����Ʒ��weight��value��iӦ��-1
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
			else//��ȥi��Ʒ�������ļ�ֵ�ͼ���i��Ʒ�����ļ�ֵ�Ƚ�
			{
				C[i][j] = C[i - 1][j];
			}
		}
	}
	//����б�
	cout << " C";
	for (int i = 0; i <= capacity; i++)
		cout << setw(3) << i;
	cout << endl;
	//����б�
	for (int i = 0; i <= N; i++)
	{
		cout << setw(2) << i << ":";
		for (int j = 0; j <= capacity; j++)
		{
			cout << setw(2) << C[i][j] << " ";
		}
		cout << endl;
	}
	//�����Ƿ�װ���i����Ʒ
	int j = capacity;
	for (int i = N; i > 0; i--)
	{
		if (C[i][j] > C[i - 1][j])//װ��i�����˼�ֵ��װ��
		{
			select[i - 1] = 1;
			j -= weight[i - 1];
		}
		else//��ֵû����������װ��
		{
			select[i - 1] = 0;
		};
	}
	//���0-1ѡ��״̬
	cout << "select:";
	for (int i = 0; i < N; i++)
	{
		cout << setw(2) << select[i] << " ";
	}
	cout << endl;
}

void gena_knap_sack(int N, int capacity)
{
	int *weight = new int[N];//ÿ����Ʒ����
	int *value = new int[N];//ÿ����Ʒ��ֵ
	int **C = new int*[N + 1];//����ֵ����
	int *select = new int[N];//����Ʒװ��״̬
	cout << "N:" << N << ",capacity:" << capacity << endl;
	for (int i = 0; i < N; i++)//��ʼ��ÿ����Ʒ��������ֵ
	{
		weight[i] = rand() % N + 1;
		value[i] = rand() % N + 1;
		select[i] = 0;
		cout << setw(2) << i + 1 << " w:" << weight[i] << " v:" << value[i] << endl;
	}
	for (int i = 0; i <= N; i++)//��ʼ������ֵ���������Ϊ0ʱ�ļ�ֵ
	{
		C[i] = new int[capacity + 1];
		C[i][0] = 0;
	}
	for (int i = 0; i <= capacity; i++)//��ʼ��ѡ0����Ʒ
	{
		C[0][i] = 0;
	}
	for (int i = 1; i <= N; i++)//�������Ž�
	{
		for (int j = 1; j <= capacity; j++)//jΪ��ǰ�������ֵ
		{
			if (weight[i - 1] <= j)
			{
				if (C[i - 1][j - weight[i - 1]] + value[i - 1] > C[i - 1][j])
				{
					//C[i][j] = C[i - 1][j - weight[i - 1]] + value[i - 1];0-1��������
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
	//����б�
	cout << " C";
	for (int i = 0; i <= capacity; i++)
		cout << setw(3) << i;
	cout << endl;
	//����б�
	for (int i = 0; i <= N; i++)
	{
		cout << setw(2) << i << ":";
		for (int j = 0; j <= capacity; j++)
		{
			cout << setw(2) << C[i][j] << " ";
		}
		cout << endl;
	}
	//�����Ƿ�װ���i����Ʒ
	int j = capacity;
	for (int i = N; i > 0; i--)
	{
		while (C[i][j] > C[i - 1][j])//װ��i�����˼�ֵ��װ��
		{
			select[i - 1]++;//�ۼ�i��Ʒ
			j -= weight[i - 1];//��ȥͬ����Ʒ������
		}
	}
	//���0-1ѡ��״̬
	cout << "select:";
	for (int i = 0; i < N; i++)
	{
		cout << setw(2) << select[i] << " ";
	}
	cout << endl;
}