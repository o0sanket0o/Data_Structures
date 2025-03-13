class SegmentTree {
    vector<int> tree;
    int n;

    void buildTree(int index, int start, int end, vector<int>& nums) {
        if (start == end) {
            tree[index] = nums[start];
            return;
        }
        int mid = start + (end - start) / 2;
        buildTree(2 * index, start, mid, nums);
        buildTree(2 * index + 1, mid + 1, end, nums);
        tree[index] = max(tree[2 * index], tree[2 * index + 1]);
    }

    void update(int pos, int start, int end, int index, int value) {
        if (start == end) {  // Leaf node
            tree[index] = value;
            return;
        }

        int mid = start + (end - start) / 2;
        if (pos <= mid) update(pos, start, mid, 2 * index, value);
        else update(pos, mid + 1, end, 2 * index + 1, value);

        tree[index] = max(tree[2 * index], tree[2 * index + 1]); // Recalculate parent node
    }

    int query(int ql, int qr, int start, int end, int index) {
        if (qr < start || ql > end) return INT_MIN;  // No overlap
        if (ql <= start && end <= qr) return tree[index]; // Complete overlap

        int mid = start + (end - start) / 2;
        int leftQuery = query(ql, qr, start, mid, 2 * index);
        int rightQuery = query(ql, qr, mid + 1, end, 2 * index + 1);
        return max(leftQuery, rightQuery);
    }

public:
    SegmentTree(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n, 0);
        buildTree(1, 0, n - 1, nums);
    }

    void update(int pos, int value) {
        update(pos, 0, n - 1, 1, value);
    }

    int query(int left, int right) {
        return query(left, right, 0, n - 1, 1);
    }
};

int main() {
    vector<int> nums = {1, 3, 5, 7, 9, 11};
    SegmentTree seg(nums);

    cout << "Max in range [1, 4]: " << seg.query(1, 4) << endl; // Output: 9
    seg.update(3, 6);
    cout << "Max in range [1, 4] after update: " << seg.query(1, 4) << endl; // Output: 9
}
How It Works
Build Tree: Recursively construct the tree in O(N).
Update: Directly updates an element, then recalculates the segment tree (O(logN)).
Query: Finds the maximum in a given range in O(logN).
Differences from Lazy Propagation
Feature	Without Lazy Propagation	With Lazy Propagation
Update Complexity	O(logN) (Direct update)	O(logN) (Deferred update)
Query Complexity	O(logN)	O(logN) (after propagation)
Best For	Point updates & queries	Range updates & queries
This version works well if you don't need frequent range updates.

Would you like a range update version (without lazy propagation)? 🚀







You said:
for sum query problem and not for the max in the range
ChatGPT said:
Sure! Here's a Segment Tree for Range Sum Query with Point Updates (Without Lazy Propagation).

Segment Tree (Sum Query, No Lazy Propagation)
cpp
Copy
Edit
#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;

    void buildTree(int index, int start, int end, vector<int>& nums) {
        if (start == end) {
            tree[index] = nums[start];
            return;
        }
        int mid = start + (end - start) / 2;
        buildTree(2 * index, start, mid, nums);
        buildTree(2 * index + 1, mid + 1, end, nums);
        tree[index] = tree[2 * index] + tree[2 * index + 1];
    }

    void update(int pos, int start, int end, int index, int value) {
        if (start == end) {  // Leaf node
            tree[index] = value;
            return;
        }

        int mid = start + (end - start) / 2;
        if (pos <= mid) update(pos, start, mid, 2 * index, value);
        else update(pos, mid + 1, end, 2 * index + 1, value);

        tree[index] = tree[2 * index] + tree[2 * index + 1]; // Update parent node
    }

    int query(int ql, int qr, int start, int end, int index) {
        if (qr < start || ql > end) return 0;  // No overlap
        if (ql <= start && end <= qr) return tree[index]; // Complete overlap

        int mid = start + (end - start) / 2;
        int leftQuery = query(ql, qr, start, mid, 2 * index);
        int rightQuery = query(ql, qr, mid + 1, end, 2 * index + 1);
        return leftQuery + rightQuery;
    }

public:
    SegmentTree(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n, 0);
        buildTree(1, 0, n - 1, nums);
    }

    void update(int pos, int value) {
        update(pos, 0, n - 1, 1, value);
    }

    int query(int left, int right) {
        return query(left, right, 0, n - 1, 1);
    }
};
