#include <bits/stdc++.h>
using namespace std;

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/cpp/templates/CompCoding/debug.cpp"
#else 
#define debug(...) 69
#endif

int mod = 1;
struct Info {
   array<long long, 2> r1, r2;
   Info() { // empty element neutral
      r1 = { 1, 0 };
      r2 = { 0, 1 };
   } 
   
   Info(array<long long, 2>& r1, array<long long, 2> r2) {  // single
      this->r1 = r1;
      this->r2 = r2;
   }

   static Info merge(const Info& a, const Info& b) {
      Info res;
      res.r1[0] = ((a.r1[0] * b.r1[0]) % mod + a.r1[1] * b.r2[0] % mod) % mod; 
      res.r1[1] = ((a.r1[0] * b.r1[1]) % mod + (a.r1[1] * b.r2[1]) % mod) % mod;
      res.r2[0] = ((a.r2[0] * b.r1[0]) % mod + (a.r2[1] * b.r2[0]) % mod) % mod;
      res.r2[1] = ((a.r2[0] * b.r1[1]) % mod + (a.r2[1] * b.r2[1]) % mod) % mod;
      return res;
   }
};

struct Segtree {
   int size;
   vector<Info> tree;

   Segtree(int n) {
      init(n);
   }

   Segtree(vector<Info>& info) {
      init((int)info.size());
      this->build(0, 0, size, info);
   }

   // set operation
   template<typename T> 
   void set(int node, int lx, int rx, int i, T v) {
      if(rx - lx == 1) {
         // leaf
         tree[node] = v;
         return;
      }
      int m = (lx + rx) >> 1;
      if(i < m) {
         set(2 * node + 1, lx, m, i, v);
      } else {
         set(2 * node + 2, m, rx, i, v);
      }
      // recalc
      tree[node] = Info::merge(tree[2 * node + 1], tree[2 * node + 2]);
   }
   
   template<typename T>
   void set(int i, T v) {
      set(0, 0, size, i, v);
   }

   // calc operation
   Info calc(int node, int lx, int rx, int l, int r) {
      // disjoint
      if(rx <= l || r <= lx) {
         return Info();
      }
      // covered
      if(l <= lx && rx <= r) {
         return tree[node];
      }
      int m = (lx + rx) >> 1;
      auto s1 = calc(2 * node + 1, lx, m, l, r);
      auto s2 = calc(2 * node + 2, m, rx, l, r);
      return Info::merge(s1, s2);
   }
   
   // function from l...r-1
   Info calc(int l, int r) {
      return calc(0, 0, size, l, r);
   }

private: 
   void init(int n) {
      size = 1;
      while(size < n) size *= 2;
      tree.assign(2 * size, Info());
   }

   void build(int node, int lx, int rx, vector<Info>& arr) {
      if(rx - lx == 1) {
         // leaf
         if(lx < (int)arr.size()) {
            tree[node] = arr[lx];
         }
         return;
      }
      int m = (lx + rx) >> 1;
      build(2 * node + 1, lx, m, arr); 
      build(2 * node + 2, m, rx, arr);
      // recalc
      tree[node] = Info::merge(tree[2 * node + 1], tree[2 * node + 2]);
   }
};

void Main() {
   int n, m;
   cin >> mod >> n >> m;

   vector<Info> infos(n);
   for(int i = 0; i < n; i++) {
      cin >> infos[i].r1[0] >> infos[i].r1[1];
      cin >> infos[i].r2[0] >> infos[i].r2[1];
   }
   Segtree st(infos);

   while(m--) {
      int l, r;
      cin >> l >> r;
      l--;
      auto res = st.calc(l, r);
      cout << res.r1[0] << " " << res.r1[1] << '\n'; 
      cout << res.r2[0] << " " << res.r2[1] << '\n'; 
   }
}

int main() {
	ios::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
	cout << setprecision(12) << fixed;
#ifdef SARTHAK_LOCAL
   freopen("./input.txt", "r", stdin); freopen("./output.txt", "w", stdout);
   clock_t start = clock();
#endif

   Main();
   
#ifdef SARTHAK_LOCAL
   clock_t end = clock();
   cerr << "Total Time: " << (double)(end - start) * 1e3 / CLOCKS_PER_SEC << "ms" << '\n';
#endif
   return 0;
}