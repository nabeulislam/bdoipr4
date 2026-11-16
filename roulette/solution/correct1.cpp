//Indeed Hardship comes with ease [94:6]
//Man will not get anything unless he works hard  [53:39]
//ᴇᴀᴄʜ ᴘᴇʀꜱᴏɴ ᴡɪʟʟ ᴏɴʟʏ ʜᴀᴠᴇ ᴡʜᴀᴛ ᴛʜᴇʏ ᴇɴᴅᴇᴀᴠᴏᴜʀᴇᴅ ᴛᴏᴡᴀʀᴅꜱ [53:39]
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
const int MAXN = 505;
const int inf = 1e9;
int n,m,k,s;
int board[MAXN][MAXN];
bool vis[MAXN][MAXN];
bool target[MAXN][MAXN];
int dist[MAXN][MAXN];
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
bool ok(int r,int c)
{
	return ((r>=1 && r <=n) && (c>=1 && c<=m));
}
bool check(int x)
{
	for(int i =1; i <=n; i++)
	{
		for(int j =1; j <=m; j++)
		{
			vis[i][j]=false;
			target[i][j]=false;
			dist[i][j]=inf;
		}
	}

	bool found = false;
	for(int r = 1; r <=n; r++)
	{
		for(int c =1; c <=m; c++)
		{
			if(board[r][c]>=x && !vis[r][c])
			{
				vector<pair<int,int>> comp;
				queue<pair<int,int>> q;
                vis[r][c]=true;
				q.push({r,c});
				while(!q.empty())
				{
					auto [cr,cc] = q.front();
					q.pop();
					comp.push_back({cr,cc});
					for(int i = 0; i < 4; i++)
					{
						int nr = cr+dr[i];
						int nc = cc+dc[i];
						if(ok(nr,nc)&&board[nr][nc]>=x && !vis[nr][nc])
						{
							vis[nr][nc]=true;
							q.push({nr,nc});
						}
					}
				}
				int sz = comp.size();
				if(sz>=s)
				{
					found=true;
					for(auto [cr,cc]:comp)
					{
						target[cr][cc]=true;
					}
				}
			}
		}
	}

	if(!found) return false;
	vector<pair<int, int>> q0, q1;
	int base_price = (board[1][1] < x?1:0);
	if(base_price>k) return false;
	dist[1][1]=base_price;
	q0.push_back({1,1});
	while(!q0.empty())
	{
		auto [r,c]=q0.back();
		q0.pop_back();
		if(target[r][c]) return true;
		for(int i = 0; i < 4; i++)
		{
			int nr = r+dr[i];
			int nc = c+dc[i];
			if(!ok(nr,nc)) continue;

			int w = (board[nr][nc]<x?1:0);
			int cost = dist[r][c]+w;
			if(cost<=k && cost < dist[nr][nc])
			{
				dist[nr][nc]=cost;
				if(w==0)
				{
					q0.push_back({nr,nc});
				}
				else
				{
					q1.push_back({nr,nc});
				}
			}
		}

		if(q0.empty())
		{
			swap(q0,q1);
		}

	}

	return false;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k >> s;
	for(int i = 1; i <= n; i++)
	{
		for(int j =1; j <= m; j++)
		{
			cin >> board[i][j];
		}
	}

	int low =1; int high = 1e9;
	int ans = 0;
	while(low<=high)
	{
		int mid = low+(high-low)/2;
		if(check(mid))
		{
			ans=mid;
			low=mid+1;
		}
		else
		{
			high=mid-1;
		}
	}


	cout << ans << "\n";



	return 0;
}