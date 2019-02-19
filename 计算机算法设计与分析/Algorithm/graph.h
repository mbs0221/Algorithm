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
		for (int i = 0; i < N; i++){
			if (indegree[i] == 0){
				q.push(i);
				visited[i] = VISITED;
			}
		}//入度为0，入队
		while (!q.empty()){
			int now = q.front();
			cout << "topo:" << now << endl;
			for (int i = 0; i < N; i++){
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
		for (int i = 0; i < N; i++){
			if (visited[i] == UNVISITED){
				cout << "topo ring:" << i << endl;
			}
		}
	}
	void dijkstra(int start, int end)
	{
		int *path = new int[N];//路径
		int *distance = new int[N];//距离
		cout << "dijkstra:" << endl;
		clock_t begin = clock();
		//初始化访问列表
		for (int i = 0; i < N; i++){
			visited[i] = UNVISITED;
			if (i != start){
				path[i] = start;//初始化路径
				distance[i] = matrix[start][i];//初始化到所有节点的最短距离
			}
		}//初始化start出发的最短路径
		path[start] = start;
		distance[start] = 0;
		visited[start] = VISITED;
		for (int i = 0; i < N; i++){
			//求出离当前节点最近的未访问节点
			int min = MAX;
			int mid = start;
			for (int j = 0; j < N; j++){
				if (visited[j] == UNVISITED&&distance[j] < min){
					min = distance[j];
					mid = j;
				}
			}
			// 标记mid已访问
			visited[mid] = VISITED;
			// 更新经过mid后到其他节点的距离
			for (int k = 0; k < N; k++){
				if (visited[k] == UNVISITED && min + matrix[mid][k] < distance[k]){
					distance[k] = min + matrix[mid][k];//更新到k的最短距离
					path[k] = mid;//更新到k的前一个节点
				}
			}
		}
		// 反向输出路径
		cout << "path:" << endl;
		int u = end;
		cout << name[u];
		while (u!=start){
			cout << "<--" << name[path[u]];
			u = path[u];
		}
		cout << endl;
		cout << "distance:" << distance[end] << endl;
		clock_t end_time = clock();
		cout << "time:" << end_time - begin << endl;
	}
	void floyd()
	{
		int **distance, **path;
		distance = new int*[N];
		path = new int*[N];
		for (int i = 0; i < N; i++){
			distance[i] = new int[N];
			path[i] = new int[N];
			for (int j = 0; j < N; j++){
				distance[i][j] = matrix[i][j];
				path[i][j] = i == j ? i : -1;
			}
		}//初始化距离
		for (int k = 0; k < N; k++){
			for (int i = 0; i < N; i++){
				for (int j = 0; j < N; j++){
					//如果经过k距离变短，则更新距离路径
					if (distance[i][j]>distance[i][k] + distance[k][j]){
						distance[i][j] = distance[i][k] + distance[k][j];
						path[i][j] = path[k][j];
					}
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
	void prim(int start)
	{
		int *path = new int[N];//记录前一个节点
		int *distance = new int[N];//记录到next最短距离
		cout << "prim:" << endl;
		//初始化到start的距离，路径
		for (int i = 0; i < N; i++){
			if (i != start){
				path[i] = start;
				distance[i] = matrix[start][i];
				visited[i] = UNVISITED;
			}
		}
		visited[start] = VISITED;//start标记为已访问
		path[start] = start;
		distance[start] = 0;
		//最小生成树prim算法
		for (int i = 0; i < N; i++){
			//找离当前生成树最近的顶点minid
			int min = MAX;
			int mid = start;
			for (int j = 0; j < N; j++){
				if ((visited[j] == UNVISITED) && distance[j] < min){
					mid = j;
					min = distance[j];
				}
			}
			if (mid == start)break;
			//标记minid已访问
			visited[mid] = VISITED;
			printf("%d-------->%d:%d\n", path[mid], mid, min);
			//更新distance[j]到上一个节点的距离
			for (int j = 0; j < N; j++){
				//更新未访问节点的距离和路径
				if (visited[j] == UNVISITED&&matrix[mid][j] < distance[j]){
					distance[j] = matrix[mid][j];
					path[j] = mid;
				}
			}
		}
		cout << "prim path:" << endl;
		//输出最小生成树的路径
		for (int j = 0; j < N; j++){
			cout << setw(2) << path[j] << "-->" << j << endl;
		}
	}
};