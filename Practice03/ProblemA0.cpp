//ACCEPT

#include <stdio.h>
#define MAX (int)(1e9)

typedef struct st {
	long long int poman;
	int hot;
	int node;
}FOOD;

FOOD fd[262145];
int N, result = MAX, food[100001][2], heap[100000][2], left, right; //0은 포만감, 1은 매운정도
int heapSize = 0;
long long int M;

int heapPush(int node, int hot)
{
	if (heapSize + 1 > MAX)
		return 0;

	heap[heapSize][0] = node, heap[heapSize][1] = hot;

	int current = heapSize;
	while (current > 0 && heap[current][1] < heap[(current - 1) / 2][1])
	{
		int temp[2];
		temp[0] = heap[(current - 1) / 2][0], temp[1] = heap[(current - 1) / 2][1];
		heap[(current - 1) / 2][0] = heap[current][0], heap[(current - 1) / 2][1] = heap[current][1];
		heap[current][0] = temp[0], heap[current][1] = temp[1];
		current = (current - 1) / 2;
	}

	heapSize = heapSize + 1;

	return 1;
}

int heapPop(int *node, int *hot)
{
	if (heapSize <= 0)
	{
		return -1;
	}

	*node = heap[0][0], *hot = heap[0][1];
	heapSize = heapSize - 1;

	heap[0][0] = heap[heapSize][0], heap[0][1] = heap[heapSize][1];
	heap[heapSize][0] = heap[heapSize][1] = 0;

	int current = 0;
	while (current * 2 + 1 < heapSize)
	{
		int child;
		if (current * 2 + 2 == heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			child = heap[current * 2 + 1][1] < heap[current * 2 + 2][1] ? current * 2 + 1 : current * 2 + 2;
		}

		if (heap[current][1] < heap[child][1])
		{
			break;
		}

		int temp[2];
		temp[0] = heap[current][0], temp[1] = heap[current][1];
		heap[current][0] = heap[child][0], heap[current][1] = heap[child][1];
		heap[child][0] = temp[0], heap[child][1] = temp[1];

		current = child;
	}
	return 1;
}

void inputData(void)
{
	scanf("%d %lld", &N, &M);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &food[i][0], &food[i][1]);
		if (heapPush(i, food[i][1])) continue;
	}
}

void initSegment(int node, int s, int e, int idx, int *data)
{
	int m;
	if (s == e) {
		fd[node].poman = data[0], fd[node].hot = data[1];
		fd[node].node = idx;
		return;
	}

	m = (s + e) / 2;

	if (idx <= m) initSegment(node * 2, s, m, idx, data);
	else initSegment(node * 2 + 1, m + 1, e, idx, data);

	fd[node] = (fd[node * 2].hot > fd[node * 2 + 1].hot) ? fd[node * 2] : fd[node * 2 + 1];
	fd[node].poman = fd[node * 2].poman + fd[node * 2 + 1].poman;
}

FOOD queryData(int node, int s, int e, int qs, int qe)
{
	int m;
	FOOD l, r;

	if (qs <= s && e <= qe) return fd[node];
	if (qs > e || s > qe) return{ 0, 0, 0 };

	m = (s + e) / 2;

	l = queryData(node * 2, s, m, qs, qe);
	r = queryData(node * 2 + 1, m + 1, e, qs, qe);

	return (l.hot < r.hot) ? r : l;
}

long long int sumData(int node, int s, int e, int qs, int qe)
{
	int m;
	long long int l, r;

	if (qs <= s && e <= qe) return fd[node].poman;
	if (qs > e || s > qe) return 0;

	m = (s + e) / 2;

	l = sumData(node * 2, s, m, qs, qe);
	r = sumData(node * 2 + 1, m + 1, e, qs, qe);

	return l + r;
}

void findBigger(int i)
{
	int cnt = 1;

	while (i - cnt >= 1 && food[i - cnt][1] <= food[i][1]) cnt++;
	left = i - cnt + 1;
	cnt = 1;
	while (i + cnt <= N && food[i + cnt][1] <= food[i][1]) cnt++;
	right = i + cnt - 1;
}

int main(void)
{
	inputData();
	for (int i = 1; i <= N; i++)
		initSegment(1, 1, N, i, food[i]);
	for (int i = 1; i <= N; i++) {
		int node, hot;
		if (heapPop(&node, &hot)) findBigger(node);
		if (left == right && food[node][0] >= M && hot < result) {
			result = hot; break;
		}
		else if (sumData(1, 1, N, left, right) >= M && hot < result) {
			result = hot; break;
		}
	}
	printf("%d\n", result);
	return 0;
}
