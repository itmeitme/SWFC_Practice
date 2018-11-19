#include <iostream>
#include <cstdio>
#define min(x,y) ( x<y ? x:y)

int N;
char **M;
int min_val = N;
int **DP_val;
bool *V;

using namespace std;


typedef struct _c_list {
	int child_cnt;
	int *childs;
}c_list;

c_list *child_list;

void make_child_list(int node_num) {
	V[node_num] = true;
	//printf("node : %d\n", node_num);
	//printf("child :");
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		if (!V[i] && M[node_num][i]) {
			cnt++;
			//printf("%3d",i);
		}
	}
	//printf("\n");
	child_list[node_num].child_cnt = cnt;
	child_list[node_num].childs = (int*)malloc(sizeof(int)*cnt);
	cnt = 0;
	for (int i = 1; i <= N; i++) {
		if (!V[i] && M[node_num][i]) {
			V[i] = 1;
			child_list[node_num].childs[cnt++] = i;
			make_child_list(i);
		}
	}

}

int DP(int node_num, bool state) {
	int return_val1 = 0;
	//printf("node : %d state : %d\n", node_num,state);
	if (DP_val[node_num][state] != -1) {
		//printf("exist node : %d state : %d ret : %d\n", node_num, state, DP_val[node_num][state]);
		return DP_val[node_num][state];
	}
	if (child_list[node_num].child_cnt == 0) {
		//printf("leaf node : %d state : %d ret : %d\n", node_num, state, DP_val[node_num][state]=state); 
		return DP_val[node_num][state] = state;
	}

	if (state == 0) { // node가 얼리 어답터가 아닐때
		for (int i = 0; i < child_list[node_num].child_cnt; i++) {
			return_val1 += DP(child_list[node_num].childs[i], 1);
		}
	}
	else if (state == 1) { // node가 얼리 어답터 일때
		return_val1 = 1;
		for (int i = 0; i < child_list[node_num].child_cnt; i++) {
			return_val1 += min(DP(child_list[node_num].childs[i], 1), DP(child_list[node_num].childs[i], 0));
		}
	}
	//printf("complete node : %d state : %d ret : %d\n", node_num, state, DP_val[node_num][state]=return_val1);
	return DP_val[node_num][state] = return_val1;
}

int main(void)
{
	scanf("%d", &N);
	int u, v;
	M = (char **)malloc(sizeof(char*)*(N + 1));
	DP_val = (int **)malloc(sizeof(int*) * (N + 1));
	V = (bool *)malloc(sizeof(bool)*(N + 1));
	child_list = (c_list*)malloc(sizeof(c_list)*(N + 1));

	for (int i = 1; i <= N; i++) {
		M[i] = (char*)malloc(sizeof(char)*(N + 1));
		for (int j = 0; j <= N; j++)
			M[i][j] = 0;
		DP_val[i] = (int *)malloc(sizeof(int) * 2);
		DP_val[i][0] = -1;
		DP_val[i][1] = -1;
		V[i] = 0;
	}
	for (int i = 1; i < N; i++) {
		scanf("%d %d", &u, &v);
		M[u][v] = 1;
		M[v][u] = 1;
	}
	make_child_list(1);
	free(V);
	printf("%d\n", min(DP(1, 0), DP(1, 1)));

	for (int i = 1; i <= N; i++) {
		free(DP_val[i]);
		free(M[i]);
		free(child_list[i].childs);
	}
	free(child_list);
	free(DP_val);
	free(M);

	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}
