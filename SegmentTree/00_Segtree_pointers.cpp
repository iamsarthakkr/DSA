#include <bits/stdc++.h>
using namespace std;

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/cpp/templates/CompCoding/debug.cpp"
#else 
#define debug(...) 69
#endif

struct Item {
   int min;
   int count;

   Item() { // empty element neutral
      min = (int)2e9;
      count = 0;
   }
   Item(int v) {  // single
      min = v;
      count = 1;
   }
   static Item merge(const Item& a, const Item& b) {
      Item res;
      res.min = std::min(a.min, b.min);
      res.count = (a.min == res.min ? a.count : 0) + (b.min == res.min ? b.count : 0);
      return res;
   };
};

struct Segtree {
   Item node;
   int leftmost, rightmost;
   Segtree *left, *right;

   Segtree(int n) {
      this->build(0, n);
   }

   template<typename T>
   Segtree(vector<T>& arr) {
      int n = (int)arr.size();
      this->build(0, n, arr);
   }

   Item calc(int l, int r) {
      // disjoint
      if(r <= leftmost || rightmost <= l) return Item();
      // covered
      if(l <= leftmost && rightmost <= r) return node;

      auto s1 = left->calc(l, r), s2 = right->calc(l, r);
      return Item::merge(s1, s2);
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

   Segtree() {
   }
   Segtree(int l, int r) {
      this->build(l, r);
   }

private:
   void build(int l, int r) {
      this->leftmost = l;
      this->rightmost = r;
      if(r - l == 1) return;
      
      int m = (r - l) >> 1;
      left = new Segtree();
      right = new Segtree();
      left->build(l, m);
      right->build(m, r);
      recalc();
   }

   template<typename T>
   void build(int l, int r, vector<T>& arr) {
      this->leftmost = l;
      this->rightmost = r;
      
      if(r - l == 1) {
         if(l < (int)arr.size()) {
            node = { arr[l] };
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
      node =  Item::merge(left->node, right->node);
   }
};

void Main() {
   int n, m;
   cin >> n >> m;
   vector<int> a(n);
   for(auto& x: a) cin >> x;

   Segtree st(a);

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