//Indeed Hardship comes with ease [94:6]
//Man will not get anything unless he works hard  [53:39]
//ᴇᴀᴄʜ ᴘᴇʀꜱᴏɴ ᴡɪʟʟ ᴏɴʟʏ ʜᴀᴠᴇ ᴡʜᴀᴛ ᴛʜᴇʏ ᴇɴᴅᴇᴀᴠᴏᴜʀᴇᴅ ᴛᴏᴡᴀʀᴅꜱ [53:39]
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
const int maxA = 100000000;
const int chunkz = (maxA>>6)+5;
uint64_t sieve[chunkz];
int pref[chunkz];

void bitsieve()
{
	memset(sieve,0xFF,sizeof(sieve));


	sieve[0] = ~(1ULL << 0 | 1ULL << 1);

	for(ll i = 2; i*i <= maxA; i++)
	{
		if(sieve[i>>6] >> (i&63)&1ULL)
		{
			for(ll j = i*i; j<=maxA; j+=i)
			{
				sieve[j>>6] &= ~(1ULL << (j&63));
			}
		}
	}

	ll sum = 0;
	for(int i =0; i < chunkz; i++)
	{
		pref[i]=sum;
		uint64_t bits = sieve[i];
		sum += __builtin_popcountll(bits);
	}


} 

ll pi(ll x)
{
	if(x<2) return 0;

	ll chunkpos = x>>6;
	ll bitpos = x&63;
	uint64_t mask = (bitpos == 63) ? ~0ULL : ((1ULL << (bitpos + 1)) - 1);

	return pref[chunkpos]+__builtin_popcountll(sieve[chunkpos]&mask);

}
struct ST
{
    ll n;
    vector<ll> tree;
    ST(int sz)
    {
        n= sz;
        tree.assign(4*n,0);
    }
void build(ll node, ll start, ll end, const vector<ll>& a) {
        if (start == end) {
            tree[node] = a[start];
            return;
        }
        ll mid = (start+end)/2;
        build(2 * node, start, mid, a);
        build(2 * node + 1, mid+1, end, a);
        tree[node] = tree[2*node] + tree[2*node+1];
}
 
void update(ll node,ll start,ll end,ll idx, ll val)
{
    if(start==end)
    {
        tree[node]=val;
        return;
    }
    ll mid=(start+end)/2;
    if(idx>=start && idx<=mid)
    {
        update(2*node,start,mid,idx,val);
    }
    else
    {
        update(2*node+1,mid+1,end,idx,val);
    }
    tree[node]=tree[2*node]+tree[2*node+1];
}
ll query(ll node,ll start, ll end,ll l, ll r)
{
    if(start>=l && end<=r)
    {
        return tree[node];
    }
    if(start>r || end<l)
    {
        return 0;
    }
    ll mid=(start+end)/2;
    ll p1=query(2*node,start,mid,l,r);
    ll p2=query(2*node+1,mid+1,end,l,r);
    return p1+p2;
}
void build(const vector<ll>& a)
{
	build(1,0,n-1,a);
}
void update(ll pos, ll val)
{
    update(1,0,n-1,pos,val);
}

ll query(ll l, ll r) { 
	return query(1, 0, n - 1, l, r); 
}

};
void solve()
{
	bitsieve();
	ll n;
	cin >> n;
	vector<ll> a(n);
	for(int i =0; i < n; i++)
	{
		ll x;
		cin >> x;
		a[i]=pi(x);
	}

	ST st(n);
	st.build(a);
	ll q;
	cin >> q;
	while(q--)
	{
		int t;
		cin >> t;
		if(t==1)
		{
			ll l,r;
			cin >> l >> r;
			--l; --r;
			cout << st.query(l,r) << "\n";
		}
		else if(t==2)
		{
			ll u,v;
			cin >> u >> v;
			--u;
			st.update(u,pi(v));
		}
	}

}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	while (t--) {
		solve();
	}

	return 0;
}