#include "cnumber.h"

void CNumber::FromUint(uint64 n)
{
    m_binary.clear();
    while (n > 0)
    {
        m_binary.push_back(n % 2);
        n = n / 2;
    }
}

void CNumber::PushDigitRight(const bool d)
{
    m_binary.push_front(d ? 1 : 0);
    TruncFirstZeros();
}

void CNumber::PushDigitLeft(const bool d)
{
    m_binary.push_back(d ? 1 : 0);
    TruncFirstZeros();
}

uint CNumber::PopDigitRight()
{
    auto d = m_binary.front();
    m_binary.pop_front();
    return d;
}

uint CNumber::PopDigitLeft()
{
    auto d = m_binary.back();
    m_binary.pop_back();
    return d;
}

CNumber& CNumber::operator<<=(const uint rhs)
{
    for (uint i = 0; i < rhs; ++i)
        m_binary.push_front(0);
    return *this;
}

CNumber& CNumber::operator>>=(const uint rhs)
{
    for (uint i = 0; (i < rhs) and (not m_binary.empty()); ++i)
        m_binary.pop_front();
    return *this;
}

const CNumber CNumber::operator<<(const uint rhs) const
{
    return (CNumber(*this) <<= rhs);
}

const CNumber CNumber::operator>>(const uint rhs) const
{
    return (CNumber(*this) >>= rhs);
}

CNumber& CNumber::operator+=(const CNumber& rv)
{
    if (rv.m_binary.empty()) return *this;
    uint carry = 0;
    auto &l_bin = m_binary;
    auto &r_bin = rv.m_binary;

    auto lv_it = l_bin.begin();
    auto rv_it = r_bin.begin();

    std::list<uint> sum;
    while ((rv_it != r_bin.end()) or (lv_it != l_bin.end()) or (carry != 0))
    {
        uint lb = (lv_it == l_bin.end()) ? 0 : *lv_it++;
        uint rb = (rv_it == r_bin.end()) ? 0 : *rv_it++;
        auto s = lb + rb + carry;
        sum.push_back(s % 2);
        carry = s / 2;
    }
    m_binary = sum;
    return *this;
}

const CNumber CNumber::operator+(const CNumber& rhs) const
{
    return CNumber(*this) += rhs;
}

CNumber& CNumber::operator-=(const CNumber& rv)
{
    if (rv.m_binary.empty()) return *this;
    if (rv == *this) {this->FromUint(0); return *this;}
    if (rv > *this) {this->FromUint(0); return *this;}

    uint carry = 0;
    auto &l_bin = m_binary;
    auto &r_bin = rv.m_binary;

    auto lv_it = l_bin.begin();
    auto rv_it = r_bin.begin();

    std::list<uint> sub;
    while ((rv_it != r_bin.end()) or (lv_it != l_bin.end()) or (carry != 0))
    {
        uint lb = (lv_it == l_bin.end()) ? 0 : *lv_it++;
        uint rb = (rv_it == r_bin.end()) ? 0 : *rv_it++;

        uint s = lb ^ rb ^ carry;
        carry = (lb & rb & carry) | ((~lb) & (rb | carry));
        sub.push_back(s);
    }
    m_binary = sub;
    TruncFirstZeros();
    return *this;
}

const CNumber CNumber::operator-(const CNumber& rhs) const
{
    return CNumber(*this) -= rhs;
}

CNumber& CNumber::operator*=(const CNumber& rv)
{
    CNumber s = *this;
    CNumber prd;

    for (uint v : rv.m_binary)
    {
        if (v == 1)
            prd += s;
        s <<= 1;
    }

    m_binary = prd.m_binary;
    TruncFirstZeros();
    return *this;
}

const CNumber CNumber::operator*(const CNumber& rhs) const
{
    return CNumber(*this) *= rhs;
}

CNumber& CNumber::operator/=(const CNumber& rhs)
{
    *this = (this->Divide(rhs)).first;
    return *this;
}

const CNumber CNumber::operator/(const CNumber& rhs) const
{
    return CNumber(*this) /= rhs;
}

