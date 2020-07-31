#ifndef CGUIQTSETGENELEMENTSINGLE_H
#define CGUIQTSETGENELEMENTSINGLE_H

#include <QMainWindow>
#include <QComboBox>

#include "../select/setgen/csetgensingle.h"
#include "cguiqtsetgenelement.h"

/**
 * @brief CGuiQtSetgenElementSingle - класс кастомного виджета для одиночного генератора множества
 */
class CGuiQtSetgenElementSingle
        : public CGuiQtSetgenElement
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtSetgenElementSingle - конструктор класса кастомного виджета для одиночного генератора множества
     * @param main_window - главное окно
     * @param setgen_single - одиночный генератор множества
     * @param rect - область виджета
     */
    CGuiQtSetgenElementSingle(QMainWindow* main_window, CSetgenSinglePtr setgen_single, QRect rect);

    virtual void Create() override final;
    virtual void Show() override final;
    virtual void Hide() override final;
    virtual bool Check() const override final;
    virtual uint64 Value() const override final;
public slots:
    /**
     * @brief onCurrentIndexChanged - изменение комбобокса
     */
    void onCurrentIndexChanged();
private:
    QComboBox*          m_cbx_variant;

    CSetgenSinglePtr    m_setgen_single;
    QRect               m_rect;
};

#endif // CGUIQTSETGENELEMENTSINGLE_H
