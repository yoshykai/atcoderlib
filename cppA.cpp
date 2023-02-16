#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep2(i, k, n) for (int i = (int)(k); i < (int)(n); i++)
#define rep3(i, k) for (int i = (int)(k); i >= 0; i--)

vector<int> inputArray(const int n){
  vector<int> v(n);
  for(int i=0;i<n;i++){
    scanf("%d",&v[i]);
  }
  return v;
}

void ln(){
  printf("\n");
}
void sp(){
  printf(" ");
}

template <class X> void pr(const X a){
  cout << a;
}
template <class X> void pl(const X a){
  cout << a << endl;
}

template <class X,class Y> void pr(const pair<X,Y> &p){
  pr(p.first);sp();pl(p.second);
}

template <class X>void pr(const vector<X> &v){
  if(v.size()>0){
    pr(v[0]);
  }
  rep2(i,1,v.size()){
    sp();pr(v[i]);
  }
  ln();
}

template <class X> void sortA(vector<X> &v){
  sort(v.begin(),v.end());
}

template <class X> void sortD(vector<X> &v){
  sort(v.begin(),v.end(),greater<X>());
}

template <class X,class Y> void sortAFirst(vector<pair<X,Y>> &v){
  sort(v.begin(),v.end());
}
template <class X,class Y> void sortDFirst(vector<pair<X,Y>> &v){
  sort(v.begin(),v.end(),greater<X>());
}
template <class X,class Y> void sortASecond(vector<pair<X,Y>> &v){
  sort(v.begin(),v.end(),[](pair<X,Y> &a,pair<X,Y> &b){
    return a.second<b.second;
  });
}
template <class X,class Y> void sortDSecond(vector<pair<X,Y>> &v){
  sort(v.begin(),v.end(),[](pair<X,Y> &a,pair<X,Y> &b){
    return a.second>b.second;
  });
}

class UnionFindTree{
public:
  vector<int> parent;
  vector<int> vol;
  UnionFindTree(const int nn){
    n=nn;
    parent.resize(n);
    vol.resize(n);
    rep(i,n){
      parent[i]=i;
      vol[i]=1;
    }
  }
  int root(const int a){
    if(parent[a]==a){
      return a;
    }
    parent[a] = root(parent[a]);
    return parent[a];
  }
  int unite(const int a,const int b){
    int ra = root(a),rb = root(b);
    if(ra==rb){return ra;}
    if(vol[ra]<vol[rb]){
      int t=ra;ra=rb;rb=t;
    }
    parent[rb]=ra;
    vol[ra]+=vol[rb];
    return ra;
  }
  bool same(const int a,const int b){
    return root(a)==root(b);
  }
private:
  int n;
};

class ModFunc{
public:
  vector<ll> fact,invfact;
  ModFunc(int nn,ll m){n=nn;mod = m;fact.reserve(n+1);invfact.reserve(n+1);construct();}
  static ll modinv(ll a,ll mod){
    ll x1=1,x2=0;
    ll p=mod,q,t;
    while(a%p!=0){
      q = a/p;
      t = x1-q*x2;
      x1=x2; x2=t;
      t=a%p;
      a=p; p=t;
    }
    return x2<0 ? x2+mod : x2;
  }
  static ll modfact(int n,ll mod){
    ll k=1;
    for(int i=1;i<=n;i++){
      k = k*i % mod;
    }
    return k;
  }
  static ll modinvfact(int n,ll mod){
    return modinv(modfact(n,mod),mod);
  }
  static ll modpow(ll x,ll n,ll pow){
    long r = 1;
    while(n>=1){
      if(1==(n&1)){
        r = r*x % pow;
      }
      x = x*x % pow;
      n/=2;
    }
    return r;
  }
  ll modConv(int n,int k){
    return ((fact[n]*invfact[n-k])%mod)*invfact[k]%mod;
  }

private:
  int n;
  ll mod;
  void construct(){
    fact[0]=1;
    for(int i=1;i<=n;i++){
      fact[i]=fact[i-1]*i%mod;
    }
    invfact[n] = modinv(fact[n],mod);
    for(int i=n-1;i>=0;i--){
      invfact[i] = invfact[i+1]*i%mod;
    }
  }
};

vector<int> compress(const vector<int> &v){
  vector<int> a = v;
  vector<int> b(v.size());
  sort(a.begin(),a.end());
  a.erase(unique(a.begin(),a.end()),a.end());
  rep(i,b.size()){
    b[i] = lower_bound(a.begin(), a.end(), v[i]) - a.begin();
  }
  return b;
}

class BIT{
public:
  BIT(const int a){
    n = a+1;
    v.resize(n,0);
  }

  void update(int i,ll x){
    for(int ii=i+1;ii<n;ii+=(ii&-ii)){
      v[ii]+=x;
    }
  }
  ll sum(const int i){
    ll k=0;
    for(int ii=i+1;ii>0;ii-=(ii&-ii)){
      k+=v[ii];
    }
    return k;
  }
private:
  int n;
  vector<ll> v;
};

class SegmentTree{
public:
  SegmentTree(const int a,const ll init){
    n = twon(a);init_num=init;
    v.resize(n*2-1,init_num);
  }

  virtual ll func(const ll a,const ll b)=0;

  void update(const int i,const ll x){
    int now = i+n-1;
    v[now] = x;
    while(now>0){
      now = (now-1)/2;
      v[now] = func(v[now*2+1],v[now*2+2]);
    }
  }
  void add(const int i,const ll x){
    update(i,v[i+n-1]+x);
  }
  ll get(const int i){
    return v[i+n-1];
  }
  ll query(const int a,const int b){
    return query(a,b,0,0,n);
  }
private:
  int n;
  ll init_num;
  vector<ll> v;

