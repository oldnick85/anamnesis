#include "ctrmenccombine.h"
#include "ctrmenccombinepermut.h"
#include "ctrmenccombinecombination.h"

using namespace TRM_TXT_RES;

CTrmEncCombine::CTrmEncCombine(ITrmEncSetgenPtr setgen)
    : m_setgen(setgen)
{

}

void CTrmEncCombine::Begin()
{
    printf("%s:\n 1 - %s\n 2 - %s\n 9 - %s\n",
           text(siCombineChoose).c_str(), text(siCombinePermut).c_str(), text(siCombineCombination).c_str(), text(siCancel).c_str());
    int opt;
    InputInt(opt);
    switch (opt)
    {
    case 1:
    {
        CTrmEncCombinePermutPtr comb_perm(new CTrmEncCombinePermut(m_setgen));
        comb_perm->Begin();
        if (comb_perm->Valid().ERROR())
        {
            printf("%s\n", text(siEncodeAddError).c_str());
            break;
        }
        m_trm_combine = comb_perm;
        break;
    }
    case 2:
    {
        CTrmEncCombineCombinationPtr comb_comb(new CTrmEncCombineCombination(m_setgen));
        comb_comb->Begin();
        if (comb_comb->Valid().ERROR())
        {
            printf("%s\n", text(siEncodeAddError).c_str());
            break;
        }
        m_trm_combine = comb_comb;
        break;
    }
    case 9:		m_trm_combine = nullptr;	break;
    default:	m_trm_combine = nullptr;    break;
    }
}

ICombinePtr CTrmEncCombine::GetCombine() const
{
    return ((m_trm_combine) ? m_trm_combine->GetCombine() : nullptr);
}

Result_t CTrmEncCombine::Valid() const
{
    auto cmb = GetCombine();
    return ((cmb) ? cmb->Valid(enPurpose::pEncode) : Result_t(RES_ERROR));
}
