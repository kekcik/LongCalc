#include "big_integer.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <cstdint>

#define ull uint64_t
#define ll int64_t
#define ui uint32_t

ull p = 1 << 30;
ull mod = 4 * p;

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
        bb = aa;
        div_long_short(bb, 1000000000);
        lexem = (aa - bb * mod).data[0];
        aa = bb;
        for (int32_t i = 0; i < 9; ++i)
        {
            res += lexem % 10 + 48;
            lexem /= 10;
        }
    }

    while (res[res.size() - 1] == '0') res.pop_back();
    if (a.flag == true) res += '-';
    for (int32_t  i = 0; i < res.size() / 2; ++i) std::swap(res[i], res[res.size()-1-i]);
    return res;
}

std::ostream& operator<<(std::ostream& s, big_integer const& a)
{
    return s << to_string(a);
}

big_integer::big_integer()
{
    data.push_back(0);
    flag = false;
}

big_integer::big_integer(std::string const& str)
{
    big_integer b10(10);
    big_integer b0(0);
    data.clear();
    data.push_back(0);
    flag = false;
    for (int32_t i = str[0] == '-' ? 1 : 0; i < str.size(); ++i)
    {
        *this *= b10;
        b0.data[0] = str[i] - 48;
        *this += b0;
    }
    flag = (str[0] == '-' ? true : false);
    resize(*this);
}

big_integer::big_integer(big_integer const& other)
{
    flag = other.flag;
    data = other.data;
}

big_integer::big_integer(int a)
{
    ll aa = a;
    flag = aa < 0;
    data.push_back((ui)(flag ? -aa : aa));
}

big_integer::big_integer(ui a)
{
    flag = false;
    data.push_back(a);
}

big_integer& big_integer::operator=(big_integer const& other)
{
    data = other.data;
    flag = other.flag;
    return *this;
}

