#ifndef ASSOCIATIONS_COMMON_H
#define ASSOCIATIONS_COMMON_H

#define RAPIDJSON_HAS_STDSTRING 1

#include <memory>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include "../longnum/cdigitnumber.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "result/result.h"

#define JSON_PASS_SYMBOLS "symbols"
#define JSON_COMBINE_PERMUT_N "n"
#define JSON_COMBINE_PERMUT_K "k"
#define JSON_COMBINE_TYPE "type"
#define JSON_COMBINE_PERMUTATION "permutation"
#define JSON_COMBINE_COMBINATION "combination"
#define JSON_SETGEN_DESCRIPTION "description"
#define JSON_SETGEN_VARIANTS "variants"
#define JSON_SETGEN_VARIANTS_FIRST "variants_first"
#define JSON_SETGEN_VARIANTS_SECOND "variants_second"
#define JSON_SETGEN_TYPE "type"
#define JSON_SETGEN_SINGLE "single"
#define JSON_SETGEN_DOUBLE "double"
#define JSON_SETCOMB_DESC "description"
#define JSON_SETCOMB_SETGEN "setgen"
#define JSON_SETCOMB_COMBINE "combine"
#define JSON_CASKET "casket"
#define JSON_VERSION "version"
#define JSON_CASKET_PASS "password"
#define JSON_CASKET_SETCOMB "setcomb"
#define JSON_CASKET_KEYHOLE "keyhole"

#undef DEBUG_ON
//#define DEBUG_ON

#ifdef DEBUG_ON
#define debug_log(...) do{printf(__VA_ARGS__);}while(0)
#else
#define debug_log(...) do{}while(0)
#endif

#define MAX_PASSWORD_LENGTH 256

enum class enPurpose
{
    pEncode,
    pDecode,
};

using Sampling_t = std::vector<uint64>;

/*!
 * \brief ISerializible - нтерфейс сериализуемого объекта
 */
class ISerializible
{
public:
    virtual ~ISerializible() = default;
    /*!
     * \brief toJSON - сериализовать объект в JSON
     * \return документ библиотеки rapidjson
     */
    virtual rapidjson::Document toJSON() const = 0;
    /*!
     * \brief fromJSON - инициализировать объект из JSON
     * \param[in] doc - значение библиотеки rapidjson
     * \return успех парсинга
     */
    virtual bool fromJSON(const rapidjson::Value& doc) = 0;
};

using ISerializiblePtr = std::shared_ptr<ISerializible>;

enum class enSetgenType : uint8_t
{
    stNone              = 0,
    stSingle,
    stDouble,
};

/*!
 * \brief ISetgen - интерфейс генератора множества, из элементов которого будет составлятся комбинация
 */
class ISetgen
        : public ISerializible
{
public:
    virtual ~ISetgen() = default;
    /*!
     * \brief Reset - сброс настроек
     */
    virtual void Reset() = 0;
    /*!
     * \brief Valid - предикат валидности генератора
     * \return валидность генератора
     */
    virtual Result_t Valid(const enPurpose purpose) const = 0;
    /*!
     * \brief VariantsCount - общее количество вариантов (размер множества)
     * \return общее количество вариантов (размер множества)
     */
    virtual uint64 VariantsCount() const = 0;
    /*!
     * \brief GetDescription - получить описание генератора
     * \return описание генератора
     */
    virtual std::string GetDescription() const = 0;
    /*!
     * \brief GetType - получить тип генератора
     * \return тип генератора
     */
    virtual enSetgenType GetType() const = 0;
};

using ISetgenPtr = std::shared_ptr<ISetgen>;

enum class enCombineType : uint8_t
{
    ctNone                  = 0,
    ctPermutation,
    ctCombination,
};

/*!
 * \brief ICombine - интерфейс комбинации элементов множества
 */
class ICombine
        : public ISerializible
{
public:
    virtual ~ICombine() = default;
    /*!
     * \brief Valid - предикат валидности генератора
     * \return валидность генератора
     */
    virtual Result_t Valid(const enPurpose purpose) const = 0;
    /*!
     * \brief VariantsCount - общее количество комбинаций
     * \return общее количество комбинаций
     */
    virtual CNumber VariantsCount() const = 0;
    /*!
     * \brief GetValue - получить значение для данной перестановки
     * \return значение для данной перестановки
     */
    virtual CNumber Value() const = 0;
    /*!
     * \brief GetType - получить тип комбинатора
     * \return тип комбинатора
     */
    virtual enCombineType GetType() const = 0;
};

using ICombinePtr = std::shared_ptr<ICombine>;

#endif // ASSOCIATIONS_COMMON_H
