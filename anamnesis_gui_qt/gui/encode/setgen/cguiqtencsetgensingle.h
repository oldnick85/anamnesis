#ifndef CGUIQTENCSETGENSINGLE_H
#define CGUIQTENCSETGENSINGLE_H

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>

#include "../../cguiqtcommon.h"
#include "../select/setgen/csetgensingle.h"

/**
 * @brief CGuiQtEncSetgenSingle - класс состояния ввода одиночного генератора множества
 */
class CGuiQtEncSetgenSingle
        : public QObject
        , public CGuiQtCommon
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtEncSetgenSingle - конструктор класса состояния ввода одиночного генератора множества
     * @param main_window - главное окно
     */
    CGuiQtEncSetgenSingle(QMainWindow* main_window);
    /**
     * @brief GetSetgen - получить генератор множества
     * @return генератор множества
     */
    ISetgenPtr GetSetgen() {return m_setgen_single;}
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
    std::array<QLineEdit*, 10>  m_edt_variant = {nullptr};

    CSetgenSinglePtr        m_setgen_single = nullptr;
};

#endif // CGUIQTENCSETGENSINGLE_H
