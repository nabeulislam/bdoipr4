#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int gift(int a,int b,int m){
    int mn=m;
    for(int x=1;a*x+b*(x+1)<=m;++x){
        int y=(m-a*x)/b;
        if(y<=x) continue;
        mn=min(mn,m-a*x-b*y);
    }
    return mn;
}

void solve(){
    int n,k,m,mx,mn=1e9;
    cin >> n >> k >> m;
    string s,s2;
    cin >> s >> s2;
    int l1=n+1,r1=0,c1=0,l2=n+1,r2=0,c2=0;
    for(int i=0;i<n;++i){
        if(s[i]=='1'){
            l1=min(l1,i+1);
            r1=max(r1,i+1);
            c1++;
        }
        if(s2[i]=='1'){
            l2=min(l2,i+1);
            r2=max(r2,i+1);
            c2++;
        }
    }
    int mn1=1e9,mn2=1e9,i1=1,i2=1;
    for(int i=1;i<=n;++i){
        mx=max({i-l1,r1-i,k+i+r2});
        if(mx<mn1){
            mn1=mx;
            i1=i;
        }
        mx=max({i-l2,r2-i,k+i+r1});
        if(mx<mn2){
            mn2=mx;
            i2=i;
        }
    }
    mn=min(mn1,mn2);
    int res=1e9,ans=1,idx=1;
    if(mn1==mn){
        res=gift(c1,c2,m);
        ans=1;
        idx=i1;
    }
    if(mn2==mn){
        int r=gift(c2,c1,m);
        if(r<res){
            res=r;
            ans=2;
            idx=i2;
        }
    }
    cout << mn << '\n' << ans << ' ' << idx << '\n' << res;
}

int32_t main(){
ios_base::sync_with_stdio(0);
cin.tie(0);
    int t=1;
    cin >> t;
    while(t--){
        solve();
        if(t!=0) cout << '\n';
    }
}