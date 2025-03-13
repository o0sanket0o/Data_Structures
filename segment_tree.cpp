class SegmentTree{
    vector<int> tree;
    int n;
    void pvtCreate(vector<int>& baskets, int start, int end, int ind){
        if(end < start) return;
        if(end == start){
            tree[ind] = baskets[start];
            return;
        }
        int mid = start + (end - start) / 2;
        pvtCreate(baskets, start, mid, 2 * ind);
        pvtCreate(baskets, mid + 1, end, 2 * ind + 1);
        tree[ind] = max(tree[ind * 2], tree[ind * 2 + 1]);
    }

    int pvtGetIndex(int index, int start, int end, int value){
        // cout<<"Called "<<start<<','<<end<<" for "<<value<<endl;
        if(end < start) return -1;
        if(tree[index] < value) return -1;
        if(end == start){
            if(tree[index] >= value){
                tree[index] = -1;
                return start;
            }
            return -1;
        }
        int mid = start + (end - start) / 2, ans = -1;
        // cout<<start<<","<<mid<<" and "<<end<<endl;
        if(tree[index * 2] >= value) ans = pvtGetIndex(2 * index, start, mid, value);
        else if(tree[index * 2 + 1] >= value) ans = pvtGetIndex(2 * index + 1, mid + 1, end, value);
        tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
        return ans;
    }
    public:
    SegmentTree(int n){
        this -> n = n;
        for(int i = 0; i < 4 * n; ++i) tree.push_back(0);
    }
    void create(vector<int>& baskets, int n){
        pvtCreate(baskets, 0, n - 1, 1);
        // for(auto a : tree) cout<<a<<" ";
        // cout<<endl;
    } 
    
    int getIndex(int value){
        int ans = pvtGetIndex(1, 0, n - 1, value);
        // cout<<"\nFor "<<value<<" we got "<<ans<<endl;
        return ans;
    } 

};
