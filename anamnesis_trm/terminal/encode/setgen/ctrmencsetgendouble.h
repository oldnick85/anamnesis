#ifndef CTRMENCSETGENDOUBLE_H
#define CTRMENCSETGENDOUBLE_H

#include "common.h"
#include "../resources/textresult.h"
#include "../select/setgen/csetgendouble.h"
#include "ctrmio.h"
#include "ctrmio_setgendouble.h"

/*!
 * \brief ITrmEncSetgenDoubleHandler - интерфейс обработчика состояний терминала задания двойного генератора множества для кодирования пароля
 */
class ITrmEncSetgenDoubleHandler
{
public:
    virtual ~ITrmEncSetgenDoubleHandler() = default;
    /*!
     * \brief Start - начало работы
     */
    virtual void Start() = 0;
    /*!
     * \brief Init - инициализация
     */
    virtual void Init() = 0;
    /*!
     * \brief Query - запрос действия
     */
    virtual void Query() = 0;
    /*!
     * \brief AddFirst - добавить вариант
     */
    virtual void AddFirst() = 0;
    /*!
     * \brief DelFirst - удалить вариант
     */
    virtual void DelFirst() = 0;
    /*!
     * \brief AddSecond - добавить вариант
     */
    virtual void AddSecond() = 0;
    /*!
     * \brief DelSecond - удалить вариант
     */
    virtual void DelSecond() = 0;
    /*!
     * \brief SetDesc - задать описание
     */
    virtual void SetDesc() = 0;
    /*!
     * \brief Show - показать варианты
     */
    virtual void Show() = 0;
    /*!
     * \brief Abort - прервать задание двойного генератора
     */
    virtual void Abort() = 0;
};

/*!
 * \brief CTrmEncSetgenDoubleStateMashine - машина состояний терминала задания двойного генератора множества для кодирования пароля
 */
class CTrmEncSetgenDoubleStateMashine
        : public IStateMashine
{
public:
    /*!
     * \brief CTrmEncSetgenDoubleStateMashine - конструктор машины состояний терминала задания двойного генератора множества для кодирования пароля
     * \param callback - интерфейс обработчика состояний
     */
    CTrmEncSetgenDoubleStateMashine(ITrmEncSetgenDoubleHandler* callback);
    virtual ~CTrmEncSetgenDoubleStateMashine() override = default;

private:
    enum enState
    {
        stStart,
        stEnd,
        stAbort,
        stInit,
        stQuery,
        stAddVarFirst,
        stDelVarFirst,
        stAddVarSecond,
        stDelVarSecond,
        stSetDesc,
        stShow,
    };

    enState						m_state = stStart;
    ITrmEncSetgenDoubleHandler*	m_callback = nullptr;

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
     * \brief SetStateAbort - установить состояние прерывания задания двойного генератора
     */
    void SetStateAbort() {m_state = stAbort;}
    /*!
     * \brief SetStateInit - установить состояние инициализации
     */
    void SetStateInit() {m_state = stInit;}
    /*!
     * \brief SetStateQuery - установить состояние запроса действия
     */
    void SetStateQuery() {m_state = stQuery;}
    /*!
     * \brief SetStateAddVarFirst - установить состояние добавления варианта
     */
    void SetStateAddVarFirst() {m_state = stAddVarFirst;}
    /*!
     * \brief SetStateDelVarFirst - установить состояние удаления варианта
     */
    void SetStateDelVarFirst() {m_state = stDelVarFirst;}
    /*!
     * \brief SetStateAddVarSecond - установить состояние добавления варианта
     */
    void SetStateAddVarSecond() {m_state = stAddVarSecond;}
    /*!
     * \brief SetStateDelVarSecond - установить состояние удаления варианта
     */
    void SetStateDelVarSecond() {m_state = stDelVarSecond;}
    /*!
     * \brief SetStateSetDesc - установить состояние задания описание
     */
    void SetStateSetDesc() {m_state = stSetDesc;}
    /*!
     * \brief SetStateShow - установить состояние показа вариантов
     */
    void SetStateShow() {m_state = stShow;}
private:
    void Mashine()
    {
        while (true)
        {
            switch (m_state)
            {
            case stStart:           m_callback->Start();        break;
            case stAbort:           m_callback->Abort();        break;
            case stInit:            m_callback->Init();         break;
            case stQuery:           m_callback->Query();        break;
            case stAddVarFirst:     m_callback->AddFirst();     break;
            case stDelVarFirst:     m_callback->DelFirst();     break;
            case stAddVarSecond:    m_callback->AddSecond();    break;
            case stDelVarSecond:    m_callback->DelSecond();    break;
            case stSetDesc:         m_callback->SetDesc();      break;
            case stShow:            m_callback->Show();         break;
            case stEnd:             return;
            }
        }
    }
public:
    virtual void Begin() override final {Mashine();}
};

