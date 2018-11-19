#include <iostream>
using namespace std;

int B, N, *bship, *npp, *npptotal, bstotal = 0, result = 0;
bool *visited;

void inputData(void)
{
	cin >> B >> N;
	bship = new int[B + 1];
	visited = new bool[B + 1];
	npp = new int[N + 1];
	npptotal = new int[N + 1];
	for (int i = 0; i < B; i++) {
		cin >> bship[i];
		bstotal += bship[i], visited[i]=false;
	}
	for (int i = 0; i < N; i++) {
		cin >> npp[i];
		if (i == 0) npptotal[i] = npp[i];
		else npptotal[i] = npptotal[i - 1] + npp[i];
	}
}

int bSearch(int ship, int s, int e, int k)
{
	int m, sol = e;

	while (s <= e) {
		m = (s + e) / 2;
		if (ship < npptotal[m]-k) e = m - 1;
		else {
			sol = m;
			s = m + 1;
		}
	}
	return sol;
}

void dfs(int ncnt, int bstotal)
{
	if (ncnt >= N) {
		if (bstotal > result) result = bstotal;
	}

	else {
		for (int b = 0; b < B; b++) {
			int temp = 0;
			if (visited[b]) continue;
			visited[b] = true;
			int k = (ncnt == 0 ? 0 : npptotal[ncnt - 1]);
			temp = ncnt;
			ncnt = bSearch(bship[b], ncnt, N - 1, k);
			dfs(ncnt + 1, bstotal - bship[b]);
			ncnt = temp;
			visited[b] = false;
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	inputData();
	if (bstotal >= npptotal[N - 1]) dfs(0, bstotal);
	else result = -1;
	cout << result << endl;
	delete(bship);
	delete(visited);
	delete(npp);
	delete(npptotal);
	return 0;
}
