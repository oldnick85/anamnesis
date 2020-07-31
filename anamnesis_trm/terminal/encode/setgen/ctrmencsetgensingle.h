#ifndef CTRMENCSETGENSINGLE_H
#define CTRMENCSETGENSINGLE_H

#include "common.h"
#include "../resources/textresult.h"
#include "../select/setgen/csetgensingle.h"
#include "ctrmio.h"
#include "ctrmio_setgensingle.h"

/*!
 * \brief ITrmEncSetgenSingleHandler - интерфейс обработчика состояний терминала задания одиночного генератора множества для кодирования пароля
 */
class ITrmEncSetgenSingleHandler
{
public:
    virtual ~ITrmEncSetgenSingleHandler() = default;
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
     * \brief Add - добавить вариант
     */
    virtual void Add() = 0;
    /*!
     * \brief Del - удалить вариант
     */
    virtual void Del() = 0;
    /*!
     * \brief Show - показать варианты
     */
    virtual void Show() = 0;
    /*!
     * \brief SetDesc - задать описание
     */
    virtual void SetDesc() = 0;
    /*!
     * \brief Abort - прервать задание одиночного генератора
     */
    virtual void Abort() = 0;
};

/*!
 * \brief CTrmEncSetgenSingleStateMashine - машина состояний терминала задания одиночного генератора множества для кодирования пароля
 */
class CTrmEncSetgenSingleStateMashine
        : public IStateMashine
{
public:
    /*!
     * \brief CTrmEncSetgenSingleStateMashine - конструктор машины состояний терминала задания одиночного генератора множества для кодирования пароля
     * \param callback - интерфейс обработчика состояний
     */
    CTrmEncSetgenSingleStateMashine(ITrmEncSetgenSingleHandler* callback);
    virtual ~CTrmEncSetgenSingleStateMashine() override = default;

private:
    enum enState
    {
        stStart,
        stEnd,
        stAbort,
        stInit,
        stQuery,
        stAddVar,
        stDelVar,
        stSetDesc,
        stShow,
    };

    enState						m_state = stStart;
    ITrmEncSetgenSingleHandler*	m_callback = nullptr;

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
     * \brief SetStateAbort - установить состояние прерывания задания одиночного генератора
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
     * \brief SetStateAddVar - установить состояние добавления варианта
     */
    void SetStateAddVar() {m_state = stAddVar;}
    /*!
     * \brief SetStateDelVar - установить состояние удаления варианта
     */
    void SetStateDelVar() {m_state = stDelVar;}
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
            case stStart:       m_callback->Start();        break;
            case stAbort:       m_callback->Abort();        break;
            case stInit:        m_callback->Init();         break;
            case stQuery:       m_callback->Query();        break;
            case stAddVar:      m_callback->Add();          break;
            case stDelVar:      m_callback->Del();          break;
            case stSetDesc:     m_callback->SetDesc();      break;
            case stShow:        m_callback->Show();         break;
            case stEnd:         return;
            }
        }
    }
public:
    virtual void Begin() override final {Mashine();}
};

/*! *********************************************************************************
 * \brief CTrmEncSetgenSingle - класс терминала установки одиночного генератора множества
 *
 * Машина состояний терминала установки генератора вариантов:
 * \dot
 * digraph state_machine_setgen_single {
 *   start	[label="Start"];
 *	 end	[label="End"];
 *   abort	[label="Abort"];
 *	 init	[label="Init"];
 *	 query	[label="Query"];
 *	 add	[label="Add variant"];
 *	 del	[label="Del variant"];
 *	 setd	[label="Set description"];
 *	 show	[label="Show variants"];
 *
 *   start	->	init
 *   init	->	query
 *	 query  ->  init
 *   query	->	end
 *   query	->	add
 *   query	->	show
 *   show   ->  query
 *   add	->	query
 *   query	->	setd
 *   setd	->	query
 *   query	->	del
 *   del	->	query
 *   query  ->  abort
 *   abort  ->  end
 * }
 * \enddot
 **********************************************************************************/

class CTrmEncSetgenSingle
        : public ITrmEncSetgenSingleHandler
        , public CTrmEncSetgenSingleStateMashine
        , public ITrmEncSetgen
        , private CTrmIO
        , private CTrmIO_SetgenSingle
{
public:
    CTrmEncSetgenSingle();
    /*!
     * \brief CTrmEncSetgenSingle - конструктор терминала установки одиночного генератора множества
     * \param setgen_single - одиночный генератор множества
     */
    CTrmEncSetgenSingle(CSetgenSinglePtr setgen_single);
    virtual ~CTrmEncSetgenSingle() override = default;
    // ITrmSetgen
    virtual Result_t ParseSample(const std::string &str, uint64 &value) const override;
    // ITrmEncSetgen
    virtual ISetgenPtr GetSetgen() override final;
    virtual Result_t Valid() const override final;
    virtual std::string SampleHint() const override final;
    /*!
     * \brief GetSetgenSingle - получить одиночный генератор множества
     * \return одиночный генератор множества
     */
    CSetgenSinglePtr GetSetgenSingle() {return m_setgen_single;}

protected:
    virtual void Start() override final;
    virtual void Init() override final;
    virtual void Query() override final;
    virtual void Add() override final;
    virtual void Del() override final;
    virtual void Show() override final;
    virtual void SetDesc() override final;
    virtual void Abort() override final;

private:
    void ShowStatus() const;
    void ShowDescription() const;
    void ShowVariants() const;
    void Done();

    CSetgenSinglePtr    m_setgen_single = nullptr;
};

using CTrmEncSetgenSinglePtr = std::shared_ptr<CTrmEncSetgenSingle>;

#endif // CTRMENCSETGENSINGLE_H
