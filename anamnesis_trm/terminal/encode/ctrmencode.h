#ifndef CTRMENCODE_H
#define CTRMENCODE_H

#include "common.h"
#include "ctrmio.h"

#include "ctrmencquestion.h"
#include "ctrmencpass.h"
#include "../select/casket/ccasket.h"
#include "../resources/textresult.h"

/*!
 * \brief ITrmEncodeHandler - интерфейс обработчика состояний терминала кодирования пароля
 */
class ITrmEncodeHandler
{
public:
	virtual ~ITrmEncodeHandler() = default;
    /*!
     * \brief Start - начало работы
     */
	virtual void Start() = 0;
    /*!
     * \brief Init - инициализация
     */
	virtual void Init() = 0;
    /*!
     * \brief Query - запрос следующего действия
     */
	virtual void Query() = 0;
    /*!
     * \brief AddQuest - добавление вопроса
     */
    virtual void AddQuest() = 0;
    /*!
     * \brief ShowQuestions - показ всех добавленных вопросов
     */
    virtual void ShowQuestions() = 0;
    /*!
     * \brief SetPass - задание пароля
     */
	virtual void SetPass() = 0;
    /*!
     * \brief Save - сохранение в файл
     */
	virtual void Save() = 0;
};

/*!
 * \brief CTrmEncodeStateMashine - машина состояний терминала кодирования пароля
 */
class CTrmEncodeStateMashine
        : public IStateMashine
{
public:
    /*!
     * \brief CTrmEncodeStateMashine - конструктор машины состояний терминала кодирования пароля
     * \param callback - обработчик состояний
     */
	CTrmEncodeStateMashine(ITrmEncodeHandler* callback)
		: m_callback(callback)
	{

	}
	virtual ~CTrmEncodeStateMashine() override = default;

private:
	enum enState
	{
        stStart,
        stEnd,
        stInit,
        stQuery,
        stAddQuest,
        stShowQuestions,
        stSetPass,
        stSave,
	};

	enState					m_state = stStart;
	ITrmEncodeHandler*		m_callback = nullptr;

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
     * \brief SetStateQuery - установить состояние запроса следующего действия
     */
	void SetStateQuery() {m_state = stQuery;}
    /*!
     * \brief SetStateAddQuest - установить состояние добавления вопроса
     */
	void SetStateAddQuest() {m_state = stAddQuest;}
    /*!
     * \brief SetStateShowQuestions - установить состояние демонстрации добавленных вопросов
     */
    void SetStateShowQuestions() {m_state = stShowQuestions;}
    /*!
     * \brief SetStateSetPass - установить состояние задания пароля
     */
	void SetStateSetPass() {m_state = stSetPass;}
    /*!
     * \brief SetStateSave - установить состояние сохранения в файл
     */
	void SetStateSave() {m_state = stSave;}
private:
	void Mashine()
	{
        while (true)
		{
            switch (m_state)
            {
            case stStart:           m_callback->Start();            break;
            case stInit:            m_callback->Init();             break;
            case stQuery:           m_callback->Query();            break;
            case stAddQuest:        m_callback->AddQuest();         break;
            case stShowQuestions:   m_callback->ShowQuestions();    break;
            case stSetPass:         m_callback->SetPass();          break;
            case stSave:            m_callback->Save();             break;
            case stEnd:             return;
            }
		}
	}
public:
	virtual void Begin() override final {Mashine();}
};

/*! **********************************************************************************
 * \brief CTerminalEncode - класс кодирования пароля
 *
 * Машина состояний кодирования:
 * \dot
 * digraph state_machine_encode {
 *   start	[label="Start"];
 *	 end	[label="End"];
 *	 init	[label="Init"];
 *	 query	[label="Query"];
 *	 add	[label="Add question"];
 *   shw    [label="Show questions"];
 *	 setp	[label="Set password"];
 *	 save	[label="Save file"];
 *
 *   start	->	init
 *   init	->	query
 *   query	->	end
 *   query	->	add
 *   add	->	query
 *   query  ->  shw
 *   shw    ->  query
 *   query	->	setp
 *   setp	->	query
 *   query	->	save
 *   save	->	query
 *   save	->	end
 * }
 * \enddot
 ***********************************************************************************/

class CGuiEncode
		: public ITrmEncodeHandler
		, public CTrmEncodeStateMashine
        , private CTrmIO
{
public:
    CGuiEncode();
    virtual ~CGuiEncode() override = default;
protected:
	virtual void Start() override final;
	virtual void Init() override final;
	virtual void Query() override final;
    virtual void AddQuest() override final;
    virtual void ShowQuestions() override final;
	virtual void SetPass() override final;
	virtual void Save() override final;
private:
    CCasketPtr MakeCasket() const;
    void ShowStatus() const;

    std::list<CTrmEncQuestionPtr>   m_trm_questions;
    CTrmEncPassPtr                  m_trm_pass = nullptr;
};

#endif // CTRMENCODE_H
