#ifndef CGUIQTSETGENELEMENTDOUBLE_H
#define CGUIQTSETGENELEMENTDOUBLE_H

#include <QMainWindow>
#include <QComboBox>

#include "../select/setgen/csetgendouble.h"
#include "../widgets/cguiqtsetgenelement.h"

/**
 * @brief CGuiQtSetgenElementDouble - класс кастомного виджета для двойного генератора множества
 */
class CGuiQtSetgenElementDouble
        : public CGuiQtSetgenElement
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtSetgenElementDouble - конструктор класса кастомного виджета для двойного генератора множества
     * @param main_window - главное окно
     * @param setgen_double - двойной генератор множества
     * @param rect - область виджета
     */
    CGuiQtSetgenElementDouble(QMainWindow* main_window, CSetgenDoublePtr setgen_double, QRect rect);

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
    QComboBox*          m_cbx_variant_first;
    QComboBox*          m_cbx_variant_second;

    CSetgenDoublePtr      m_setgen_double;
    QRect               m_rect;
};

#endif // CGUIQTSETGENELEMENTDOUBLE_H
