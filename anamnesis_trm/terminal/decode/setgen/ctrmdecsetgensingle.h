#ifndef CTRMDECSETGENSINGLE_H
#define CTRMDECSETGENSINGLE_H

#include "common.h"
#include "../select/setgen/csetgensingle.h"
#include "ctrmio.h"
#include "ctrmio_setgensingle.h"

/*!
 * \brief ITrmDecSetgenSingleHandler - интерфейс обработчика состояний терминала запроса одиночного генератора множества для декодирования пароля
 */
class ITrmDecSetgenSingleHandler
{
public:
    virtual ~ITrmDecSetgenSingleHandler() = default;
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
 * \brief CTrmDecSetgenSingleStateMashine - машина состояний терминала запроса одиночного генератора множества для декодирования пароля
 */
class CTrmDecSetgenSingleStateMashine
        : public IStateMashine
{
public:
    /*!
     * \brief CTrmDecSetgenSingleStateMashine - конструктор машины состояний терминала запроса одиночного генератора множества для декодирования пароля
     * \param callback - интерфейс обработчика состояний
     */
    CTrmDecSetgenSingleStateMashine(ITrmDecSetgenSingleHandler* callback);
    virtual ~CTrmDecSetgenSingleStateMashine() override = default;

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
    ITrmDecSetgenSingleHandler*	m_callback = nullptr;

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
 * \brief CTrmDecSetgenSingle - класс терминала запроса одиночного генератора множества
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
class CTrmDecSetgenSingle
        : public ITrmDecSetgenSingleHandler
        , public CTrmDecSetgenSingleStateMashine
        , public ITrmDecSetgen
        , private CTrmIO
        , private CTrmIO_SetgenSingle
{
public:
    /*!
     * \brief CTrmDecSetgenSingle - конструктор терминала обработки одиночного генератора для декодирования
     * \param[in] setgen - генератор
     */
    CTrmDecSetgenSingle(ISetgenPtr setgen);
    virtual ~CTrmDecSetgenSingle() override = default;
    // ITrmSetgen
    virtual Result_t ParseSample(const std::string &str, uint64 &value) const override;
    // ITrmDecSetgen
    virtual ISetgenPtr GetSetgen() override final;
    virtual Result_t Valid() const override final;
    virtual std::string SampleHint() const override final;
    // ITrmDecSetgenSingleHandler
    virtual void Start() override final;
    virtual void Init() override final;
    virtual void Query() override final;
    virtual void Confirm() override final;

private:
    ISetgenPtr          m_setgen = nullptr;
    CSetgenSingle*      m_setgen_single = nullptr;
};
using CTrmDecSetgenSinglePtr = std::shared_ptr<CTrmDecSetgenSingle>;

#endif // CTRMDECSETGENSINGLE_H
