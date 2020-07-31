#ifndef CTRMDECQUESTION_H
#define CTRMDECQUESTION_H

#include "common.h"
#include "ctrmio.h"
#include "../select/variant/csetcomb.h"
#include "setgen/ctrmdecsetgen.h"
#include "combine/ctrmdeccombine.h"

/*!
 * \brief ITrmDecQuestionHandler - интерфейс обработчика состояний терминала ответа на вопрос
 */
class ITrmDecQuestionHandler
{
public:
    virtual ~ITrmDecQuestionHandler() = default;
    /*!
     * \brief Start - начало работы
     */
    virtual void Start() = 0;
    /*!
     * \brief Init - инициализация
     */
    virtual void Init() = 0;
};

/*!
 * \brief CTrmDecQuestionStateMashine - машина состояний терминала ответа на вопрос
 */
class CTrmDecQuestionStateMashine
        : public IStateMashine
{
public:
    /*!
     * \brief CTrmEncPassStateMashine - конструктор машины состояний терминала ответа на вопрос
     * \param callback - указатель на интерфейс обработчика состояний, которому будет передаваться управление
     */
    CTrmDecQuestionStateMashine(ITrmDecQuestionHandler* callback);
    virtual ~CTrmDecQuestionStateMashine() override = default;

private:
    enum enState
    {
        stStart,
        stEnd,
        stInit,
    };

    enState                 	m_state = stStart;
    ITrmDecQuestionHandler*     m_callback = nullptr;

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

private:
    void Mashine()
    {
        while (true)
        {
            switch (m_state)
            {
            case stStart:           m_callback->Start();            break;
            case stInit:            m_callback->Init();             break;
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
 * \brief CTrmDecQuestion - класс терминала ответа на вопрос
 *
 * Машина состояний терминала ответа на вопрос:
 * \dot
 * digraph state_machine_pass {
 *   start	[label="Start"];
 *	 end	[label="End"];
 *	 init	[label="Init"];
 *
 *   start	->	init
 *   init	->	end
 * }
 * \enddot
 **********************************************************************************/

class CTrmDecQuestion
        : public ITrmDecQuestionHandler
        , public CTrmDecQuestionStateMashine
        , private CTrmIO
{
public:
    CTrmDecQuestion();
    /*!
     * \brief SetSetcomb - задать связку генератора и комбинатора
     * \param[in] setcomb - связка генератора и комбинатора
     * \return успех задания
     */
    bool SetSetcomb(CSetCombPtr setcomb);
    /*!
     * \brief Valid - проверка на валидность данных
     * \return валидность
     */
    Result_t Valid(const enPurpose purpose) const;
private:
    // ITrmDecQuestionHandler
    virtual void Start() override final;
    virtual void Init() override final;

    CSetCombPtr         m_setcomb = nullptr;
    CTrmDecSetgenPtr    m_trm_setgen = nullptr;
    CTrmDecCombinePtr   m_trm_combine = nullptr;
};

using CTrmDecQuestionPtr = std::shared_ptr<CTrmDecQuestion>;

#endif // CTRMDECQUESTION_H
