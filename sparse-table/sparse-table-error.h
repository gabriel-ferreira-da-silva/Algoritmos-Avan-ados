#include<iostream>
#include<cmath>
#include<vector>


int mu(int (*func) (std::vector<int> F ,int start, int end),std::vector<int> F1 , std::vector<int> F2, int start, int end){
    std::vector<int> ans;
    for(int i=start; i < F1.size() ; i++){
        ans.push_back(F1[i]);
    }
    for(int i=0; i < end ; i++){
        ans.push_back(F2[i]);
    }
    return func(ans, 0,ans.size());
}

std::vector<std::vector<int>> preprocess(int neutro, std::vector<int> A, int (*func) (std::vector<int>, int, int)){
    std::vector< std::vector<int> > table;
    
    int n = A.size();
    int m =  floor(log2(n)) + 1;
    
    for(int i=0; i < m; i++){
        std::vector<int> column;
        for(int j=0; j < n ; j++){
            column.push_back(neutro);
        }
        table.push_back(column);        
    }

    for(int i =0; i < n; i++){
        table[0][i] = A[i];
    }

    int k=2;
    for(int i=1; i<m; i++){
        for(int j=0; j<n ; j++){
            table[i][j] = func(table[i-1], j, j+k);        
        }
        k = k*2;
    }

    
    for(int i =0; i < m; i++){
        for(int j=0; j < n ; j++){
            std::cout << table[i][j] << " ";
        }
        std::cout<< "\n";
    }

    return table;
}

int rangeQuery( int (*func) (std::vector<int> F ,int start, int end), std::vector<std::vector<int>> table, int neutral, int left, int right ){
    int ans = neutral;
    int index;
    while(left< right ){
        index = log2(right -left);
        std::vector<int> a,b;
        a.push_back(ans);
        b.push_back(table[index][left]);
        ans = mu(func, a,b,0,a.size() );
        left= left + (int) pow(2,(double) index); 
    }
    return ans;

}