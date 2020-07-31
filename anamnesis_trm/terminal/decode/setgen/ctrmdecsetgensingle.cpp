#include "ctrmdecsetgensingle.h"

using namespace TRM_TXT_RES;

CTrmDecSetgenSingleStateMashine::CTrmDecSetgenSingleStateMashine(ITrmDecSetgenSingleHandler* callback)
    : m_callback(callback)
{

}

CTrmDecSetgenSingle::CTrmDecSetgenSingle(ISetgenPtr setgen)
    : CTrmDecSetgenSingleStateMashine(this)
    , m_setgen(setgen)
{
    m_setgen_single = static_cast<CSetgenSingle*>(m_setgen.get());
}

ISetgenPtr CTrmDecSetgenSingle::GetSetgen()
{
    return m_setgen;
}

Result_t CTrmDecSetgenSingle::Valid() const
{
    return (m_setgen) ? m_setgen->Valid(enPurpose::pDecode) : Result_t(RES_ERROR);
}

std::string CTrmDecSetgenSingle::SampleHint() const
{
    char s[64];
    snprintf(s, sizeof(s), "%s 1..%zu",
             text(siSetgenSingleSampleHint).c_str(), m_setgen_single->GetVariants().size());
    return s;
}

void CTrmDecSetgenSingle::Start()
{
    SetStateInit();
}

void CTrmDecSetgenSingle::Init()
{
    SetStateQuery();
}

void CTrmDecSetgenSingle::Query()
{
    SetStateConfirm();
    printf("%s\n\n", m_setgen_single->GetDescription().c_str());
    uint cntr = 0;
    for (auto &variant : m_setgen_single->GetVariants())
    {
        cntr++;
        printf("%3u - %s\n", cntr, variant.c_str());
    }
}

void CTrmDecSetgenSingle::Confirm()
{
    SetStateEnd();
}

Result_t CTrmDecSetgenSingle::ParseSample(const std::string &str, uint64 &value) const
{
    return CTrmIO_SetgenSingle::ParseSample(str, value);
}
