#include "big_integer.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <string>
#define ull unsigned long long
#define ll long long
#define ui unsigned int
unsigned long long p = 1 << 30;
unsigned long long mod = 4 * p;

big_integer& resize (big_integer & a)
{
    while (!a.data[a.data.size() - 1] and a.data.size() != 1) a.data.pop_back();
    if (a.data.size() == 1 and a.data[0] == 0) a.flag = false;
    return a;
}
std::string to_string(big_integer const& a)
{
    std::string res = "";
    big_integer aa (a);
    big_integer bb (0);
    big_integer mod(1000000000);
    
    ui lexem;
    aa.flag = false;
    if (a == big_integer(0)) return "0";
    
    while (aa > big_integer(0))
    {
        bb = div_long_short(aa, 1000000000);
        lexem = (aa - bb * mod).data[0];
        aa = bb;
        for (int i = 0; i < 9; i++)
        {
            res += lexem % 10 + 48;
            lexem /= 10;
        }
    }
    
    while (res[res.size() - 1] == '0') res.pop_back();
    if (a.flag == 1) res += '-';
    for (int  i = 0; i < res.size() / 2; ++i) std::swap(res[i], res[res.size()-1-i]);
    return res;
}

std::ostream& operator<<(std::ostream& s, big_integer const& a)
{
    return s << to_string(a);
}

big_integer::big_integer()
{
    this->data.clear();
    this->data.push_back(0);
    this->flag = false;
}

big_integer::big_integer(std::string str)
{
    
    for (int i = str[0] == '-' ? 1 : 0; i < str.size(); ++i)
    {
        *this *= big_integer(10);
        *this += big_integer(str[i] - 48);
    }
    flag = (str[0] == '-' ? true : false);
    resize(*this);
}

big_integer::big_integer(big_integer const& other)
{
    this -> flag = other.flag;
    this -> data = other.data;
}

big_integer::big_integer(int a)
{
    this -> flag = a < 0 ? 1 : 0;
    data.push_back(a < 0 ? -a : a);
}

big_integer::big_integer(ui a)
{
    flag = false;
    data.push_back(a);
}

big_integer& big_integer::operator=(big_integer const& other)
{
    this -> data = other.data;
    this -> flag = other.flag;
    return *this;
}

bool operator==(big_integer const& a, big_integer const& b)
{
    if (a.flag == b.flag and a.data.size() == b.data.size()) {
        for (int i = 0; i < (int)a.data.size(); i++) {
            if (a.data[i] != b.data[i]) return false;
        }
        return true;
    }
    return false;
}

bool operator!=(big_integer const& a, big_integer const& b)
{
    return !operator==(a, b);
}

bool operator<(big_integer const& a, big_integer const& b)
{
    
    if (a.flag != b.flag) return a.flag;
    if (a.data.size() != b.data.size())
    {
        return ((a.data.size() < b.data.size()) ^ a.flag);
    }
    int i;
    for (i = (int) a.data.size() - 1; i >= 0 and a.data[i] == b.data[i]; --i);
    if (i < 0)
    {
        return false;
    }
    return (a.data[i] < b.data[i] and !a.flag);
}

bool operator>(big_integer const& a, big_integer const& b)
{
    return !operator<=(a, b);
}

bool operator<=(big_integer const& a, big_integer const& b)
{
    return operator<(a, b) || operator==(a, b);
}

bool operator>=(big_integer const& a, big_integer const& b)
{
    return !operator<(a, b);
}

//?

big_integer div_long_short (big_integer& a, ui b)
{
    big_integer result (a);
    ull balance = 0;
    for (int i = (int) result.data.size() - 1; i >=0; --i)
    {
        ull cur = (ull) result.data[i] + balance * mod;
        result.data[i] = (ui) (cur / b);
        balance = cur % b;
    }
    resize(result);
    return result;
}

