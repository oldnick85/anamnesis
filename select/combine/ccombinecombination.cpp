#include "ccombinecombination.h"

#include <algorithm>

void CCombineCombination::Reset()
{
    m_n = 0;
    m_k = 0;
    m_comb.clear();
}

Result_t CCombineCombination::SetParameters(const uint64 n, const uint64 k)
{
    if (k > n)
        return Result_t(RES_COMB_N_LESS_K);
    m_n = n;
    m_k = k;
    return Result_t(RES_OK);
}

Result_t CCombineCombination::SetCombination(const Sampling_t &comb, bool set_k)
{
    if ((not set_k) and (comb.size() != m_k))
        return Result_t(RES_COMB_SIZE_NEQ_K);
    if (set_k)
    {
        if (comb.size() > m_n)
            return Result_t(RES_COMB_SIZE_GR_N);
        m_k = comb.size();
    }

    for (const uint64 i : comb)
    {
        if (i >= m_n)
            return Result_t(RES_COMB_VAL_GEQ_N);
        if (std::count(comb.cbegin(), comb.cend(), i) != 1)
            return Result_t(RES_COMB_VAL_DUPLICATE);
        m_comb.insert(i);
    }

    return Result_t(RES_OK);
}

CNumber CCombineCombination::Value() const
{
    std::vector<uint64> comb_map;
    for (const auto v : m_comb)
    {
        comb_map.push_back(v);
    }

    std::sort(comb_map.begin(), comb_map.end());
    auto res = CalcValue(comb_map, m_n);

    return res;
}

CNumber CCombineCombination::CalcValue(const std::vector<uint64> &comb_map, const uint64 n) const
{
    if (n == 0) return 0;
    if (comb_map.empty()) return 0;

    auto c_map = comb_map;

    CNumber res;
    if (c_map.front() == 0)
    {
        c_map.erase(c_map.begin());
        std::for_each(c_map.begin(), c_map.end(), [](uint64 &v){ v--; });
        res = CalcValue(c_map, n-1);
        res += BinomialCoeff(n-1, comb_map.size());
    }
    else
    {
        std::for_each(c_map.begin(), c_map.end(), [](uint64 &v){ v--; });
        res = CalcValue(c_map, n-1);
    }

    return res;
}

CNumber CCombineCombination::BinomialCoeff(const uint64 n, const uint64 k) const
{
    CNumber res(1);
    for (uint64 i = n - k + 1; i <= n; ++i)
        res *= i;

    CNumber divider(1);
    for (uint64 i = 1; i <= k; ++i)
        divider *= i;

    res /= divider;

    return res;
}

enCombineType CCombineCombination::GetType() const
{
    return enCombineType::ctCombination;
}

rapidjson::Document CCombineCombination::toJSON() const
{
    rapidjson::Value json_val;
    rapidjson::Document doc;
    auto& allocator = doc.GetAllocator();

    doc.SetObject();

    json_val.SetString(JSON_COMBINE_COMBINATION, allocator);
    doc.AddMember(JSON_COMBINE_TYPE, json_val, allocator);

    json_val.SetUint64(m_n);
    doc.AddMember(JSON_COMBINE_PERMUT_N, json_val, allocator);

    json_val.SetUint64(m_k);
    doc.AddMember(JSON_COMBINE_PERMUT_K, json_val, allocator);

    return doc;
}

bool CCombineCombination::fromJSON(const rapidjson::Value& doc)
{
    if (not doc.IsObject())
        return false;

    if (not doc.HasMember(JSON_COMBINE_PERMUT_N)) return false;
    m_n = doc[JSON_COMBINE_PERMUT_N].GetUint64();

    if (not doc.HasMember(JSON_COMBINE_PERMUT_K)) return false;
    m_k = doc[JSON_COMBINE_PERMUT_K].GetUint64();

    return true;
}

bool CCombineCombination::operator==(const CCombineCombination& rhs) const
{
    return ((m_n == rhs.m_n) and (m_k == rhs.m_k) and (m_comb == rhs.m_comb));
}

Result_t CCombineCombination::Valid(const enPurpose purpose) const
{
    Result_t res;
    if (m_n == 0)
        res.AddResult(RES_COMB_N_0);

    if (purpose == enPurpose::pEncode)
    {
        if (m_comb.empty())
            res.AddResult(RES_NO_COMBINATION);
    }
    else
    {

    }
    return res;
}

CNumber CCombineCombination::VariantsCount() const
{
    if (Valid(enPurpose::pDecode).ERROR()) return 0;

    return BinomialCoeff(m_n, m_k);
}
