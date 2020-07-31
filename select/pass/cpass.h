#ifndef CPASS_H
#define CPASS_H

#include <vector>
#include "select_common.h"
#include "result/result.h"

using PassSymbol_t = uint8_t;
using Pass_t = std::vector<PassSymbol_t>;

/*!
 * \brief CPass - пароль вместе со своим допустимым набором символов
 */
class CPass
        : public ISerializible
{
public:
    /*!
     * \brief sSymbolClass - комбинация из классов доступных символов
     */
    struct sSymbolClass
    {
        sSymbolClass()
        {
            upper_case = false;
            lower_case = false;
            digits = false;
            minus = false;
            underline = false;
            space = false;
            special = false;
            brackets = false;
        }

        bool    upper_case  = false;        ///< заглавные латинские буквы
        bool    lower_case  = false;        ///< строчные латинские буквы
        bool    digits	    = false;        ///< цифры
        bool    minus	    = false;        ///< минус
        bool    underline   = false;        ///< подчеркивание
        bool	space	    = false;        ///< пробел
        bool	special	    = false;        ///< специальные символы
        bool	brackets    = false;        ///< скобки
    };

    CPass() = default;

    // ISerializible
    virtual rapidjson::Document toJSON() const override final;
    virtual bool fromJSON(const rapidjson::Value& doc) override final;

    /*!
     * \brief Reset - сброс пароля и набора символов
     */
    void Reset();
    /*!
     * \brief AddSymbols - добавить символы в набор
     * \param[in] symbols - символы
     */
    void AddSymbols(const Pass_t &symbols);
    /*!
     * \brief SetSymbols - установить набор символов
     * \param[in] symbols - символы
     * \return успех установки набора
     */
    Result_t SetSymbols(const Pass_t &symbols);
    /*!
     * \brief SetSymbols - установить набор символов через классы символов
     * \param[in] symbols_class - классы символов
     * \return успех установки
     */
    Result_t SetSymbols(const sSymbolClass &symbols_class);
    /*!
     * \brief SymbolsFromPassword - получить используемые в пароле типы символов
     * \param[in] pass_str - строка с паролем
     * \return структура с типами символов
     */
    sSymbolClass SymbolsFromPassword(const std::string &pass_str);
    /*!
     * \brief GetSymbols - получить набор допустимых символов
     * \return набор допустимых символов
     */
    Pass_t GetSymbols();
    /*!
     * \brief SetPassword - установить пароль
     * \param[in] pass - пароль
     * \return успех установки
     */
    Result_t SetPassword(const Pass_t &pass);
    /*!
     * \brief GetPassword - получить пароль
     * \return пароль
     */
    Pass_t &GetPassword();
    /*!
     * \brief SetPassword - установить пароль с помощью строки
     * \param[in] pass_str - строка с паролем
     * \return успех установки
     */
    Result_t SetPassword(const std::string &pass_str);
    /*!
     * \brief GetPasswordString - получить строковое представление пароля
     * \return строковое представление пароля
     */
    std::string GetPasswordString() const;
    /*!
     * \brief Valid - проверка на валидность пароля
     * \return валидность
     */
    Result_t Valid(const enPurpose purpose) const;
    /*!
     * \brief VariantsCount - получить общее число возможных вариантов пароля
     * \return общее число возможных вариантов пароля
     */
    CNumber VariantsCount() const;
    /*!
     * \brief Value - получить значение, соответствующее заданному паролю
     * \return значение, соответствующее заданному паролю
     */
    CNumber Value() const;
    /*!
     * \brief SetValue - установить пароль по значению
     * \param[in] val - значение
     * \return успех установки
     */
    Result_t SetValue(const CNumber val);
    /*!
     * \brief SetPasswordLength - установить длину пароля
     * \param[in] pass_len  длина пароля
     * \return успех установки длины
     */
    Result_t SetPasswordLength(const uint pass_len);

private:
    Result_t CheckPassSymbols(const Pass_t &symbols, const Pass_t &pass) const;
    bool fromJSON_symbols(const rapidjson::Value& doc);
    rapidjson::Document toJSON_symbols() const;
    void AddStringToSymbols(Pass_t &symbols, const std::string &chars);
    uint64 SymbolValue(const PassSymbol_t symb) const;
    PassSymbol_t ValueSymbol(const uint64 vl) const;

    Pass_t      m_symbols;
    Pass_t      m_pass;
    uint64      m_pass_len = 0;

    const std::string   m_symbols_lower_case    = "abcdefghijklmnopqrstuvwxyz";
    const std::string   m_symbols_upper_case    = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string   m_symbols_digits        = "0123456789";
    const std::string   m_symbols_minus         = "-";
    const std::string   m_symbols_underline     = "_";
    const std::string   m_symbols_space         = " ";
    const std::string   m_symbols_special       = "!@#$%^&*+=\"'\\|/.,:;~`?";
    const std::string   m_symbols_brackets      = "(){}[]<>";
};

using CPassPtr = std::shared_ptr<CPass>;

#endif // CPASS_H
