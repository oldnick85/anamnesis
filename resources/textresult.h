#ifndef TEXTRESULT_H
#define TEXTRESULT_H

#include "ctextresources.h"
#include "../select/result/result.h"

/*!
 * \brief CTextResult - класс для получения текстового описания результата
 */
class CTextResult
        : private Result_t
{
public:
    /*!
     * \brief CTextResult - конструктор с инициализацией по результату
     * \param[in] result - результат
     */
    CTextResult(const Result_t result) : Result_t(result) {}
    /*!
     * \brief Text - получить текстовое описание результата
     * \return текстовое описание
     */
    std::string Text() const
    {
        std::string str;
        for (const auto &r : m_issues)
        {
            std::string s;
            switch (r.issue)
            {
            case RES_OK:                        s = TextById(TRM_TXT_RES::enStringId::siResultOK);                  break;
            case RES_ERROR:                     s = TextById(TRM_TXT_RES::enStringId::siResultError);               break;
            case RES_INCORRECT_INDEX:           s = TextById(TRM_TXT_RES::enStringId::siResultIncorrectIndex);      break;
            case RES_VAR_IN_LIST:               s = TextById(TRM_TXT_RES::enStringId::siResultVarInList);           break;
            case RES_COMB_N_LESS_K:             s = TextById(TRM_TXT_RES::enStringId::siResultComb_N_less_K);       break;
            case RES_COMB_SIZE_NEQ_K:           s = TextById(TRM_TXT_RES::enStringId::siResultCombSize_neq_K);      break;
            case RES_COMB_SIZE_GR_N:            s = TextById(TRM_TXT_RES::enStringId::siResultCombSize_gr_N);       break;
            case RES_COMB_VAL_GEQ_N:            s = TextById(TRM_TXT_RES::enStringId::siResultCombVal_geq_N);       break;
            case RES_COMB_VAL_DUPLICATE:        s = TextById(TRM_TXT_RES::enStringId::siResultCombValDuplicate);    break;
            case RES_SYMB_DUPLICATE:            s = TextById(TRM_TXT_RES::enStringId::siResultSymbDuplicate);       break;
            case RES_PASS_WRONG_SYMBOL:         s = TextById(TRM_TXT_RES::enStringId::siResultPassWrongSymbol);     break;
            case RES_PERM_N_0:                  s = TextById(TRM_TXT_RES::enStringId::siResultPerm_N_0);            break;
            case RES_COMB_N_0:                  s = TextById(TRM_TXT_RES::enStringId::siResultComb_N_0);            break;
            case RES_PASS_NO_SYMBOLS_SET:       s = TextById(TRM_TXT_RES::enStringId::siResultPassNoSymbSet);       break;
            case RES_PASS_NO_PASSWORD:          s = TextById(TRM_TXT_RES::enStringId::siResultPassNoPassword);      break;
            case RES_NO_SETCOMB:                s = TextById(TRM_TXT_RES::enStringId::siResultNoSetcomb);           break;
            case RES_NO_DESCRIPTION:            s = TextById(TRM_TXT_RES::enStringId::siResultNoDescription);       break;
            case RES_NO_PASSWORD:               s = TextById(TRM_TXT_RES::enStringId::siResultNoPassword);          break;
            case RES_NO_SETGEN:                 s = TextById(TRM_TXT_RES::enStringId::siResultNoSetgen);            break;
            case RES_NO_COMBINE:                s = TextById(TRM_TXT_RES::enStringId::siResultNoCombine);           break;
            case RES_NO_VARIANTS:               s = TextById(TRM_TXT_RES::enStringId::siResultNoVariants);          break;
            case RES_NO_VARIANTS_IN_BANK:       s = TextNoVariantsInBank(r.param);                                  break;
            case RES_NO_PERMUTATION:            s = TextById(TRM_TXT_RES::enStringId::siResultNoPermutation);       break;
            case RES_NO_COMBINATION:            s = TextById(TRM_TXT_RES::enStringId::siResultNoCombination);       break;
            case RES_EMPTY_STRING:              s = TextById(TRM_TXT_RES::enStringId::siResultEmptyString);         break;
            case RES_NO_DELIMETER:              s = TextById(TRM_TXT_RES::enStringId::siResultNoDelimeter);         break;
            case RES_NO_VALUE_IN_TOKEN:         s = TextById(TRM_TXT_RES::enStringId::siResultNoValueInToken);      break;
            case RES_NOT_UNIQUE_VARIANTS:       s = TextById(TRM_TXT_RES::enStringId::siResultNotUniqueVariants);   break;
            case RES_NOT_UNIQUE_VARIANTS_IN_BANK:   s = TextNotUniqueVariantsInBank(r.param);                       break;
            case RES_CAN_NOT_FILE_OPEN:             s = TextById(TRM_TXT_RES::enStringId::siOpenFileNoFile);     break;
            case RES_UNKNOWN_FILE_FORMAT:           s = TextById(TRM_TXT_RES::enStringId::siOpenFileContentErr); break;
            case RES_INAPPROPRIATE_FILE_CONTENT:    s = TextById(TRM_TXT_RES::enStringId::siOpenFileJsonErr);    break;
            }
            str += s + "; ";
        }
        return str;
    }
private:
    std::string TextById(const TRM_TXT_RES::enStringId str_id) const {return text(str_id);}
    std::string TextNotUniqueVariantsInBank(const unsigned int param) const
    {
        char s[128];
        snprintf(s, sizeof(s), "%s %u", text(TRM_TXT_RES::enStringId::siResultNotUniqueVariantsInBank).c_str(), param);
        return s;
    }
    std::string TextNoVariantsInBank(const unsigned int param) const
    {
        char s[128];
        snprintf(s, sizeof(s), "%s %u", text(TRM_TXT_RES::enStringId::siResultNoVariantsInBank).c_str(), param);
        return s;
    }
};

#endif // TEXTRESULT_H
