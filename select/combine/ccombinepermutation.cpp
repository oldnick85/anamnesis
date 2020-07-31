#include "ccombinepermutation.h"

void CCombinePermutation::Reset()
{
    m_n = 0;
    m_k = 0;
    m_perm.clear();
}

Result_t CCombinePermutation::SetParameters(const uint64 n, const uint64 k)
{
    if (k > n) return Result_t(RES_COMB_N_LESS_K);
	m_n = n;
	m_k = k;
    return Result_t();
}

Result_t CCombinePermutation::SetPermutation(const Sampling_t &perm, bool set_k)
{
    if ((not set_k) and (perm.size() != m_k))
        return Result_t(RES_COMB_SIZE_NEQ_K);
    if (set_k)
    {
        if (perm.size() > m_n)
            return Result_t(RES_COMB_SIZE_GR_N);
        m_k = perm.size();
    }

    for (const uint64 i : perm)
	{
        if (i >= m_n)
            return Result_t(RES_COMB_VAL_GEQ_N);
        if (std::count(perm.cbegin(), perm.cend(), i) != 1)
            return Result_t(RES_COMB_VAL_DUPLICATE);
	}
	m_perm = perm;
    return Result_t(RES_OK);
}

CNumber CCombinePermutation::Value() const
{
	CNumber res = 0;
	std::unordered_set<uint64> perm;
	for (uint64 i = 0; i < m_n; ++i)
		perm.insert(i);

	uint64 m = m_n;
	for (const auto i : m_perm)
	{
		res *= m;
		m--;
		auto cnt = std::count_if(perm.begin(), perm.end(), [i](const uint64 ii) -> bool {return (i > ii);});
		CNumber o_i = static_cast<uint64>(cnt);
		perm.erase(i);
		res += o_i;
	}
	return res;
}

enCombineType CCombinePermutation::GetType() const
{
    return enCombineType::ctPermutation;
}

rapidjson::Document CCombinePermutation::toJSON() const
{
	rapidjson::Value json_val;
	rapidjson::Document doc;
	auto& allocator = doc.GetAllocator();

	doc.SetObject();

    json_val.SetString(JSON_COMBINE_PERMUTATION, allocator);
    doc.AddMember(JSON_COMBINE_TYPE, json_val, allocator);

	json_val.SetUint64(m_n);
	doc.AddMember(JSON_COMBINE_PERMUT_N, json_val, allocator);

	json_val.SetUint64(m_k);
	doc.AddMember(JSON_COMBINE_PERMUT_K, json_val, allocator);

	return doc;
}

bool CCombinePermutation::fromJSON(const rapidjson::Value& doc)
{
	if (not doc.IsObject())
		return false;

	if (not doc.HasMember(JSON_COMBINE_PERMUT_N)) return false;
	m_n = doc[JSON_COMBINE_PERMUT_N].GetUint64();

	if (not doc.HasMember(JSON_COMBINE_PERMUT_K)) return false;
	m_k = doc[JSON_COMBINE_PERMUT_K].GetUint64();

	return true;
}

bool CCombinePermutation::operator==(const CCombinePermutation& rhs) const
{
    return ((m_n == rhs.m_n) and (m_k == rhs.m_k) and (m_perm == rhs.m_perm));
}

Result_t CCombinePermutation::Valid(const enPurpose purpose) const
{
    Result_t res;
    if (m_n == 0)
        res.AddResult(RES_PERM_N_0);

    if (purpose == enPurpose::pEncode)
    {
        if (m_perm.empty())
            res.AddResult(RES_NO_PERMUTATION);
    }
    else
    {

    }
    return res;
}

CNumber CCombinePermutation::VariantsCount() const
{
    if (Valid(enPurpose::pDecode).ERROR()) return 0;

    CNumber res(1);
    for (uint64 i = m_n - m_k + 1; i <= m_n; ++i)
        res *= i;
    return res;
}
