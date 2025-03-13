class Tree {
    vector<int> tree;
    vector<int> lazy;
    int n;

    void pvtCreateTree(int index, int start, int end, vector<int>& nums) {
        if (start == end) {
            tree[index] = nums[start];
            return;
        }
        int mid = start + (end - start) / 2;
        pvtCreateTree(index * 2, start, mid, nums);
        pvtCreateTree(index * 2 + 1, mid + 1, end, nums);
        tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
    }

    void propagate(int index, int start, int end) {
        if (lazy[index] != 0) {
            tree[index] = max(tree[index] - lazy[index], 0);
            if (start != end) {
                lazy[index * 2] += lazy[index];
                lazy[index * 2 + 1] += lazy[index];
            }
            lazy[index] = 0;
        }
    }

    void pvtUpdate(int ql, int qr, int start, int end, int index, int value) {
        propagate(index, start, end);  // Apply pending updates first

        if (end < start || ql > end || qr < start) return;  // No overlap

        if (ql <= start && end <= qr) {  // Complete overlap
            lazy[index] += value;
            propagate(index, start, end);
            return;
        }

        int mid = start + (end - start) / 2;
        pvtUpdate(ql, qr, start, mid, index * 2, value);
        pvtUpdate(ql, qr, mid + 1, end, index * 2 + 1, value);

        tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
    }

public:
    Tree(int n) {
        this -> n = n;
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    bool createTree(vector<int>& nums, int n) {
        pvtCreateTree(1, 0, n - 1, nums);
        return tree[1] == 0;
    }

    bool update(int left, int right, int value) {
        pvtUpdate(left, right, 0, n - 1, 1, value);
        return tree[1] <= 0;
    }
};
