#include <stdio.h>

template <typename T>
class pqueue
{
private:
	T * heap;
	int heapSize;
	int max_size;
public:
	pqueue()
		: heapSize(0), max_size(0)
	{}
	pqueue(int num)
		: heapSize(0), max_size(num)
	{
		heap = new T[num];
	}
	~pqueue()
	{
		delete[] heap;
	}
	bool push(T value)
	{
		if (heapSize + 1 > max_size)
		{
			printf("queue is full!");
			return false;
		}

		heap[heapSize] = value;

		int current = heapSize;
		while (current > 0 && heap[current] < heap[(current - 1) / 2])
		{
			T temp = heap[(current - 1) / 2];
			heap[(current - 1) / 2] = heap[current];
			heap[current] = temp;
			current = (current - 1) / 2;
		}

		heapSize = heapSize + 1;

		return true;
	}
	bool pop()
	{
		if (heapSize <= 0)
		{
			return false;
		}

		heapSize = heapSize - 1;

		heap[0] = heap[heapSize];

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
				child = heap[current * 2 + 1] < heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
			}

			if (heap[current] < heap[child])
				break;

			T temp = heap[current];
			heap[current] = heap[child];
			heap[child] = temp;

			current = child;
		}
		return true;
	}
	T& top()
	{
		return heap[0];
	}
};

struct goods
{
	int price;
	int idx;

	bool operator< (goods& op)
	{
		return price < op.price;
	}
};

int main(int argc, char* argv[])
{
	int N, K;
	long long M;
	
	scanf("%d %d %lld", &N, &K, &M);

	pqueue<goods> normal(N);
	pqueue<goods> sale(N);
	pqueue<long long> reserve(K);

	goods *P = new goods[N];
	bool *buy = new bool[N]();

	goods buf;
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &P[i].price, &buf.price);
		P[i].idx = buf.idx = i;
		normal.push(P[i]);
		sale.push(buf);
	}

	for (int i = 0; i < K; i++)
		reserve.push(0LL);

	int cnt = 0;
	long long budget = M;
	while (cnt < N && budget > 0)
	{
		while (buy[sale.top().idx])
			sale.pop();
		while (buy[normal.top().idx])
			normal.pop();

		if (sale.top().price + reserve.top() < normal.top().price)
		{
			long long cost = sale.top().price + reserve.top();
			if (cost <= budget)
				budget -= cost;
			else
				break;
			reserve.pop();
			reserve.push(P[sale.top().idx].price - sale.top().price);
			buy[sale.top().idx] = true;
		}
		else
		{
			long long cost = normal.top().price;
			if (cost <= budget)
				budget -= cost;
			else
				break;
			buy[normal.top().idx] = true;
		}
		cnt++;
	}

	printf("%d\n", cnt);

	delete[] P;
	delete[] buy;

	return 0;
}