CNumber& CNumber::operator%=(const CNumber& rhs)
{
    *this = (this->Divide(rhs)).second;
    return *this;
}

const CNumber CNumber::operator%(const CNumber& rhs) const
{
    return CNumber(*this) %= rhs;
}

bool CNumber::operator==(const CNumber& rhs) const 
{
    if (m_binary.size() != rhs.m_binary.size()) return false;
    auto lhs_it = m_binary.begin();
    auto rhs_it = rhs.m_binary.begin();
    while (lhs_it != m_binary.end())
    {
        if ((*lhs_it) != (*rhs_it)) return false;
        lhs_it++;
        rhs_it++;
    }
    return true;
}

bool CNumber::operator!=(const CNumber& rhs) const 
{
    return (not (*this == rhs));
}

bool CNumber::operator<(const CNumber& rhs) const
{
    if (m_binary.size() < rhs.m_binary.size()) return true;
    if (m_binary.size() > rhs.m_binary.size()) return false;
    if (m_binary.empty()) return false;
    auto lhs_it = m_binary.rbegin();
    auto rhs_it = rhs.m_binary.rbegin();
    while (lhs_it != m_binary.rend())
    {
        if ((*lhs_it) < (*rhs_it)) return true;
        if ((*lhs_it) > (*rhs_it)) return false;
        lhs_it++;
        rhs_it++;
    }
    return false;
}

bool CNumber::operator>(const CNumber& rhs) const
{
    if (m_binary.size() > rhs.m_binary.size()) return true;
    if (m_binary.size() < rhs.m_binary.size()) return false;
    if (m_binary.empty()) return false;
    auto lhs_it = m_binary.rbegin();
    auto rhs_it = rhs.m_binary.rbegin();
    while (lhs_it != m_binary.rend())
    {
        if ((*lhs_it) > (*rhs_it)) return true;
        if ((*lhs_it) < (*rhs_it)) return false;
        lhs_it++;
        rhs_it++;
    }
    return false;
}

bool CNumber::operator<=(const CNumber& rhs) const
{
    return ((*this < rhs) or (*this == rhs));
}

bool CNumber::operator>=(const CNumber& rhs) const
{
    return ((*this > rhs) or (*this == rhs));
}

CNumber& CNumber::operator++() { //префиксный
    *this += CNumber(1);
    return *this;
}

CNumber CNumber::operator++(int) { //постфиксный
    CNumber tmp(*this);
    ++(*this);
    return *this;
}

CNumber& CNumber::operator--() { //префиксный
    *this -= CNumber(1);
    return *this;
}

CNumber CNumber::operator--(int) { //постфиксный
    CNumber tmp(*this);
    --(*this);
    return *this;
}

CNumber CNumber::Factorial() const
{
    if (*this < 2) return 1;
    if (*this == 2) return 2;
    if (*this == 3) return 6;
    if (*this == 4) return 24;
    if (*this == 5) return 120;
    CNumber fact(720);
    for (CNumber i = 7; i <= *this; ++i)
        fact *= i;
    return fact;
}

uint64 CNumber::ToUint64() const
{
    uint64 v = 0;
    uint64 vm = 1;
    auto c = std::min(static_cast<uint>(m_binary.size()), static_cast<uint>(64));
    auto b_it = m_binary.begin();
    for (uint i = 0; i < c; ++i)
    {
        v += (*b_it) * vm;
        vm *= 2;
        b_it++;
    }
    return v;
}

std::string CNumber::PrintBin() const
{
    if (m_binary.empty()) return "0";
    std::string str;
    auto v_it = m_binary.rbegin();
    while (v_it != m_binary.rend())
    {
        uint v = *v_it;
        str.append((v == 0) ? "0" : "1");
        v_it++;
    }
    return str;
}

std::string CNumber::PrintHex() const
{
    return Print(16);
}

std::string CNumber::PrintDec() const
{
    return Print(10);
}

std::string CNumber::Print(const uint base) const
{
    if ((base < 1) or (base > 36)) return "";
    if (m_binary.empty()) return "0";
    std::string str;
    CNumber n = *this;
    CNumber b(base);

    while (n > 0)
    {
        auto cv = (n % b).ToUint64();
        char c;
        if (cv < 10)
            c = static_cast<char>('0' + static_cast<char>(cv));
        else
            c = static_cast<char>('A' + static_cast<char>(cv) - 10);
        str = c + str;
        n /= b;
    }

    return str;
}