/*! *********************************************************************************
 * \brief CTrmEncSetgenDouble - класс терминала установки двойного генератора множества
 *
 * Машина состояний терминала установки генератора вариантов:
 * \dot
 * digraph state_machine_setgen_Double {
 *   start	[label="Start"];
 *	 end	[label="End"];
 *   abort	[label="Abort"];
 *	 init	[label="Init"];
 *	 query	[label="Query"];
 *	 add_f	[label="Add variant first"];
 *	 del_f	[label="Del variant first"];
 *	 add_s	[label="Add variant second"];
 *	 del_s	[label="Del variant second"];
 *	 setd	[label="Set description"];
 *   show	[label="Show variants"];
 *
 *   start	->	init
 *   init	->	query
 *	 query  ->  init
 *   query	->	end
 *   query	->	add_f
 *   query	->	add_s
 *   add_f	->	query
 *   add_s	->	query
 *   query	->	setd
 *   setd	->	query
 *   query	->	del_f
 *   query	->	del_s
 *   del_f	->	query
 *   del_s	->	query
 *   query  ->  abort
 *   abort  ->  end
 *   query	->	show
 *   show	->	query
 * }
 * \enddot
 **********************************************************************************/

class CTrmEncSetgenDouble
        : public ITrmEncSetgenDoubleHandler
        , public CTrmEncSetgenDoubleStateMashine
        , public ITrmEncSetgen
        , private CTrmIO
        , private CTrmIO_SetgenDouble
{
public:
    CTrmEncSetgenDouble();
    /*!
     * \brief CTrmEncSetgenDouble - конструктор терминала установки двойного генератора множества
     * \param setgen_double - двойной генератор множества
     */
    CTrmEncSetgenDouble(CSetgenDoublePtr setgen_double);
    virtual ~CTrmEncSetgenDouble() override = default;
    // ITrmSetgen
    virtual Result_t ParseSample(const std::string &str, uint64 &value) const override;
    // ITrmEncSetgen
    virtual ISetgenPtr GetSetgen() override final;
    virtual Result_t Valid() const override final;
    virtual std::string SampleHint() const override final;
    /*!
     * \brief GetSetgenDouble - получить двойной генератор множества
     * \return двойной генератор множества
     */
    CSetgenDoublePtr GetSetgenDouble() {return m_setgen_double;}

protected:
    virtual void Start() override final;
    virtual void Init() override final;
    virtual void Query() override final;
    virtual void AddFirst() override final;
    virtual void DelFirst() override final;
    virtual void AddSecond() override final;
    virtual void DelSecond() override final;
    virtual void SetDesc() override final;
    virtual void Abort() override final;
    virtual void Show() override final;

private:
    void ShowStatus() const;
    void ShowDescription() const;
    void ShowFirst() const;
    void ShowSecond() const;
    void Done();

    CSetgenDoublePtr    m_setgen_double = nullptr;
};

using CTrmEncSetgenDoublePtr = std::shared_ptr<CTrmEncSetgenDouble>;

#endif // CTRMENCSETGENDOUBLE_H
