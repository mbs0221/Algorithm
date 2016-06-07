#include "network.h"

void main(){
	FILE file;
	FILE *fp = &file;
	fopen_s(&fp, "Text.txt", "r");
	network net(fp);
	fclose(fp);
	net.train();
	net.selftest();
	net.test();
	getchar();
}