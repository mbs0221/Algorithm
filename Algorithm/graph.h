#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <stack>
#include <list>
#include <array>
#include <omp.h>

using namespace std;

#define MAX 6233

class Graph{
private:
	int N;
	int **matrix;
	int *visited;
	int *indegree;
	char **name;
public:
	Graph(){
	}
	~Graph(){
	}
	const int UNVISITED = 0;//δ������
	const int VISITED = 1;//�ѷ���
	void init_matrix(char *path)
	{
		fstream fin(path);
		if (!fin.is_open())
		{
			cout << "open file failed!" << endl;
			return;
		}
		fin >> N;
		matrix = new int*[N];
		visited = new int[N];
		indegree = new int[N];
		name = new char*[N];
		for (int i = 0; i < N; i++)
		{
			indegree[i] = 0;//��ʼ�����
		}
		for (int i = 0; i < N; i++)
		{
			matrix[i] = new int[N];
			name[i] = new char[5];
			visited[i] = UNVISITED;//δ���ʱ��
			for (int j = 0; j < N; j++)
			{
				fin >> matrix[i][j];
				if (matrix[i][j] > 0 && matrix[i][j] != MAX)indegree[j]++;//����j�����
			}
			matrix[i][i] = 0;
		}
		for (int i = 0; i < N; i++)
		{
			fin >> name[i];
		}
		fin.close();
	}
	void init_matrix(int **path, int n)
	{
		N = n;
		matrix = new int*[N];
		visited = new int[N];
		indegree = new int[N];	
		for (int i = 0; i < N; i++)
		{
			indegree[i] = 0;//��ʼ�����
		}
		for (int i = 0; i < N; i++)
		{
			matrix[i] = new int[N];
			visited[i] = UNVISITED;//δ���ʱ��
			for (int j = 0; j < N; j++)
			{
				matrix[i][j] = path[i][j];
				if (matrix[i][j] > 0 && matrix[i][j] != MAX)indegree[j]++;//����j�����
			}
			matrix[i][i] = 0;
		}
	}
	void init_matrix(int n)
	{
		N = n;
		matrix = new int*[N];
		visited = new int[N];
		indegree = new int[N];
		for (int i = 0; i < N; i++)
		{
			indegree[i] = 0;//��ʼ�����
		}
		for (int i = 0; i < N; i++)
		{
			matrix[i] = new int[N];
			visited[i] = UNVISITED;//δ���ʱ��
			for (int j = 0; j < N; j++)
			{
				matrix[i][j] = rand() % N + 1;
				if (rand()<0x0fff)matrix[i][j] = MAX;
				if (matrix[i][j] > 0 && matrix[i][j] != MAX)indegree[j]++;//����j�����
			}
			matrix[i][i] = 0;
		}
	}
	int get_id(char *str)
	{
		for (int i = 0; i < N; i++)
		{
			if (!strcmp(name[i], str))
			{
				return i;
			}
		}
	}
	void show_matrix()
	{
		cout << "matrix:" << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (matrix[i][j] == MAX)
					cout << setw(2) << "M" << " ";
				else
					cout << setw(2) << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	void dfs(int start, int n)
	{
		visited[start] = VISITED;
		cout << setw(5 * (n + 1)) << "visit:" << start << endl;
		for (int i = 0; i < N; i++)
		{
			if (matrix[start][i] != MAX && visited[i] == UNVISITED)
			{
				dfs(i, n + 1);
			}
		}
	}
	void bfs(int start)
	{
		queue<int> q;
		q.push(start);
		visited[start] = VISITED;
		while (!q.empty())
		{
			int now = q.front();
			cout << now << "-->" << endl;
			for (int i = 0; i < N; i++)
			{
				if (matrix[now][i] != MAX && visited[i] == UNVISITED)
				{
					visited[i] = VISITED;
					q.push(i);
				}
			}
			q.pop();
		}
	}
	void topo_sort()
	{
		queue<int> q;
		cout << "topo sort:" << endl;
		for (int i = 0; i < N; i++)
		{
			if (indegree[i] == 0)
			{
				q.push(i);
			}
		}//���Ϊ0�����
		while (!q.empty())
		{
			int now = q.front();
			cout << "topo:" << now << endl;
			for (int i = 0; i < N; i++)
			{
				if (matrix[now][i] != MAX){
					indegree[i]--;
					if (indegree[i] == 0)
					{
						q.push(i);
						visited[i] = VISITED;
					}//����1�����Ϊ0 �Ľڵ����
				}//���ڽڵ�
			}
			q.pop();
		}
		for (int i = 0; i < N; i++)
		{
			if (visited[i] == UNVISITED)
			{
				cout << "topo ring:" << i << endl;
			}
		}
	}
	//Dijkstra�㷨
	void dijkstra(int start, int end)
	{
		int *path = new int[N];//·��
		int *distance = new int[N];//����
		cout << "dijkstra:" << endl;
		clock_t begin = clock();
		for (int i = 0; i < N; i++)
		{
			visited[i] = UNVISITED;//��ʼ�������б�
			if (i != start)
			{
				path[i] = start;//��ʼ��·��
				distance[i] = matrix[start][i];//��ʼ�������нڵ����̾���
			}
		}//��ʼ��start���������·��
		path[start] = start;
		distance[start] = 0;
		visited[start] = VISITED;
		for (int i = 0; i < N; i++)
		{
			int min = MAX;
			int midid = start;
			for (int j = 0; j < N; j++)
			{
				if (visited[j] == UNVISITED&&distance[j] < min)
				{
					min = distance[j];
					midid = j;
				}
			}//����뵱ǰ�ڵ������δ���ʽڵ�
			visited[midid] = VISITED;
			for (int k = 0; k < N; k++)
			{
				if (visited[k] == UNVISITED && min + matrix[midid][k] < distance[k])
				{
					distance[k] = min + matrix[midid][k];//���µ�k����̾���
					path[k] = midid;//����·��
				}
			}
		}
		cout << "path:" << endl;
		int u = end;
		cout << name[u];
		while (u!=start)
		{
			cout << "<--" << name[path[u]];
			u = path[u];
		}
		cout << endl;
		cout << "distance:" << distance[end] << endl;
		clock_t end_time = clock();
		cout << "time:" << end_time - begin << endl;
	}
	//Floyd�㷨
	void floyd()
	{
		int **distance;
		distance = new int*[N];
		for (int i = 0; i < N; i++){
			distance[i] = new int[N];
			for (int j = 0; j < N; j++){
				distance[i][j] = matrix[i][j];
			}
		}//��ʼ������
		for (int k = 0; k < N; k++){
			for (int i = 0; i < N; i++){
				for (int j = 0; j < N; j++){
					if (distance[i][j]>distance[i][k] + distance[k][j]){
						distance[i][j] = distance[i][k] + distance[k][j];
					}//���kʹ��d[i][j]��С�ˣ��͸ı�d[i][j]��ֵ
				}
			}
		}//floyd�㷨
		cout << "floyd:" << endl;
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				cout << setw(2) << distance[i][j] << " ";
			}
			cout << endl;
		}
	}
	//Prim�㷨
	void prim(int start)
	{
		int *path = new int[N];//��¼ǰһ���ڵ�
		int *distance = new int[N];//��¼��next��̾���
		cout << "prim:" << endl;
		for (int i = 0; i < N; i++)//��ʼ����start�ľ��룬·��
		{
			if (i != start)
			{
				path[i] = start;
				distance[i] = matrix[start][i];
				visited[i] = UNVISITED;
			}
		}
		visited[start] = VISITED;//start���Ϊ�ѷ���
		path[start] = start;
		distance[start] = 0;
		for (int i = 0; i < N; i++)//��С������prim�㷨
		{
			int min = MAX;//��̾���
			int minid = start;//����Ľڵ���
			for (int j = 0; j < N; j++)//�ҳ���һ����next��̵ľ���
			{
				if ((visited[j] == UNVISITED) && distance[j] < min)
				{
					minid = j;//����ڵ��id
					min = distance[j];//����ڵ�ľ���
				}
			}
			if (minid == start)break;//û���ҵ���һ��δ�����ʵĿɵ���ڵ㣬����ѭ��
			visited[minid] = VISITED;//���minid�ѷ���
			printf("%d-------->%d:%d\n", path[minid], minid, min);
			for (int j = 0; j < N; j++)//����distance[j]����һ���ڵ�ľ���
			{
				if (visited[j] == UNVISITED&&matrix[minid][j] < distance[j])//����δ���ʽڵ�ľ���
				{
					distance[j] = matrix[minid][j];
					path[j] = minid;
				}
			}
		}
		cout << "prim path:" << endl;
		for (int j = 0; j < N; j++)//�����С��������·��
		{
			cout << setw(2) << path[j] << "-->" << j << endl;
		}
	}
};
