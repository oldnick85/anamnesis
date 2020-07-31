#ifndef CGUIQTCOMMON_H
#define CGUIQTCOMMON_H

#include <QMainWindow>
#include "../common.h"

/**
 * @brief CGuiQtCommon - класс состояния главного окна
 */
class CGuiQtCommon
{
public:
    /**
     * @brief CGuiQtCommon - конструктор класса состояния главного окна
     * @param main_window - главное окно
     */
    CGuiQtCommon(QMainWindow* main_window);
    virtual ~CGuiQtCommon() = default;
    /**
     * @brief Begin - передача управления новому состоянию
     */
    virtual void Begin();
protected:
    /**
     * @brief CreateWidgets - создать виджеты
     */
    virtual void CreateWidgets() = 0;
    /**
     * @brief ShowWidgets - отобразить виджеты
     */
    virtual void ShowWidgets();
    /**
     * @brief HideWidgets - скрыть виджеты
     */
    virtual void HideWidgets();
    /**
     * @brief CheckProperties - проверка и установка свойств виджетов
     * @return готовность состояния
     */
    virtual bool CheckProperties() {return false;}
    /**
     * @brief AddWidget - добавить новый виджет в список обработки
     * @param widget - виджет
     */
    void AddWidget(QWidget* widget);

    QMainWindow*            m_main_window = nullptr;    ///< главное окно
private:
    std::list<QWidget*>     m_widgets;
};

#endif // CGUIQTCOMMON_H
