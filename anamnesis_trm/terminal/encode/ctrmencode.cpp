#include "ctrmencode.h"

#include <iostream>
#include <fstream>

using namespace TRM_TXT_RES;

CGuiEncode::CGuiEncode()
    : CTrmEncodeStateMashine(this)
{
    DEBUG_LOG("%s", __FUNCTION__);
}

void CGuiEncode::Start()
{
    DEBUG_LOG("%s", __FUNCTION__);
    SetStateInit();
}

void CGuiEncode::Init()
{
    DEBUG_LOG("%s", __FUNCTION__);
    SetStateQuery();
}

void CGuiEncode::Query()
{
    DEBUG_LOG("%s", __FUNCTION__);
    ShowStatus();
    printf("\n%s\n", text(siHorisontalSeparator).c_str());
    printf("%s. %s:\n 0 - %s\n 1 - %s\n 2 - %s\n 3 - %s\n 9 - %s\n",
           text(siEncodeQuery).c_str(), text(siQueryNextStep).c_str(), text(siEncodeQueryAnew).c_str(),
           text(siEncodeQueryAdd).c_str(), text(siEncodeQuerySetPass).c_str(),
           text(siEncodeQuerySave).c_str(), text(siExit).c_str());
    int opt;
    InputInt(opt);
    switch (opt)
    {
    case 0:		SetStateInit();		break;
    case 1:		SetStateAddQuest();	break;
    case 2:		SetStateSetPass();	break;
    case 3:		SetStateSave();		break;
    case 9:		SetStateEnd();		break;
    default:	SetStateQuery();	break;
    }
}

void CGuiEncode::AddQuest()
{
    DEBUG_LOG("%s", __FUNCTION__);
    ClearScreen();
    SetStateQuery();
    CTrmEncQuestionPtr quest = CTrmEncQuestionPtr(new CTrmEncQuestion());
    quest->Begin();
    auto res = quest->Valid();
    if (res.OK())
    {
        m_trm_questions.push_back(quest);
    }
    else
    {
        printf("%s\n", CTextResult(res).Text().c_str());
    }
}

void CGuiEncode::ShowQuestions()
{
    DEBUG_LOG("%s", __FUNCTION__);
    ClearScreen();
    SetStateQuery();
    if (m_trm_questions.empty())
    {
        printf("No questions added!");
        return;
    }
    uint i = 0;
    for (CTrmEncQuestionPtr trm_quest : m_trm_questions)
    {
        i++;
        printf("%u. %s\n", i, trm_quest->GetSetComb()->GetDescription().c_str());
    }
}

void CGuiEncode::SetPass()
{
    DEBUG_LOG("%s", __FUNCTION__);
    ClearScreen();
    SetStateQuery();
    m_trm_pass = CTrmEncPassPtr(new CTrmEncPass());
    m_trm_pass->Begin();
}

void CGuiEncode::Save()
{
    DEBUG_LOG("%s", __FUNCTION__);
    SetStateQuery();
    ClearScreen();
    CCasketPtr csct = MakeCasket();
    if (not csct) {printf("%s\n", text(siError).c_str()); return;}

    printf("%s: ", text(siSaveFileEnterName).c_str());
    std::string fname;
    if (not InputStr(fname)) {SetStateQuery(); return;}

    csct->KeyholeFromPass();
    const auto res = csct->SaveFileJSON(fname);
    if (not res.OK()) printf("%s\n", CTextResult(res).Text().c_str());
}

CCasketPtr CGuiEncode::MakeCasket() const
{
    DEBUG_LOG("%s", __FUNCTION__);
    if (not m_trm_pass)
    {
        printf("%s\n", text(siEncodeErrorNoPass).c_str());
        return nullptr;
    }
    CCasketPtr csct = CCasketPtr(new CCasket());
    csct->SetPass(m_trm_pass->GetPass());
    std::list<CSetCombPtr> setcombs;
    for (const auto &trm_question : m_trm_questions)
        setcombs.push_back(trm_question->GetSetComb());
    csct->SetSetcombs(setcombs);
    if (csct->Valid(enPurpose::pEncode).ERROR())
        return nullptr;
    return csct;
}

void CGuiEncode::ShowStatus() const
{
    DEBUG_LOG("%s", __FUNCTION__);
    printf("\n%s\n", text(siHorisontalSeparator).c_str());
    printf("%s\n", text(siEncodeStatus).c_str());
    std::string pass_status;
    std::string pass_entropy;
    if ((m_trm_pass) and (m_trm_pass->GetPass()->Valid(enPurpose::pEncode).OK()))
    {
        pass_status = text(siOK);
        auto variants = m_trm_pass->GetPass()->VariantsCount();
        char s[128];
        snprintf(s, sizeof(s), "%lu %s", variants.BitsCount(), text(siBit).c_str());
        pass_entropy = s;
    }
    else
    {
        pass_status = text(siNotSet);
        pass_entropy = "---";
    }
    printf("%s: %s [%s]\n", text(siEncodeStatusPass).c_str(), pass_status.c_str(), pass_entropy.c_str());

    std::string quest_entropy;
    CCasketPtr csct = MakeCasket();
    if (not csct)
    {
        quest_entropy = "---";
    }
    else
    {
        auto variants = csct->VariantsCount();
        char s[128];
        snprintf(s, sizeof(s), "%lu %s", variants.BitsCount(), text(siBit).c_str());
        quest_entropy = s;
    }
    printf("%s: %zu [%s]\n", text(siEncodeStatusQuestions).c_str(), m_trm_questions.size(), quest_entropy.c_str());
}
