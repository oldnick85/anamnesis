#ifndef CCOMBINECOMBINATION_H
#define CCOMBINECOMBINATION_H

#include "select_common.h"
#include "result/result.h"

/**
 * @brief CCombineCombination - класс перестановки с повторениями
 */
class CCombineCombination
        : public ICombine
{
public:
    CCombineCombination() = default;
    // ISerializible
    virtual rapidjson::Document toJSON() const override final;
    virtual bool fromJSON(const rapidjson::Value& doc) override final;
    // ICombine
    virtual Result_t Valid(const enPurpose purpose) const override final;
    virtual CNumber VariantsCount() const override final;
    virtual CNumber Value() const override final;
    virtual enCombineType GetType() const override final;
    /*!
     * \brief Reset- сброс параметров
     */
    void Reset();
    /*!
     * \brief SetParameters - установить параметры перестановки
     * \param[in] n - общее число вариантов
     * \param[in] k - размер перестановки
     * \return успех установки параметров
     */
    Result_t SetParameters(const uint64 n, const uint64 k = 0);
    /*!
     * \brief SetPermutation - установить перестановку
     * \param[in] comb - комбинация
     * \param[in] set_k - установить размер перестановки по заданной
     * \return успех установки перестановки
     */
    Result_t SetCombination(const Sampling_t &comb, bool set_k = true);
    /*!
     * \brief operator == - сравнение классов перестановок
     * \param[in] rhs - сравниваемое значение
     * \return результат сравнения
     */
    bool operator==(const CCombineCombination& rhs) const;

private:
    /*!
     * \brief CalcValue - вычислить число, соответствующее набору значений
     * \param comb_map - упорядоченный по возрастанию список индексов (значений набора)
     * \return число, соответствующее набору значений
     */
    CNumber CalcValue(const std::vector<uint64> &comb_map, const uint64 n) const;
    CNumber BinomialCoeff(const uint64 n, const uint64 k) const;

    uint64                      m_n = 0;
    uint64                      m_k = 0;
    std::unordered_set<uint64>  m_comb;
};

using CCombineCombinationPtr = std::shared_ptr<CCombineCombination>;

#endif // CCOMBINECOMBINATION_H
