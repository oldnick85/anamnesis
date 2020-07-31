#include "ctrmencpass.h"

using namespace TRM_TXT_RES;

CTrmEncPass::CTrmEncPass()
	: CTrmEncPassStateMashine(this)
{

}

void CTrmEncPass::Start()
{
    SetStateInit();
}

void CTrmEncPass::Init()
{
    m_pass = CPassPtr(new CPass());
    SetStateAddSymb();
}

void CTrmEncPass::AddSymb()
{
    SetStateSetPass();
    ClearScreen();
    printf("\n%s\n", text(siHorisontalSeparator).c_str());
    printf("%s:\n 1 - %s\n 2 - %s\n 3 - %s\n 4 - %s\n 10 - %s\n",
           text(siPassSymbQuery).c_str(),
           text(siPassSymbDigits).c_str(), text(siPassSymbLower).c_str(), text(siPassSymbUpper).c_str(),
           text(siPassSymbBraces).c_str(), text(siAbort).c_str());
    printf("(%s)\n", text(siInputVectorInt).c_str());
    std::vector<int> opt;
    if (not InputVecInt(opt))
    {
        printf("%s\n", text(siOK).c_str());
        SetStateEnd();
        return;
    }
    if (std::find(opt.begin(), opt.end(), 10) != opt.end())
    {
        printf("%s\n", text(siAbort).c_str());
        m_pass->Reset();
        SetStateEnd();
        return;
    }
    CPass::sSymbolClass s_class;
    if (std::find(opt.begin(), opt.end(), 1) != opt.end())  s_class.digits = true;
    if (std::find(opt.begin(), opt.end(), 2) != opt.end())  s_class.lower_case = true;
    if (std::find(opt.begin(), opt.end(), 3) != opt.end())  s_class.upper_case = true;
    if (std::find(opt.begin(), opt.end(), 4) != opt.end())  s_class.brackets = true;
    m_pass->SetSymbols(s_class);
    ShowSymbols();
}

void CTrmEncPass::SetPass()
{
    ClearScreen();
    printf("\n%s\n", text(siHorisontalSeparator).c_str());
    printf("%s:", text(siPassPassQuery).c_str());
    std::string pass;
    if (not InputStr(pass))
    {
        SetStateEnd();
        return;
    }

    auto res = m_pass->SetPassword(pass);
    if (res.OK())
    {
        SetStateEnd();
    }
    else
    {
        printf("%s: %s", text(siPassPassError).c_str(), CTextResult(res).Text().c_str());
        SetStateSetPass();
    }

}

void CTrmEncPass::ShowSymbols() const
{
    Pass_t sm = m_pass->GetSymbols();
    std::string str;
    for (auto c : sm)
    {
        str.push_back(static_cast<char>(c));
    }
    printf("%s: %s", text(siPassCurSymbSet).c_str(), str.c_str());
}
