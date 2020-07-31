#ifndef CTRMDECSETGENDOUBLE_H
#define CTRMDECSETGENDOUBLE_H

#include "common.h"
#include "../select/setgen/csetgendouble.h"
#include "ctrmio.h"
#include "ctrmio_setgendouble.h"

/*!
 * \brief ITrmDecSetgenDoubleHandler - интерфейс обработчика состояний терминала запроса двойного генератора множества для декодирования пароля
 */
class ITrmDecSetgenDoubleHandler
{
public:
    virtual ~ITrmDecSetgenDoubleHandler() = default;
    /*!
     * \brief Start - начало работы
     */
    virtual void Start() = 0;
    /*!
     * \brief Init - инициализация
     */
    virtual void Init() = 0;
    /*!
     * \brief Query - запрос данных
     */
    virtual void Query() = 0;
    /*!
     * \brief Confirm - подтверждение данных
     */
    virtual void Confirm() = 0;
};

/*!
 * \brief CTrmDecSetgenSingleStateMashine - машина состояний терминала запроса двойного генератора множества для декодирования пароля
 */
class CTrmDecSetgenDoubleStateMashine
        : public IStateMashine
{
public:
    /*!
     * \brief CTrmDecSetgenDoubleStateMashine - конструктор машины состояний терминала запроса двойного генератора множества для декодирования пароля
     * \param callback - интерфейс обработчика состояний
     */
    CTrmDecSetgenDoubleStateMashine(ITrmDecSetgenDoubleHandler* callback);
    virtual ~CTrmDecSetgenDoubleStateMashine() override = default;

private:
    enum enState
    {
        stStart,
        stEnd,
        stInit,
        stQuery,
        stConfirm,
    };

    enState						m_state = stStart;
    ITrmDecSetgenDoubleHandler*	m_callback = nullptr;

public:
    /*!
     * \brief SetStateStart - установить состояние начала работы
     */
    void SetStateStart() {m_state = stStart;}
    /*!
     * \brief SetStateEnd - установить состояние завершения работы
     */
    void SetStateEnd() {m_state = stEnd;}
     /*!
     * \brief SetStateInit - установить состояние инициализации
     */
    void SetStateInit() {m_state = stInit;}
    /*!
     * \brief SetStateQuery - установить состояние запроса данных
     */
    void SetStateQuery() {m_state = stQuery;}
    /*!
     * \brief SetStateConfirm - установить состояние подтверждения
     */
    void SetStateConfirm() {m_state = stConfirm;}
private:
    void Mashine()
    {
        while (true)
        {
            switch (m_state)
            {
            case stStart:       m_callback->Start();        break;
            case stInit:        m_callback->Init();         break;
            case stQuery:       m_callback->Query();        break;
            case stConfirm:     m_callback->Confirm();      break;
            case stEnd:         return;
            }
        }
    }
public:
    virtual void Begin() override final {Mashine();}
};

/*! *********************************************************************************
 * \brief CTrmDecSetgenDouble - класс терминала запроса двойного генератора множества
 *
 * Машина состояний терминала запроса генератора вариантов:
 * \dot
 * digraph state_machine_setgen_single {
 *   start	[label="Start"];
 *	 end	[label="End"];
 *	 init	[label="Init"];
 *	 query	[label="Query"];
 *	 conf	[label="Confirm"];
 *
 *   start	->	init
 *   init	->	query
 *	 query  ->  conf
 *   conf	->	query
 *   conf	->	end
 * }
 * \enddot
 **********************************************************************************/
class CTrmDecSetgenDouble
        : public ITrmDecSetgenDoubleHandler
        , public CTrmDecSetgenDoubleStateMashine
        , public ITrmDecSetgen
        , private CTrmIO
        , private CTrmIO_SetgenDouble
{
public:
    /*!
     * \brief CTrmDecSetgenDouble - конструктор класса терминала запроса двойного генератора множества
     * \param setgen - интерфейс генератора множества для инициализации
     */
    CTrmDecSetgenDouble(ISetgenPtr setgen);
    virtual ~CTrmDecSetgenDouble() override = default;
    // ITrmSetgen
    virtual Result_t ParseSample(const std::string &str, uint64 &value) const override;
    // ITrmDecSetgen
    virtual ISetgenPtr GetSetgen() override final;
    virtual Result_t Valid() const override final;
    std::string SampleHint() const override final;
    // ITrmDecSetgenSingleHandler
    virtual void Start() override final;
    virtual void Init() override final;
    virtual void Query() override final;
    virtual void Confirm() override final;
private:
    ISetgenPtr          m_setgen = nullptr;
    CSetgenDouble*      m_setgen_double = nullptr;
};
using CTrmDecSetgenDoublePtr = std::shared_ptr<CTrmDecSetgenDouble>;


#endif // CTRMDECSETGENDOUBLE_H
