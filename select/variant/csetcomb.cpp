#include "csetcomb.h"

#include "../setgen/csetgensingle.h"
#include "../setgen/csetgendouble.h"
#include "../combine/ccombinepermutation.h"
#include "../combine/ccombinecombination.h"

rapidjson::Document CSetComb::toJSON() const
{
    rapidjson::Document doc;
    if (Valid(enPurpose::pEncode).OK())
    {
        rapidjson::Value json_val;
        auto& allocator = doc.GetAllocator();
        doc.SetObject();

        json_val.SetString(m_desc, allocator);
        doc.AddMember(JSON_SETCOMB_DESC, json_val, allocator);

        auto setgen_json = m_setgen->toJSON();
#ifdef DEBUG_ON
        {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            setgen_json.Accept(writer);
            printf("DEBUG: SETGEN_JSON = %s\n", buffer.GetString());
        }
#endif
        json_val.CopyFrom(setgen_json, allocator);
        doc.AddMember(JSON_SETCOMB_SETGEN, json_val, allocator);

        auto combine_json = m_combine->toJSON();
#ifdef DEBUG_ON
        {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            combine_json.Accept(writer);
            printf("DEBUG: COMBINE_JSON = %s\n", buffer.GetString());
        }
#endif
        json_val.CopyFrom(combine_json, allocator);
        doc.AddMember(JSON_SETCOMB_COMBINE, json_val, allocator);
    }
    return doc;
}

bool CSetComb::fromJSON(const rapidjson::Value& doc)
{
    if (not doc.IsObject())
        return false;

    if (not doc.HasMember(JSON_SETCOMB_DESC)) return false;
    m_desc = doc[JSON_SETCOMB_DESC].GetString();

    if (not doc.HasMember(JSON_SETCOMB_SETGEN)) return false;
    if (not doc[JSON_SETCOMB_SETGEN].HasMember(JSON_SETGEN_TYPE)) return false;
    if (doc[JSON_SETCOMB_SETGEN][JSON_SETGEN_TYPE] == JSON_SETGEN_SINGLE)
    {
        m_setgen = ISetgenPtr(new CSetgenSingle());
        if (not m_setgen->fromJSON(doc[JSON_SETCOMB_SETGEN])) return false;
    }
    else if (doc[JSON_SETCOMB_SETGEN][JSON_SETGEN_TYPE] == JSON_SETGEN_DOUBLE)
    {
        m_setgen = ISetgenPtr(new CSetgenDouble());
        if (not m_setgen->fromJSON(doc[JSON_SETCOMB_SETGEN])) return false;
    }
    else
    {
        return false;
    }

    if (not doc.HasMember(JSON_SETCOMB_COMBINE)) return false;
    if (not doc[JSON_SETCOMB_COMBINE].HasMember(JSON_COMBINE_TYPE)) return false;
    if (doc[JSON_SETCOMB_COMBINE][JSON_COMBINE_TYPE] == JSON_COMBINE_PERMUTATION)
    {
        m_combine = ICombinePtr(new CCombinePermutation());
        if (not m_combine->fromJSON(doc[JSON_SETCOMB_COMBINE])) return false;
    }
    else if (doc[JSON_SETCOMB_COMBINE][JSON_COMBINE_TYPE] == JSON_COMBINE_COMBINATION)
    {
        m_combine = ICombinePtr(new CCombineCombination());
        if (not m_combine->fromJSON(doc[JSON_SETCOMB_COMBINE])) return false;
    }
    else
    {
        return false;
    }

    return true;
}

Result_t CSetComb::Valid(const enPurpose purpose) const
{
    Result_t res;

    if (m_desc.empty())
        res.AddResult(RES_NO_DESCRIPTION);

    if (m_setgen)
        res.AddResult(m_setgen->Valid(purpose));
    else
        res.AddResult(RES_NO_SETGEN);

    if (m_combine)
        res.AddResult(m_combine->Valid(purpose));
    else
        res.AddResult(RES_NO_COMBINE);

    return res;
}
