#include <bits/stdc++.h>
using namespace std;
int a[10005];
int n, k;
//change test
bool check(int s){
 
    int cnt = 1, plu = 0;
    int i = 0;
    i = lower_bound(a, a+n, a[i]+s)-a;
    while(i<n){
        i = lower_bound(a, a+n, a[i]+s)-a;
        cnt++;
    }
 
 
 
    return(cnt>=k);
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    cin >> a[0];
    int l = INT_MAX;
    for(int i=1; i<n; i++){
        cin >> a[i];
        l = min(l, a[i]-a[i-1]);
    }
    int r = a[n-1]-a[0]+1;
 
    int mx = 0;
    while(l<r){
        int mid = (l+r)/2;
        if(check(mid)){
            l = mid+1;
            mx = mid;
        }
        else{
            r = mid;
        }
    }
    cout << mx;
}