#include <bits/stdc++.h>
#include <cassert>
using namespace std;

class BitInt {
private:
    vector<int> num;
    bool flag = false;
    
    BitInt add(const BitInt& a, const BitInt& b) {
        vector<int> x1 = rev(a.num), x2 = rev(b.num);
        int len1 = x1.size(), len2 = x2.size();
        vector<int> x3(max(len1, len2) + 1, 0);
        for(int i = 0; i < max(len1, len2); i++) {
            int c = x3[i];
            if(i < len1) c += x1[i];
            if(i < len2) c += x2[i];
            x3[i] = c % 10;
            x3[i + 1] += c / 10;
        }
        trim(x3);
        vector<int> res = rev(x3);
        return BitInt(res);
    }
    
    BitInt sub(const BitInt& a, const BitInt& b) {
        vector<int> x1 = rev(a.num), x2 = rev(b.num);
        int len1 = x1.size(), len2 = x2.size();
        vector<int> x3(max(len1, len2), 0);
        for(int i = 0; i < len1; i++) {
            int c = x1[i];
            if(i < len2) c -= x2[i];
            if(c < 0){
                c += 10;
                x1[i + 1]--;
            }
            x3[i] = c;
        }
        trim(x3);
        vector<int> res = rev(x3);
        return BitInt(res);
    }

public:
    BitInt(vector<int>& a) : num(a), flag(false) {}
    
    BitInt(const vector<int>& a) : num(a), flag(false) {}

    BitInt() = default;

    friend std::istream& operator>>(std::istream& is, BitInt& obj) {
        string s;
        is >> s; 
        obj.flag = false;
        obj.num.clear();
        for(char &i : s) {
            if(i == '-') {
                obj.flag = true;
                continue;
            }
            obj.num.push_back(i - '0');
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, BitInt& obj) {
        if(obj.num.empty()) {
            os << "0";
            return os;
        }
        if(obj.flag) os << '-';
        for(int &i : obj.num) {
            os << (char)('0' + i);
        }
        return os;
    }

    BitInt operator+ (const BitInt& other){
        bool f1 = this->flag, f2 = other.flag;
        BitInt ans;
        if((f1 && f2) || (!f1 && !f2)) {
            ans = add(*this, other);
            if(f1 && f2) ans.flag = true;
        }
        else {
            if(BigMore(*this, other)) {
                ans = sub(*this, other);
                if(f1) ans.flag = true;
            }
            else {
                ans = sub(other, *this);
                if(f2) ans.flag = true;
            }
        }
        return ans;
    }

    BitInt operator- (const BitInt& other) {
        BitInt other_copy = other;
        other_copy.flag = !other_copy.flag;
        return (*this) + other_copy; 
    }

private:
    vector<int> rev(const vector<int>& a)const {
        int n = a.size();
        vector<int> res(n);
        for(int i = 0; i < n; i++) {
            res[i] = a[n - i - 1];
        }
        return res;
    }

    void trim(vector<int>& a) {
        while(!a.empty() && a.back() == 0) 
            a.pop_back();
        if(a.empty()) a.push_back(0); 
    }

    bool BigMore(const BitInt& a, const BitInt& b) {
        int len1 = a.num.size(), len2 = b.num.size();
        if(len1 > len2) return true;
        else if(len1 < len2) return false;
        else {
            for(int i = 0; i < len1; i++) { 
                if(a.num[i] < b.num[i])
                    return false;
                else if(a.num[i] > b.num[i])
                    return true;
            }
            return true; 
        }
    }
};