big_integer& big_integer::operator+=(big_integer const& b)
{
    
    big_integer result;
    result.data.pop_back();
    
    ll balance = 0, first, second;
    ui length = (data.size() > b.data.size() ? (ui) data.size() : (ui) b.data.size());
    
    if (flag == b.flag)
    {
        result.flag = flag;
    }
    else if ((*this < -b and !flag) or (-*this > b and flag))
    {
        result.flag = true;
    }
    
    
    for (int i = 0; i < length; ++i)
    {
        first = i < data.size() ? data[i] : 0;
        if (result.flag ^ flag) first = -first;
        
        second = i < b.data.size() ? b.data[i] : 0;
        if (result.flag ^ b.flag) second = -second;
        
        result.data.push_back((ui)((ll)mod + first + second + balance));
        if (first + second + balance < 0)
        {
            balance = -1;
        }
        else if (first + second + balance >= mod)
        {
            balance = 1;
        }
        else
        {
            balance = 0;
        }
    }
    
    result.data.push_back((ui)balance);
    resize(result);
    *this = result;
    return *this;
}


big_integer& big_integer::operator-=(big_integer const& b)
{
    return *this += -b;
}

big_integer operator+(big_integer a, big_integer const& b)
{
    return a += b;
}

big_integer operator-(big_integer a, big_integer const& b)
{
    return a -= b;
}

big_integer& big_integer::operator--()
{
    this->operator-=(1);
    return *this;
}

big_integer big_integer::operator--(int)
{
    big_integer t = *this;
    --(*this);
    return t;
}

big_integer& big_integer::operator++()
{
    this->operator += (1);
    return *this;
}

big_integer big_integer::operator++(int)
{
    big_integer t = *this;
    ++(*this);
    return t;
}

big_integer big_integer::operator-() const
{
    big_integer r = *this;
    r.flag = (r.flag ? 0 : 1);
    if (*this == big_integer(0)) r = big_integer(0);
    return r;
}
big_integer big_integer::operator+() const
{
    return *this;
}


big_integer& big_integer::operator*=(big_integer const& b)
{
    big_integer result;
    ull mul;
    ui mU, mD;
    int k;
    
    result.data.resize((int)data.size() + (int)b.data.size());
    result.flag = flag != b.flag ? 1 : 0;
    
    for (int i = 0; i < (int)data.size(); ++i)
    {
        for (int j = 0; j < (int)b.data.size(); ++j)
        {
            mul = (ull)data[i] * (ull)b.data[j];
            mU  = (ui) (mul >> 32);
            mD  = (ui) mul;
            k = 0;
            while (mD + mU > 0)
            {
                mU += ((ull)result.data[i + j + k] + (ull)mD) >> 32;
                result.data[i + j + k] += mD;
                mD = mU;
                mU = 0;
                k++;
            }
        }
    }
    resize(result);
    return *this = result;
}


big_integer operator*(big_integer a, big_integer const& b)
{
    return a *= b;
}

big_integer& big_integer::operator/=(big_integer const& b)
{
    big_integer result;
    big_integer up, down;
    big_integer mod("4294967296");
    ll left, right, mid = 0;
    int amount = (int)(data.size() - b.data.size());
    if (amount < 0)
    {
        *this = 0;
        return *this;
    }
    up.data.resize(b.data.size());
    down.data.resize(b.data.size());
    for (int i = 0; i < b.data.size(); ++i)
    {
        up.data[i] = data[i + amount];
        down.data[i] = b.data[i];
    }
    for (int i = amount; i >= 0; --i)
    {
        left = 0;
        right = 1ll << 32;
        while (right - left > 1)
        {
            mid = (left + right) / 2 ;
            if (big_integer((ui)mid) * down > up)
            {
                right = mid;
            }
            else
            {
                left = mid;
            }
        }
        result *= mod;
        result += big_integer((ui)left);
        up -= big_integer((ui)left) * down;
        up *= mod;
        if (i) up += data[i - 1];
    }
    result.flag = flag ^ b.flag;
    *this = result;
    return *this;
}

