#include <bits/stdc++.h>
using namespace std;

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/cpp/templates/CompCoding/debug.cpp"
#else 
#define debug(...) 69
#endif

struct Info {
   int min;
   int count;

   Info() { // empty element neutral
      min = (int)2e9;
      count = 0;
   }
   Info(int v) {  // single
      min = v;
      count = 1;
   }
   static Info merge(const Info& a, const Info& b) {
      Info res;
      res.min = std::min(a.min, b.min);
      res.count = (a.min == res.min ? a.count : 0) + (b.min == res.min ? b.count : 0);
      return res;
   };
};

struct Segtree {
   Info node;
   int leftmost, rightmost;
   Segtree *left, *right;

   Segtree() {}

   Segtree(vector<Info>& info) {
      int size = (int)info.size();
      this->build(0, size, info);
   }

   Info calc(int l, int r) {
      // disjoint
      if(r <= leftmost || rightmost <= l) return Info();
      // covered
      if(l <= leftmost && rightmost <= r) return node;

      auto s1 = left->calc(l, r), s2 = right->calc(l, r);
      return Info::merge(s1, s2);
   }

   void set(int i, int v) {
      if(rightmost - leftmost == 1) {
         node = { v };
         return;
      }

      int m = (rightmost + leftmost) >> 1;
      if(i < m) left->set(i, v);
      else right->set(i, v);
      recalc();
   }

private:
   void build(int l, int r, vector<Info>& arr) {
      this->leftmost = l;
      this->rightmost = r;
      
      if(r - l == 1) {
         if(l < (int)arr.size()) {
            node = arr[l];
         }
         return;
      }
      
      int m = (r + l) >> 1;
      left = new Segtree();
      right = new Segtree();
      left->build(l, m, arr);
      right->build(m, r, arr);
      recalc();
   }
   void recalc() {
      if(rightmost - leftmost == 1) return;
      node =  Info::merge(left->node, right->node);
   }
};

void Main() {
   int n, m;
   cin >> n >> m;
   vector<int> a(n);
   for(auto& x: a) cin >> x;

   vector<Info> info(n);
   for(int i = 0; i < n; i++) info[i] = Info(a[i]);
   Segtree st(info);

   while(m--) {
      int t;
      cin >> t;
      if(t == 1) {
         int i, v;
         cin >> i >> v;
         st.set(i, v);
      } else {
         int l, r;
         cin >> l >> r;
         auto res = st.calc(l, r);
         cout << res.min << " " << res.count << '\n';
      }
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