#include "ctrmdecode.h"

#include <fstream>
#include <string>

using namespace TRM_TXT_RES;

CTrmDecode::CTrmDecode()
    : CTrmDecodeStateMashine(this)
{

}

void CTrmDecode::Start()
{
	SetStateInit();
}

void CTrmDecode::Init()
{
	SetStateOpen();
}

void CTrmDecode::Open()
{
    SetStateAnswer();
    ClearScreen();

    printf("%s: ", text(siOpenFileEnterName).c_str());
    std::string fname;
    if (not InputStr(fname)) {ShowError(siOpenFileNoName); return;}

    ParseFile(fname);
}

void CTrmDecode::ParseFile(const std::string &fname)
{
    const auto res = m_casket->LoadFileJSON(fname);
    if (not res.OK())
    {
        printf("%s", CTextResult(res).Text().c_str());
        SetStateEnd();
        return;
    }

    for (CSetCombPtr &sc : m_casket->GetSetcombs())
    {
        CTrmDecQuestionPtr trm_quest = CTrmDecQuestionPtr(new CTrmDecQuestion());
        trm_quest->SetSetcomb(sc);
        m_trm_questions.push_back(trm_quest);
    }
}

void CTrmDecode::ShowError(const enStringId str_id)
{
    printf("%s", text(str_id).c_str());
    SetStateEnd();
}

void CTrmDecode::Answer()
{
    SetStateEnd();

    for (auto &trm_question : m_trm_questions)
    {
        trm_question->Begin();
        if (trm_question->Valid(enPurpose::pEncode).ERROR())
        {
            printf("%s\n", text(siError).c_str());
            SetStateEnd();
            return;
        }
    }

    SetStateResult();
}

void CTrmDecode::Result()
{
	SetStateEnd();
    printf("%s:\n", text(siPassResult).c_str());
    m_casket->PassFromKeyhole();
    printf("%s\n", m_casket->GetPass()->GetPasswordString().c_str());
}
