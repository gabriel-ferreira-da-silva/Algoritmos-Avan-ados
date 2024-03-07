#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

class Vebt{
    public:
        long long int u, min, max;
        Vebt* summary;
        vector<Vebt*> cluster;

        Vebt(long long int size){
            min = size;
            max = -1;
            u=size;
            if(u<=2){
                return;
            }
            long long int ru =(long long int) sqrt(size);
            summary = new Vebt(ru);
            for(long long int i=0; i < u;i++){
                Vebt* n = new Vebt(ru);
                cluster.push_back(n);
            }
        }
};

long long int high (Vebt *v, long long int x){
    return (long long int ) floor( x/ sqrt(v->u));
}

long long int low(Vebt *v, long long int x){
    return (long long int ) x % (long long int) floor((sqrt(v->u)));
}

long long int index(Vebt *v,long long int h, long long int l){
    return h*( (long long int) sqrt(v->u) ) + l;
}



void insert(Vebt *v, long long int x){
    if(x==v->min || x==v->max){
        return;
    }
    if(v->u==2){
        // pode não ser isso q as notas descrevem como min() e max()
        v->min = v->min < x ? v->min : x;
        v->max = v->max > x ? v->max : x;
        return;
    }
    if(v->min == v->u){
        v->min = x;
        v->max = x;
        return;
    }
    if( x < v->min){
        long long int t =x;
        x = v->min;
        v->min = t;
    }
    v->max = v->max > x ? v->max : x;
    long long int h = high(v , x);
    long long int l = low(v , x);

    if(v->cluster[h]->min==v->cluster[h]->u){
        insert(v->summary, h);
    }
    insert(v->cluster[h],l);
}

long long int sucessor(Vebt *v, long long int x){
    if(x < v->min){
        return v->min;
    }
    if(x > v->max){
        return v->u;
    }
    if(v->u == 2){
        if(x==0&& v->max==1){
            return 1;
        }else{
            return 2;
        }
    }
    long long int h = high(v,x);
    long long int l = low(v,x);
    if(l < v->cluster[h]->max){
        long long int s = sucessor(v->cluster[h], l);
        return index(v, h, s);
    }else{
        h =sucessor(v->summary, h);
        if(h==v->summary->u){
            return v->u;
        }else{
            long long int s =v->cluster[h]->min;
            return index(v, h, s);
        }
    }
}

void remove(Vebt *v, long long int x){
    if(v->u==2){
        if(x==v->min){
            v->min = v->max != v->min ? v->max : 2;
        }
        if(x==v->max){
            v->max = v->min != v->u ? v->min: -1;
        }
        return;
    }

    if(x==v->min){
        long long int i = v->summary->min;
        if(i==v->summary->u){
            v->min = v->u;
            v->max = -1;
        }else{
            v->min = index(v, i,v->cluster[i]->min);
            x=v->min;
        }
    }
    long long int h =high(v, x);
    long long int l =low(v, x);
    remove(v->cluster[h], l);
    if(v->cluster[h]->min == v->cluster[h]->u){
        remove(v->summary, h);
    }
    if(x==v->max){
        long long int i=v->summary->max;
        if(i==-1){
            v->max = v->min;
        }else{
            v->max = index(v, i,v->cluster[i]->max);
        }
    }
}


int main(){
    Vebt v(256);
    insert(&v, 1);
    insert(&v, 12);
    insert(&v, 43);
    insert(&v, 124);
    insert(&v, 12);
    insert(&v, 43);
    insert(&v, 34);
    insert(&v, 156);
    insert(&v, 236);

    printf("%lld\n", sucessor(&v, 4));
    printf("%lld\n", sucessor(&v, 40));
    printf("%lld\n", sucessor(&v, 94));
    printf("%lld\n", sucessor(&v, 150));
    printf("%lld\n", sucessor(&v, 220));
    printf("%lld\n", sucessor(&v, 240));


}