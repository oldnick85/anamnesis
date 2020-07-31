#include "ccasket.h"
#include "../common/version.h"

#include <iostream>
#include <fstream>

void CCasket::SetPass(const CPassPtr pass)
{
    debug_log("%s pass=%s\n", __PRETTY_FUNCTION__, pass->GetPasswordString().c_str());
    m_pass = pass;
}

CPassPtr CCasket::GetPass()
{
    debug_log("%s pass=%s\n", __PRETTY_FUNCTION__, m_pass->GetPasswordString().c_str());
    return m_pass;
}

void CCasket::SetSetcombs(const std::list<CSetCombPtr> &setcombs)
{
    m_setcombs = setcombs;
}

std::list<CSetCombPtr>& CCasket::GetSetcombs()
{
    return m_setcombs;
}

Result_t CCasket::SaveFileJSON(const std::string &fname)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    toJSON().Accept(writer);
    std::ofstream file(fname);
    if (not file.is_open()) return Result_t(RES_CAN_NOT_FILE_OPEN);
    file << buffer.GetString() << std::endl;
    file.close();
    return Result_t(RES_OK);
}

Result_t CCasket::LoadFileJSON(const std::string &fname)
{
    std::ifstream file(fname);
    if (not file.is_open()) return Result_t(RES_CAN_NOT_FILE_OPEN);
    std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    rapidjson::Document doc;
    doc.Parse(content);
    if (not fromJSON(doc)) return Result_t(RES_UNKNOWN_FILE_FORMAT);
    if (Valid(enPurpose::pDecode).ERROR()) return Result_t(RES_INAPPROPRIATE_FILE_CONTENT);
    return Result_t(RES_OK);
}

rapidjson::Document CCasket::toJSON() const
{
    rapidjson::Value json_val;
    rapidjson::Document doc;
    auto& allocator = doc.GetAllocator();

    doc.SetObject();

    CVersion version;
    json_val.SetString(version.Print(), allocator);
    doc.AddMember(JSON_VERSION, json_val, allocator);

    json_val.CopyFrom(toJSON_pass(), allocator);
    doc.AddMember(JSON_CASKET_PASS, json_val, allocator);

    json_val.CopyFrom(toJSON_setcombs(), allocator);
    doc.AddMember(JSON_CASKET_SETCOMB, json_val, allocator);

    json_val.SetString(m_keyhole.PrintHex(), allocator);
    doc.AddMember(JSON_CASKET_KEYHOLE, json_val, allocator);

    return doc;
}

rapidjson::Document CCasket::toJSON_pass() const
{
    return m_pass->toJSON();
}

rapidjson::Document CCasket::toJSON_setcombs() const
{
    rapidjson::Document doc;
    rapidjson::Value json_val;
    auto& allocator = doc.GetAllocator();
    doc.SetArray();
    for (const auto &sc : m_setcombs)
    {
        auto setcomb_json = sc->toJSON();
#ifdef DEBUG_ON
        {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            setcomb_json.Accept(writer);
            printf("DEBUG: SETCOMB_JSON = %s\n", buffer.GetString());
        }
#endif
        json_val.CopyFrom(setcomb_json, allocator);
        doc.PushBack(json_val, allocator);
    }
    return doc;
}

bool CCasket::fromJSON(const rapidjson::Value& doc)
{
    if (not doc.IsObject())
        return false;
    if (not doc.HasMember(JSON_CASKET_PASS))
        return false;
    m_pass = CPassPtr(new CPass());
    if (not m_pass->fromJSON(doc[JSON_CASKET_PASS]))
    {
        m_pass = nullptr;
        return false;
    }
    if (not doc.HasMember(JSON_CASKET_SETCOMB))
        return false;
    if (not fromJSON_setcombs(doc[JSON_CASKET_SETCOMB]))
        return false;
    if (not doc.HasMember(JSON_CASKET_KEYHOLE))
        return false;
    std::string str_keyhole = doc[JSON_CASKET_KEYHOLE].GetString();
    m_keyhole.FromString(str_keyhole, 16);
    return true;
}

