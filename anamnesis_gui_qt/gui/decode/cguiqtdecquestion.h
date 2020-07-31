#ifndef CGUIQTDECQUESTION_H
#define CGUIQTDECQUESTION_H

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "../select/variant/csetcomb.h"
#include "../select/combine/ccombinecombination.h"
#include "../select/combine/ccombinepermutation.h"
#include "../cguiqtcommon.h"
#include "../widgets/cguiqtsetgenelementsingle.h"
#include "../widgets/cguiqtsetgenelementdouble.h"

/**
 * @brief CGuiQtDecQuestion - класс состояния ответа на вопрос
 */
class CGuiQtDecQuestion
        : public QObject
        , public CGuiQtCommon
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtDecQuestion - конструктор класса состояния ответа на вопрос
     * @param main_window - главное окно
     * @param setcomb - вопрос
     */
    CGuiQtDecQuestion(QMainWindow* main_window, CSetCombPtr setcomb);
    /**
     * @brief GetSetcomb - получить вопрос
     * @return вопрос
     */
    CSetCombPtr GetSetcomb() {return m_setcomb;}
public slots:
    /**
     * @brief onBtnAbortClick - нажатие на кнопку отмены
     */
    void onBtnAbortClick();
    /**
     * @brief onBtnAbortClick - нажатие на кнопку перехода к следующему вопросу
     */
    void onBtnNextClick();
    /**
     * @brief onAnamnesisElementChanged - изменился виджет генератора множества
     */
    void onAnamnesisElementChanged();
signals:
    /**
     * @brief AnamnesisStateEnd - сигнал завершения работы состояния
     */
    void AnamnesisStateEnd(const enResultStateEnd result);
private:
    virtual void CreateWidgets() override final;
    virtual bool CheckProperties() override final;
    virtual void ShowWidgets() override final;
    virtual void HideWidgets() override final;
    CGuiQtSetgenElement* MakeSetgenElement(const ISetgenPtr setgen, const QRect rect) const;

    QLabel*                             m_lbl_main = nullptr;
    QLabel*                             m_lbl_status = nullptr;
    QPushButton*                        m_btn_abort = nullptr;
    QPushButton*                        m_btn_next = nullptr;
    QLabel*                             m_lbl_description = nullptr;

    CSetCombPtr                         m_setcomb = nullptr;
    std::array<CGuiQtSetgenElement*, 10>  m_elt_setgen = {nullptr};

    CCombineCombinationPtr              m_combination = nullptr;
    CCombinePermutationPtr              m_permutation = nullptr;
};


#endif // CGUIQTDECQUESTION_H
