#include "ctrmencsetgensingle.h"

using namespace TRM_TXT_RES;

CTrmEncSetgenSingleStateMashine::CTrmEncSetgenSingleStateMashine(ITrmEncSetgenSingleHandler* callback)
    : m_callback(callback)
{
    DEBUG_LOG("%s", __FUNCTION__);
}

CTrmEncSetgenSingle::CTrmEncSetgenSingle()
    : CTrmEncSetgenSingleStateMashine(this)
{
    DEBUG_LOG("%s", __FUNCTION__);
    m_setgen_single = CSetgenSinglePtr(new CSetgenSingle());
}

CTrmEncSetgenSingle::CTrmEncSetgenSingle(CSetgenSinglePtr setgen_single)
    : CTrmEncSetgenSingleStateMashine(this)
    , m_setgen_single(setgen_single)
{
    DEBUG_LOG("%s", __FUNCTION__);
}

void CTrmEncSetgenSingle::Start()
{
    DEBUG_LOG("%s", __FUNCTION__);
    SetStateInit();
}

void CTrmEncSetgenSingle::Init()
{
    DEBUG_LOG("%s", __FUNCTION__);
    m_setgen_single->Reset();
    SetStateQuery();
}

void CTrmEncSetgenSingle::Query()
{
    DEBUG_LOG("%s", __FUNCTION__);
    ShowStatus();
    printf("\n%s\n", text(siHorisontalSeparator).c_str());
    printf("%s. %s:\n", text(siSetgenSingleQuery).c_str(), text(siQueryNextStep).c_str());
    printf(" 0 - %s\n", text(siEncodeQueryAnew).c_str());
    printf(" 1 - %s\n", text(siSetgenSingleQueryAdd).c_str());
    printf(" 2 - %s\n", text(siSetgenSingleQueryDel).c_str());
    printf(" 3 - %s\n", text(siSetgenQuerySetDesc).c_str());
    printf(" 4 - %s\n", text(siSetgenShow).c_str());
    printf(" 9 - %s\n", text(siDone).c_str());
    printf("10 - %s\n", text(siAbort).c_str());
    int opt;
    InputInt(opt);
    switch (opt)
    {
    case 0:		SetStateInit();		break;
    case 1:		SetStateAddVar();	break;
    case 2:		SetStateDelVar();	break;
    case 3:		SetStateSetDesc();	break;
    case 4:		SetStateShow();     break;
    case 9:		Done();             break;
    case 10:	SetStateAbort();	break;
    default:	SetStateQuery();	break;
    }
}

void CTrmEncSetgenSingle::Done()
{
    const auto res = m_setgen_single->Valid(enPurpose::pEncode);
    if (res.OK())
    {
        ShowVariants();
        SetStateEnd();
    }
    else
    {
        printf("%s\n", CTextResult(res).Text().c_str());
        SetStateQuery();
    }
}

void CTrmEncSetgenSingle::Add()
{
    DEBUG_LOG("%s", __FUNCTION__);
    printf("\n%s:\n", text(siSetgenSingleQueryAdd).c_str());
    std::string str;
    InputStr(str);
    auto res = m_setgen_single->AddVariant(str);
    if (res.ERROR())
        printf("%s: %s\n", text(siSetgenAddError).c_str(), CTextResult(res).Text().c_str());
    SetStateQuery();
}

void CTrmEncSetgenSingle::Del()
{
    DEBUG_LOG("%s", __FUNCTION__);
    ShowVariants();
    int var_id;
    InputInt(var_id);
    m_setgen_single->DelVariant(static_cast<uint>(var_id - 1));
    SetStateQuery();
}

void CTrmEncSetgenSingle::Show()
{
    DEBUG_LOG("%s", __FUNCTION__);
    ShowDescription();
    ShowVariants();
    SetStateQuery();
}

void CTrmEncSetgenSingle::SetDesc()
{
    DEBUG_LOG("%s", __FUNCTION__);
    printf("\n%s:\n", text(siSetgenQuerySetDesc).c_str());
    std::string str;
    InputStr(str);
    m_setgen_single->SetDescription(str);
    SetStateQuery();
}

void CTrmEncSetgenSingle::Abort()
{
    DEBUG_LOG("%s", __FUNCTION__);
    m_setgen_single->Reset();
    SetStateEnd();
}

ISetgenPtr CTrmEncSetgenSingle::GetSetgen()
{
    DEBUG_LOG("%s", __FUNCTION__);
    return m_setgen_single;
}

void CTrmEncSetgenSingle::ShowDescription() const
{
    printf("\n%s\n", text(siHorisontalSeparator).c_str());
    printf("%s\n", m_setgen_single->GetDescription().c_str());
}

void CTrmEncSetgenSingle::ShowVariants() const
{
    printf("%s\n", text(siHorisontalSeparator).c_str());
    uint i = 1;
    for (const auto &var : m_setgen_single->GetVariants())
    {
        printf("  %u. %s\n", i, var.c_str());
        i++;
    }
}

void CTrmEncSetgenSingle::ShowStatus() const
{
    printf("\n%s\n", text(siHorisontalSeparator).c_str());
    if (not m_setgen_single)
    {
        printf("%s\n", text(siSetgenNotValid).c_str());
        return;
    }
    if (m_setgen_single->Valid(enPurpose::pEncode).ERROR())
    {
        printf("%s\n", text(siSetgenNotValid).c_str());
    }
    if (m_setgen_single->GetDescription().empty())
        printf("%s\n", text(siNoDescription).c_str());
    else
        printf("%s\n", m_setgen_single->GetDescription().c_str());

    printf("%s: %lu\n", text(siVariantsCount).c_str(), m_setgen_single->VariantsCount());
}

Result_t CTrmEncSetgenSingle::Valid() const
{
    DEBUG_LOG("%s", __FUNCTION__);
    Result_t res;
    if (m_setgen_single)
        res = m_setgen_single->Valid(enPurpose::pEncode);
    else
        res = Result_t(RES_ERROR);
    return res;
}

std::string CTrmEncSetgenSingle::SampleHint() const
{
    char s[64];
    snprintf(s, sizeof(s), "%s 1..%zu",
             text(siSetgenSingleSampleHint).c_str(), m_setgen_single->GetVariants().size());
    return s;
}

Result_t CTrmEncSetgenSingle::ParseSample(const std::string &str, uint64 &value) const
{
    DEBUG_LOG("%s", __FUNCTION__);
    return CTrmIO_SetgenSingle::ParseSample(str, value);
}