bool CCasket::fromJSON_setcombs(const rapidjson::Value& doc)
{
    if (not doc.IsArray())
        return false;
    m_setcombs.clear();
    for (uint i = 0; i < doc.Size(); ++i)
    {
        CSetCombPtr sc = CSetCombPtr(new CSetComb());
        if (not sc->fromJSON(doc[i]))
        {
            m_setcombs.clear();
            return false;
        }
        m_setcombs.push_back(sc);
    }

    return true;
}

Result_t CCasket::Valid(const enPurpose purpose) const
{
    Result_t res;
    if (m_pass)
        res.AddResult(m_pass->Valid(purpose));
    else
        res.AddResult(RES_NO_PASSWORD);

    if (not m_setcombs.empty())
    {
        for (const auto &sc : m_setcombs)
        {
            if ((not sc) or (sc->Valid(purpose).ERROR()))
            {
                res.AddResult(RES_ERROR);
                break;
            }
        }
    }
    else
    {
        res.AddResult(RES_NO_SETCOMB);
    }
    return res;
}

CNumber CCasket::VariantsCount() const
{
    if (Valid(enPurpose::pDecode).ERROR()) return 0;
    CNumber variants(1);
    for (const auto &setcomb : m_setcombs)
        variants *= setcomb->GetCombine()->VariantsCount();
    return variants;
}

Result_t CCasket::KeyholeFromPass()
{
    auto res = Valid(enPurpose::pEncode);
    if (res.ERROR())
        return res;

    auto quest_value = QuestionsValue();
    auto pass_size_key = quest_value % MAX_PASSWORD_LENGTH;
    quest_value /= MAX_PASSWORD_LENGTH;
    CNumber pass_key = GenerateKey(quest_value);

    CNumber pass_size = m_pass->GetPassword().size();
    CNumber pass_value = m_pass->Value();

    m_keyhole = (pass_value ^ pass_key)* MAX_PASSWORD_LENGTH + (pass_size ^ pass_size_key);
    debug_log("%s keyhole=0x%s; pass_value=0x%s; key=0x%s;\n",
              __PRETTY_FUNCTION__, m_keyhole.PrintHex().c_str(),
              pass_value.PrintHex().c_str(), key.PrintHex().c_str());

    return Result_t(RES_OK);
}

Result_t CCasket::PassFromKeyhole()
{
    auto res = Valid(enPurpose::pDecode);
    if (res.ERROR())
        return res;

    auto pass_size_keyhole = m_keyhole % MAX_PASSWORD_LENGTH;
    auto pass_keyhole = m_keyhole/MAX_PASSWORD_LENGTH;

    auto quest_value = QuestionsValue();
    auto pass_size_key = quest_value % MAX_PASSWORD_LENGTH;
    quest_value /= MAX_PASSWORD_LENGTH;

    CNumber pass_size = pass_size_keyhole ^ pass_size_key;
    m_pass->SetPasswordLength(static_cast<uint>(pass_size.ToUint64()));

    CNumber pass_key = GenerateKey(quest_value);
    CNumber pass_value = pass_keyhole ^ pass_key;
    debug_log("%s pass_value=0x%s; keyhole=0x%s; key=0x%s;\n",
              __PRETTY_FUNCTION__, pass_value.PrintHex().c_str(),
              m_keyhole.PrintHex().c_str(), key.PrintHex().c_str());
    m_pass->SetValue(pass_value);

    return Result_t(RES_OK);
}

CNumber CCasket::QuestionsValue()
{
    CDigitNumber quest_digits;
    for (const auto &setcomb : m_setcombs)
    {
        CDigitNumber::sDigit d;
        d.base = setcomb->GetCombine()->VariantsCount();
        d.num = setcomb->GetCombine()->Value();
        quest_digits.AddDigit(d);
    }
    CNumber quest_value = quest_digits.GetNumber();
    return quest_value;
}

CNumber CCasket::GenerateKey(CNumber quest_value)
{
    CNumber pass_variants = m_pass->VariantsCount();
    std::pair<CNumber, CNumber> div;
    CNumber key = 0;
    do{
        div = quest_value.Divide(pass_variants);
        key ^= div.second;
        quest_value = div.first;
    }
    while (quest_value != 0);

    debug_log("%s key=0x%s;\n", __PRETTY_FUNCTION__, key.PrintHex().c_str());

    return key;
}
