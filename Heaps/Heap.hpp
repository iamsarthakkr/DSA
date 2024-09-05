#include<bits/stdc++.h>

class Heap {
public:
    virtual void insert(int x) = 0;
    virtual int top() = 0;
    virtual int remove_min() = 0;
    virtual bool empty() = 0;
    virtual size_t size() = 0;
};


class PriorityQueue: Heap {
public:
    void insert(int x) {
        m_h.push_back(x);
        shift_up(m_h, (int)m_h.size() - 1);
    }
    int top() {
        return m_h.front();
    }
    int remove_min() {
        int min = m_h.front();
        std::swap(m_h.front(), m_h.back());
        m_h.pop_back();
        shift_down(m_h, (int)m_h.size(), 0);
        return min;
    }
    bool empty() { return m_h.empty(); }
    size_t size() { return m_h.size(); }

public:
    static void sort(std::vector<int>& a) {
        heapify(a);
        for(int i = (int)a.size() - 1; i >= 0; --i) {
            std::swap(a[0], a[i]);
            shift_down(a, i, 0);
        }
        std::reverse(a.begin(), a.end());
    }

private:
    static int left(int i) { return 2 * i + 1; }
    static int right(int i) { return 2 * i + 2; }
    static int parent(int i) { return (i - 1) >> 1; }

    static void shift_down(std::vector<int>& a, int size, int i) {
        while(left(i) < size) {
            int j = left(i);
            if(right(i) < size && a[right(i)] < a[j]) j = right(i);
            if(a[i] <= a[j]) break;
            std::swap(a[i], a[j]);
            i = j;
        }
    }
    static void shift_up(std::vector<int>& a, int i) {
        while(i > 0 && a[parent(i)] > a[i]) {
            std::swap(a[i], a[parent(i)]);
            i = parent(i);
        }
    }
    static void heapify(std::vector<int>& a) {
        for(int i = (int)a.size() - 1; i >= 0; --i) {
            shift_down(a, (int)a.size(), i);
        }
    }
private:
    std::vector<int> m_h;
};