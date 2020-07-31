#include "ctrmencsetgen.h"
#include "ctrmencsetgensingle.h"
#include "ctrmencsetgendouble.h"

using namespace TRM_TXT_RES;

void CTrmEncSetgen::Begin()
{
    DEBUG_LOG("%s", __FUNCTION__);
    printf("%s:\n 1 - %s\n 2 - %s\n 9 - %s\n",
           text(siSetgenChoose).c_str(), text(siSetgenSingle).c_str(), text(siSetgenDouble).c_str(), text(siCancel).c_str());
    int opt;
    InputInt(opt);
    switch (opt)
    {
    case 1:
    {
        CTrmEncSetgenSinglePtr setg_sing(new CTrmEncSetgenSingle());
        setg_sing->Begin();
        const auto res = setg_sing->GetSetgen()->Valid(enPurpose::pEncode);
        if (res.ERROR())
        {
            printf("%s: %s\n", text(siEncodeAddError).c_str(), CTextResult(res).Text().c_str());
            break;
        }
        m_trm_setgen = setg_sing;
        break;
    }
    case 2:
    {
        CTrmEncSetgenDoublePtr setg_dbl(new CTrmEncSetgenDouble());
        setg_dbl->Begin();
        const auto res = setg_dbl->GetSetgen()->Valid(enPurpose::pEncode);
        if (res.ERROR())
        {
            printf("%s: %s\n", text(siEncodeAddError).c_str(), CTextResult(res).Text().c_str());
            break;
        }
        m_trm_setgen = setg_dbl;
        break;
    }
    case 9:		m_trm_setgen = nullptr;		break;
    default:	m_trm_setgen = nullptr;     break;
    }
}

Result_t CTrmEncSetgen::ParseSample(const std::string &str, uint64 &value) const
{
    DEBUG_LOG("%s", __FUNCTION__);
    return (m_trm_setgen) ? m_trm_setgen->ParseSample(str, value) : Result_t(RES_NO_SETGEN);
}

ISetgenPtr CTrmEncSetgen::GetSetgen()
{
    DEBUG_LOG("%s", __FUNCTION__);
    return (m_trm_setgen) ? m_trm_setgen->GetSetgen() : nullptr;
}

Result_t CTrmEncSetgen::Valid() const
{
    DEBUG_LOG("%s", __FUNCTION__);
    Result_t res;
    if (m_trm_setgen)
        res = m_trm_setgen->GetSetgen()->Valid(enPurpose::pEncode);
    else
        res = Result_t(RES_NO_SETGEN);
    return res;
}

std::string CTrmEncSetgen::SampleHint() const
{
    DEBUG_LOG("%s", __FUNCTION__);
    return (m_trm_setgen) ? m_trm_setgen->SampleHint() : "NO SET GENERATOR";
}
