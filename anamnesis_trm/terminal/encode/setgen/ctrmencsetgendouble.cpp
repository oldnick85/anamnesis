#include "ctrmencsetgendouble.h"

using namespace TRM_TXT_RES;

CTrmEncSetgenDoubleStateMashine::CTrmEncSetgenDoubleStateMashine(ITrmEncSetgenDoubleHandler* callback)
    : m_callback(callback)
{

}

CTrmEncSetgenDouble::CTrmEncSetgenDouble()
    : CTrmEncSetgenDoubleStateMashine(this)
{
    m_setgen_double = CSetgenDoublePtr(new CSetgenDouble());
}

CTrmEncSetgenDouble::CTrmEncSetgenDouble(CSetgenDoublePtr setgen_double)
    : CTrmEncSetgenDoubleStateMashine(this)
    , m_setgen_double(setgen_double)
{

}

void CTrmEncSetgenDouble::Start()
{
    SetStateInit();
}

void CTrmEncSetgenDouble::Init()
{
    m_setgen_double->Reset();
    SetStateQuery();
}

void CTrmEncSetgenDouble::Query()
{
    ShowStatus();
    printf("\n%s\n", text(siHorisontalSeparator).c_str());
    printf("%s. %s:\n", text(siSetgenDoubleQuery).c_str(), text(siQueryNextStep).c_str());
    printf(" 0 - %s\n", text(siEncodeQueryAnew).c_str());
    printf(" 1 - %s\n", text(siSetgenQuerySetDesc).c_str());
    printf(" 2 - %s\n", text(siSetgenDoubleQueryAddFirst).c_str());
    printf(" 3 - %s\n", text(siSetgenDoubleQueryAddSecond).c_str());
    printf(" 4 - %s\n", text(siSetgenDoubleQueryDelFirst).c_str());
    printf(" 5 - %s\n", text(siSetgenDoubleQueryDelSecond).c_str());
    printf(" 9 - %s\n", text(siDone).c_str());
    printf("10 - %s\n", text(siAbort).c_str());
    int opt;
    InputInt(opt);
    switch (opt)
    {
    case 0:		SetStateInit();         break;
    case 1:		SetStateSetDesc();      break;
    case 2:		SetStateAddVarFirst();	break;
    case 3:		SetStateAddVarSecond();	break;
    case 4:		SetStateDelVarFirst();	break;
    case 5:		SetStateDelVarSecond();	break;
    case 9:		Done();                 break;
    case 10:	SetStateAbort();        break;
    default:	SetStateQuery();        break;
    }
}

void CTrmEncSetgenDouble::Done()
{
    const auto res = m_setgen_double->Valid(enPurpose::pEncode);
    if (res.OK())
    {
        ShowFirst();
        ShowSecond();
        SetStateEnd();
    }
    else
    {
        printf("%s\n", CTextResult(res).Text().c_str());
        SetStateQuery();
    }
}

void CTrmEncSetgenDouble::AddFirst()
{
    printf("\n%s:\n", text(siSetgenDoubleQueryAddFirst).c_str());
    std::string str;
    InputStr(str);
    auto res = m_setgen_double->AddVariant(str, CSetgenDouble::enVariantsBank::vbFirst);
    if (res.ERROR())
        printf("%s: %s\n", text(siSetgenAddError).c_str(), CTextResult(res).Text().c_str());
    SetStateQuery();
}

void CTrmEncSetgenDouble::AddSecond()
{
    printf("\n%s:\n", text(siSetgenDoubleQueryAddSecond).c_str());
    std::string str;
    InputStr(str);
    auto res = m_setgen_double->AddVariant(str, CSetgenDouble::enVariantsBank::vbSecond);
    if (res.ERROR())
        printf("%s: %s\n", text(siSetgenAddError).c_str(), CTextResult(res).Text().c_str());
    SetStateQuery();
}

