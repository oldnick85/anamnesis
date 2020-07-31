#ifndef CTRMENCCOMBINECOMBINATION_H
#define CTRMENCCOMBINECOMBINATION_H

#include "common.h"
#include "../select/combine/ccombinecombination.h"
#include "ctrmio.h"
#include "ctrmio_combine.h"
#include "../resources/textresult.h"

/*!
 * \brief ITrmEncCombineCombinationHandler - интерфейс обработчика состояний терминала установки комбинации-сочетания
 */
class ITrmEncCombineCombinationHandler
{
public:
    virtual ~ITrmEncCombineCombinationHandler() = default;
    /*!
     * \brief Start - начало работы
     */
    virtual void Start() = 0;
    /*!
     * \brief Init - инициализация состояния
     */
    virtual void Init() = 0;
    /*!
     * \brief SetCombination - ввод сочетания
     */
    virtual void SetCombination() = 0;
};

/*!
 * \brief CTrmEncCombineCombinationStateMashine - машина состояний терминала установки комбинации-сочетания
 */
class CTrmEncCombineCombinationStateMashine
        : private IStateMashine
{
public:
    /*!
     * \brief CTrmEncCombineCombinationStateMashine - конструктор машины состояний
     * \param callback - интерфейс обработчика состояний терминала установки комбинации-сочетания
     */
    CTrmEncCombineCombinationStateMashine(ITrmEncCombineCombinationHandler* callback);
    virtual ~CTrmEncCombineCombinationStateMashine() override = default;

private:
    enum enState
    {
        stStart,
        stEnd,
        stInit,
        stSetCombination,
    };

    enState                             m_state = stStart;
    ITrmEncCombineCombinationHandler*	m_callback = nullptr;

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
     * \brief SetStateSetCombination - установить состояние задания сочетания
     */
    void SetStateSetCombination() {m_state = stSetCombination;}
private:
    void Mashine()
    {
        while (true)
        {
            switch (m_state)
            {
            case stStart:           m_callback->Start();            break;
            case stInit:            m_callback->Init();             break;
            case stSetCombination:  m_callback->SetCombination();   break;
            case stEnd:             return;
            }
        }
    }
public:
    virtual void Begin() override final {Mashine();}
};

/*! *********************************************************************************
 * \brief CTrmEncCombineCombination - класс терминала установки комбинации-сочетания
 *
 * Машина состояний терминала установки комбинации-сочетания:
 * \dot
 * digraph state_machine_setgen_single {
 *   start	[label="Start"];
 *	 end	[label="End"];
 *	 init	[label="Init"];
 *	 setc	[label="Set combination"];
 *
 *   start	->	init
 *   init	->	setc
 *   setc   ->  setc
 *   setc   ->  end
 * }
 * \enddot
 **********************************************************************************/
class CTrmEncCombineCombination
        : public ITrmEncCombineCombinationHandler
        , public CTrmEncCombineCombinationStateMashine
        , public ITrmEncCombine
        , private CTrmIO
        , private CTrmIO_Combine
{
public:
    /*!
     * \brief CTrmEncCombineCombination - конструктор терминала установки комбинации-сочетания
     * \param set_generator - генератор множества
     */
    CTrmEncCombineCombination(ITrmEncSetgenPtr set_generator);
    /*!
     * \brief CTrmEncCombineCombination - конструктор терминала установки комбинации-сочетания
     * \param comb_combination - комбинатор сочетания
     * \param set_generator - генератор множества
     */
    CTrmEncCombineCombination(ITrmEncSetgenPtr set_generator, CCombineCombinationPtr comb_combination);
    // ITrmCombine
    virtual ICombinePtr GetCombine() const override final;
    // ITrmCombineCombinationHandler
    virtual void Start() override final;
    virtual void Init() override final;
    virtual void SetCombination() override final;
    /*!
     * \brief GetCombineCombination - получить комбинатор перестановок
     * \return комбинатор перестановок
     */
    CCombineCombinationPtr GetCombineCombination() {return m_comb_combination;}
    /*!
     * \brief Valid - предикат валидности
     * \return валидность
     */
    Result_t Valid() const;

private:
    Result_t ParseString(const std::string &str, Sampling_t &samp);

    ITrmEncSetgenPtr            m_trm_setgen = nullptr;
    CCombineCombinationPtr      m_comb_combination = nullptr;
};

using CTrmEncCombineCombinationPtr = std::shared_ptr<CTrmEncCombineCombination>;

#endif // CTRMENCCOMBINECOMBINATION_H
