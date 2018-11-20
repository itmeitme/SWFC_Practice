#include <stdio.h>

#define MAXN 131072

class food
{
private:
	int* tree;
	int max(int a, int b)
	{
		return a > b ? a : b;
	}
public:
	food()
	{
		tree = new int[MAXN * 2]();
	}
	~food()
	{
		delete[] tree;
	}
	void insert(int idx, int val, int s, int e, int node = 1)
	{
		if (s > e)
			return;
		if (s == e)
		{
			tree[node] = val;
			return;
		}

		int m = (s + e) / 2;
		if (idx <= m)
			insert(idx, val, s, m, node * 2 + 0);
		else
			insert(idx, val, m + 1, e, node * 2 + 1);

		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}
	int query(int qs, int qe, int s, int e, int node = 1)
	{
		if (qs <= s && e <= qe)
			return tree[node];
		else if (qs > e || s > qe)
			return 0;

		int m = (s + e) / 2;
		int l = query(qs, qe, s, m, node * 2);
		int r = query(qs, qe, m + 1, e, node * 2 + 1);

		return max(l, r);
	}
};

int main(void)
{
	int N;
	long long M;
	scanf("%d %lld", &N, &M);

	food spicy;
	int* arr = new int[N + 1];

	int f, s;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d %d", &f, &s);
		arr[i] = f;
		spicy.insert(i, s, 1, N);
	}

	long long totalM = 0;
	int submaxS = 0;
	int minS = 0x7fffffff;


	int front = 1;
	int rear = 1;
	
	while (front <= N)
	{
		totalM += arr[front++];

		while (rear < front && totalM - arr[rear] >= M)
			totalM -= arr[rear++];

		if (totalM >= M)
		{
			submaxS = spicy.query(rear, front - 1, 1, N);
			minS = minS < submaxS ? minS : submaxS;
		}
	}

	printf("%d\n", minS);

	delete[] arr;
};
