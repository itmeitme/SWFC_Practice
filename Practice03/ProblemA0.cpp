//wrong answer
#pragma warning (disable:4996)

#include <stdio.h>
#define MAX (int)(1e9)

typedef struct st {
	long long int poman;
	int hot;
	int node;
}FOOD;

FOOD fd[262145];
int N, result = MAX, maxhot[2], food[100000][2]; //0은 포만감, 1은 매운정도
long long int M;

void inputData(void)
{
	scanf("%d %lld", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &food[i][0], &food[i][1]);
		if (food[i][1] > maxhot[1]) maxhot[1] = food[i][1], maxhot[0] = i;
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
	if (qs > e || s > qe) return { 0,0,0 };

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

int main(void)
{
	inputData();
	for (int i = 0; i < N; i++)
		initSegment(1, 1, N, i + 1, food[i]);
	for (int i = 1; i <= N; i++) {
		FOOD L, R;
		int left, right;
		if (maxhot[0] == i - 1) {
			if (fd[1].poman >= M && maxhot[1] < result) result = maxhot[1];
		}
		else {
			L = queryData(1, 1, N, 1, i), R = queryData(1, 1, N, i, N);
			left = (food[i - 1][1] < L.hot) ? L.node + 1 : L.node;
			right = (food[i - 1][1] < R.hot) ? R.node - 1 : R.node;
			if (left == right && food[i - 1][0] >= M && food[i - 1][1] < result) result = food[i - 1][1];
			else if (sumData(1, 1, N, left, right) >= M && food[i - 1][1] < result) result = food[i - 1][1];
		}
	}
	printf("%d\n", result);
	return 0;
}
