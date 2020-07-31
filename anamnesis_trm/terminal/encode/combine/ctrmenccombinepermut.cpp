#include "ctrmenccombinepermut.h"

#include <iostream>
#include <sstream>

using namespace TRM_TXT_RES;

CTrmEncCombinePermutStateMashine::CTrmEncCombinePermutStateMashine(ITrmEncCombinePermutHandler* callback)
    : m_callback(callback)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

CTrmEncCombinePermut::CTrmEncCombinePermut(ITrmEncSetgenPtr set_generator)
    : CTrmEncCombinePermutStateMashine(this)
    , m_trm_setgen(set_generator)
{
    m_comb_perm = CCombinePermutationPtr(new CCombinePermutation());
}

CTrmEncCombinePermut::CTrmEncCombinePermut(ITrmEncSetgenPtr set_generator, CCombinePermutationPtr comb_perm)
    : CTrmEncCombinePermutStateMashine(this)
    , m_trm_setgen(set_generator)
    , m_comb_perm(comb_perm)
{

}

void CTrmEncCombinePermut::Start()
{
    SetStateInit();
}

void CTrmEncCombinePermut::Init()
{
    m_comb_perm->Reset();
    SetStateSetPermut();
}

void CTrmEncCombinePermut::SetPermut()
{
    SetStateEnd();
    printf("\n%s:\n", text(siCombinePermutSetPerm).c_str());
    printf("1..%lu %s %s\n", m_trm_setgen->GetSetgen()->VariantsCount(), text(siCombinePermutHint).c_str(), m_trm_setgen->SampleHint().c_str());
    std::string str;
    InputStr(str);
    Sampling_t perm;
    auto res = ParseString(str, perm);
    if (res.ERROR())
    {
        printf("%s\n", CTextResult(res).Text().c_str());
        m_comb_perm = nullptr;
        return;
    }
    m_comb_perm->SetParameters(m_trm_setgen->GetSetgen()->VariantsCount());
    res = m_comb_perm->SetPermutation(perm);
    if (res.ERROR())
    {
        printf("%s\n", CTextResult(res).Text().c_str());
        m_comb_perm = nullptr;
        return;
    }
}

Result_t CTrmEncCombinePermut::ParseString(const std::string &str, Sampling_t &samp)
{
    std::list<std::string> str_samples;
    auto res = ParseSamples(str, str_samples);
    if (res.ERROR())
        return res;
    if (str_samples.empty())
        return Result_t(RES_EMPTY_STRING);

    samp.clear();
    for (const auto &s : str_samples)
    {
        uint64 v;
        res = m_trm_setgen->ParseSample(s, v);
        if (res.ERROR())
            return res;
        samp.push_back(v);
    }
    return res;
}

ICombinePtr CTrmEncCombinePermut::GetCombine() const
{
    return m_comb_perm;
}

Result_t CTrmEncCombinePermut::Valid() const
{
    return (m_comb_perm) ? m_comb_perm->Valid(enPurpose::pEncode) : Result_t(RES_ERROR);
}