void CTrmEncSetgenDouble::DelFirst()
{
    ShowFirst();
    printf("\n%s:\n", text(siSetgenDoubleQueryDelFirst).c_str());
    int var_id;
    InputInt(var_id);
    auto res = m_setgen_double->DelVariant(static_cast<uint>(var_id - 1), CSetgenDouble::enVariantsBank::vbFirst);
    if (res.ERROR())
        printf("%s\n", CTextResult(res).Text().c_str());
    SetStateQuery();
}

void CTrmEncSetgenDouble::DelSecond()
{
    ShowSecond();
    printf("\n%s:\n", text(siSetgenDoubleQueryDelSecond).c_str());
    int var_id;
    InputInt(var_id);
    auto res = m_setgen_double->DelVariant(static_cast<uint>(var_id - 1), CSetgenDouble::enVariantsBank::vbSecond);
    if (res.ERROR())
        printf("%s\n", CTextResult(res).Text().c_str());
    SetStateQuery();
}

void CTrmEncSetgenDouble::SetDesc()
{
    printf("\n%s:\n", text(siSetgenQuerySetDesc).c_str());
    std::string str;
    InputStr(str);
    m_setgen_double->SetDescription(str);
    SetStateQuery();
}

void CTrmEncSetgenDouble::Abort()
{
    m_setgen_double->Reset();
    SetStateEnd();
}

void CTrmEncSetgenDouble::Show()
{
    ShowDescription();
    ShowFirst();
    ShowSecond();
}

void CTrmEncSetgenDouble::ShowDescription() const
{
    printf("\n%s\n", text(siHorisontalSeparator).c_str());
    if (m_setgen_double->GetDescription().empty())
        printf("%s\n", text(siNoDescription).c_str());
    else
        printf("%s\n", m_setgen_double->GetDescription().c_str());
}

void CTrmEncSetgenDouble::ShowFirst() const
{
    printf("%s\n", text(siHorisontalSeparator).c_str());
    uint i = 1;
    for (const auto &var : m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbFirst))
    {
        printf("  %u. %s\n", i, var.c_str());
        i++;
    }
}

void CTrmEncSetgenDouble::ShowSecond() const
{
    printf("%s\n", text(siHorisontalSeparator).c_str());
    uint i = 1;
    for (const auto &var : m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbSecond))
    {
        printf("  %u. %s\n", i, var.c_str());
        i++;
    }
}

ISetgenPtr CTrmEncSetgenDouble::GetSetgen()
{
    return m_setgen_double;
}

void CTrmEncSetgenDouble::ShowStatus() const
{
    printf("\n%s\n", text(siHorisontalSeparator).c_str());
    if (not m_setgen_double)
    {
        printf("%s\n", text(siSetgenNotValid).c_str());
        return;
    }
    if (m_setgen_double->Valid(enPurpose::pEncode).ERROR())
    {
        printf("%s\n", text(siSetgenNotValid).c_str());
    }
    ShowDescription();

    printf("%s: 1 %s %zu; 2 %s %zu; %s %lu;\n",
           text(siVariantsCount).c_str(),
           text(siBank).c_str(), m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbFirst).size(),
           text(siBank).c_str(), m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbSecond).size(),
           text(siTotal).c_str(), m_setgen_double->VariantsCount());
}

Result_t CTrmEncSetgenDouble::Valid() const
{
    Result_t res;
    if (m_setgen_double)
        res = m_setgen_double->Valid(enPurpose::pEncode);
    else
        res = Result_t(RES_ERROR);
    return res;
}

std::string CTrmEncSetgenDouble::SampleHint() const
{
    char s[64];
    snprintf(s, sizeof(s), "%s 1..%zu:1..%zu",
             text(siSetgenDoubleSampleHint).c_str(),
             m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbFirst).size(),
             m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbSecond).size());
    return s;
}

Result_t CTrmEncSetgenDouble::ParseSample(const std::string &str, uint64 &value) const
{
    std::pair<uint64, uint64> vl;
    auto res = CTrmIO_SetgenDouble::ParseSample(str, vl);
    if (res.OK())
        value = vl.first+m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbFirst).size()*vl.second;
    return res;
}
