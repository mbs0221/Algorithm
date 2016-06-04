#include "graphics.h"

#define COLOR RGB(255, 255, 172)

void inline setpixel(int x, int y, int x0, int y0){
	putpixel(x + x0, y + y0, COLOR);
	putpixel(x + x0, -y + y0, COLOR);
	putpixel(-x + x0, y + y0, COLOR);
	putpixel(-x + x0, -y + y0, COLOR);
	putpixel(y + x0, x + y0, COLOR);
	putpixel(y + x0, -x + y0, COLOR);
	putpixel(-y + x0, x + y0, COLOR);
	putpixel(-y + x0, -x + y0, COLOR);
}
// 数值微分法
void Graphics::dda_line(int x0, int y0, int x1, int y1)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	float k = dy / dx;
	float x = x0;
	float y = y0;
	if (dx > dy)
	{
		for (x = x0; x < x1; x++)
		{
			putpixel((int)round(x), (int)y, RGB(255, 255, 0));
			y += k;
		}
	}
	else
	{
		for (y = y0; y < y1; y++)
		{
			putpixel((int)x, (int)round(y), RGB(255, 255, 0));
			x += 1 / k;
		}
	}
}
// 中点画线法
void Graphics::mid_line(int x0, int y0, int x1, int y1)
{
	int a, b, d1, d2, d, x, y;
	float k = (y1 - y0) / (x1 - x0);
	a = y0 - y1, b = x1 - x0, d = 2 * a + b;
	if (k > 1){
		// L[x+1][y+1]->H[x][y+1]
		d1 = 2 * (a + b), d2 = 2 * b;
	}
	else if (k >= 0){
		// L[x+1][y]->H[x+1][y+1]
		d1 = 2 * a, d2 = 2 * (a + b);
	}
	else if (k >= -1){
		// L[x+1][y-1]->H[x+1][y]
		d1 = 2 * (a - b), d2 = 2 * a;
	}
	else{
		// [x][y-1]->[x+1][y-1]
		d1 = 2 * -b, d2 = 2 * (a - b);
	}
	x = x0, y = y0;
	putpixel(x, y, COLOR);
	while (x < x1){
		if (d < 0){
			x++, y++, d += d2;
		}
		else{
			x++, d += d1;
		}
		putpixel(x, y, COLOR);
	}
}
// 中点画圆算法
void Graphics::circle1(int x0, int y0, int r){
	int x, y;
	float d;
	x = 0, y = r, d = 1 - r;
	float d1 = 3, d2 = 5 - 2 * r;
	setpixel(x, y, x0, y0);
	while (y > x){
		if (d < 0){
			d += d1; d2 += 2;
		}
		else{
			d += d2; d2 += 4; y--;
		}
		d1 += 2;
		x++;
		setpixel(x, y, x0, y0);
	}
}
// Bresenham画圆算法
void Graphics::circle2(int x0, int y0, int r)
{
	int x, y;
	int dH, dL, d;
	x = 0;
	y = r;
	setpixel(x, y, x0, y0);
	while (y > x){
		dH = (x + 1)*(x + 1) + y*y - r*r;
		dL = (x + 1)*(x + 1) + (y - 1)*(y - 1) - r*r;
		d = dH + dL;
		if (d >= 0)
		{
			setpixel(x + 1, y - 1, x0, y0);
			x = x + 1;
			y = y - 1;
		}
		else
		{
			setpixel(x + 1, y, x0, y0);
			x = x + 1;
		}
	}
}
// 多边形扫描转换
void Graphics::polygon(vector<Point> &ps){
	vector<Edge> VET[320];
	vector<Edge> AET;
	int x, ymax;
	int size = ps.size();
	float dx;
	for (int i = 0; i < 320; i++){
		for (int j = 0; j < size - 1; j++){
			if (ps[j].y == i){
				// 添加边
				if (ps[j + 1].y>ps[j].y){
					x = ps[j].x;
					dx = ((float)(ps[j + 1].x - ps[j].x)) / (ps[j + 1].y - ps[j].y);
					ymax = ps[j + 1].y;
					VET[ps[j].y].push_back(Edge{x, dx, ymax});
				}
				else if (ps[j + 1].y < ps[j].y){
					x = ps[j + 1].x;
					dx = ((float)(ps[j].x - ps[j + 1].x)) / (ps[j].y - ps[j + 1].y);
					ymax = ps[j].y;
					VET[ps[j + 1].y].push_back(Edge{ x, dx, ymax });
				}
			}
		}
	}
	vector<Edge>::iterator iter;
	AET.clear();
	for (int y = 0; y < 320; y++){
		// 若ET中第y类元素非空
		if (!VET[y].empty()){
			// 将ET中有关y扫描线的信息和并到AET中
			AET.insert(AET.begin(), VET[y].begin(), VET[y].end());
			// 使AET按x递增顺序排列;
			sort(AET.begin(), AET.end());
			// 对于扫描线y, 取AET中两两一对x坐标, 填充所需的象素值(color);
		}
		int size = AET.size();
		for (int j = 1; j < size; j++){
			line(AET[j].x, y, AET[j - 1].x, y);;
		}
		for (iter = AET.begin(); iter != AET.end(); iter++){
			if (iter->ymax == y){
				// 从AET中删去y = ymax的项;
				AET.erase(iter);
				iter = AET.begin();
			}
			else{
				// 对AET中保留的项,令x=x+1/m;(即xi+1=xi+x);
				iter->x += iter->dx;
			}
		}
	}
}