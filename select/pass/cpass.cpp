#include "cpass.h"

void CPass::Reset()
{
    m_symbols.clear();
    m_pass.clear();
}

Pass_t CPass::GetSymbols()
{
    return m_symbols;
}

void CPass::AddSymbols(const Pass_t &symbols)
{
    for(const auto v : symbols)
        if (std::find(m_symbols.begin(), m_symbols.end(), v) == m_symbols.end())
            m_symbols.push_back(v);
}

Result_t CPass::SetSymbols(const Pass_t &symbols)
{
    auto res = CheckPassSymbols(symbols, m_pass);
    if (res.ERROR())
        return res;

    m_symbols = symbols;
    return Result_t(RES_OK);
}

Result_t CPass::SetSymbols(const sSymbolClass &symbols_class)
{
    Pass_t symbols;

    if (symbols_class.lower_case)   AddStringToSymbols(symbols, m_symbols_lower_case);
    if (symbols_class.upper_case)   AddStringToSymbols(symbols, m_symbols_upper_case);
    if (symbols_class.digits)       AddStringToSymbols(symbols, m_symbols_digits);
    if (symbols_class.minus)        AddStringToSymbols(symbols, m_symbols_minus);
    if (symbols_class.underline)    AddStringToSymbols(symbols, m_symbols_underline);
    if (symbols_class.space)        AddStringToSymbols(symbols, m_symbols_space);
    if (symbols_class.special)      AddStringToSymbols(symbols, m_symbols_special);
    if (symbols_class.brackets)     AddStringToSymbols(symbols, m_symbols_brackets);

    auto res = CheckPassSymbols(symbols, m_pass);
    if (res.ERROR())
        return res;
    m_symbols = symbols;
    return Result_t(RES_OK);
}

void CPass::AddStringToSymbols(Pass_t &symbols, const std::string &chars)
{
    for (const char c : chars)
        symbols.push_back(static_cast<PassSymbol_t>(c));
}

Result_t CPass::SetPassword(const Pass_t &pass)
{
    auto res = CheckPassSymbols(m_symbols, pass);
    if (res.ERROR())
        return res;
    m_pass = pass;
    m_pass_len = m_pass.size();
    return Result_t(RES_OK);
}

Pass_t& CPass::GetPassword()
{
    return m_pass;
}

Result_t CPass::SetPassword(const std::string &pass_str)
{
    Pass_t pass;
    for (auto c : pass_str)
        pass.push_back(static_cast<PassSymbol_t>(c));
    return SetPassword(pass);
}

std::string CPass::GetPasswordString() const
{
    std::string str;
    for (auto v : m_pass)
        str.push_back(static_cast<char>(v));
    return str;
}

Result_t CPass::Valid(const enPurpose purpose) const
{
    Result_t res;
    if (m_symbols.empty())
        res.AddResult(RES_PASS_NO_SYMBOLS_SET);

    if (purpose == enPurpose::pEncode)
    {
        if ((m_pass_len == 0) or (m_pass.empty()))
            res.AddResult(RES_PASS_NO_PASSWORD);
    }
    return res;
}

Result_t CPass::CheckPassSymbols(const Pass_t &symbols, const Pass_t &pass) const
{
    for (const auto v : symbols)
        if (std::count(symbols.begin(), symbols.end(), v) != 1)
            return Result_t(RES_SYMB_DUPLICATE);
    for (const auto v : pass)
        if (std::find(symbols.begin(), symbols.end(), v) == symbols.end())
            return Result_t(RES_PASS_WRONG_SYMBOL);
    return Result_t(RES_OK);
}

rapidjson::Document CPass::toJSON() const
{
    rapidjson::Value json_val;
    rapidjson::Document doc;
    auto& allocator = doc.GetAllocator();

    doc.SetObject();

    json_val.CopyFrom(toJSON_symbols(), allocator);
    doc.AddMember(JSON_PASS_SYMBOLS, json_val, allocator);

    return doc;
}

