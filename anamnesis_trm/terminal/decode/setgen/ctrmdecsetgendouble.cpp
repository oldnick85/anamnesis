#include "ctrmdecsetgendouble.h"

using namespace TRM_TXT_RES;

CTrmDecSetgenDoubleStateMashine::CTrmDecSetgenDoubleStateMashine(ITrmDecSetgenDoubleHandler* callback)
    : m_callback(callback)
{

}

CTrmDecSetgenDouble::CTrmDecSetgenDouble(ISetgenPtr setgen)
    : CTrmDecSetgenDoubleStateMashine(this)
    , m_setgen(setgen)
{
    m_setgen_double = static_cast<CSetgenDouble*>(m_setgen.get());
}

ISetgenPtr CTrmDecSetgenDouble::GetSetgen()
{
    return m_setgen;
}

Result_t CTrmDecSetgenDouble::Valid() const
{
    return (m_setgen) ? m_setgen->Valid(enPurpose::pDecode) : Result_t(RES_ERROR);
}

std::string CTrmDecSetgenDouble::SampleHint() const
{
    char s[64];
    snprintf(s, sizeof(s), "%s 1..%zu:1..%zu",
             text(siSetgenDoubleSampleHint).c_str(),
             m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbFirst).size(),
             m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbSecond).size());
    return s;
}

void CTrmDecSetgenDouble::Start()
{
    SetStateInit();
}

void CTrmDecSetgenDouble::Init()
{
    SetStateQuery();
}

void CTrmDecSetgenDouble::Query()
{
    SetStateConfirm();
    printf("%s\n\n", m_setgen_double->GetDescription().c_str());
    uint cntr = 0;
    for (auto &variant : m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbFirst))
    {
        cntr++;
        printf("%3u - %s\n", cntr, variant.c_str());
    }
    cntr = 0;
    for (const auto &variant : m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbSecond))
    {
        cntr++;
        printf("%3u - %s\n", cntr, variant.c_str());
    }
}

void CTrmDecSetgenDouble::Confirm()
{
    SetStateEnd();
}

Result_t CTrmDecSetgenDouble::ParseSample(const std::string &str, uint64 &value) const
{
    std::pair<uint64, uint64> vl;
    auto res = CTrmIO_SetgenDouble::ParseSample(str, vl);
    if (res.OK())
        value = vl.first*vl.second;
    return res;
}
