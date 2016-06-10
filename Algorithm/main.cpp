#include "network.h"

void main(){
	FILE file;
	FILE *fp = &file;
	// ¶ÁÈ¡×´Ì¬
	fopen_s(&fp, "Text.txt", "r");
	network net(fp);
	fclose(fp);
	initgraph(600, 320);
	net.train();
	// ±£´æ×´Ì¬
	fopen_s(&fp, "Text.txt", "w");
	net.save(fp);
	fclose(fp);
	getchar();
	closegraph();
}