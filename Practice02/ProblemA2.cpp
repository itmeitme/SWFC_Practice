#include <cstdio>
#include <algorithm>
 
using namespace std;
 
#define MAXN 131072
 
typedef struct pos
{
    int x;
    int y;
}pos;
 
class marathon
{
private:
    pos chk[MAXN];
    int dist[MAXN * 2];
    int detour[MAXN * 2];
 
public:
    marathon()
    {}
    void change_chk(int idx, int x, int y)
    {
        chk[idx].x = x;
        chk[idx].y = y;
    }
    int manhattan(int cs, int ce)
    {
        return abs(chk[cs].x - chk[ce].x) + abs(chk[cs].y - chk[ce].y);
    }
    void initialize(int root, int cs, int ce, int num_pos)
    {
        if (cs > ce)
            return;
        if (cs == ce)
        {
            if (cs < num_pos)
                dist[root] = manhattan(cs, cs + 1);
            else
                dist[root] = 0;
 
            if (cs < num_pos - 1)
                detour[root] = manhattan(cs, cs + 1) + manhattan(cs + 1, cs + 2) - manhattan(cs, cs + 2);
            else
                detour[root] = 0;
 
            return;
        }
        int mid = (cs + ce) / 2;
        initialize(root * 2 + 0, cs, mid, num_pos);
        initialize(root * 2 + 1, mid + 1, ce, num_pos);
 
        dist[root] = dist[root * 2] + dist[root * 2 + 1];
        detour[root] = max(detour[root * 2], detour[root * 2 + 1]);
    }
    int info_dist(int root, int cs, int ce, int ps, int pe)
    {
        if (cs > pe || ce < ps)
            return 0;
        if (ps <= cs && pe >= ce)
            return dist[root];
 
        int mid = (cs + ce) / 2;
        return info_dist(root * 2, cs, mid, ps, pe) + info_dist(root * 2 + 1, mid + 1, ce, ps, pe);
    }
    int info_detour(int root, int cs, int ce, int ps, int pe)
    {
        if (cs > pe || ce < ps)
            return 0;
        if (ps <= cs && pe >= ce)
            return detour[root];
 
        int mid = (cs + ce) / 2;
        return max(info_detour(root * 2, cs, mid, ps, pe), info_detour(root * 2 + 1, mid + 1, ce, ps, pe));
    }
    void update_dist(int root, int cs, int ce, int ps, int pe, int num_pos)
    {
        if (cs > pe || ce < ps) return;
        if (ps <= cs && pe >= ce)
        {
            if (cs >= 1 && cs < num_pos)
                dist[root] = manhattan(cs, cs + 1);
            else
                dist[root] = 0;
            return;
        }
        int mid = (cs + ce) / 2;
        update_dist(root * 2 + 0, cs, mid, ps, pe, num_pos);
        update_dist(root * 2 + 1, mid + 1, ce, ps, pe, num_pos);
 
        dist[root] = dist[root * 2] + dist[root * 2 + 1];
    }
    void update_detour(int root, int cs, int ce, int ps, int pe, int num_pos)
    {
        if (cs > pe || ce < ps) return;
        if (ps <= cs && pe >= ce) {
            if (cs >= 1 && cs < num_pos - 1)
                detour[root] = manhattan(cs, cs + 1) + manhattan(cs + 1, cs + 2) - manhattan(cs, cs + 2);
            else
                detour[root] = 0;
            return;
        }
        int mid = (cs + ce) / 2;
        update_detour(root * 2 + 0, cs, mid, ps, pe, num_pos);
        update_detour(root * 2 + 1, mid + 1, ce, ps, pe, num_pos);
        detour[root] = max(detour[root * 2], detour[root * 2 + 1]);
    }
};
 
marathon race;
int N, Q;
int x, y;
int ps, pe;
int pidx, nx, ny;
int info_dist, info_detour;
 
int main()
{
    scanf("%d %d", &N, &Q);
 
    for (int i = 1; i <= N; i++)
    {
        scanf("%d %d", &x, &y);
        while (getchar() != '\n');
        race.change_chk(i, x, y);
    }
 
    race.initialize(1, 1, N, N);
 
    for (int i = 0; i < Q; i++)
    {
        char cmd;
        scanf(" %c", &cmd);
        if (cmd == 'Q')
        {
            scanf("%d %d", &ps, &pe);
            info_dist = race.info_dist(1, 1, N, ps, pe - 1);
            info_detour = race.info_detour(1, 1, N, ps, pe - 2);
            printf("%d\n", info_dist - info_detour);
        }
        else
        {
            scanf("%d %d %d", &pidx, &nx, &ny);
            race.change_chk(pidx, nx, ny);
 
            race.update_dist(1, 1, N, pidx - 1, pidx - 1, N);
            race.update_dist(1, 1, N, pidx - 0, pidx - 0, N);
 
            race.update_detour(1, 1, N, pidx - 2, pidx - 2, N);
            race.update_detour(1, 1, N, pidx - 1, pidx - 1, N);
            race.update_detour(1, 1, N, pidx - 0, pidx - 0, N);
        }
    }
}
