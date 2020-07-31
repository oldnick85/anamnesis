#ifndef CGUIQTENCCOMBINE_H
#define CGUIQTENCCOMBINE_H

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>

#include "../select/select_common.h"
#include "../../cguiqtcommon.h"
#include "cguiqtenccombinecombination.h"
#include "cguiqtenccombinepermutation.h"

/**
 * @brief CGuiQtEncCombine - класс состояния выбора типа комбинатора для кодирования пароля
 */
class CGuiQtEncCombine
        : public QObject
        , public CGuiQtCommon
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtEncCombine - класс состояния выбора типа комбинатора для кодирования пароля
     * @param main_window - главное окно
     * @param setgen - генератор множества
     */
    CGuiQtEncCombine(QMainWindow* main_window, ISetgenPtr setgen);
    /**
     * @brief GetCombine - получить комбинатор множества
     * @return комбинатор множества
     */
    ICombinePtr GetCombine() const {return m_combine;}
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
     * @brief onBtnCombineCombinationClick - нажатие на кнопку выбора сочетания
     */
    void onBtnCombineCombinationClick();
    /**
     * @brief onBtnCombinePermutationClick - нажатие на кнопку выбора перестановки
     */
    void onBtnCombinePermutationClick();
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
    QPushButton*                m_btn_combine_combination = nullptr;
    QPushButton*                m_btn_combine_permutation = nullptr;

    CGuiQtEncCombineCombination*  m_gui_combine_combination = nullptr;
    CGuiQtEncCombinePermutation*  m_gui_combine_permutation = nullptr;
    ICombinePtr                 m_combine;
    ISetgenPtr                  m_setgen;
};

#endif // CGUIENCCOMBINE_H
