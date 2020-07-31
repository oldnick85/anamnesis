#ifndef RESULT_H
#define RESULT_H

#include <list>
#include <algorithm>

enum enResult
{
    RES_OK,
    RES_ERROR,
    RES_INCORRECT_INDEX,
    RES_VAR_IN_LIST,
    RES_PERM_N_0,
    RES_COMB_N_0,
    RES_COMB_N_LESS_K,
    RES_COMB_SIZE_NEQ_K,
    RES_COMB_SIZE_GR_N,
    RES_COMB_VAL_GEQ_N,
    RES_COMB_VAL_DUPLICATE,
    RES_SYMB_DUPLICATE,
    RES_PASS_WRONG_SYMBOL,
    RES_PASS_NO_SYMBOLS_SET,
    RES_PASS_NO_PASSWORD,
    RES_NO_SETCOMB,
    RES_NO_DESCRIPTION,
    RES_NO_PASSWORD,
    RES_NO_SETGEN,
    RES_NO_COMBINE,
    RES_NO_VARIANTS,
    RES_NO_VARIANTS_IN_BANK,
    RES_NOT_UNIQUE_VARIANTS,
    RES_NOT_UNIQUE_VARIANTS_IN_BANK,
    RES_NO_PERMUTATION,
    RES_NO_COMBINATION,
    RES_EMPTY_STRING,
    RES_NO_DELIMETER,
    RES_NO_VALUE_IN_TOKEN,
    RES_CAN_NOT_FILE_OPEN,
    RES_UNKNOWN_FILE_FORMAT,
    RES_INAPPROPRIATE_FILE_CONTENT,
};

/*!
 * \brief Result_t - класс результата выполнения
 */
class Result_t
{
public:

    Result_t() = default;
    /*!
     * \brief Result_t - конструктор по типу результата
     * \param[in] result - тип результата
     * \param[in] param - параметр результата
     */
    Result_t(const enResult result, const unsigned int param = 0)
    {
        AddResult(result, param);
    }
    /*!
     * \brief AddResult - добавить результат в список
     * \param[in] result - тип результата
     * \param[in] param - параметр результата
     */
    void AddResult(const enResult result, const unsigned int param = 0)
    {
        m_issues.push_back(sIssue(result, param));
    }
    /*!
     * \brief AddResult  - добавить результат в список
     * \param[in] res - добавляемый результат
     */
    void AddResult(const Result_t &res)
    {
        for (const auto &r : res.m_issues) m_issues.push_back(r);
    }
    /*!
     * \brief OK - предикат успеха
     * \return результат успешен
     */
    bool OK() const
    {
        return (std::all_of(m_issues.begin(), m_issues.end(),
                            [](const sIssue &r){return r.OK();}));
    }
    /*!
     * \brief ERROR - предикат ошибки
     * \return результат ошибочный
     */
    bool ERROR() const
    {
        return (std::any_of(m_issues.begin(), m_issues.end(),
                            [](const sIssue &r){return r.ERROR();}));
    }

protected:

    /*!
     * \brief sIssue - структура исхода для результата
     */
    struct sIssue
    {
        /*!
         * \brief sIssue
         * \param res
         * \param prm
         */
        sIssue(const enResult res, const unsigned int prm = 0) {issue = res; param = prm;}
        /*!
         * \brief OK - предикат корректности исхода
         * \return корректность исхода
         */
        bool OK() const {return (issue == RES_OK);}
        /*!
         * \brief ERROR - предикат ошибочности исхода
         * \return ошибочность исхода
         */
        bool ERROR() const {return (issue != RES_OK);}

        enResult        issue = RES_OK;        ///< тип исхода
        unsigned int    param = 0;              ///< параметр исхода
    };
    std::list<sIssue>  m_issues;                ///< список исходов
};

#endif // RESULT_H
