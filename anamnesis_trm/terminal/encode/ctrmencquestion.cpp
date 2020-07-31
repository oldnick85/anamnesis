#include "ctrmencquestion.h"

using namespace TRM_TXT_RES;

CTrmEncQuestionStateMashine::CTrmEncQuestionStateMashine(ITrmEncQuestionHandler* callback)
    : m_callback(callback)
{

}

CTrmEncQuestion::CTrmEncQuestion()
    : CTrmEncQuestionStateMashine(this)
{
    DEBUG_LOG("%s", __FUNCTION__);
}

void CTrmEncQuestion::Start()
{
    DEBUG_LOG("%s", __FUNCTION__);
    SetStateInit();
}

void CTrmEncQuestion::Init()
{
    DEBUG_LOG("%s", __FUNCTION__);
    SetStateSetDescription();
    m_setcomb = CSetCombPtr(new CSetComb());
    m_trm_setgen = nullptr;
    m_trm_comb = nullptr;
}

void CTrmEncQuestion::SetDescription()
{
    DEBUG_LOG("%s", __FUNCTION__);
    SetStateSetGenerator();
    printf("%s:\n", text(siEncodeAddQuestDesc).c_str());
    std::string desc;
    if (not InputStr(desc))
    {
        printf("%s\n", text(siEncodeAddError).c_str());
        SetStateEnd();
        return;
    }
    m_setcomb->SetDescription(desc);
}

void CTrmEncQuestion::SetGenerator()
{
    DEBUG_LOG("%s", __FUNCTION__);
    SetStateSetCombinator();
    m_trm_setgen = CTrmEncSetgenPtr(new CTrmEncSetgen());
    m_trm_setgen->Begin();
    if (m_trm_setgen->Valid().ERROR())
    {
        printf("%s\n", text(siEncodeAddError).c_str());
        SetStateEnd();
        return;
    }
    m_setcomb->SetSetgen(m_trm_setgen->GetSetgen());
}

void CTrmEncQuestion::SetCombinator()
{
    DEBUG_LOG("%s", __FUNCTION__);
    SetStateSetAnswer();
    m_trm_comb = CTrmEncCombinePtr(new CTrmEncCombine(m_trm_setgen));
    m_trm_comb->Begin();
    if (m_trm_comb->Valid().ERROR())
    {
        printf("%s\n", text(siEncodeAddError).c_str());
        SetStateEnd();
        return;
    }
    m_setcomb->SetCombine(m_trm_comb->GetCombine());
}

void CTrmEncQuestion::SetAnswer()
{
    DEBUG_LOG("%s", __FUNCTION__);
    SetStateEnd();
}

CSetCombPtr CTrmEncQuestion::GetSetComb()
{
    DEBUG_LOG("%s", __FUNCTION__);
    return m_setcomb;
}

Result_t CTrmEncQuestion::Valid() const
{
    DEBUG_LOG("%s", __FUNCTION__);
    if (not m_setcomb)
        return Result_t(RES_ERROR);
    return (m_setcomb->Valid(enPurpose::pEncode));
}
