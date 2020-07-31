#include "ctrmdecquestion.h"

CTrmDecQuestionStateMashine::CTrmDecQuestionStateMashine(ITrmDecQuestionHandler* callback)
    : m_callback(callback)
{

}

CTrmDecQuestion::CTrmDecQuestion()
    : CTrmDecQuestionStateMashine(this)
{

}

void CTrmDecQuestion::Start()
{
    SetStateInit();
}

void CTrmDecQuestion::Init()
{
    SetStateEnd();
    m_trm_setgen->Begin();
    if (m_trm_setgen->Valid().ERROR())
        return;
    m_trm_combine->Begin();
}

bool CTrmDecQuestion::SetSetcomb(CSetCombPtr setcomb)
{
    m_setcomb = setcomb;

    m_trm_setgen = CTrmDecSetgenPtr(new CTrmDecSetgen(m_setcomb->GetSetgen()));
    m_trm_combine = CTrmDecCombinePtr(new CTrmDecCombine(m_setcomb->GetCombine(), m_trm_setgen));

    return true;
}

Result_t CTrmDecQuestion::Valid(const enPurpose purpose) const
{
    return (m_setcomb) ? m_setcomb->Valid(purpose) : Result_t(RES_ERROR);
}