  int twon(const int a){
    int k=1;
    while(k<a){
      k*=2;
    }
    return k;
  }

  ll query(const int a,const int b,const int k,const int l,const int r){
    if(r<=a||b<=l){
      return init_num;
    }else if(a<=l&&r<=b){
      return v[k];
    }
    ll t1=query(a,b,k*2+1,l,(l+r)/2),t2=query(a,b,k*2+2,(l+r)/2,r);
    return func(t1,t2);
  }
};

class SegmentTreeEOR : public SegmentTree{
public:
  SegmentTreeEOR(const int a):SegmentTree(a,0){};
  ll func(const ll a,const ll b) override{
    return a^b;
  }
};

class SegmentTreeMin : public SegmentTree{
public:
  SegmentTreeMin(const int a):SegmentTree(a,LLONG_MAX){};
  ll func(const ll a,const ll b) override{
    return min(a,b);
  }
};

class SegmentTreeMax : public SegmentTree{
public:
  SegmentTreeMax(const int a):SegmentTree(a,LLONG_MIN){};
  ll func(const ll a,const ll b) override{
    return max(a,b);
  }
};

class SegmentTreeS : public SegmentTree{
public:
  SegmentTreeS(const int a):SegmentTree(a,0){};
  ll func(const ll a,const ll b) override{
    return a+b;
  }
};

class Graph{
public:
  int n;
  vector<vector<pair<int,ll>>> g;
  Graph(const int nn){
    n=nn;
    g.resize(n);
  }
  void add(const int s,const int t,const ll d){
    g[s].push_back({t,d});
    g[t].push_back({s,d});
  }
  void add(const int s,const int t){
    g[s].push_back({t,1});
    g[t].push_back({s,1});
  }
  void addY(const int s,const int t,const ll d){
    g[s].push_back({t,d});
  }
  void addY(const int s,const int t){
    g[s].push_back({t,1});
  }
  void dfs(){
    vector<bool> flg(n);
    rep(i,n){
      if(!flg[i]){
        dfs(i,flg);
      }
    }
  }
  void dfs(const int s,vector<bool> &flg){
    flg[s]=true;
    rep(i,g[s].size()){
      if(flg[g[s][i].first]){continue;}
      dfs(g[s][i].first,flg);
    }
  }
  void bfs(){
    vector<bool> flg(n);
    queue<int> q;
    rep(i,n){
      if(!flg[i]){
        q.push(i);
        while(q.size()>0){
          int v=q.front();
          q.pop();
          flg[v]=true;
          rep(j,g[v].size()){
            if(flg[g[v][j].first]){continue;}
            q.push(g[v][j].first);
          }
        }
      }
    }
  }

  vector<int> bfs_dist(const int s){
    vector<int> dist(n,-1);
    queue<int> q;
    q.push(s);
    dist[s]=0;
    while(q.size()>0){
      int v = q.front();
      q.pop();
      rep(i,g[v].size()){
        if(dist[g[v][i].first]!=-1){continue;}
        dist[g[v][i].first]=dist[v]+1;
        q.push(g[v][i].first);
      }
    }
    return dist;
  }

  vector<ll> dijkstra(const int s){
    auto cmp = [](const pair<int,ll>& lhs, const pair<int,ll>& rhs)
      {
        return lhs.second > rhs.second;
      };
    vector<ll> dist(n,LLONG_MAX);
    priority_queue<pair<int,ll>,vector<pair<int,ll>>,decltype(cmp)> q(cmp);
    q.push({s,0L});
    dist[s]=0;
    while(q.size()>0){
      int v = q.top().first;ll d=q.top().second;
      q.pop();
      if(dist[v]!=d){continue;}
      rep(i,g[v].size()){
        int next = g[v][i].first;
        if(dist[next]<=dist[v]+g[v][i].second){continue;}
        dist[next]=dist[v]+g[v][i].second;
        q.push({next,dist[next]});
      }
    }
    return dist;
  }

  ll minspantree(){
    auto cmp = [](const pair<int,ll>& lhs, const pair<int,ll>& rhs)
      {
        return lhs.second > rhs.second;
      };
    priority_queue<pair<int,ll>,vector<pair<int,ll>>,decltype(cmp)> q(cmp);
    vector<bool> flg(n,false);
    flg[0]=true;
    int c=1;
    ll dist=0;
    for(auto e:g[0]){
      q.push(e);
    }
    while(q.size()>0&&c<n){
      auto e = q.top();
      q.pop();
      if(flg[e.first]){continue;}
      dist+=e.second;
      flg[e.first]=true;
      c++;
      for(auto i:g[e.first]){
        if(!flg[i.first]){
          q.push(i);
        }
      }
    }
    return dist;
  }
};

int main(){
  int n,m;
  scanf("%d",&n);
  vector<pair<int,string>> a(n);
  vector<int> ans(n,0);
  string s;
  rep(i,n){
    cin >> s;
    a[i] = {i,s};
  }
  sortASecond(a);
  rep(i,n-1){
    m = 0;
    for(;m<min(a[i].second.size(),a[i+1].second.size());m++){
      if(a[i].second[m]!=a[i+1].second[m]){
        break;
      }
    }
    ans[a[i].first] = max(ans[a[i].first],m);
    ans[a[i+1].first] = max(ans[a[i+1].first],m);
  }
  rep(i,n){
    printf("%d\n",ans[i]);
  }
  return 0;
}
