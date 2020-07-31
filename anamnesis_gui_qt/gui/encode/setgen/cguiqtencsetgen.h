#ifndef CGUIQTENCSETGEN_H
#define CGUIQTENCSETGEN_H

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>

#include "../select/select_common.h"
#include "cguiqtencsetgensingle.h"
#include "cguiqtencsetgendouble.h"
#include "../../cguiqtcommon.h"

/**
 * @brief CGuiQtEncSetgen - класс состояния выбора типа генератора множества
 */
class CGuiQtEncSetgen
        : public QObject
        , public CGuiQtCommon
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtEncSetgen - конструктор класса состояния выбора типа генератора множества
     * @param main_window - главное окно
     */
    CGuiQtEncSetgen(QMainWindow* main_window);
    /**
     * @brief GetSetgen - получить генератор множества
     * @return генератор множества
     */
    ISetgenPtr GetSetgen() const {return m_setgen;}
public slots:
    /**
     * @brief onAnamnesisStateEnd - произошло завершение работы дочернего состояния
     */
    void onAnamnesisStateEnd();
    /**
     * @brief onBtnAbortClick - нажатие на кнопку отмены
     */
    void onBtnAbortClick();
    /**
     * @brief onBtnDoneClick - нажатие на кнопку завершения
     */
    void onBtnDoneClick();
    /**
     * @brief onBtnSetgenSingleClick - нажатие на кнопку выбора одиночного генератора
     */
    void onBtnSetgenSingleClick();
    /**
     * @brief onBtnSetgenDoubleClick - нажатие на кнопку выбора двойного генератора
     */
    void onBtnSetgenDoubleClick();
signals:
    /**
     * @brief AnamnesisStateEnd - сигнал завершения работы состояния
     */
    void AnamnesisStateEnd();
private:
    virtual void CreateWidgets() override final;
    virtual bool CheckProperties() override final;

    QLabel*                 m_lbl_main = nullptr;
    QLabel*                 m_lbl_status = nullptr;
    QPushButton*            m_btn_abort = nullptr;
    QPushButton*            m_btn_done = nullptr;
    QPushButton*            m_btn_setgen_single = nullptr;
    QPushButton*            m_btn_setgen_double = nullptr;

    CGuiQtEncSetgenSingle*    m_gui_setgen_single = nullptr;
    CGuiQtEncSetgenDouble*    m_gui_setgen_double = nullptr;
    ISetgenPtr              m_setgen;
};

#endif // CGUIQTENCSETGEN_H
