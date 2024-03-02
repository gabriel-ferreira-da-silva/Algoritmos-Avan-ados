#include<iostream>
#include<vector>
#include<cmath>

class vEBT{
    public:
        std::vector<long int> sm;
        std::vector<vEBT*> cluster;
        vEBT* summary;        
        long int min;
        long int max;
        long int u;
        long int size;

        vEBT(long int M){
            min = -1;
            max = -1;
            
            long int size = M;
            long int n;

            u = 1 << M;

            if(size<=2){
                summary = nullptr;
                cluster = std::vector<vEBT*> (0, nullptr);
            }else{
                long int nc = ceil(sqrt(size));
                summary = new vEBT(nc);
                cluster = std::vector<vEBT*> (nc, nullptr);
                for(int i=0 ; i < nc ; i++){
                    cluster[i]= new vEBT(ceil(sqrt(size)));
                }
            }

            size = cluster.size();
        }

        void insert(vEBT* v, long int x){
            if( x == v->min ||  x== v->max){
                return;
            } 
            if(v->u==2){
                v->min = v->min < x? v->min : x;
                v->max = v->max > x? v->max : x;
                return;
            }
            if(v->min == v->u){
                v->min = x;
                v->max = x;
                return;
            }
            if(x < v->min){
                long int a = v->min;
                v->min =x;
                x = a;
            }

            v->max = v->max > x? v->max : x;
            long int h = high(v, x);
            long int l = low(v, x);
            
            if( v->cluster[h]->min == v->cluster[h]->u){
                insert(v->summary, h);
            }
            //insert(v->cluster[h], l);
            
        
    
        }

        long int high(vEBT* v, long int x){
            return floor( x / sqrt(v->u));
        }
        long int low(vEBT* v, long int x){
            return  (long int) x % (long int) sqrt(v->u);
        }
        long int index(vEBT* v, long int h, long int l){
            return (long int) h*sqrt(v->u) + l;
        }

};