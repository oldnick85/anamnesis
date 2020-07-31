#ifndef CSETGENSINGLE_H
#define CSETGENSINGLE_H

#include <list>
#include "select_common.h"
#include "result/result.h"

/*!
 * \brief CSetgenSingle - генератор множества из простого списка вариантов
 */
class CSetgenSingle
        : public ISetgen
{
public:
    CSetgenSingle() = default;
    // ISetgen
    virtual void Reset() override final;
    virtual Result_t Valid(const enPurpose purpose) const override final;
    virtual uint64 VariantsCount() const override final;
    virtual std::string GetDescription() const override final;
    virtual enSetgenType GetType() const override final;
    // ISerializible
    virtual rapidjson::Document toJSON() const override final;
    virtual bool fromJSON(const rapidjson::Value& doc) override final;
    /*!
     * \brief SetDescription - установить описание генератора
     * \param[in] desc - строка с описанием
     */
    void SetDescription(const std::string &desc);
    /*!
     * \brief SetVariants - установить набор вариантов
     * \param[in] variants - строки-варианты
     */
    void SetVariants(const std::list<std::string> &variants);
    /*!
     * \brief AddVariant - добавить вариант
     * \param[in] variant - строка-вариант
     * \return успех добавления
     */
    Result_t AddVariant(const std::string &variant);
    /*!
     * \brief DelVariant - удалить вариант
     * \param[in] var_id - номер варианта
     * \return успех удаления
     */
    Result_t DelVariant(const uint var_id);
    /*!
     * \brief GetVariants - получить список вариантов
     * \return список вариантов
     */
    std::list<std::string> GetVariants();
    /*!
     * \brief operator == - равенство генераторов
     * \param[in] rhs - сравниваемый генератор
     * \return равенство
     */
    bool operator==(const CSetgenSingle& rhs) const;
private:
    bool UniqVariants(const std::list<std::string> &vars) const;
    rapidjson::Document toJSON_variants() const;
    bool fromJSON_variants(const rapidjson::Value& doc);

    std::list<std::string>	m_variants;
    std::string             m_description;
};

using CSetgenSinglePtr = std::shared_ptr<CSetgenSingle>;

#endif // CSETGENSINGLE_H
