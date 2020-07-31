#include "ctrmdeccombine.h"

CTrmDecCombine::CTrmDecCombine(ICombinePtr combine, ITrmDecSetgenPtr trm_setgen)
    : m_combine(combine)
    , m_trm_setgen(trm_setgen)
{

}

void CTrmDecCombine::Begin()
{
    switch (m_combine->GetType())
    {
    case enCombineType::ctNone:
    {
        m_trm_combine = nullptr;
        break;
    }
    case enCombineType::ctPermutation:
    {
        auto combine_permut = new CTrmDecCombinePermut(m_combine, m_trm_setgen);
        combine_permut->Begin();
        if (combine_permut->Valid())
            m_trm_combine = ITrmDecCombinePtr(combine_permut);
        break;
    }
    case enCombineType::ctCombination:
    {
        auto combine_combination = new CTrmDecCombineCombination(m_combine, m_trm_setgen);
        combine_combination->Begin();
        if (combine_combination->Valid())
            m_trm_combine = ITrmDecCombinePtr(combine_combination);
        break;
    }
    }
}

ICombinePtr CTrmDecCombine::GetCombine() const
{
    return nullptr;
}

bool CTrmDecCombine::Valid() const
{
    return true;
}
