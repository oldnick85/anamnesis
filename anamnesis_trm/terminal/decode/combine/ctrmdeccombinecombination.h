#ifndef CTRMDECCOMBINECOMBINATION_H
#define CTRMDECCOMBINECOMBINATION_H

#include "common.h"
#include "../select/combine/ccombinecombination.h"
#include "ctrmio.h"
#include "ctrmio_combine.h"

/*!
 * \brief ITrmDecCombineCombinationHandler - интерфейс обработчика состояний терминала запроса сочетания
 */
class ITrmDecCombineCombinationHandler
{
public:
    virtual ~ITrmDecCombineCombinationHandler() = default;
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
 * \brief CTrmDecCombineCombinationStateMashine - машина состояний терминала запроса сочетания
 */
class CTrmDecCombineCombinationStateMashine
        : public IStateMashine
{
public:
    /*!
     * \brief CTrmDecCombineCombinationStateMashine - конструктор машины состояний терминала запроса сочетания
     * \param callback - интерфейс обработчика состояний
     */
    CTrmDecCombineCombinationStateMashine(ITrmDecCombineCombinationHandler* callback);
    virtual ~CTrmDecCombineCombinationStateMashine() override = default;

private:
    enum enState
    {
        stStart,
        stEnd,
        stInit,
        stQuery,
        stConfirm,
    };

    enState                                 m_state = stStart;
    ITrmDecCombineCombinationHandler*       m_callback = nullptr;

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
 * \brief TrmDecCombineCombination - класс терминала запроса сочетания
 *
 * Машина состояний терминала запроса сочетания:
 * \dot
 * digraph state_machine_combine_Combination {
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
class CTrmDecCombineCombination
        : public ITrmDecCombineCombinationHandler
        , public CTrmDecCombineCombinationStateMashine
        , public ITrmDecCombine
        , private CTrmIO
        , private CTrmIO_Combine
{
public:
    /*!
     * \brief CTrmDecCombineCombination - конструктор терминала обработки комбинатора сочетания для декодирования
     * \param[in] combine - комбинатор
     * \param[in] trm_setgen - терминал генератора
     */
    CTrmDecCombineCombination(ICombinePtr combine, ITrmDecSetgenPtr trm_setgen);
    virtual ~CTrmDecCombineCombination() override = default;
    // ITrmDecCombine
    virtual ICombinePtr GetCombine() const override final;
    virtual bool Valid() const override final;
    // ITrmDecCombineCombinationHandler
    virtual void Start() override final;
    virtual void Init() override final;
    virtual void Query() override final;
    virtual void Confirm() override final;

private:
    ICombinePtr             m_combine = nullptr;
    CCombineCombination*    m_combine_Combination = nullptr;
    ITrmDecSetgenPtr        m_trm_setgen = nullptr;
};
using CTrmDecCombineCombinationPtr = std::shared_ptr<CTrmDecCombineCombination>;

#endif // CTRMDECCOMBINECOMBINATION_H
