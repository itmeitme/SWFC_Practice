#include <iostream>
#include <cstring>
#include <cstdio>
 
#define MAX 5000
#define MAX_MAP 400
 
using namespace std;
 
 
 
template <class ItemType>
void Swap(ItemType& one, ItemType& two)
{
    ItemType temp;
    temp = one;
    one = two;
    two = temp;
}
 
template<class ItemType>
struct HeapType
{
    void ReheapDown(int root, int bottom)
    {
        int maxChild;
        int rightChild;
        int leftChild;
 
        leftChild = root * 2 + 1;
        rightChild = root * 2 + 2;
        if (leftChild <= bottom)
        {
            if (leftChild == bottom)
                maxChild = leftChild;
            else
            {
                if (elements[leftChild] >= elements[rightChild])
                    maxChild = rightChild;
                else
                    maxChild = leftChild;
            }
            if (elements[root] > elements[maxChild])
            {
                Swap(elements[root], elements[maxChild]);
                ReheapDown(maxChild, bottom);
            }
        }
    }
    void ReheapUp(int root, int bottom)
    {
        int parent;
 
        if (bottom > root)
        {
            parent = (bottom - 1) / 2;
            if (elements[parent] > elements[bottom])
            {
                Swap(elements[parent], elements[bottom]);
                ReheapUp(root, parent);
            }
        }
    }
    ItemType* elements;
    int numElements;
};
 
 
class FullPQ {};
class EmptyPQ {};
template<class ItemType>
class PQType
{
public:
    PQType(int max)
    {
        maxItems = max;
        items.elements = new ItemType[max];
        length = 0;
    }
    ~PQType()
    {
        delete[] items.elements;
    }
    void MakeEmpty()
    {
        length = 0;
    }
    bool IsEmpty() const
    {
        return length == 0;
    }
    bool IsFull() const
    {
        return length == maxItems;
    }
    void Enqueue(ItemType newItem)
    {
        if (length == maxItems)
            throw FullPQ();
        else
        {
            length++;
            items.elements[length - 1] = newItem;
            items.ReheapUp(0, length - 1);
        }
    }
    void Dequeue(ItemType& item)
    {
        if (length == 0)
            throw EmptyPQ();
        else
        {
            item = items.elements[0];
            items.elements[0] = items.elements[length - 1];
            length--;
            items.ReheapDown(0, length - 1);
        }
    }
 
private:
    int length;
    HeapType<ItemType> items;
    int maxItems;
};
 
 
 
 
 
 
typedef struct pos
{
    int x;
    int y;
    int cost;
}pos;
bool operator>(pos d1, pos d2)
{
    return d1.cost > d2.cost;
}
bool operator>=(pos d1, pos d2)
{
    return d1.cost >= d2.cost;
}
 
 
int cal_cost(int*map, int*cost, int row, int col, pos s, pos e);
 
int dir[4][2] = { { 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 } };
 
 
int main(void)
{
    int row, col, num;
    scanf("%d %d", &row, &col);
 
    int* map = new int[row*col];
    int* cost = new int[row*col];
    for (int r = 0; r < row; r++)
        for (int c = 0; c < col; c++)
            scanf("%d", &map[r*col + c]);
     
    cin >> num;
    pos* arr = new pos[num + 1];
    arr[0].x = 0, arr[0].y = 0;
    for (int i = 1; i <= num; i++)
    {
        scanf("%d %d", &arr[i].y, &arr[i].x);
        arr[i].y -= 1;
        arr[i].x -= 1;
    }
 
    int sum = 0;
    int tmp = 0;
 
    int t = 0;
    for (int i = 1; i <= num; i++)
        sum += cal_cost(map, cost, row, col, arr[i - 1], arr[i]);
    sum += map[0];
 
    printf("%d\n",sum);
 
    delete[] map;
    delete[] cost;
    delete[] arr;
 
    return 0;
}
 
int cal_cost(int*map, int*cost, int row, int col, pos s, pos e)
{
    register PQType<pos> que(MAX_MAP);
 
    memset(cost, -1, sizeof(int)*row*col);
    cost[s.y*col + s.x] = 0;
 
    pos tmp = { s.x, s.y, 0 };
    que.Enqueue(tmp);
 
    while (!que.IsEmpty())
    {
        que.Dequeue(tmp);
        int x = tmp.x, y = tmp.y;
 
        if (x == e.x && y == e.y)
            break;
        int nx = 0, ny = 0;
 
        for (int i = 0; i < 4; i++)
        {
            if (i == 1 || i == 3)
                if (x > 0 && x < col - 1)
                    continue;
            nx = x + dir[i][0];
            ny = y + dir[i][1];
 
            if (nx >= 0 && nx < col && ny >= 0 && ny < row)
                if (cost[ny*col + nx] == -1 || cost[y*col + x] + map[ny*col + nx] < cost[ny*col + nx])
                {
                    if (cost[ny*col + nx] > MAX)
                        continue;
                    cost[ny*col + nx] = cost[y*col + x] + map[ny*col + nx];
                    pos tmp = { nx,ny,cost[ny*col + nx] };
                    que.Enqueue(tmp);
                }
                else
                    continue;
            else
                continue;
        }
    }
    return cost[e.y*col + e.x];
}
