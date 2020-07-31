#include "ctrmdecsetgen.h"

CTrmDecSetgen::CTrmDecSetgen(ISetgenPtr setgen)
    : m_setgen(setgen)
{

}

void CTrmDecSetgen::Begin()
{
    switch (m_setgen->GetType())
    {
    case enSetgenType::stNone:
    {
        m_trm_setgen = nullptr;
        break;
    }
    case enSetgenType::stSingle:
    {
        auto setgen_single = new CTrmDecSetgenSingle(m_setgen);
        setgen_single->Begin();
        if (setgen_single->Valid().OK())
            m_trm_setgen = ITrmDecSetgenPtr(setgen_single);
        break;
    }
    case enSetgenType::stDouble:
    {
        auto setgen_double = new CTrmDecSetgenDouble(m_setgen);
        setgen_double->Begin();
        if (setgen_double->Valid().OK())
            m_trm_setgen = ITrmDecSetgenPtr(setgen_double);
        break;
    }
    }
}

ISetgenPtr CTrmDecSetgen::GetSetgen()
{
    return (m_trm_setgen ? m_trm_setgen->GetSetgen() : nullptr);
}

Result_t CTrmDecSetgen::Valid() const
{
    return ((m_trm_setgen) and (m_setgen)) ? m_setgen->Valid(enPurpose::pDecode) : Result_t(RES_ERROR);
}

Result_t CTrmDecSetgen::ParseSample(const std::string &str, uint64 &value) const
{
    return (m_trm_setgen) ? m_trm_setgen->ParseSample(str, value) : Result_t(RES_NO_SETGEN);
}

std::string CTrmDecSetgen::SampleHint() const
{
    return (m_trm_setgen) ? m_trm_setgen->SampleHint() : "NO SET GENERATOR";
}
