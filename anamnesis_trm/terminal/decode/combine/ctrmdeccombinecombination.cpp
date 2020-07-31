#include "ctrmdeccombinecombination.h"

using namespace TRM_TXT_RES;

CTrmDecCombineCombinationStateMashine::CTrmDecCombineCombinationStateMashine(ITrmDecCombineCombinationHandler* callback)
    : m_callback(callback)
{

}

CTrmDecCombineCombination::CTrmDecCombineCombination(ICombinePtr combine, ITrmDecSetgenPtr trm_setgen)
    : CTrmDecCombineCombinationStateMashine(this)
    , m_combine(combine)
    , m_trm_setgen(trm_setgen)
{
    m_combine_Combination = static_cast<CCombineCombination*>(m_combine.get());
}

ICombinePtr CTrmDecCombineCombination::GetCombine() const
{
    return m_combine;
}

void CTrmDecCombineCombination::Start()
{
    SetStateInit();
}

void CTrmDecCombineCombination::Init()
{
    SetStateQuery();
}

void CTrmDecCombineCombination::Query()
{
    SetStateConfirm();
    printf("%s:\n", text(siCombineCombinationGetComb).c_str());
    printf("1..%lu %s %s\n", m_trm_setgen->GetSetgen()->VariantsCount(), text(siCombinePermutHint).c_str(), m_trm_setgen->SampleHint().c_str());
    std::string str_Combination;
    if (not InputStr(str_Combination))
    {
        SetStateEnd();
        return;
    }

    std::list<std::string> str_samples;
    auto res = ParseSamples(str_Combination, str_samples);
    if (res.ERROR())
    {
        return;
    }

    Sampling_t perm;
    for (const auto &str_sample : str_samples)
    {
        uint64 val;
        res = m_trm_setgen->ParseSample(str_sample, val);
        if (res.ERROR())
        {
            return;
        }
        perm.push_back(val);
    }
    res = m_combine_Combination->SetCombination(perm, false);
    if (res.ERROR())
    {
        return;
    }
}

void CTrmDecCombineCombination::Confirm()
{
    SetStateEnd();
}

bool CTrmDecCombineCombination::Valid() const
{
    return true;
}
