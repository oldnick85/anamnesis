#ifndef CTRMDECCOMBINEPERMUT_H
#define CTRMDECCOMBINEPERMUT_H

#include "common.h"
#include "../select/combine/ccombinepermutation.h"
#include "ctrmio.h"
#include "ctrmio_combine.h"
#include "../resources/textresult.h"

/*!
 * \brief ITrmDecCombinePermutHandler - интерфейс обработчика состояний терминала запроса перестановки
 */
class ITrmDecCombinePermutHandler
{
public:
    virtual ~ITrmDecCombinePermutHandler() = default;
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
 * \brief CTrmDecCombinePermutStateMashine - машина состояний терминала запроса перестановки
 */
class CTrmDecCombinePermutStateMashine
        : public IStateMashine
{
public:
    /*!
     * \brief CTrmDecCombinePermutStateMashine - конструктор машины состояний терминала запроса перестановки
     * \param callback - интерфейс обработчика состояний
     */
    CTrmDecCombinePermutStateMashine(ITrmDecCombinePermutHandler* callback);
    virtual ~CTrmDecCombinePermutStateMashine() override = default;

private:
    enum enState
    {
        stStart,
        stEnd,
        stInit,
        stQuery,
        stConfirm,
    };

    enState                         m_state = stStart;
    ITrmDecCombinePermutHandler*    m_callback = nullptr;

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
 * \brief TrmDecCombinePermut - класс терминала запроса перестановки
 *
 * Машина состояний терминала запроса перестановки:
 * \dot
 * digraph state_machine_combine_permut {
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
class CTrmDecCombinePermut
        : public ITrmDecCombinePermutHandler
        , public CTrmDecCombinePermutStateMashine
        , public ITrmDecCombine
        , private CTrmIO
        , private CTrmIO_Combine
{
public:
    /*!
     * \brief CTrmDecCombinePermut - конструктор терминала обработки комбинатора перестановки для декодирования
     * \param[in] combine - комбинатор
     * \param[in] trm_setgen - терминал генератора
     */
    CTrmDecCombinePermut(ICombinePtr combine, ITrmDecSetgenPtr trm_setgen);
    virtual ~CTrmDecCombinePermut() override = default;
    // ITrmDecCombine
    virtual ICombinePtr GetCombine() const override final;
    virtual bool Valid() const override final;
    // ITrmDecCombinePermutHandler
    virtual void Start() override final;
    virtual void Init() override final;
    virtual void Query() override final;
    virtual void Confirm() override final;

private:
    ICombinePtr             m_combine = nullptr;
    CCombinePermutation*    m_combine_permut = nullptr;
    ITrmDecSetgenPtr        m_trm_setgen = nullptr;
};
using CTrmDecCombinePermutPtr = std::shared_ptr<CTrmDecCombinePermut>;

#endif // CTRMDECCOMBINEPERMUT_H
