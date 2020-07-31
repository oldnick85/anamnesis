#ifndef TERMINAL_COMMON_H
#define TERMINAL_COMMON_H

#include <memory>
#include "ctextresources.h"
#include "../select/select_common.h"
#include "../select/result/result.h"

#define DEBUG_LOG_ON
#undef DEBUG_LOG_ON

#ifdef DEBUG_LOG_ON
    #define DEBUG_LOG(...) {char s[256]; snprintf(s, sizeof(s), __VA_ARGS__); printf("%s:%d %s\n", __FILE__, __LINE__, s);}
#else
    #define DEBUG_LOG(...) {}while(false)
#endif

using uint = unsigned int;
using uint32 = uint32_t;
using uint64 = uint64_t;

//! \todo создание многоязыковой документации (см. как это сделано для класса CArgParser)
//! \todo написать хелп для консольной версии программы

/*!
 * \brief IStateMashine - интерфейс машины состояний
 */
class IStateMashine
{
public:
    IStateMashine() = default;
    virtual ~IStateMashine() = default;
    /*!
     * \brief Begin - запуск машины состояний
     */
    virtual void Begin() = 0;
};

/*!
 * \brief ITrmSetgen - интерфейс терминала для генератора вариантов
 */
class ITrmSetgen
{
public:
    virtual ~ITrmSetgen() = default;
    /*!
     * \brief ParseSample - распарсить введённую строку
     * \param[in] str - строка для парсинга
     * \param[out] value - сгенерированное значение
     * \return успех парсинга
     */
    virtual Result_t ParseSample(const std::string &str, uint64 &value) const = 0;
    /*!
     * \brief SampleHint - получить описание текстового вида семплов
     * \return описание текстового вида семплов, как их должен вводить пользователь
     */
    virtual std::string SampleHint() const = 0;
};

/*!
 * \brief ITrmEncSetgen - интерфейс кодирования терминала для генератора множества
 */
class ITrmEncSetgen
        : public ITrmSetgen
{
public:
    virtual ~ITrmEncSetgen() = default;
    /*!
     * \brief GetSetgen - получить генератор множества
     * \return генератор множества
     */
    virtual ISetgenPtr GetSetgen() = 0;
    /*!
     * \brief Valid - предикат валидности
     * \return валидность
     */
    virtual Result_t Valid() const = 0;
};
using ITrmEncSetgenPtr = std::shared_ptr<ITrmEncSetgen>;

/*!
 * \brief ITrmDecSetgen - интерфейс кодирования терминала для генератора множества
 */
class ITrmDecSetgen
        : public ITrmSetgen
{
public:
    virtual ~ITrmDecSetgen() = default;
    /*!
     * \brief GetSetgen - получить генератор множества
     * \return генератор множества
     */
    virtual ISetgenPtr GetSetgen() = 0;
    /*!
     * \brief Valid - предикат валидности
     * \return валидность
     */
    virtual Result_t Valid() const = 0;
    virtual std::string SampleHint() const = 0;
};
using ITrmDecSetgenPtr = std::shared_ptr<ITrmDecSetgen>;

/*!
 * \brief ITrmEncCombine - интерфейс терминала для комбинатора значений
 */
class ITrmEncCombine
{
public:
    virtual ~ITrmEncCombine() = default;
    /*!
     * \brief GetCombine - получить комбинатор значений
     * \return комбинатор значений
     */
    virtual ICombinePtr GetCombine() const = 0;
};
using ITrmEncCombinePtr = std::shared_ptr<ITrmEncCombine>;

/*!
 * \brief ITrmDecCombine - интерфейс терминала для комбинатора значений
 */
class ITrmDecCombine
{
public:
    virtual ~ITrmDecCombine() = default;
    /*!
     * \brief GetCombine - получить комбинатор значений
     * \return комбинатор значений
     */
    virtual ICombinePtr GetCombine() const = 0;
    /*!
     * \brief Valid - предикат валидности
     * \return валидность
     */
    virtual bool Valid() const = 0;
};
using ITrmDecCombinePtr = std::shared_ptr<ITrmDecCombine>;

#endif // TERMINAL_COMMON_H
