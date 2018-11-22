//

#include <iostream>
#include <stdio.h>
using namespace std;

int N, K, heapPiSize = 0, heapCiSize = 0, result = 0;
long long int M, heapPi[50001][3], heapCi[50001][3]; // 0 : 노드 번호, 1 : 정상가격 Pi, 2 : 쿠폰가격 Ci
bool visited[50001];


int heapPush(long long int heap[50001][3], int *heapSize, int node, long long int pi, long long int ci, int comp)
{
	if ((*heapSize) + 1 > 50000)
		return 0;

	heap[*heapSize][0] = node, heap[*heapSize][1] = pi, heap[*heapSize][2] = ci;

	int current = *heapSize;
	if (comp == 1) {
		while (current > 0 && heap[current][1] < heap[(current - 1) / 2][1])
		{
			long long int temp[3];
			temp[0] = heap[(current - 1) / 2][0], temp[1] = heap[(current - 1) / 2][1], temp[2] = heap[(current - 1) / 2][2];
			heap[(current - 1) / 2][0] = heap[current][0], heap[(current - 1) / 2][1] = heap[current][1], heap[(current - 1) / 2][2] = heap[current][2];
			heap[current][0] = temp[0], heap[current][1] = temp[1], heap[current][2] = temp[2];
			current = (current - 1) / 2;
		}
	}
	else {
		while (current > 0 && heap[current][1] > heap[(current - 1) / 2][1])
		{
			long long int temp[3];
			temp[0] = heap[(current - 1) / 2][0], temp[1] = heap[(current - 1) / 2][1], temp[2] = heap[(current - 1) / 2][2];
			heap[(current - 1) / 2][0] = heap[current][0], heap[(current - 1) / 2][1] = heap[current][1], heap[(current - 1) / 2][2] = heap[current][2];
			heap[current][0] = temp[0], heap[current][1] = temp[1], heap[current][2] = temp[2];
			current = (current - 1) / 2;
		}
	}

	*heapSize = (*heapSize) + 1;

	return 1;
}

int heapPop(long long int heap[50001][3], int *heapSize, long long int *node, long long int *pi, long long int *ci, int comp)
{
	if (*heapSize <= 0)
	{
		return -1;
	}

	*node = heap[0][0], *pi = heap[0][1], *ci = heap[0][2];
	*heapSize = *heapSize - 1;

	heap[0][0] = heap[*heapSize][0], heap[0][1] = heap[*heapSize][1], heap[0][2] = heap[*heapSize][2];
	heap[*heapSize][0] = heap[*heapSize][1] = heap[*heapSize][2] = 0;

	int current = 0;
	while (current * 2 + 1 < *heapSize)
	{
		int child;
		if (current * 2 + 2 == *heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			if (comp == 1) child = heap[current * 2 + 1][1] < heap[current * 2 + 2][1] ? current * 2 + 1 : current * 2 + 2;
			else child = heap[current * 2 + 1][1] > heap[current * 2 + 2][1] ? current * 2 + 1 : current * 2 + 2;
		}

		if (comp == 1) {
			if (heap[current][1] < heap[child][1])
			{
				break;
			}
		}
		else {
			if (heap[current][1] > heap[child][1])
			{
				break;
			}
		}

		long long int temp[3];
		temp[0] = heap[current][0], temp[1] = heap[current][1], temp[2] = heap[current][2];
		heap[current][0] = heap[child][0], heap[current][1] = heap[child][1], heap[current][2] = heap[child][2];
		heap[child][0] = temp[0], heap[child][1] = temp[1], heap[child][2] = temp[2];

		current = child;
	}
	return 1;
}

void inputData(void)
{
	scanf("%d %d %lld", &N, &K, &M);
	for (int i = 1; i <= N; i++) {
		long long int pi, ci;
		scanf("%lld %lld", &pi, &ci);
		if (heapPush(heapPi, &heapPiSize, i, pi, ci, 1) && heapPush(heapCi, &heapCiSize, i, pi, ci, 2)) continue;
	}
}

int findData(void)
{
	long long int compPi[3] = { 0,0,0 }, compCi[3] = { 0,0,0 }; //0 : 노드 번호, 1 : pi, 2 : ci
	while (M >= 0) {
		if (heapPiSize <= 0 && heapCiSize <= 0) return 0;
		while (compPi[0]==0) {
			if (heapPop(heapPi, &heapPiSize, &compPi[0], &compPi[1], &compPi[2], 1)) {
				if (visited[compPi[0]]) compPi[0] = 0;
				else continue;
			}
		}
		while (K > 0 && compCi[0] == 0) {
			if (heapPop(heapCi, &heapCiSize, &compCi[0], &compCi[1], &compCi[2], 2)) {
				if (visited[compCi[0]]) compCi[0] = 0;
				else continue;
			}
		}

		if (K > 0) {
			if (compPi[1] >= compCi[2]) {
				K--;
				M -= compCi[2];
				visited[compCi[0]] = true;
				if (compCi[0] == compPi[0]) compPi[0] = 0;
				compCi[0] = 0;
			}
			else {
				M -= compPi[1];
				visited[compPi[0]] = true;
				compPi[0] = 0;
			}
		}
		else {
			M -= compPi[1];
			visited[compPi[0]] = true;
			compPi[0] = 0;
		}

		result++;
	}
	result--;
	return 1;
}

int main(void)
{
	inputData();
	if(findData())	printf("%d\n", result);
	
	return 0;
}
