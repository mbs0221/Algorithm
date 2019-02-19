#include <stdio.h>
#include "algorithm.h"

void print(int nums[], int n){
	printf("result:\n%3d", nums[0]);
	for (int i = 1; i < n; i++)
	{
		printf(" %3d", nums[i]);
	}
	printf("\n");
}

void main(int argc, char* argv[])
{
	int nums[] = { 1,-3,5,7,9,2,4,-6,-13,5,7,9,-2,3,5,6,-8,10,12 };
	int start;
	DPSolver dp;
	dp.Reset();
	dp.MaxiumSubsequenceSum(nums, start);
	print(nums, 19);
	printf("MaxiumSubsequenceSum start at:%d", start);
	getchar();
}