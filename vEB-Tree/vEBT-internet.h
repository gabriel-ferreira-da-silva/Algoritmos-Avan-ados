/* 
 * Code for van emde boas tree. Try to implement function for predecessor as
 * an exercise.
 */

#include <cmath>
#include <iostream>
#include <vector>

class vEB
{
    int u;
    int min;
    int max;
    vEB *summary;
    std::vector<vEB *> children;

    int high(int k){
        int x = std::ceil(std::sqrt(u));
        return std::floor(k / x);
    }

    int low(int k){
        int x = std::ceil(std::sqrt(u));
        return k % x;
    }

    int index(int k, int kk){
        return (k * (int)std::sqrt(u)) + kk;
    }

public:

    vEB(int U){
        // u = std::pow(std::sqrt(U), 2);
        u = U;
        min = U;
        max = -1;
        
        if (u <= 2){
            summary = nullptr;
            children = std::vector<vEB *> (0, nullptr);
        }
        else{
            int children_count = std::ceil(std::sqrt(u));
            int children_size = std::ceil(u / std::sqrt(u));

            summary = new vEB(children_count);
            children = std::vector<vEB *> (children_count, nullptr);
            for(int i = 0; i < children_count; ++i){
                children[i] = new vEB(children_count);
            }
        }
    }

    void insert(int k){
        if(min > max){
            min = max = k;
            return;
        }

        if(k < min){
            int temp;
            temp = min;
            min = k;
            k = temp;
        }

        if(k > max)
            max = k;
        
        if(u == 2){
            max = k;
            return;
        }

        int i = high(k);
        int j = low(k);

        children[i]->insert(j);

        if(children[i]->max == children[i]->min)
            summary->insert(i);
    }

    void remove(int k){
        if(min > max)
            return;

        if(min == max){
            min = u;
            max = -1;
            return;
        }

        if(u == 2){
            if(k == 1){
                if(min == 1){
                    min = u;
                    max = -1;
                }
                else if(min == 0)
                    max = 0;
            }
            else
                if(max == 0){
                    min = u;
                    max = -1;
                }
                else if(max == 1)
                    min = 1;
            return;
        }

        if(k == min){
            int i = summary->min;
            min = index(i, children[i]->min);
            return;
        }

        int i = high(k);
        int j = low(k);

        children[i]->remove(j);

        if(children[i]->min > children[i]->max){
            summary->remove(i);
        }

        if(k == max){
            if(summary->min > summary->max){
                max = min;
            }
            else{
                i = summary->min;
                max = index(i, children[i]->max);
            }
        }
    }

    int getMin(){
        return min;
    }
    int getMax(){
        return max;
    }

    int universe(){
        return u;
    }

    int successor(int k){
        if(k <= min)
            return min;
        else if(k > max)
            return u;
        
        int i = high(k);
        int j = low(k);

        if(j <= children[i]->max){
            int res = children[i]->successor(j);
            if(res >= (u / (int)std::sqrt(u)))
                return u;
            return k - j + res;
        }
        else{
            int res = children[summary->successor(i)]->min;
            if(res >= children[summary->min]->u)
                return u;
            return index(summary->successor(i), res);
        }
    }
};

