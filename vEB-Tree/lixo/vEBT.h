#include<iostream>
#include<vector>
#include<cmath>



long int high(long int u, long int k){
    long int x = std::ceil(std::sqrt(u));
    return std::floor(k / x);
}

long int low(long int u, long int k){
    long int x = std::ceil(std::sqrt(u));
    return k % x;
}

long int index(long int u, long int h, long int l){
    return (h * (long int)std::sqrt(u)) + l;
}

class vEBT{
    public:
        std::vector<long int> sm;
        std::vector<vEBT*> cluster;
        vEBT* summary;        
        long int min;
        long int max;
        long int u;
        //long int size;

        vEBT(long int size){
            u =size;
            min = u;
            max =-1;
            
            if(size <= 2){
                summary = nullptr;
                cluster = std::vector<vEBT*> (0, nullptr);
                return;
            }else{
                long int nc = (long int) ceil(sqrt(u));
                
                cluster = std::vector<vEBT*> (nc, nullptr);
                summary = new vEBT(nc);

                for(long int i=0; i < nc ; i++){
                    cluster[i]= new vEBT( ceil(sqrt(size)));
                }
            }
        }
};


void insert(vEBT* v, long int x){

    if(x==v->min || x==v->max){
        return;
    }
    if(v->min > v->max){
        v->min=x;
        v->max=x;
        return;
    }

    if(v->u==2){
        v->min = v->min > x ? x : v->min;
        v->max = v->max < x ? x : v->max;
        return;
    }
    if(v->min > x){
        long int a= x;
        x = v->min;
        v->min = a;
    }

    if(v->max < x){
        v->max = x;
    }

    long int h= high(v->u, x);
    long int l= low(v->u, x);
    if(v->cluster[h]->min >= v->cluster[h]->u){
        insert(v->cluster[h], l);
        insert(v->summary, h);
    }else{
        insert(v->cluster[h], l);
    }
}

long int successor(vEBT* v, long int x){
    if(x < v->min){
        return v->min;
    }
    if(x > v->max){
        return v->u;
    }
    if(v->u==2){
        if(x==0 && v->max ==1){
            return 1;
        }else{
            return 2;
        }
    }
    long int h= high(v->u, x);
    long int l = low(v->u, x);

    if(l < v->cluster[h]->max){
        long s = successor(v->cluster[h], l);
        return index(v->u, h,s);
    }else{
        h = successor(v->summary, h);
        if(h==v->summary->u){
            return v->u;
        }else{
            long s = v->cluster[h]->min;
            return index(v->u, h,s);
        }
    }

}


void remove( vEBT* v, long int x){
    if(v->u==2){
        if(x==v->min){
            v->min = v->max != v->min ? v->max :2;
        }
        if(x==v->max){
            v->max = v->min != v->u ? v->min :-1;
        }
        return;
    }
    if(x==v->min){
        long int i = v->summary->min;
        if(i==v->summary->u){
            v->min=v->u;
            v->max=-1;
            return;
        }else{
            v->min= index(v->u, i, v->cluster[i]->min);
            x= v->min;
        }
    }
    long int h = high(v->u, x);
    long int l = low(v->u, x);

    remove(v->cluster[h], l);
    if(v->cluster[h]->min == v->cluster[h]->u){
        remove(v->summary, h);
    }
    if(x==v->max){
        long int i= v->summary->max;
        if(i==-1){
            v->max=v->min;
        }else{
            v->max = index(v->u,i, v->cluster[i]->max);
        }
    }

}