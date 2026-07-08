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
        // len1 >= len2, x1 >= x2
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

    BitInt mul(const BitInt& a, const BitInt& b) {
        vector<int> x1 = rev(a.num), x2 = rev(b.num);
        int len1 = x1.size(), len2 = x2.size();
        if((len1 == 1 && x1[0] == 0) || (len2 == 1 && x2[0] == 0)) {
            return BitInt();
        }
        vector<int> x3(len1 + len2, 0);
        for(int i = 0; i < len1; i++) {
            for(int j = 0; j < len2; j++) {
                x3[i + j] += x1[i] * x2[j];
            }
        }
        int carry = 0;
        for(int i = 0; i < len1 + len2; i++) {
            x3[i] += carry;
            carry = x3[i] / 10;
            x3[i] %= 10;
        }
        trim(x3);
        vector<int> res = rev(x3);
        return res;
    }

    pair<BitInt, BitInt> div(const BitInt& a, const BitInt& b) {
        BitInt x1(a.num), x2(b.num);
        int len1 = x1.num.size(), len2 = x2.num.size();
        if(len2 == 1 && x2.num[0] == 0) {
            throw runtime_error("div 0");
        }
        if(!BigMore(x1, x2)) {
            return {BitInt(), a};
        }
        BitInt r = x1, res;
        int shift = r.num.size() - x2.num.size();
        vector<int> shifted_x2 = x2.num;
        for(int i = 0; i < shift; i++) {
            shifted_x2.push_back(0);
        }
        for(int i = shift; i >= 0; i--) {
            int count = 0;
            while(BigMore(r, shifted_x2)) {
                r = sub(r, BitInt(shifted_x2));
                count++;
            }
            if(count || !res.num.empty())
                res.num.push_back(count);
            if(!shifted_x2.empty() && shifted_x2.back() == 0) {
                shifted_x2.pop_back();
            }
        }
        
        return {res, r};
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

    BitInt operator* (const BitInt& other) {
        bool f1 = this->flag, f2 = other.flag;
        BitInt ans = mul(*this, other);
        if(f1 ^ f2) ans.flag = true;
        return ans;
    }
    pair<BitInt, BitInt> operator/ (const BitInt& other) {
        bool f1 = this->flag, f2 = other.flag;
        auto [res, r] = div(*this, other);
        if(f1 ^ f2) {
            res.flag = true;
        }
        if(f1) {
            r.flag = true;
        }
        return {res, r};
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
        if(len1 != len2) return len1 > len2;
        for(int i = 0; i < len1; i++) { 
            if(a.num[i] != b.num[i]) 
                return a.num[i] > b.num[i];
        }
        return true;
    }
};