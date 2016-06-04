#include <math.h>
#include <easyx.h>
#include <graphics.h>
#include <iostream>
#include <vector>
#include <array>

using namespace std;

struct Point{
	int x, y;
};

struct Edge{
	int x;
	float dx;
	int ymax;
	void print(){
		printf("[%2d %.02f %2d]->", x, dx, ymax);
	}
	friend bool operator <(Edge &a, Edge &b){
		if (a.x < b.x)return true;
		if (a.x == b.x && a.dx < b.dx)return true; 
		return false;
	}
};

class Graphics{
public:
	void dda_line(int x0, int y0, int x1, int y1);
	void mid_line(int x0, int y0, int x1, int y1);
	void circle1(int x, int y, int r);
	void circle2(int x, int y, int r);
	void polygon(vector<Point> &p);
};