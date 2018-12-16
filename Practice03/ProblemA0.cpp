
#include <stdio.h>
#define abs(a) (a <0? -(a):(a))
#define max(a,b) ((a > b) ? (a):(b))
#define min(a,b) ((a < b) ? (a):(b))
int N, Q;

typedef struct _node {
	int sum;
	int max_val;
	int max_index;
}node;

node tree[400004];
int arr[100001][2];

node init(int node_val, int start, int end) {
	if (start == end) {
		//printf("start : %d  dist : %d\n", start, dist[start]);
		tree[node_val].sum = arr[start][0];
		tree[node_val].max_val = arr[start][1];
		tree[node_val].max_index = start;
		return tree[node_val];
	}
	int mid = (start + end) / 2;
	node a, b;
	a = init(node_val * 2, start, mid);
	b = init(node_val * 2 + 1, mid + 1, end);
	if (a.max_val > b.max_val) {
		tree[node_val].max_index = a.max_index;
	}
	else {
		tree[node_val].max_index = b.max_index;
	}

	tree[node_val].max_val = max(a.max_val, b.max_val);
	tree[node_val].sum = a.sum + b.sum;
	return tree[node_val];
}

node sum(int node_val, int start, int end, int left, int right) {
	node temp;
	if (left > end || right < start)
		return temp;
	if (left <= start && end <= right)
		return tree[node_val];
	int mid = (start + end) / 2;
	temp.sum = sum(node_val * 2, start, mid, left, right).sum + sum(node_val * 2 + 1, mid + 1, end, left, right).sum;
	temp.max_val = max(sum(node_val * 2, start, mid, left, right).max_val, sum(node_val * 2 + 1, mid + 1, end, left, right).max_val);
	return temp;
}

int main(void)
{

	int res=0;
	//freopen("input.txt", "r", stdin);
	scanf("%d %d", &N, &Q);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &arr[i][0], &arr[i][1]);
	}
	init(1, 1, N);
	printf("%d %d\n", sum(1,1,N,1,N).sum, sum(1, 1, N, 1, N).max_val);


	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}
