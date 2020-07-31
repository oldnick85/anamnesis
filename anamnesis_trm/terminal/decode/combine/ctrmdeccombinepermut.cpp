#include "ctrmdeccombinepermut.h"

using namespace TRM_TXT_RES;

CTrmDecCombinePermutStateMashine::CTrmDecCombinePermutStateMashine(ITrmDecCombinePermutHandler* callback)
    : m_callback(callback)
{

}

CTrmDecCombinePermut::CTrmDecCombinePermut(ICombinePtr combine, ITrmDecSetgenPtr trm_setgen)
    : CTrmDecCombinePermutStateMashine(this)
    , m_combine(combine)
    , m_trm_setgen(trm_setgen)
{
    m_combine_permut = static_cast<CCombinePermutation*>(m_combine.get());
}

ICombinePtr CTrmDecCombinePermut::GetCombine() const
{
    return m_combine;
}

void CTrmDecCombinePermut::Start()
{
    SetStateInit();
}

void CTrmDecCombinePermut::Init()
{
    SetStateQuery();
}

void CTrmDecCombinePermut::Query()
{
    SetStateConfirm();
    printf("%s:\n", text(siCombinePermutGetPerm).c_str());
    printf("1..%lu %s %s\n", m_trm_setgen->GetSetgen()->VariantsCount(), text(siCombinePermutHint).c_str(), m_trm_setgen->SampleHint().c_str());
    std::string str_permut;
    if (not InputStr(str_permut))
    {
        SetStateEnd();
        return;
    }

    std::list<std::string> str_samples;
    auto res = ParseSamples(str_permut, str_samples);
    if (res.ERROR())
    {
        printf("%s\n", CTextResult(res).Text().c_str());
        return;
    }

    Sampling_t perm;
    for (const auto &str_sample : str_samples)
    {
        uint64 val;
        res = m_trm_setgen->ParseSample(str_sample, val);
        if (res.ERROR())
        {
            printf("%s\n", CTextResult(res).Text().c_str());
            return;
        }
        perm.push_back(val);
    }
    res = m_combine_permut->SetPermutation(perm, false);
    if (res.ERROR())
    {
        printf("%s\n", CTextResult(res).Text().c_str());
        return;
    }
}

void CTrmDecCombinePermut::Confirm()
{
    SetStateEnd();
}

bool CTrmDecCombinePermut::Valid() const
{
    return true;
}