big_integer operator/(big_integer a, big_integer const& b)
{
    return big_integer(a) /= b;
}


big_integer& big_integer::operator%=(big_integer const& rhs)
{
    
    big_integer res = *this - rhs * (*this / rhs);
    *this = res;
    return *this;
}

big_integer operator%(big_integer a, big_integer const& b)
{
    return a %= b;
}

big_integer& big_integer::operator<<=(int a)
{
    ull current, next = 0;
    int aShort = a % 32;
    int aLong  = a / 32;
    data.resize(aLong + data.size());
    
    //left short shift
    for (int i = 0; i < (int) data.size() - aLong; ++i)
    {
        current = (data[i] >> ((32 - aShort)) << (32 - aShort));
        data[i] <<= aShort;
        data[i] += (1ll << (32 - aShort)) * next;
        next = current;
    }
    
    //left long shift
    for (int i = (int)data.size() - 1; i >= 0; --i)
        data[i] = i - aLong >= 0 ? data[i - aLong] : 0;
    
    return *this;
}

big_integer& big_integer::operator>>=(int a)
{
    ull current, previous = 0;
    int aShort = a % 32;
    int aLong  = a / 32;
    bool inv = flag;
    
    if (flag)
    {
        flag = 0;
        *this -= 1;
    }
    
    //right short shift
    for (int i = (int) data.size() - 1; i >= 0; --i)
    {
        current = (data[i] << ((32 - aShort)) >> (32 - aShort));
        data[i] >>= aShort;
        data[i] += (1ll << (32 - aShort)) * previous;
        previous = current;
    }
    
    //right long shift
    for (int i = 0; i < (int) data.size(); ++i)
        data[i] = i < (int) data.size() - aLong ? data[i + aLong] : 0;
    
    if (inv)
    {
        *this += 1;
        flag = 1;
    }
    return resize(*this);
}


big_integer operator<<(big_integer a, int b)
{
    return a <<= b;
}

big_integer operator>>(big_integer a, int b)
{
    return a >>= b;
}

// pre
// type == 1 it's and-operation
// type == 2 it's or-operation
// type == 3 it's xor-operation
big_integer& binaryOperation (big_integer& a, big_integer const& b, int type)
{
    bool invA = a.flag;
    bool invB = b.flag;
    a.flag = false;
    int length = (int) std::max(a.data.size(), b.data.size());
    ui first =  invA ? ~(a.data[0] - 1) : a.data[0];
    ui second = invB ? ~(b.data[0] - 1) : b.data[0];
    a.data.resize(length);
    for (int i = 0; i < length; ++i)
    {
        if (type == 0) a.data[i] = first & second;
        if (type == 1) a.data[i] = first | second;
        if (type == 2) a.data[i] = first ^ second;
        first = i + 1 < a.data.size() ? a.data[i + 1] : 0;
        if (invA) first = ~first;
        second = i + 1 < b.data.size() ? b.data[i + 1] : 0;
        if (invB) second = ~second;
    }
    if (a.data[a.data.size() - 1] >> 1ll*31)
    {
        a -= 1;
        a.flag = true;
        for (int i = 0; i < (int) a.data.size(); ++i)
        {
            a.data[i] = ~a.data[i];
        }
    }
    return resize(a);
}

big_integer& big_integer::operator&=(big_integer const& b)
{
    return binaryOperation(*this, b, 0);
}

big_integer& big_integer::operator|=(big_integer const& b)
{
    return binaryOperation(*this, b, 1);
}

big_integer& big_integer::operator^=(big_integer const& b)
{
    return binaryOperation(*this, b, 2);
}


big_integer operator&(big_integer a, big_integer const& b)
{
    return a &= b;
}

big_integer operator|(big_integer a, big_integer const& b)
{
    return a |= b;
}

big_integer operator^(big_integer a, big_integer const& b)
{
    return a ^= b;
}

big_integer big_integer::operator~() const
{
    big_integer r = -(*this + 1);
    return r;
}
