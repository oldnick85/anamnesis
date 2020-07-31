#ifndef CTRMDECODE_H
#define CTRMDECODE_H

#include "common.h"
#include "ctrmio.h"
#include "ctrmdecquestion.h"
#include "../select/casket/ccasket.h"

/*!
 * \brief ITrmDecodeHandler - интерфейс обработчика состояний терминала декодирования пароля
 */
class ITrmDecodeHandler
{
public:
    virtual ~ITrmDecodeHandler() = default;
    /*!
     * \brief Start - начало работы
     */
	virtual void Start() = 0;
    /*!
     * \brief Init - инициализация
     */
	virtual void Init() = 0;
    /*!
     * \brief Open - открытие файла
     */
	virtual void Open() = 0;
    /*!
     * \brief Answer - ответы на вопросы
     */
	virtual void Answer() = 0;
    /*!
     * \brief Result - выдача результата
     */
	virtual void Result() = 0;
};

/*!
 * \brief CTrmDecodeStateMashine - машина состояний обработчика состояний терминала декодирования пароля
 */
class CTrmDecodeStateMashine
        : public IStateMashine
{
public:
    /*!
     * \brief CTrmDecodeStateMashine - конструктор машины состояний обработчика состояний терминала декодирования пароля
     * \param callback - обработчик состояний
     */
    CTrmDecodeStateMashine(ITrmDecodeHandler* callback)
		: m_callback(callback)
	{

	}
    virtual ~CTrmDecodeStateMashine() override = default;

private:
	enum enState
	{
		stStart,
		stEnd,
		stInit,
		stOpen,
		stAnswer,
		stResult,
	};

    enState				m_state = stStart;
    ITrmDecodeHandler*  m_callback = nullptr;

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
     * \brief SetStateOpen - установить состояние открытия файла
     */
	void SetStateOpen() {m_state = stOpen;}
    /*!
     * \brief SetStateAnswer - установить состояние ответа на вопрос
     */
	void SetStateAnswer() {m_state = stAnswer;}
    /*!
     * \brief SetStateResult - установить состояние выдачи результата
     */
	void SetStateResult() {m_state = stResult;}
private:
	void Mashine()
	{
        while (true)
		{
            switch (m_state)
            {
            case stStart:       m_callback->Start();        break;
            case stInit:        m_callback->Init();         break;
            case stOpen:        m_callback->Open();         break;
            case stAnswer:      m_callback->Answer();       break;
            case stResult:      m_callback->Result();       break;
            case stEnd:         return;
            }
		}
	}
public:
	virtual void Begin() override final {Mashine();}
};

/*! ************************************************************************************
 * \brief CTrmDecode - класс декодирования пароля
 *
 * Машина состояний декодирования:
 * \dot
 * digraph state_machine_encode {
 *   start	[label="Start"];
 *	 end	[label="End"];
 *	 init	[label="Init"];
 *	 open	[label="Open"];
 *	 ans	[label="Answer questions"];
 *	 result	[label="Show password"];
 *
 *   start	->	init
 *   init	->	open
 *   open	->	ans
 *   open	->	end
 *   ans	->	result
 *   result	->	end
 * }
 * \enddot
 ************************************************************************************/

class CTrmDecode
        : public ITrmDecodeHandler
        , public CTrmDecodeStateMashine
        , private CTrmIO
{
public:
    CTrmDecode();
    virtual ~CTrmDecode() override = default;

private:
	virtual void Start() override final;
	virtual void Init() override final;
	virtual void Open() override final;
	virtual void Answer() override final;
	virtual void Result() override final;

    void ParseFile(const std::string &fname);
    void ShowError(const TRM_TXT_RES::enStringId str_id);

    CCasketPtr                      m_casket = nullptr;
    std::list<CTrmDecQuestionPtr>   m_trm_questions;
    //CTrmDecPassPtr                  m_trm_pass = nullptr;
};

#endif // CTRMDECODE_H
