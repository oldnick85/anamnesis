#include "ctrmenccombinecombination.h"


#include <iostream>
#include <sstream>

using namespace TRM_TXT_RES;

CTrmEncCombineCombinationStateMashine::CTrmEncCombineCombinationStateMashine(ITrmEncCombineCombinationHandler* callback)
    : m_callback(callback)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

CTrmEncCombineCombination::CTrmEncCombineCombination(ITrmEncSetgenPtr set_generator)
    : CTrmEncCombineCombinationStateMashine(this)
    , m_trm_setgen(set_generator)
{
    m_comb_combination = CCombineCombinationPtr(new CCombineCombination());
}

CTrmEncCombineCombination::CTrmEncCombineCombination(ITrmEncSetgenPtr set_generator, CCombineCombinationPtr comb_combination)
    : CTrmEncCombineCombinationStateMashine(this)
    , m_trm_setgen(set_generator)
    , m_comb_combination(comb_combination)
{

}

void CTrmEncCombineCombination::Start()
{
    SetStateInit();
}

void CTrmEncCombineCombination::Init()
{
    m_comb_combination->Reset();
    SetStateSetCombination();
}

void CTrmEncCombineCombination::SetCombination()
{
    SetStateEnd();
    printf("\n%s:\n", text(siCombinePermutSetPerm).c_str());
    printf("1..%lu %s %s\n", m_trm_setgen->GetSetgen()->VariantsCount(), text(siCombinePermutHint).c_str(), m_trm_setgen->SampleHint().c_str());
    std::string str;
    InputStr(str);
    Sampling_t comb;
    auto res = ParseString(str, comb);
    if (res.ERROR())
    {
        printf("%s\n", CTextResult(res).Text().c_str());
        m_comb_combination = nullptr;
        return;
    }
    m_comb_combination->SetParameters(m_trm_setgen->GetSetgen()->VariantsCount());
    res = m_comb_combination->SetCombination(comb);
    if (res.ERROR())
    {
        printf("%s\n", CTextResult(res).Text().c_str());
        m_comb_combination = nullptr;
        return;
    }
}

Result_t CTrmEncCombineCombination::ParseString(const std::string &str, Sampling_t &samp)
{
    std::list<std::string> str_samples;
    auto res = ParseSamples(str, str_samples);
    if (res.ERROR())
        return res;
    if (str_samples.empty())
        return Result_t(RES_EMPTY_STRING);

    samp.clear();
    for (auto &s : str_samples)
    {
        uint64 v;
        res = m_trm_setgen->ParseSample(s, v);
        if (res.ERROR())
            return res;
        samp.push_back(v);
    }
    return res;
}

ICombinePtr CTrmEncCombineCombination::GetCombine() const
{
    return m_comb_combination;
}

Result_t CTrmEncCombineCombination::Valid() const
{
    return (m_comb_combination) ? m_comb_combination->Valid(enPurpose::pEncode) : Result_t(RES_ERROR);
}
