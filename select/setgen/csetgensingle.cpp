#include <algorithm>
#include "csetgensingle.h"

void CSetgenSingle::SetVariants(const std::list<std::string> &variants)
{
    m_variants = variants;
}

void CSetgenSingle::SetDescription(const std::string &desc)
{
    m_description = desc;
}

Result_t CSetgenSingle::AddVariant(const std::string &variant)
{
    if (std::find(m_variants.begin(), m_variants.end(), variant) != m_variants.end())
        return Result_t(RES_VAR_IN_LIST);
    m_variants.push_back(variant);
    return Result_t();
}

Result_t CSetgenSingle::DelVariant(const uint var_id)
{
    if (var_id >= m_variants.size())
        return Result_t(RES_INCORRECT_INDEX);
    auto v_it = m_variants.begin();
    std::advance(v_it, var_id);
    m_variants.erase(v_it);
    return Result_t(RES_OK);
}

std::list<std::string> CSetgenSingle::GetVariants()
{
    return m_variants;
}

void CSetgenSingle::Reset()
{
    m_variants.clear();
}

Result_t CSetgenSingle::Valid(const enPurpose purpose) const
{
    Result_t res;
    if ((purpose == enPurpose::pEncode) and (m_description.empty()))
        res.AddResult(RES_NO_DESCRIPTION);
    if (m_variants.size() == 0)
        res.AddResult(RES_NO_VARIANTS);

    if (not UniqVariants(m_variants))
        res.AddResult(RES_NOT_UNIQUE_VARIANTS);
    return res;
}

bool CSetgenSingle::UniqVariants(const std::list<std::string> &vars) const
{
    auto var_uniq = vars;
    var_uniq.sort();
    var_uniq.unique();
    return (vars.size() == var_uniq.size());
}

uint64 CSetgenSingle::VariantsCount() const
{
    return m_variants.size();
}

std::string CSetgenSingle::GetDescription() const
{
    return m_description;
}

enSetgenType CSetgenSingle::GetType() const
{
    return enSetgenType::stSingle;
}

rapidjson::Document CSetgenSingle::toJSON() const
{
    rapidjson::Value json_val;
    rapidjson::Document doc;
    auto& allocator = doc.GetAllocator();

    doc.SetObject();

    json_val.SetString(JSON_SETGEN_SINGLE, allocator);
    doc.AddMember(JSON_SETGEN_TYPE, json_val, allocator);

    json_val.SetString(m_description, allocator);
    doc.AddMember(JSON_SETGEN_DESCRIPTION, json_val, allocator);

    json_val.CopyFrom(toJSON_variants(), allocator);
    doc.AddMember(JSON_SETGEN_VARIANTS, json_val, allocator);

    return doc;
}

rapidjson::Document CSetgenSingle::toJSON_variants() const
{
    rapidjson::Document doc;
    rapidjson::Value json_val;
    auto& allocator = doc.GetAllocator();
    doc.SetArray();
    for (const auto &v : m_variants)
    {
        json_val.SetString(v.c_str(), allocator);
        doc.PushBack(json_val, allocator);
    }
    return doc;
}

bool CSetgenSingle::fromJSON(const rapidjson::Value& doc)
{
    if (not doc.IsObject())
        return false;

    if (not doc.HasMember(JSON_SETGEN_DESCRIPTION)) return false;
    m_description = doc[JSON_SETGEN_DESCRIPTION].GetString();

    if (not doc.HasMember(JSON_SETGEN_VARIANTS)) return false;
    if (not fromJSON_variants(doc[JSON_SETGEN_VARIANTS]))
        return false;

    return true;
}

bool CSetgenSingle::fromJSON_variants(const rapidjson::Value& doc)
{
    if (not doc.IsArray())
        return false;

    m_variants.clear();
    for (uint i = 0; i < doc.Size(); ++i)
        m_variants.push_back(doc[i].GetString());

    return true;
}

bool CSetgenSingle::operator==(const CSetgenSingle& rhs) const
{
    return (m_variants == rhs.m_variants);
}