bool operator==(big_integer const& a, big_integer const& b)
{
    if (a.flag == b.flag and a.data.size() == b.data.size()) {
        for (int32_t i = 0; i < (int32_t)a.data.size(); ++i) {
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
    int32_t i;
    for (i = (int32_t) a.data.size() - 1; i >= 0 and a.data[i] == b.data[i]; --i);
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

void div_long_short (big_integer& a, ui b)
{
    ull balance = 0;
    ull cur;
    for (int32_t i = (int32_t) a.data.size() - 1; i >=0; --i)
    {
        cur = a.data[i] + balance * mod;
        a.data[i] = (ui) (cur / b);
        balance = cur % b;
    }
    resize(a);
}

big_integer& big_integer::operator+=(big_integer const& b)
{
    if (b.data.size() > data.size()) data.resize(b.data.size());
    bool f = false;
    ll balance = 0, first, second;
    int32_t length = (data.size() > b.data.size() ? (int32_t) data.size() : (int32_t) b.data.size());

    if (flag == b.flag)
    {
        f = flag;
    }
    else
    {
        if ((*this < -b and !flag) or (-*this > b and flag))
        {
            f = true;
        }
    }
    for (int32_t i = 0; i < length; ++i)
    {
        first = i < data.size() ? data[i] : 0;
        if (f ^ flag) first = -first;
        
        second = i < b.data.size() ? b.data[i] : 0;
        if (f ^ b.flag) second = -second;
        
        data[i] = ((ui)(first + second + balance));
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
        if (balance == 0 and i > std::min(data.size(), b.data.size()))
        {
            break;
        }
    }
    flag = f;
    data.push_back((ui)balance);
    resize(*this);
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
    /*t->*/operator-=(1);
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
    /*t->*/operator += (1);
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
    r.flag = (r.flag ? false : true);
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
    int32_t k;
    int a = (int32_t)data.size() + (int32_t)b.data.size() + 1;
    result.data.resize(a);
    result.flag = flag != b.flag ? true : false;
    for (int32_t i = 0; i < (int32_t) data.size(); ++i)
    {
        for (int32_t j = 0; j < (int32_t) b.data.size(); ++j)
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
    if (data.size() < b.data.size())
    {
        data.clear();
        data.push_back(0);
        flag = false;
        return *this;
    }
    if (b.data.size() == 1)
    {
        div_long_short(*this, b.data[0]);
        flag = flag ^ b.flag;
        return *this;
    }
    
    bool f = flag;
    big_integer u (*this);
    
    u.data.push_back(0);
    big_integer bb (b);
    big_integer result (0);
    result.data.resize(data.size() + 2);
    
    ll n = bb.data.size();
    ll m = data.size() - bb.data.size();
    ll uJ, vJ, i;
    ull temp1, temp2, temp;
    ull scale;
    ull qGuessm, r;
    ull borrow, carry;
    
    scale = mod / (bb.data[n-1] + 1);
    if (scale > 1)
    {
        u *=  big_integer((ui) scale);
        bb *= big_integer((ui) scale);
    }
    u.data.resize(std::max(data.size(),u.data.size()) + 2);
    for (vJ = m, uJ = n + vJ; vJ >= 0; --vJ, -- uJ)
    {
        qGuessm = ((ull)u.data[uJ] * mod + (ull)u.data[uJ - 1]) / (ull)bb.data[n-1];
        r =       ((ull)u.data[uJ] * mod + (ull)u.data[uJ - 1]) % (ull)bb.data[n-1];
        while (r < mod)
        {
            temp2 = (ull) bb.data[n - 2] * qGuessm;
            temp1 = r * mod + (ull) u.data[uJ - 2];
            
            if ((temp2 > temp1) || (qGuessm == mod))
            {
                --qGuessm;
                r += bb.data[n - 1];
            } else break;
        }
        carry = 0;
        borrow = 0;
        for (i = 0; i < n; i++)
        {
            temp1 = (ull)bb.data[i] * qGuessm + carry;
            carry = temp1 >> 32;
            temp1 = (ui) temp1;
            temp2 = (ull)u.data[i + vJ] - temp1 - borrow;
            borrow = (ull)u.data[i + vJ]  < temp1 + borrow ? 1 : 0;
            u.data[i + vJ] = (ui)temp2;
        }
        temp2 =  (ull)u.data[i + vJ] - carry - borrow;
        borrow = (ull)u.data[i + vJ]  < carry + borrow ? 1 : 0;
        u.data[i + vJ] = (ui)temp2;
        
        if (borrow == 0)
        {
            result.data[vJ] = (ui)qGuessm;
        }
        else
        {
            result.data[vJ] = (ui)qGuessm - 1;
            carry = 0;
            for (i = 0; i < n; ++i)
            {
                temp = (ull)u.data[i+vJ] + (ull)bb.data[i] + carry;
                carry = temp >= mod ? 1 : 0;
                u.data[i + vJ] = (ui)temp;
            }
            u.data[i + vJ] += carry - mod;
        }
//        resize(u);
    }
    resize(result);
    *this = result;
    flag = f ^ b.flag;
    return *this;
}

big_integer operator/(big_integer a, big_integer const& b)
{
    return a /= b;
}

big_integer& big_integer::operator%=(big_integer const& rhs)
{
    *this -= rhs * (*this / rhs);
    return *this;
}

big_integer operator%(big_integer a, big_integer const& b)
{
    return a %= b;
}

big_integer& big_integer::operator<<=(int a)
{
    ull current, next = 0;
    int32_t aShort = a % 32;
    int32_t aLong  = a / 32;
    data.resize(aLong + data.size() + 2);
    
    //left short shift
    for (int32_t i = 0; i < (int32_t) data.size() - aLong; ++i)
    {
        current = (data[i] >> ((32 - aShort)) << (32 - aShort));
        data[i] <<= aShort;
        data[i] += (1ll << (32 - aShort)) * next;
        next = current;
    }
    
    //left long shift
    for (int32_t i = (int32_t)data.size() - 1; i >= 0; --i)
        data[i] = i - aLong >= 0 ? data[i - aLong] : 0;
    
    return resize(*this);
}

big_integer& big_integer::operator>>=(int a)
{
    ull current, previous = 0;
    int32_t aShort = a % 32;
    int32_t aLong  = a / 32;
    bool inv = flag;
    
    if (flag)
    {
        flag = false;
        *this -= 1;
    }
    
    //right short shift
    for (int32_t i = (int32_t) data.size() - 1; i >= 0; --i)
    {
        current = (data[i] << ((32 - aShort)) >> (32 - aShort));
        data[i] >>= aShort;
        data[i] += (1ll << (32 - aShort)) * previous;
        previous = current;
    }
    
    //right long shift
    for (int32_t i = 0; i < (int32_t) data.size(); ++i)
        data[i] = i < (int32_t) data.size() - aLong ? data[i + aLong] : 0;
    
    if (inv)
    {
        *this += 1;
        flag = true;
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
    int32_t length = (int32_t) std::max(a.data.size(), b.data.size());
    ui first =  invA ? ~(a.data[0] - 1) : a.data[0];
    ui second = invB ? ~(b.data[0] - 1) : b.data[0];
    a.data.resize(length);
    for (int32_t i = 0; i < length; ++i)
    {
        if (type == 0) a.data[i] = first & second;
        if (type == 1) a.data[i] = first | second;
        if (type == 2) a.data[i] = first ^ second;
        first = i + 1 < length ? a.data[i + 1] : 0;
        if (invA) first = ~first;
        second = i + 1 < b.data.size() ? b.data[i + 1] : 0;
        if (invB) second = ~second;
    }
    if (a.data[a.data.size() - 1] >> 1ll*31)
    {
        a -= 1;
        a.flag = true;
        for (int i = 0; i < (int32_t) a.data.size(); ++i)
        {
            a.data[i] = ~a.data[i];
        }
    }
    return resize(a);
}

big_integer::~big_integer()
{
    
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
