#include "csetgendouble.h"

void CSetgenDouble::Reset()
{
    m_variants_first.clear();
    m_variants_second.clear();
}

Result_t CSetgenDouble::Valid(const enPurpose purpose) const
{
    Result_t res;
    if ((purpose == enPurpose::pEncode) and (m_description.empty()))
        res.AddResult(RES_NO_DESCRIPTION);
    if (m_variants_first.empty())
        res.AddResult(RES_NO_VARIANTS_IN_BANK, 1);
    if (m_variants_second.empty())
        res.AddResult(RES_NO_VARIANTS_IN_BANK, 2);
    if (not UniqVariants(m_variants_first))
        res.AddResult(RES_NOT_UNIQUE_VARIANTS_IN_BANK, 1);
    if (not UniqVariants(m_variants_second))
        res.AddResult(RES_NOT_UNIQUE_VARIANTS_IN_BANK, 2);
    return res;
}

bool CSetgenDouble::UniqVariants(const std::list<std::string> &vars) const
{
    auto var_uniq = vars;
    var_uniq.sort();
    var_uniq.unique();
    return (vars.size() == var_uniq.size());
}

uint64 CSetgenDouble::VariantsCount() const
{
    return (m_variants_first.size()*m_variants_second.size());
}

std::string CSetgenDouble::GetDescription() const
{
    return m_description;
}

enSetgenType CSetgenDouble::GetType() const
{
    return enSetgenType::stDouble;
}

rapidjson::Document CSetgenDouble::toJSON() const
{
    rapidjson::Value json_val;
    rapidjson::Document doc;
    auto& allocator = doc.GetAllocator();

    doc.SetObject();

    json_val.SetString(JSON_SETGEN_DOUBLE, allocator);
    doc.AddMember(JSON_SETGEN_TYPE, json_val, allocator);

    json_val.SetString(m_description, allocator);
    doc.AddMember(JSON_SETGEN_DESCRIPTION, json_val, allocator);

    json_val.CopyFrom(toJSON_variants_first(), allocator);
    doc.AddMember(JSON_SETGEN_VARIANTS_FIRST, json_val, allocator);

    json_val.CopyFrom(toJSON_variants_second(), allocator);
    doc.AddMember(JSON_SETGEN_VARIANTS_SECOND, json_val, allocator);

    return doc;
}

bool CSetgenDouble::fromJSON(const rapidjson::Value& doc)
{
    if (not doc.IsObject())
        return false;

    if (not doc.HasMember(JSON_SETGEN_DESCRIPTION)) return false;
    m_description = doc[JSON_SETGEN_DESCRIPTION].GetString();

    if (not doc.HasMember(JSON_SETGEN_VARIANTS_FIRST)) return false;
    if (not fromJSON_variants_first(doc[JSON_SETGEN_VARIANTS_FIRST]))
        return false;

    if (not doc.HasMember(JSON_SETGEN_VARIANTS_SECOND)) return false;
    if (not fromJSON_variants_second(doc[JSON_SETGEN_VARIANTS_SECOND]))
        return false;

    return true;
}

rapidjson::Document CSetgenDouble::toJSON_variants_first() const
{
    rapidjson::Document doc;
    rapidjson::Value json_val;
    auto& allocator = doc.GetAllocator();
    doc.SetArray();
    for (const auto &v : m_variants_first)
    {
        json_val.SetString(v.c_str(), allocator);
        doc.PushBack(json_val, allocator);
    }
    return doc;
}

rapidjson::Document CSetgenDouble::toJSON_variants_second() const
{
    rapidjson::Document doc;
    rapidjson::Value json_val;
    auto& allocator = doc.GetAllocator();
    doc.SetArray();
    for (const auto &v : m_variants_second)
    {
        json_val.SetString(v.c_str(), allocator);
        doc.PushBack(json_val, allocator);
    }
    return doc;
}

bool CSetgenDouble::fromJSON_variants_first(const rapidjson::Value& doc)
{
    if (not doc.IsArray())
        return false;

    m_variants_first.clear();
    for (uint i = 0; i < doc.Size(); ++i)
        m_variants_first.push_back(doc[i].GetString());

    return true;
}

bool CSetgenDouble::fromJSON_variants_second(const rapidjson::Value& doc)
{
    if (not doc.IsArray())
        return false;

    m_variants_second.clear();
    for (uint i = 0; i < doc.Size(); ++i)
        m_variants_second.push_back(doc[i].GetString());

    return true;
}

void CSetgenDouble::SetVariants(const std::list<std::string> &variants, const enVariantsBank bank)
{
    switch (bank)
    {
    case enVariantsBank::vbFirst:   m_variants_first = variants;    break;
    case enVariantsBank::vbSecond:  m_variants_second = variants;   break;
    }
}

void CSetgenDouble::SetDescription(const std::string &desc)
{
    m_description = desc;
}

Result_t CSetgenDouble::AddVariant(const std::string &variant, const enVariantsBank bank)
{
    std::list<std::string>* variants = nullptr;
    switch (bank)
    {
    case enVariantsBank::vbFirst:   variants = &m_variants_first;   break;
    case enVariantsBank::vbSecond:  variants = &m_variants_second;  break;
    }
    if (std::find(variants->begin(), variants->end(), variant) != variants->end())
        return Result_t(RES_VAR_IN_LIST);
    variants->push_back(variant);
    return Result_t();
}

Result_t CSetgenDouble::DelVariant(const uint var_id, const enVariantsBank bank)
{
    std::list<std::string> &variants = (bank == enVariantsBank::vbFirst) ? m_variants_first : m_variants_second;
    if (var_id >= variants.size())
        return Result_t(RES_INCORRECT_INDEX);
    auto v_it = variants.begin();
    std::advance(v_it, var_id);
    variants.erase(v_it);
    return Result_t(RES_OK);
}

std::list<std::string> CSetgenDouble::GetVariants(const enVariantsBank bank)
{
    switch (bank)
    {
    case enVariantsBank::vbFirst:   return m_variants_first;
    case enVariantsBank::vbSecond:  return m_variants_second;
    }
    return m_variants_first;
}

bool CSetgenDouble::operator==(const CSetgenDouble& rhs) const
{
    bool first_equal = (m_variants_first == rhs.m_variants_first);
    bool second_equal = (m_variants_second == rhs.m_variants_second);
    return (first_equal and second_equal);
}
