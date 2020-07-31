#ifndef CSETCOMB_H
#define CSETCOMB_H

#include "select_common.h"
#include "result/result.h"

/*!
 * \brief CSetComb - класс-связка генератора множества и комбинатора его элементов
 */
class CSetComb
        : public ISerializible
{
public:
    CSetComb() = default;
    // ISerializible
    virtual rapidjson::Document toJSON() const override final;
    virtual bool fromJSON(const rapidjson::Value& doc) override final;
    /*!
     * \brief SetDescription - становить описание
     * \param[in] desc - строка с описанием
     */
    void SetDescription(const std::string &desc) {m_desc = desc;}
    /*!
     * \brief SetSetgen - установить генератор
     * \param[in] setgen - генератор
     */
    void SetSetgen(ISetgenPtr setgen) {m_setgen = setgen;}
    /*!
     * \brief SetCombine - установить комбинатор
     * \param[in] combine - комбинатор
     */
    void SetCombine(ICombinePtr combine) {m_combine = combine;}
    /*!
     * \brief GetDescription - олучить описание
     * \return строка с описанием
     */
    std::string GetDescription() const {return m_desc;}
    /*!
     * \brief GetSetgen - получить генератор
     * \return генератор
     */
    ISetgenPtr GetSetgen() const {return m_setgen;}
    /*!
     * \brief GetCombine - получить комбинатор
     * \return комбинатор
     */
    ICombinePtr GetCombine() const {return m_combine;}
    /*!
     * \brief Valid - предикат валидности связки
     * \return валидность
     */
    Result_t Valid(const enPurpose purpose) const;
private:
    std::string             m_desc;
    ISetgenPtr              m_setgen = nullptr;
    ICombinePtr             m_combine = nullptr;
};

using CSetCombPtr = std::shared_ptr<CSetComb>;

#endif // CSETCOMB_H
