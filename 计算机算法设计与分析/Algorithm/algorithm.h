#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define M 19
#define N 19

class DPSolver
{
	int dp[N];
public:
	// ��ȡ���
	int *GetResult() 
	{
		return dp;
	}
	// ����
	void Reset()
	{
		memset(dp, 0, sizeof(int)*N);
	}
	// ��������½�������
	void LongestAscentSequence(int nums[]) 
	{
		memset(dp, 0, sizeof(int)*N);
		for (int i = 0; i < N; i++) {
			dp[i] = 1;
			for (int k = 0; k < i; k++) {
				if ((nums[k] < nums[i]) && (dp[i] < (dp[k] + 1)))
				{
					dp[i] = dp[k] + 1;
				}
			}
		}
	}
	// ��������еĺ�����
	void MaxiumSubsequenceSum(int nums[], int &first)
	{
		int max = 0, index = -1;
		int a0, a1;
		a0 = nums[0];
		first = -1;
		int start = 0;
		for (int i = 1; i < N; i++)
		{
			a1 = a0 + nums[i];// ����
			if (nums[i] < 0)
			{
				a1 = 0;
				start = i + 1;
			}
			if (max < a1)
			{
				max = a1;
				first = start;
			}
			a0 = a1;
		}
	}
	// 01��������
	void OneZeroBagPack(int v[], int c[], int n)
	{
		
	}
};