rapidjson::Document CPass::toJSON_symbols() const
{
    rapidjson::Document doc;
    rapidjson::Value json_val;
    auto& allocator = doc.GetAllocator();
    doc.SetArray();
    for (const auto &v : m_symbols)
    {
        json_val.SetUint(v);
        doc.PushBack(json_val, allocator);
    }
    return doc;
}

bool CPass::fromJSON(const rapidjson::Value& doc)
{
    if (not doc.IsObject())
        return false;

    if (not doc.HasMember(JSON_PASS_SYMBOLS)) return false;
    if (not fromJSON_symbols(doc[JSON_PASS_SYMBOLS]))
    {
        Reset();
        return false;
    }

    return true;
}

bool CPass::fromJSON_symbols(const rapidjson::Value& doc)
{
    if (not doc.IsArray())
        return false;

    m_symbols.clear();
    for (uint i = 0; i < doc.Size(); ++i)
        m_symbols.push_back(static_cast<PassSymbol_t>(doc[i].GetUint()));

    return true;
}

CNumber CPass::VariantsCount() const
{
    if (Valid(enPurpose::pDecode).ERROR()) return 0;
    CNumber variants(1);
    for (size_t i = 0; i < m_pass_len; ++i)
    {
        variants *= m_symbols.size();
    }
    return variants;
}

CNumber CPass::Value() const
{
    CNumber val(0);
    for (const auto symb : m_pass)
    {
        val *= m_symbols.size();
        val += SymbolValue(symb);
    }
    debug_log("%s val=0x%s\n", __PRETTY_FUNCTION__, val.PrintHex().c_str());
    return val;
}

uint64 CPass::SymbolValue(const PassSymbol_t symb) const
{
    uint64 val = 0;
    for (PassSymbol_t s : m_symbols)
    {
        if (symb == s) return val;
        val++;
    }
    return val;
}

PassSymbol_t CPass::ValueSymbol(const uint64 vl) const
{
    if (vl >= m_symbols.size())
        return 0;
    return m_symbols[vl];
}

Result_t CPass::SetPasswordLength(const uint pass_len)
{
    if (pass_len > MAX_PASSWORD_LENGTH)
        return Result_t(RES_ERROR);
    m_pass_len = pass_len;
    return Result_t(RES_OK);
}

Result_t CPass::SetValue(const CNumber val)
{
    debug_log("%s val=0x%s\n", __PRETTY_FUNCTION__, val.PrintHex().c_str());
    m_pass.clear();

    CNumber residue = val;
    for (uint i = 0; i < m_pass_len; ++i)
    {
        CNumber v = residue % m_symbols.size();
        PassSymbol_t sv = ValueSymbol(v.ToUint64());
        m_pass.push_back(sv);
        debug_log("v=0x%s; sv=%c\n", v.PrintHex().c_str(), sv);
        residue /= m_symbols.size();
    }
    std::reverse(std::begin(m_pass), std::end(m_pass));
    return Result_t(RES_OK);
}

CPass::sSymbolClass CPass::SymbolsFromPassword(const std::string &pass_str)
{
    sSymbolClass sc;

    auto l = [](const std::string &str, const std::string &chars)
    {
        for (const char c : chars)
            if (str.find(c) != std::string::npos) return true;
        return false;
    };

    sc.lower_case   = l(pass_str, m_symbols_lower_case);
    sc.upper_case   = l(pass_str, m_symbols_upper_case);
    sc.digits       = l(pass_str, m_symbols_digits);
    sc.minus        = l(pass_str, m_symbols_minus);
    sc.underline    = l(pass_str, m_symbols_underline);
    sc.space        = l(pass_str, m_symbols_space);
    sc.special      = l(pass_str, m_symbols_special);
    sc.brackets     = l(pass_str, m_symbols_brackets);
    return sc;
}
