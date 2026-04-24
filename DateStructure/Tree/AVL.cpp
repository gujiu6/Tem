#include <bits/stdc++.h>
using namespace std;



template<typename T=int>
class AVL{
private:
    vector<int>left,right,count,sz,hei;
    vector<T>key;
    int cnt,head;
    void up(int i){
        sz[i]=sz[left[i]]+sz[right[i]]+count[i];
        hei[i]=max(hei[left[i]],hei[right[i]])+1;
    }
    int LeftRotate(int i){
        int r=right[i];
        right[i]=left[r];
        left[r]=i;
        up(i);
        up(r);
        return r;
    }
    int RightRotate(int i){
        int l=left[i];
        left[i]=right[l];
        right[l]=i;
        up(i);
        up(l);
        return l;
    }
    int maintain(int i){
        int l=left[i],r=right[i];
        int lh=hei[l],rh=hei[r];
        if(lh-rh>1){
            if(hei[left[l]]>=hei[right[l]]){
                i=RightRotate(i);
            }
            else{
                left[i]=LeftRotate(l);
                i=RightRotate(i);
            }
        }
        else if(rh-lh>1){
            if(hei[right[r]]>=hei[left[l]]){
                i=LeftRotate(i);
            }
            else{
                right[i]=RightRotate(r);
                i=LeftRotate(i);
            }
        }
        return i;
    }
    int add(int i,T value){
        if(i==0){
            key[++cnt]=value;
            count[cnt]=sz[cnt]=hei[cnt]=1;
            return cnt;
        }
        if(value==key[i]){
            count[i]++;
        }
        else if(value<key[i]){
            left[i]=add(left[i],value);
        }
        else{
            right[i]=add(right[i],value);
        }
        up(i);
        return maintain(i);
    }
    int getRank(int i,T value){
        if(i==0) return 0;
        if(value<=key[i]){
            return getRank(left[i],value);
        }
        else{
            return sz[left[i]]+count[i]+getRank(right[i],value);
        }
    }
    T index(int i,int x){
        if(sz[left[i]]>=x){
            return index(left[i],x);
        }
        else if(sz[left[i]]+count[i]<x){
            return index(right[i],x-sz[left[i]]-count[i]);
        }
        return key[i];
    }
    int findMin(int i){
        if(i==0) return 0;
        while(left[i]!=0){
            i=left[i];
        }
        return i;
    }
    int findMax(int i){
        if(i==0) return 0;
        while(right[i]!=0){
            i=right[i];
        }
        return i;
    }
    int removeMostleft(int i,int MostLeft){
        if(i==MostLeft){
            return right[i];
        }
        else{
            left[i]=removeMostleft(left[i],MostLeft);
            up(i);
            return maintain(i);
        }
    }
    int remove(int i,T value){
        if(value<key[i]){
            left[i]=remove(left[i],value);
        }
        else if(value>key[i]){
            right[i]=remove(right[i],value);
        }
        else{
            if(count[i]>1){
                count[i]--;
            }
            else{
                if(left[i]==0&&right[i]==0) return 0;
                else if(left[i]!=0&&right[i]==0) i=left[i];
                else if(left[i]==0&&right[i]!=0) i=right[i];
                else{
                    int MostLeft=findMin(right[i]);
                    right[i]=removeMostleft(right[i],MostLeft);
                    left[MostLeft]=left[i];
                    right[MostLeft]=right[i];
                    i=MostLeft;
                }
            }
        }
        up(i);
        return maintain(i);
    }
    T pre(int i,T value){
        if(i==0) return INT_MIN;
        if(value<=key[i]) return pre(left[i],value);
        else return max(key[i],pre(right[i],value));
    }
    T post(int i,T value){
        if(i==0) return INT_MAX;
        if(value>=key[i]) return post(right[i],value);
        else return min(key[i],post(left[i],value));
    }
public:
    AVL(int Maxx):cnt(0),head(0){
        left.resize(Maxx);right.resize(Maxx);
        count.resize(Maxx);sz.resize(Maxx);
        key.resize(Maxx);hei.resize(Maxx);
    }
    void add(int value){
        head=add(head,value);
    }
    int getRank(T value){
        return getRank(head,value)+1;
    }
    T index(int x){
        return index(head,x);
    }
    void remove(int value){
        if(getRank(value)!=getRank(value+1)){
            head=remove(head,value);
        }
    }
    T pre(T value){
        return pre(head,value);
    }
    T post(T value){
        return post(head,value);
    }
};









