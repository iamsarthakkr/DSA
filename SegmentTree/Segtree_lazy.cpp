#include <bits/stdc++.h>
using namespace std;

template<typename Info, typename Operation>
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

   // set node i to v
   void set(int i, const Info& v) {
      setImpl(0, 0, size, i, v);
   }

   // Calculate function from l ... r-1
   Info calc(int l, int r) {
      return calcImpl(0, 0, size, l, r);
   }

   // Apply operation to a segment
   void apply(int l, int r, const Operation& operation) {
      applyImpl(0, 0, size, l, r, operation);
   };

   // Get node i
   Info get(int i) {
      return calc(i, i + 1);
   }

private:
   // set operation
   void setImpl(int node, int lx, int rx, int i, const Info& v) {
      if(rx - lx == 1) {
         tree[node] = v;
         return;
      }
      propagate(node, lx, rx);

      int m = (lx + rx) >> 1;
      if(i < m) {
         setImpl(2 * node + 1, lx, m, i, v);
      } else {
         setImpl(2 * node + 2, m, rx, i, v);
      }

      recalc(node, lx, rx);
   }

   // calc operation
   Info calcImpl(int node, int lx, int rx, int l, int r) {
      // disjoint
      if(rx <= l || r <= lx) {
         return Info();
      }
      // covered
      if(l <= lx && rx <= r) {
         return tree[node];
      }
      propagate(node, lx, rx);

      int m = (lx + rx) >> 1;
      auto s1 = calcImpl(2 * node + 1, lx, m, l, r);
      auto s2 = calcImpl(2 * node + 2, m, rx, l, r);

      return Info::merge(s1, s2);
   }

   void  applyImpl(int node, int lx, int rx, int l, int r, const Operation& operation) {
      // disjoint
      if(rx <= l || r <= lx) {
         return;
      }
      // covered
      if(l <= lx && rx <= r) {
         tree[node].apply(lx, rx, operation);
         return;
      }
      propagate(node, lx, rx);

      int m = (lx + rx) >> 1;
      applyImpl(2 * node + 1, lx, m, l, r, operation);
      applyImpl(2 * node + 2, m, rx, l, r, operation);

      recalc(node, lx, rx);
   };

private:
   void propagate(int node, int lx, int rx) {
      if(rx - lx == 1) {
         return;
      }
      int m = (lx + rx) >> 1;
      auto& us = tree[node];
      tree[2 * node + 1].apply(lx, m, us);
      tree[2 * node + 2].apply(m, rx, us);
      us.resetOperation();
   }

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

/* Operation for segtree */
struct Operation {
   long long add;

   Operation() { // No operation
      add = 0;
   }

   Operation(long long _add) {
      add = _add;
   }

   void change(const Operation& other) {
      if(other == NO_OP) return;
      if(*this == NO_OP) add = other.add;
      else {
         add += other.add;
      }
   }

   bool operator == (const Operation& other) const {
      return other.add == add;
   }

   static const Operation NO_OP;
};

/* No operation */
const Operation NO_OP = { 0 };

/* Info for segtree */
struct Info {
public:
   long long val;
   Operation operation;

public:
   Info() { // Neutral element
      val = 0;
      operation = NO_OP;
   }
   
   Info(long long v) { // single
      val = v;
      operation = NO_OP;
   }

   void resetOperation() {
      operation = NO_OP;
   }

   void apply(int lx, int rx, const Operation& to_apply) {
      if(to_apply == NO_OP) return;
   
      val += (rx - lx) * to_apply.add;
      operation.change(to_apply);
   };
   
   static void unite(Info& node, const Info& a, const Info& b) {
      node.val = a.val + b.val;
   }

   void apply(int lx, int rx, const Info& node) {
      apply(lx, rx, node.operation);
   };

   static Info merge(const Info& a, const Info& b) {
      Info res;
      unite(res, a, b);
      return res;
   }
};

/* usage -> Segtree<Info, Operation> st(infos) */
