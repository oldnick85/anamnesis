#ifndef CCOMBINEPERMUTATION_H
#define CCOMBINEPERMUTATION_H

#include "select_common.h"
#include "result/result.h"

/**
 * @brief CCombinePermutation - класс перестановки без повторений
 */
class CCombinePermutation
        : public ICombine
{
public:
    CCombinePermutation() = default;
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
     * \param[in] perm - перестановка
     * \param[in] set_k - установить размер перестановки по заданной
     * \return успех установки перестановки
     */
    Result_t SetPermutation(const Sampling_t &perm, bool set_k = true);
    /*!
     * \brief operator == - сравнение классов перестановок
     * \param[in] rhs - chfdybdftvjt pyfxtybt
     * \return результат сравнения
     */
    bool operator==(const CCombinePermutation& rhs) const;
    /*!
     * \brief GetParameterN - получить общее число элементов
     * \return общее число элементов
     */
    uint64 GetParameterN() const {return m_n;}
    /*!
     * \brief GetParameterK - получить число элементов в перестановке
     * \return число элементов в перестановке
     */
    uint64 GetParameterK() const {return m_k;}

private:
    uint64          m_n = 0;
    uint64          m_k = 0;
    Sampling_t      m_perm;
};

using CCombinePermutationPtr = std::shared_ptr<CCombinePermutation>;

#endif // CCOMBINEPERMUTATION_H
