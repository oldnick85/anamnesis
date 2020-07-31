#ifndef CSETGENDOUBLE_H
#define CSETGENDOUBLE_H

#include "select_common.h"
#include "result/result.h"

/*!
 * \brief CSetgenDouble - класс двойного генератора множества
 */
class CSetgenDouble
        : public ISetgen
{
public:
    /*!
     * \brief enVariantsBank - банк вариантов
     */
    enum class enVariantsBank
    {
        vbFirst,
        vbSecond,
    };

    CSetgenDouble() = default;
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
     * \param[in] bank - устанавливаемый банк
     */
    void SetVariants(const std::list<std::string> &variants, const enVariantsBank bank);
    /*!
     * \brief AddVariant - добавить вариант
     * \param[in] variant - строка-вариант
     * \param[in] bank - дополняемый банк
     * \return успех добавления
     */
    Result_t AddVariant(const std::string &variant, const enVariantsBank bank);
    /*!
     * \brief DelVariant - удалить вариант
     * \param[in] var_id - номер варианта
     * \param[in] bank - банк вариантов
     * \return успех удаления
     */
    Result_t DelVariant(const uint var_id, const enVariantsBank bank);
    /*!
     * \brief GetVariants - получить список вариантов
     * \return список вариантов
     */
    std::list<std::string> GetVariants(const enVariantsBank bank);
    /*!
     * \brief operator == - равенство генераторов
     * \param[in] rhs - сравниваемый генератор
     * \return равенство
     */
    bool operator==(const CSetgenDouble& rhs) const;
private:
    bool UniqVariants(const std::list<std::string> &vars) const;
    rapidjson::Document toJSON_variants_first() const;
    rapidjson::Document toJSON_variants_second() const;
    bool fromJSON_variants_first(const rapidjson::Value& doc);
    bool fromJSON_variants_second(const rapidjson::Value& doc);

    std::list<std::string>	m_variants_first;
    std::list<std::string>	m_variants_second;
    std::string			m_description;
};

using CSetgenDoublePtr = std::shared_ptr<CSetgenDouble>;

#endif // CSETGENDOUBLE_H
