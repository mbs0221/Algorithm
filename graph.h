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
	const int UNVISITED = 0;//未被访问
	const int VISITED = 1;//已访问
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
			indegree[i] = 0;//初始化入度
		}
		for (int i = 0; i < N; i++)
		{
			matrix[i] = new int[N];
			name[i] = new char[5];
			visited[i] = UNVISITED;//未访问标记
			for (int j = 0; j < N; j++)
			{
				fin >> matrix[i][j];
				if (matrix[i][j] > 0 && matrix[i][j] != MAX)indegree[j]++;//计算j的入度
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
			indegree[i] = 0;//初始化入度
		}
		for (int i = 0; i < N; i++)
		{
			matrix[i] = new int[N];
			visited[i] = UNVISITED;//未访问标记
			for (int j = 0; j < N; j++)
			{
				matrix[i][j] = path[i][j];
				if (matrix[i][j] > 0 && matrix[i][j] != MAX)indegree[j]++;//计算j的入度
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
			indegree[i] = 0;//初始化入度
		}
		for (int i = 0; i < N; i++)
		{
			matrix[i] = new int[N];
			visited[i] = UNVISITED;//未访问标记
			for (int j = 0; j < N; j++)
			{
				matrix[i][j] = rand() % N + 1;
				if (rand()<0x0fff)matrix[i][j] = MAX;
				if (matrix[i][j] > 0 && matrix[i][j] != MAX)indegree[j]++;//计算j的入度
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
		}//入度为0，入队
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
					}//减了1后入度为0 的节点入队
				}//相邻节点
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
	//Dijkstra算法
	void dijkstra(int start, int end)
	{
		int *path = new int[N];//路径
		int *distance = new int[N];//距离
		cout << "dijkstra:" << endl;
		clock_t begin = clock();
		for (int i = 0; i < N; i++)
		{
			visited[i] = UNVISITED;//初始化访问列表
			if (i != start)
			{
				path[i] = start;//初始化路径
				distance[i] = matrix[start][i];//初始化到所有节点的最短距离
			}
		}//初始化start出发的最短路径
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
			}//求出离当前节点最近的未访问节点
			visited[midid] = VISITED;
			for (int k = 0; k < N; k++)
			{
				if (visited[k] == UNVISITED && min + matrix[midid][k] < distance[k])
				{
					distance[k] = min + matrix[midid][k];//更新到k的最短距离
					path[k] = midid;//更新路径
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
	//Floyd算法
	void floyd()
	{
		int **distance;
		distance = new int*[N];
		for (int i = 0; i < N; i++){
			distance[i] = new int[N];
			for (int j = 0; j < N; j++){
				distance[i][j] = matrix[i][j];
			}
		}//初始化距离
		for (int k = 0; k < N; k++){
			for (int i = 0; i < N; i++){
				for (int j = 0; j < N; j++){
					if (distance[i][j]>distance[i][k] + distance[k][j]){
						distance[i][j] = distance[i][k] + distance[k][j];
					}//如果k使得d[i][j]变小了，就改变d[i][j]的值
				}
			}
		}//floyd算法
		cout << "floyd:" << endl;
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				cout << setw(2) << distance[i][j] << " ";
			}
			cout << endl;
		}
	}
	//Prim算法
	void prim(int start)
	{
		int *path = new int[N];//记录前一个节点
		int *distance = new int[N];//记录到next最短距离
		cout << "prim:" << endl;
		for (int i = 0; i < N; i++)//初始化到start的距离，路径
		{
			if (i != start)
			{
				path[i] = start;
				distance[i] = matrix[start][i];
				visited[i] = UNVISITED;
			}
		}
		visited[start] = VISITED;//start标记为已访问
		path[start] = start;
		distance[start] = 0;
		for (int i = 0; i < N; i++)//最小生成树prim算法
		{
			int min = MAX;//最短距离
			int minid = start;//最近的节点编号
			for (int j = 0; j < N; j++)//找出下一个到next最短的距离
			{
				if ((visited[j] == UNVISITED) && distance[j] < min)
				{
					minid = j;//最近节点的id
					min = distance[j];//最近节点的距离
				}
			}
			if (minid == start)break;//没有找到下一个未被访问的可到达节点，跳出循环
			visited[minid] = VISITED;//标记minid已访问
			printf("%d-------->%d:%d\n", path[minid], minid, min);
			for (int j = 0; j < N; j++)//更新distance[j]到上一个节点的距离
			{
				if (visited[j] == UNVISITED&&matrix[minid][j] < distance[j])//更新未访问节点的距离
				{
					distance[j] = matrix[minid][j];
					path[j] = minid;
				}
			}
		}
		cout << "prim path:" << endl;
		for (int j = 0; j < N; j++)//输出最小生成树的路径
		{
			cout << setw(2) << path[j] << "-->" << j << endl;
		}
	}
};
