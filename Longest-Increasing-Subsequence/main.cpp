#include <stdio.h>
#include <algorithm>
#include <deque>
using namespace std;
 
const int MAX_N = 100000;
int v[MAX_N + 1], N;


/* There are 2 LIS algorithms with different complexities: O(n^2) and O(n log n) */

void N_sq() {
 
    int L[MAX_N + 1] = {0}, next[MAX_N + 1] = {0};
    L[N] = 1, next[N] = 0;

    for (register int i = N - 1; i > 0; -- i) {
        L[i] = 1, next[i] = 0;
 
        for (register int j = i + 1; j <= N; ++ j)
            if (v[i] < v[j] and L[j] + 1 > L[i])
                L[i] = L[j] + 1, next[i] = j;
    }
 
    int lis = L[1], pos = 1;
 
    for(register int i = 2; i <= N; ++ i)
        if(L[i] > lis)
            lis = L[i], pos = i;
 
    printf("%d\n", lis);
 
    int x = pos;
 
    while(x) {
        printf("%d ", v[x]);
        x = next[x];
    }
     
}
 
void N_log_N() {
    int p[MAX_N + 1]={0}, q[MAX_N + 1] = {0};
 
    q[1] = v[1];
    p[1] = 1;
 
    int sq = 1;
 
    for(register int i = 1; i <= N; ++ i) {
 
        int *pointer = lower_bound(q + 1, q + sq + 1, v[i]); // or upper bound if you want elements to be in increasing or equal order
        fprintf(stderr, "%d %ld\n", v[i], pointer - q);
        if(pointer == q + sq + 1)
            q[++ sq] = v[i], p[i] = sq;
        else
            q[pointer - q] = v[i], p[i] = pointer - q;
    }
 
    printf("%d\n", sq);
 
    int target = sq;
 
    deque<int> sol;
 
    for(register int i = N; i > 0; -- i) {
        if(p[i] == target) {
            sol.push_front(v[i]);
            -- target;
        }
    }
 
    deque<int> :: iterator it = sol.begin();
 
    while(it != sol.end())
        printf("%d ", *(it++));
 
}
int main() {
 
    freopen( "lis.in", "r", stdin );
    freopen( "lis.out", "w", stdout );
 
    scanf("%d", &N); 
    for(register int i = 1; i <= N; ++ i)
        scanf("%d", &v[i]);
 
    N_log_N();
    printf("\n");
    return 0;
}
