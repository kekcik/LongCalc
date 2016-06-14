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
        else
            if (first + second + balance >= mod)
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
    *this = result;
    return *this;
}


big_integer operator*(big_integer a, big_integer const& b)
{
    return a *= b;
}

big_integer div2(big_integer a)
{
    ull b, c = 0;
    for (int i = (int)a.data.size() - 1; i >= 0; --i)
    {
        b = a.data[i] % 2;
        a.data[i] >>= 1;
        a.data[i] += (2*p) * c;
        c = b;
    }
    resize(a);
    return a;
}



big_integer& big_integer::operator/=(big_integer const& rhs)
{
    return *this;
}

big_integer operator/(big_integer a, big_integer const& b)
{
    return a /= b;
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

/*
 big_integer::big_integer(std::string const& str)
 {
 if (mpz_init_set_str(mpz, str.c_str(), 10))
 {
 mpz_clear(mpz);
 throw std::runtime_error("invalid string");
 }
 }
 
 
 
 big_integer& big_integer::operator%=(big_integer const& rhs)
 {
 mpz_tdiv_r(mpz, mpz, rhs.mpz);
 return *this;
 }
 
 big_integer& big_integer::operator&=(big_integer const& rhs)
 {
 mpz_and(mpz, mpz, rhs.mpz);
 return *this;
 }
 
 big_integer& big_integer::operator|=(big_integer const& rhs)
 {
 mpz_ior(mpz, mpz, rhs.mpz);
 return *this;
 }
 
 big_integer& big_integer::operator^=(big_integer const& rhs)
 {
 mpz_xor(mpz, mpz, rhs.mpz);
 return *this;
 }
 
 big_integer& big_integer::operator<<=(int rhs)
 {
 mpz_mul_2exp(mpz, mpz, rhs);
 return *this;
 }
 
 big_integer& big_integer::operator>>=(int rhs)
 {
 mpz_div_2exp(mpz, mpz, rhs);
 return *this;
 }
 
 big_integer big_integer::operator~() const
 {
 big_integer r;
 mpz_com(r.mpz, mpz);
 return r;
 }
 
 big_integer& big_integer::operator++()
 {
 mpz_add_ui(mpz, mpz, 1);
 return *this;
 }
 
 big_integer big_integer::operator++(int)
 {
 big_integer r = *this;
 ++*this;
 return r;
 }
 
 big_integer& big_integer::operator--()
 {
 mpz_sub_ui(mpz, mpz, 1);
 return *this;
 }
 
 big_integer big_integer::operator--(int)
 {
 big_integer r = *this;
 --*this;
 return r;
 }
 
 big_integer operator+(big_integer a, big_integer const& b)
 {
 return a += b;
 }
 
 big_integer operator-(big_integer a, big_integer const& b)
 {
 return a -= b;
 }
 
 
 
 
 
 big_integer operator%(big_integer a, big_integer const& b)
 {
 return a %= b;
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
 
 big_integer operator<<(big_integer a, int b)
 {
 return a <<= b;
 }
 
 big_integer operator>>(big_integer a, int b)
 {
 return a >>= b;
 }
 */
