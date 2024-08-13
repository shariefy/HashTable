

class UnionFind{
    private:
        int* parent;
        int* heights;
        int size;
    public:
        UnionFind(int intial_size):parent(new int[intial_size]) , heights(new int[intial_size] ) , size(intial_size) {
            for(int i=0 ; i<intial_size ; i++){
                parent[i] = -1;
                heights[i] = 0 ;
            }
        }
        ~UnionFind(){delete [] parent; delete [] heights ;}
        void make_set(int new_set);
        int find(int element);
        void unite(int set1 , int set2);

    private:

        void resize();
        
};

void UnionFind::resize() {
    int* new_parent = new int[size * 2];
    int* new_heights = new int[size * 2];

    for (int i = 0; i < size; i++) {
        new_parent[i] = parent[i];
        new_heights[i] = heights[i];
    }

    for (int i = size; i < size * 2; i++) {
        new_parent[i] = i; 
        new_heights[i] = -1; 
    }

    delete[] parent;
    delete[] heights;

    parent = new_parent;
    heights = new_heights;
    size *= 2;
}

void UnionFind::make_set(int new_set){
    if(new_set <size)
        parent[new_set] = new_set ;
    else{
        while (new_set >= size)
        {
            resize();
        }
        parent[new_set] = new_set ;
    }
}
void UnionFind::unite(int set1 , int set2){

    int root1= find(set1);
    int root2 = find(set2);

    if(root1!=-1 && root2 != -1){
        if(root1 != root2){
            if(heights[root1] > heights[root2]){
                parent[root2] = root1;
            }
            else if (heights[root1] < heights[root2]){
                parent[root1] = root2;
            }
            else{
                parent[root2] = root1 ;
                heights[root1]++;
            }
        }
    }
}

int UnionFind::find(int element){
    if(element < 0 || element >= size)
        return -1 ;

    if(parent[element] == -1)
        return -1; 
    int find_root = element;
    while (parent[find_root] != find_root){

        find_root = parent[find_root];
    }
    
    while (parent[element] != find_root)
    {
        int temp = parent[element];
        parent[element] = find_root;
        element = temp ;
    }
    

   return find_root ;

}


