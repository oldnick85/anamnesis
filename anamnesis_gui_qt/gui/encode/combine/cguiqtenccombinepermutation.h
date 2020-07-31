#ifndef CGUIQTENCCOMBINEPERMUTATION_H
#define CGUIQTENCCOMBINEPERMUTATION_H

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

#include "../../cguiqtcommon.h"
#include "../select/combine/ccombinepermutation.h"
#include "../../widgets/cguiqtsetgenelementsingle.h"
#include "../../widgets/cguiqtsetgenelementdouble.h"

/**
 * @brief CGuiQtEncCombinePermutation - класс состояния ввода перестановки для кодирования пароля
 */
class CGuiQtEncCombinePermutation
        : public QObject
        , public CGuiQtCommon
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtEncCombinePermutation - конструктор класса состояния ввода перестановки для кодирования пароля
     * @param main_window - главное окно
     * @param setgen - генератор множества
     */
    CGuiQtEncCombinePermutation(QMainWindow *main_window, ISetgenPtr setgen);
    /**
     * @brief GetCombine - получить комбинатор множества
     * @return комбинатор множества
     */
    ICombinePtr GetCombine() const {return m_permutation;}
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
     * @brief onAnamnesisElementChanged - изменение кастомного виджета
     */
    void onAnamnesisElementChanged();
signals:
    /**
     * @brief AnamnesisStateEnd - сигнал завершения работы состояния
     */
    void AnamnesisStateEnd();
private:
    virtual void CreateWidgets() override final;
    virtual bool CheckProperties() override final;
    virtual void ShowWidgets() override final;
    virtual void HideWidgets() override final;

    QLabel*                             m_lbl_main = nullptr;
    QLabel*                             m_lbl_status = nullptr;
    QPushButton*                        m_btn_abort = nullptr;
    QPushButton*                        m_btn_done = nullptr;
    std::array<CGuiQtSetgenElement*, 10>  m_elt_setgen = {nullptr};

    CCombinePermutationPtr              m_permutation;
    ISetgenPtr                          m_setgen;
};

#endif // CGUIWTENCCOMBINEPERMUTATION_H
