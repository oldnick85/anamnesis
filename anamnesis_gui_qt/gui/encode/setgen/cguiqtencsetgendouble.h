#ifndef CGUIQTENCSETGENDouble_H
#define CGUIQTENCSETGENDouble_H

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>

#include "../../cguiqtcommon.h"
#include "../select/setgen/csetgendouble.h"

/**
 * @brief CGuiQtEncSetgenDouble - класс состояния ввода двойного генератора множества
 */
class CGuiQtEncSetgenDouble
        : public QObject
        , public CGuiQtCommon
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtEncSetgenDouble - конструктор класса состояния ввода двойного генератора множества
     * @param main_window - главное окно
     */
    CGuiQtEncSetgenDouble(QMainWindow* main_window);
    /**
     * @brief GetSetgen - получить генератор множества
     * @return генератор множества
     */
    ISetgenPtr GetSetgen() {return m_setgen_double;}
public slots:
    /**
     * @brief onBtnAbortClick - нажатие на кнопку отмены
     */
    void onBtnAbortClick();
    /**
     * @brief onBtnDoneClick - нажатие на кнопку завершения
     */
    void onBtnDoneClick();
    /**
     * @brief onEdtChange - изменение поля описания генератора
     */
    void onEdtChange();
signals:
    /**
     * @brief AnamnesisStateEnd - сигнал завершения работы состояния
     */
    void AnamnesisStateEnd();
private:
    virtual void CreateWidgets() override final;
    virtual bool CheckProperties() override final;

    QLabel*                     m_lbl_main = nullptr;
    QLabel*                     m_lbl_status = nullptr;
    QPushButton*                m_btn_abort = nullptr;
    QPushButton*                m_btn_done = nullptr;
    QLineEdit*                  m_edt_description = nullptr;
    std::array<QLineEdit*, 10>  m_edt_variant_bank1 = {nullptr};
    std::array<QLineEdit*, 10>  m_edt_variant_bank2 = {nullptr};

    CSetgenDoublePtr            m_setgen_double = nullptr;
};

#endif // CGUIQTENCSETGENDouble_H
