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
        //long int size;

        vEBT(long int size){
            min = size;
            max = -1;
            u=size;
            summary = new vEBT(sqrt(size));
            cluster = std::vector<vEBT*>(sqrt(size), nullptr);
            

        }
        void insert(vEBT* v , long int x){
            if(x==v->min || x==v->max ){
                return;
            }
            if(v->u==2){    // eu não sei o que isso
                v->min = x < v->min? x: v->min; // faz e pode dar errado
                v->max = x > v->max? x: v->max;
                return;
            }
            if(v->min==v->u){
                v->min = v->max = x;
                return;
            }
            if(x < v->min){
                long int a = v->min;
                v->min = x;
                x = a;
            }

            v->max = v->max > x ? v->max : x;
            long int h = high(v,x);
            long int l = low(v, x);

            if(v->cluster[h]->min == v->cluster[h]->u){
                if(v->summary == nullptr){
                    v->summary = new vEBT(sqrt(v->u));
                }
                insert(v->summary, h);
            }
            if(v->cluster[h]==nullptr){
                v->cluster[h]== new vEBT(sqrt(v->u));
            }
            insert(v->cluster[h], l);

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