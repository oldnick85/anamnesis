#ifndef CGUIQTENCQUESTION_H
#define CGUIQTENCQUESTION_H

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "../select/variant/csetcomb.h"
#include "../cguiqtcommon.h"
#include "combine/cguiqtenccombine.h"
#include "setgen/cguiqtencsetgen.h"

/**
 * @brief CGuiQtEncQuestion - класс состояния ввода вопроса
 */
class CGuiQtEncQuestion
        : public QObject
        , public CGuiQtCommon
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtEncQuestion - конструктор класса состояния ввода вопроса
     * @param main_window - главное окно
     */
    CGuiQtEncQuestion(QMainWindow* main_window);
    /**
     * @brief GetSetcomb - получить вопрос
     * @return вопрос
     */
    CSetCombPtr GetSetcomb() {return m_setcomb;}
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
     * @brief onEdtChange - изменение поля с описанием вопроса
     */
    void onEdtChange();
    /**
     * @brief onBtnSetgenAddClick - нажатие на кнопку добавления генератора множества
     */
    void onBtnSetgenAddClick();
    /**
     * @brief onBtnCombineAddClick - нажатие на кнопку добавления комбинатора
     */
    void onBtnCombineAddClick();
signals:
    /**
     * @brief AnamnesisStateEnd - сигнал завершения работы состояния
     */
    void AnamnesisStateEnd();
private:
    virtual void CreateWidgets() override final;
    virtual bool CheckProperties() override final;

    QLabel*             m_lbl_main = nullptr;
    QLabel*             m_lbl_status = nullptr;
    QPushButton*        m_btn_abort = nullptr;
    QPushButton*        m_btn_done = nullptr;
    QPushButton*        m_btn_setgen_add = nullptr;
    QPushButton*        m_btn_combine_add = nullptr;
    QLineEdit*          m_edt_description = nullptr;

    CGuiQtEncCombine*     m_gui_enc_combine = nullptr;
    CGuiQtEncSetgen*      m_gui_enc_setgen = nullptr;
    CSetCombPtr         m_setcomb = nullptr;
};

#endif // CGUIQTENCQUESTION_H
