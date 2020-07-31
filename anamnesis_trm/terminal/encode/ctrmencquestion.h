#ifndef CTRMENCQUESTION_H
#define CTRMENCQUESTION_H

#include "common.h"
#include "ctrmio.h"
#include "../select/variant/csetcomb.h"
#include "setgen/ctrmencsetgen.h"
#include "combine/ctrmenccombine.h"

/*!
 * \brief ITrmEncQuestionHandler - интерфейс обработчика состояний терминала добавления вопроса
 */
class ITrmEncQuestionHandler
{
public:
    virtual ~ITrmEncQuestionHandler() = default;
    /*!
     * \brief Start - начало работы
     */
    virtual void Start() = 0;
    /*!
     * \brief Init - инициализация
     */
    virtual void Init() = 0;
    /*!
     * \brief SetDescription - установка описания вопроса
     */
    virtual void SetDescription() = 0;
    /*!
     * \brief SetGenerator - установка генератора
     */
    virtual void SetGenerator() = 0;
    /*!
     * \brief SetCombinator - установка комбинатора
     */
    virtual void SetCombinator() = 0;
    /*!
     * \brief SetAnswer - установка ответа
     */
    virtual void SetAnswer() = 0;
};

/*!
 * \brief CTrmEncQuestionStateMashine - машина состояний терминала добавления вопроса
 */
class CTrmEncQuestionStateMashine
        : public IStateMashine
{
public:
    /*!
     * \brief CTrmEncPassStateMashine - конструктор машины состояний терминала добавления вопроса
     * \param callback - указатель на интерфейс обработчика состояний, которому будет передаваться управление
     */
    CTrmEncQuestionStateMashine(ITrmEncQuestionHandler* callback);
    virtual ~CTrmEncQuestionStateMashine() override = default;

private:
    enum enState
    {
        stStart,
        stEnd,
        stInit,
        stSetDescription,
        stSetGenerator,
        stSetCombinator,
        stSetAnswer,
    };

    enState                 	m_state = stStart;
    ITrmEncQuestionHandler*     m_callback = nullptr;

public:
    /*!
     * \brief SetStateStart - установка состояния начала работы
     */
    void SetStateStart() {m_state = stStart;}
    /*!
     * \brief SetStateEnd - установка состояния завершения работы
     */
    void SetStateEnd() {m_state = stEnd;}
    /*!
     * \brief SetStateInit - установка состояния инициализации
     */
    void SetStateInit() {m_state = stInit;}
    /*!
     * \brief SetStateSetDescription - установка состояния задания описания вопроса
     */
    void SetStateSetDescription() {m_state = stSetDescription;}
    /*!
     * \brief SetStateSetGenerator - установка состояния задания генератора
     */
    void SetStateSetGenerator() {m_state = stSetGenerator;}
    /*!
     * \brief SetStateSetCombinator - установка состояния задания комбинатора
     */
    void SetStateSetCombinator() {m_state = stSetCombinator;}
    /*!
     * \brief SetStateSetAnswer - установка состояния задания ответа
     */
    void SetStateSetAnswer() {m_state = stSetAnswer;}
private:
    void Mashine()
    {
        while (true)
        {
            switch (m_state)
            {
            case stStart:           m_callback->Start();            break;
            case stInit:            m_callback->Init();             break;
            case stSetDescription:  m_callback->SetDescription();   break;
            case stSetGenerator:    m_callback->SetGenerator();     break;
            case stSetCombinator:   m_callback->SetCombinator();    break;
            case stSetAnswer:       m_callback->SetAnswer();        break;
            case stEnd:             return;
            }
        }
    }
public:
    /*!
     * \brief Begin - запуск машины состояний
     */
    virtual void Begin() override final {Mashine();}
};

/*! *********************************************************************************
 * \brief CTrmEncQuestion - класс терминала добавления вопроса
 *
 * Машина состояний терминала добавления вопроса:
 * \dot
 * digraph state_machine_pass {
 *   start	[label="Start"];
 *	 end	[label="End"];
 *	 init	[label="Init"];
 *	 set_d	[label="Set description"];
 *	 set_g	[label="Set generator"];
 *	 set_c	[label="Set combinator"];
 *	 set_a	[label="Set answer"];
 *
 *   start	->	init
 *   init	->	set_d
 *   set_d  ->  set_g
 *   set_g  ->  set_c
 *   set_c  ->  set_a
 *   set_a  ->  end
 * }
 * \enddot
 **********************************************************************************/
class CTrmEncQuestion
        : public ITrmEncQuestionHandler
        , public CTrmEncQuestionStateMashine
        , private CTrmIO
{
public:
    CTrmEncQuestion();
    // ITrmEncQuestionHandler
    virtual void Start() override final;
    virtual void Init() override final;
    virtual void SetDescription() override final;
    virtual void SetGenerator() override final;
    virtual void SetCombinator() override final;
    virtual void SetAnswer() override final;
    /*!
     * \brief GetSetComb - получить генератор и комбинатор
     * \return класс-связка генератора и комбинатора
     */
    CSetCombPtr GetSetComb();
    /*!
     * \brief Valid - проверка на валидность данных
     * \return валидность
     */
    Result_t Valid() const;
private:
    CTrmEncSetgenPtr    m_trm_setgen = nullptr;
    CTrmEncCombinePtr   m_trm_comb = nullptr;
    CSetCombPtr         m_setcomb = nullptr;
};

using CTrmEncQuestionPtr = std::shared_ptr<CTrmEncQuestion>;

#endif // CTRMENCQUESTION_H
