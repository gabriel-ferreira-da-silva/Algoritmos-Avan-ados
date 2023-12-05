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
        //tem alguma coisa errado com a inserção
        //min max do cluster folha não estou batendo
        void insert(vEBT* v , long int x){

            if(v->min==v->u){
                v->min = v->max = x;
                return;
            }

            if(x==v->min || x==v->max ){
                return;
            }

            if(v->u==2){    // eu não sei o que isso
                v->min = x < v->min? x: v->min; // faz e pode dar errado
                v->max = x > v->max? x: v->max;
                
                return;
            }

            if(x < v->min){
                long int a = v->min;
                v->min = x;
                x = a;
            }

            if(v->max < x){
                v->max = x;
            }

            v->max = v->max > x ? v->max : x;
            long int h = high(v,x);
            long int l = low(v, x);

            if(v->cluster[h]->min == v->cluster[h]->u){
                insert(v->summary, h);
            }

            insert(v->cluster[h], l);
        }


        void remove(vEBT* v, long int x){
            if(v->u == 2){
                if(x == v->min){
                    v->min = v->max != v->min ? v->max : v->u;
                }
                if(x==v->max){
                    v->max = v->min != v->min ? v->u : -1;
                }
                return;
            }

            if(x==v->min){
                long int i = v->summary->min;
                if(i == v->summary->u){
                    v->min = v->u;
                    v->max = -1;
                    return;
                }else{
                    v->min =index(v, i,v->cluster[i]->min);
                    x = v->min;
                }
                long int h,l;
                h= high(v,x);
                l= low(v,x);

                if(v->cluster[h]->min == v->cluster[h]->u ){
                    remove(v->summary, h);
                }

                if(x== v->max){
                    i = v->summary->max;
                    if(i==-1){
                        v->max = v->min;
                    }else{
                        v->max = index(v,i, v->cluster[i]->max);
                    }
                }
            }
        }

        long int sucessor(vEBT* v, long int x){
            if(x < v->min){
                return v->min;
            }
            if(x > v->max){
                return v->u;
            }
            if(v->u ==2){
                if(x==0 && v->max ==1){
                    return 1;
                }else{
                    return 2;
                }
            }

            long int h,l;
            h = high(v, x);
            l = low(v, x);

            if(l < v->cluster[h]->max){
                long int s= sucessor(v->cluster[h], l);
                return index(v, h,s);
            }else{
                h= sucessor(v->summary, h);
                if(h==v->summary->u){
                    return v->u;
                }else{
                    long int s= v->cluster[h]->min;
                    return index(v,h,s);
                }
            }
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

        void show(vEBT* v){
            if(v->u==2){
                if(v->max ==v->min){
                    std::cout << "1 ";
                }else{
                    std::cout << "0 ";
                }

                return;
            }

            for(long int i = 0; i < v->cluster.size() ; i++){
                show(v->cluster[i]);
            }
        }

};