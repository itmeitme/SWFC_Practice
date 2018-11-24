#include <stdio.h>

struct box
{
	int depart;
	int arrive;
	int num_box;

	bool operator<(box& op)
	{
		if (arrive == op.arrive)
			return depart < op.depart;
		else
			return arrive < op.arrive;
	}
};

void quickSort(box* input, int first, int last)
{
	int pivot;
	int i;
	int j;
	box temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (input[i] < input[pivot] && i < last)
			{
				i++;
			}
			while (input[pivot] < input[j])
			{
				j--;
			}
			if (i < j)
			{
				temp = input[i];
				input[i] = input[j];
				input[j] = temp;
			}
		}

		temp = input[pivot];
		input[pivot] = input[j];
		input[j] = temp;

		quickSort(input, first, j - 1);
		quickSort(input, j + 1, last);
	}
}


int main(void)
{
	int N, C, num;
	scanf("%d %d", &N, &C);
	scanf("%d", &num);

	box* arr = new box[num];

	int s, e, n;
	for (int i = 0; i < num; i++)
	{
		scanf("%d %d %d", &s, &e, &n);
		arr[i] = { s,e,n };
	}

	quickSort(arr, 0, num - 1);

	int tbox = 0;
	int f = 0, r = 0;

	for (int i = 1; i <= N; i++)
	{
		while (arr[f].depart == i)
		{
			if (arr[f].num_box > C)
				arr[f].num_box = C;
			C -= arr[f].num_box;
			tbox += arr[f].num_box;
			f++;
		}
		while (arr[r].arrive <= i)
			C += arr[r++].num_box;

	}
	printf("%d\n", tbox);

	delete[] arr;

	return 0;
}
