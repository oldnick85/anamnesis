#ifndef CTRMENCPASS_H
#define CTRMENCPASS_H

#include "common.h"
#include "../select/pass/cpass.h"
#include "ctrmio.h"
#include "../resources/textresult.h"

/*!
 * \brief ITrmEncPassHandler - интерфейс обработчика состояний терминала кодирования пароля
 */
class ITrmEncPassHandler
{
public:
    virtual ~ITrmEncPassHandler() = default;
    /*!
     * \brief Start - начало работы
     */
    virtual void Start() = 0;
    /*!
     * \brief Init - инициализация
     */
    virtual void Init() = 0;
    /*!
     * \brief AddSymb - добавление набора допустимых символов
     */
    virtual void AddSymb() = 0;
    /*!
     * \brief SetPass - установка пароля
     */
    virtual void SetPass() = 0;
};

/*!
 * \brief CTrmEncPassStateMashine - машина состояний терминала кодирования пароля
 */
class CTrmEncPassStateMashine
        : public IStateMashine
{
public:
    /*!
     * \brief CTrmEncPassStateMashine - конструктор машины состояний терминала кодирования пароля
     * \param callback - указатель на интерфейс обработчика состояний, которому будет передаваться управление
     */
    CTrmEncPassStateMashine(ITrmEncPassHandler* callback)
        : m_callback(callback)
    {

    }
    virtual ~CTrmEncPassStateMashine() override = default;

private:
    enum enState
    {
        stStart,
        stEnd,
        stInit,
        stAddSymb,
        stSetPass,
    };

    enState			m_state = stStart;
    ITrmEncPassHandler*            m_callback = nullptr;

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
     * \brief SetStateAddSymb - установка состояния добавления допустимых символов
     */
    void SetStateAddSymb() {m_state = stAddSymb;}
    /*!
     * \brief SetStateSetPass - установка состояния ввода пароля
     */
    void SetStateSetPass() {m_state = stSetPass;}
private:
    void Mashine()
    {
        while (true)
        {
            switch (m_state)
            {
            case stStart:       m_callback->Start();        break;
            case stInit:        m_callback->Init();         break;
            case stAddSymb:     m_callback->AddSymb();      break;
            case stSetPass:     m_callback->SetPass();      break;
            case stEnd:         return;
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
 * \brief CTrmPass - класс терминала установки пароля
 *
 * Машина состояний терминала установки пароля:
 * \dot
 * digraph state_machine_pass {
 *   start	[label="Start"];
 *	 end	[label="End"];
 *	 init	[label="Init"];
 *	 add_s	[label="Add symbols"];
 *	 set_p	[label="Set password"];
 *
 *   start	->	init
 *   init	->	add_s
 *   add_s	->	init
 *   add_s	->	add_s
 *   add_s	->	set_p
 *   add_s	->	end
 *   set_p  ->  init
 *   set_p  ->  set_p
 *   set_p  ->  end
 * }
 * \enddot
 **********************************************************************************/
class CTrmEncPass
        : public ITrmEncPassHandler
        , public CTrmEncPassStateMashine
        , private CTrmIO
{
public:
    CTrmEncPass();
    // ITrmPassHandler
    virtual void Start() override final;
    virtual void Init() override final;
    virtual void AddSymb() override final;
    virtual void SetPass() override final;
    /*!
     * \brief GetPass - получить класс пароля
     * \return класс-хранитель пароля
     */
    CPassPtr GetPass() {return m_pass;}
private:
    void ShowSymbols() const;

    CPassPtr        m_pass;
};

using CTrmEncPassPtr = std::shared_ptr<CTrmEncPass>;

#endif // CTRMENCPASS_H
