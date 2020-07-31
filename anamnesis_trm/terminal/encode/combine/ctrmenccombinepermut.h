#ifndef CTRMENCCOMBINEPERMUT_H
#define CTRMENCCOMBINEPERMUT_H

#include "common.h"
#include "../select/combine/ccombinepermutation.h"
#include "ctrmio.h"
#include "ctrmio_combine.h"
#include "../resources/textresult.h"

/*!
 * \brief ITrmEncCombinePermutHandler - интерфейс обработчика состояний терминала установки комбинации-перестановки
 */
class ITrmEncCombinePermutHandler
{
public:
    virtual ~ITrmEncCombinePermutHandler() = default;
    /*!
     * \brief Start - начало работы
     */
    virtual void Start() = 0;
    /*!
     * \brief Init - инициализация состояния
     */
    virtual void Init() = 0;
    /*!
     * \brief SetPermut - ввод перестановки
     */
    virtual void SetPermut() = 0;
};

/*!
 * \brief CTrmEncCombinePermutStateMashine - машина состояний терминала установки комбинации-перестановки
 */
class CTrmEncCombinePermutStateMashine
        : private IStateMashine
{
public:
    /*!
     * \brief CTrmEncCombinePermutStateMashine - конструктор машины состояний
     * \param callback - интерфейс обработчика состояний терминала установки комбинации-перестановки
     */
    CTrmEncCombinePermutStateMashine(ITrmEncCombinePermutHandler* callback);
    virtual ~CTrmEncCombinePermutStateMashine() override = default;

private:
    enum enState
    {
        stStart,
        stEnd,
        stInit,
        stSetPermut,
    };

    enState						m_state = stStart;
    ITrmEncCombinePermutHandler*	m_callback = nullptr;

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
     * \brief SetStateSetPermut - установить состояние задания перестановки
     */
    void SetStateSetPermut() {m_state = stSetPermut;}
private:
    void Mashine()
    {
        while (true)
        {
            switch (m_state)
            {
            case stStart:       m_callback->Start();        break;
            case stInit:        m_callback->Init();         break;
            case stSetPermut:   m_callback->SetPermut();    break;
            case stEnd:         return;
            }
        }
    }
public:
    virtual void Begin() override final {Mashine();}
};

/*! *********************************************************************************
 * \brief CTrmEncCombinePermut - класс терминала установки комбинации-перестановки
 *
 * Машина состояний терминала установки комбинации-перестановки:
 * \dot
 * digraph state_machine_setgen_single {
 *   start	[label="Start"];
 *	 end	[label="End"];
 *	 init	[label="Init"];
 *	 setp	[label="Set permutation"];
 *
 *   start	->	init
 *   init	->	setp
 *   setp   ->  setp
 *   setp   ->  end
 * }
 * \enddot
 **********************************************************************************/
class CTrmEncCombinePermut
        : public ITrmEncCombinePermutHandler
        , public CTrmEncCombinePermutStateMashine
        , public ITrmEncCombine
        , private CTrmIO
        , private CTrmIO_Combine
{
public:
    /*!
     * \brief CTrmEncCombinePermut - конструктор терминала установки комбинации-перестановки
     * \param set_generator - генератор множества
     */
    CTrmEncCombinePermut(ITrmEncSetgenPtr set_generator);
    /*!
     * \brief CTrmEncCombinePermut - конструктор терминала установки комбинации-перестановки
     * \param comb_perm - комбинатор перестановки
     * \param set_generator - генератор множества
     */
    CTrmEncCombinePermut(ITrmEncSetgenPtr set_generator, CCombinePermutationPtr comb_perm);
    // ITrmCombine
    virtual ICombinePtr GetCombine() const override final;
    // ITrmCombinePermutHandler
    virtual void Start() override final;
    virtual void Init() override final;
    virtual void SetPermut() override final;
    /*!
     * \brief GetCombinePermut - получить комбинатор перестановок
     * \return комбинатор перестановок
     */
    CCombinePermutationPtr GetCombinePermut() {return m_comb_perm;}
    /*!
     * \brief Valid - предикат валидности
     * \return валидность
     */
    Result_t Valid() const;

private:
    Result_t ParseString(const std::string &str, Sampling_t &samp);

    ITrmEncSetgenPtr        m_trm_setgen = nullptr;
    CCombinePermutationPtr  m_comb_perm = nullptr;
};

using CTrmEncCombinePermutPtr = std::shared_ptr<CTrmEncCombinePermut>;

#endif // CTRMENCCOMBINEPERMUT_H
