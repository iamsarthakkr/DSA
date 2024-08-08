#include <bits/stdc++.h>
using namespace std;

template<typename Info>
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
   void set(int node, int lx, int rx, int i, const Info& v) {
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
      recalc(node, lx, rx);
   }
   
   void set(int i, const Info& v) {
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
   void recalc(int node, int lx, int rx) {
      if(rx - lx == 1) {
         return;
      }
      Info::unite(tree[node], tree[2 * node + 1], tree[2 * node + 2]);
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

      recalc(node, lx, rx);
   }
};

struct Info {
   int val;

   Info() { // Neutral element
      val = 0;
   }
   
   Info(int v) { // single
      val = v;
   }

   static Info merge(const Info& a, const Info& b) {
      Info res;
      unite(res, a, b);
      return res;
   }

   static void unite(Info& node, const Info& a, const Info& b) {
      node.val = a.val + b.val;
   }
};

/* usage -> Segtree<Info> st(infos) */