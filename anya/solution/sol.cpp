//Indeed Hardship comes with ease [94:6]
//Man will not get anything unless he works hard  [53:39]
//ᴇᴀᴄʜ ᴘᴇʀꜱᴏɴ ᴡɪʟʟ ᴏɴʟʏ ʜᴀᴠᴇ ᴡʜᴀᴛ ᴛʜᴇʏ ᴇɴᴅᴇᴀᴠᴏᴜʀᴇᴅ ᴛᴏᴡᴀʀᴅꜱ [53:39]
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXV = 100000000; // 1e8

// Memory:
// is_prime: ~12.5 MB (fast odd sieve)
// pi_val:   ~382.0 MB (direct 1e8 prefix sum array)
// Total:    ~395 MB (Requires 512 MB contest memory limit)
bitset<MAXV + 1> is_prime;
int pi_val[MAXV + 1];

void init_sieve() {
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;

    for (int i = 4; i <= MAXV; i += 2) {
        is_prime[i] = 0;
    }

    for (ll i = 3; i * i <= MAXV; i += 2) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= MAXV; j += 2 * i) {
                is_prime[j] = 0;
            }
        }
    }

    // Direct prefix sum up to 1e8: no chunks, no checkpoints
    for (int i = 1; i <= MAXV; i++) {
        pi_val[i] = pi_val[i - 1] + is_prime[i];
    }
}

// O(1) direct lookup
inline ll pi(ll x) {
    return pi_val[x];
}

struct ST {
    ll n;
    vector<ll> tree;

    ST(int sz) {
        n = sz;
        tree.assign(4 * n, 0);
    }

    void build(ll node, ll start, ll end, const vector<ll>& a) {
        if (start == end) {
            tree[node] = a[start];
            return;
        }
        ll mid = (start + end) / 2;
        build(2 * node, start, mid, a);
        build(2 * node + 1, mid + 1, end, a);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void update(ll node, ll start, ll end, ll idx, ll val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        ll mid = (start + end) / 2;
        if (idx >= start && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    ll query(ll node, ll start, ll end, ll l, ll r) {
        if (start >= l && end <= r) return tree[node];
        if (start > r || end < l) return 0;
        ll mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
    }

    void build(const vector<ll>& a) { build(1, 0, n - 1, a); }
    void update(ll pos, ll val) { update(1, 0, n - 1, pos, val); }
    ll query(ll l, ll r) { return query(1, 0, n - 1, l, r); }
};

void solve() {
    init_sieve();

    ll n;
    if (!(cin >> n)) return;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        a[i] = pi(x);
    }

    ST st(n);
    st.build(a);

    ll q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            ll l, r;
            cin >> l >> r;
            --l; --r;
            cout << st.query(l, r) << "\n";
        } else if (t == 2) {
            ll u, v;
            cin >> u >> v;
            --u;
            st.update(u, pi(v));
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}