bool CNumber::FromStringBin(const std::string &str)
{
	m_binary.clear();
	for (const char c : str)
	{
		if ((c == '0') or (c == '1'))
			PushDigitRight(c - '0');
	}
	return true;
}

bool CNumber::FromString(const std::string &str, const uint base)
{
	if ((base < 1) or (base > 36)) return false;
	m_binary.clear();
	for (const char c : str)
	{
		CNumber d;
		if ((c >= '0') and (c <= '9'))
            d = static_cast<uint64>(c - '0');
		else
            d = static_cast<uint64>(c - 'A' + 10);

		*this *= base;
		*this += d;
	}
	return true;
}

std::pair<CNumber, CNumber> CNumber::Divide(const CNumber &divider)
{
    if (divider == 0)
        return {0, 0};

    if (*this == 0)
        return {0, 0};

    CNumber division;
    CNumber remainder;

    auto th_it = m_binary.rbegin();
    while(th_it != m_binary.rend())
    {
        auto v = *th_it;
        remainder.PushDigitRight(v);

        if (remainder >= divider)
        {
            remainder -= divider;
            division.PushDigitRight(1);
        }
        else
            division.PushDigitRight(0);

        th_it++;
    }

    return {division, remainder};
}

CNumber& CNumber::operator^=(const CNumber& rv)
{
    auto &l_bin = m_binary;
    auto &r_bin = rv.m_binary;

    auto lv_it = l_bin.begin();
    auto rv_it = r_bin.begin();

    std::list<uint> bin;
    while ((rv_it != r_bin.end()) or (lv_it != l_bin.end()))
    {
        uint lb = (lv_it == l_bin.end()) ? 0 : *lv_it++;
        uint rb = (rv_it == r_bin.end()) ? 0 : *rv_it++;
        bin.push_back(lb ^ rb);
    }
    m_binary = bin;
    TruncFirstZeros();
    return *this;
}

const CNumber CNumber::operator^(const CNumber& rhs) const
{
    return CNumber(*this) ^= rhs;
}

CNumber& CNumber::operator&=(const CNumber& rv)
{
    auto &l_bin = m_binary;
    auto &r_bin = rv.m_binary;

    auto lv_it = l_bin.begin();
    auto rv_it = r_bin.begin();

    std::list<uint> bin;
    while ((rv_it != r_bin.end()) or (lv_it != l_bin.end()))
    {
        uint lb = (lv_it == l_bin.end()) ? 0 : *lv_it++;
        uint rb = (rv_it == r_bin.end()) ? 0 : *rv_it++;
        bin.push_back(lb & rb);
    }
    m_binary = bin;
    TruncFirstZeros();
    return *this;
}

const CNumber CNumber::operator&(const CNumber& rhs) const
{
    return CNumber(*this) &= rhs;
}

CNumber& CNumber::operator|=(const CNumber& rv)
{
    auto &l_bin = m_binary;
    auto &r_bin = rv.m_binary;

    auto lv_it = l_bin.begin();
    auto rv_it = r_bin.begin();

    std::list<uint> bin;
    while ((rv_it != r_bin.end()) or (lv_it != l_bin.end()))
    {
        uint lb = (lv_it == l_bin.end()) ? 0 : *lv_it++;
        uint rb = (rv_it == r_bin.end()) ? 0 : *rv_it++;
        bin.push_back(lb | rb);
    }
    m_binary = bin;
    TruncFirstZeros();
    return *this;
}

const CNumber CNumber::operator|(const CNumber& rhs) const
{
    return CNumber(*this) |= rhs;
}

void CNumber::TruncFirstZeros()
{
    bool first_zero = true;
    while ((not m_binary.empty()) and first_zero)
        if (m_binary.back() != 0)
            first_zero = false;
        else
            m_binary.pop_back();
}

uint64 CNumber::BitsCount() const
{
    return m_binary.size();
}
