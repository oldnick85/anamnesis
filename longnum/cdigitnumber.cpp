#include "cdigitnumber.h"

bool CDigitNumber::AddDigit(const sDigit &digit)
{
	if (digit.base < 2) return false;
	if (digit.num >= digit.base) return false;
	m_digits.push_front(digit);
	return true;
}

void CDigitNumber::Clear()
{
	m_digits.clear();
}

CNumber CDigitNumber::GetNumber() const
{
	CNumber res;
	if (m_digits.empty()) return res;

	CNumber cur_base;
	auto dn_it = m_digits.rbegin();
	while (dn_it != m_digits.rend())
	{
		res *= cur_base;
		const sDigit &d = *dn_it;
		res += d.num;
		cur_base = d.base;
		dn_it++;
	}

	return res;
}

std::string CDigitNumber::PrintHex() const
{
	std::string str;
	auto dg_it = m_digits.crbegin();
	while (dg_it != m_digits.crend())
	{
		const sDigit &dg = *dg_it;
		str.append(dg.PrintHex());
		dg_it++;
	}
	return str;
}

bool CDigitNumber::FromHex(const std::string str)
{
	Clear();
	std::string s = str;
	bool digit_ok = true;
	while ((not s.empty()) and digit_ok)
	{
		sDigit dg;
		digit_ok = dg.FromHex(s);
		if (digit_ok)
			digit_ok = AddDigit(dg);
	}
	return true;
}
