#ifndef CGUIQTENCPASS_H
#define CGUIQTENCPASS_H

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>

#include "../select/pass/cpass.h"
#include "../cguiqtcommon.h"

/**
 * @brief CGuiQtEncPass - класс состояния запроса пароля
 */
class CGuiQtEncPass
        : public QObject
        , public CGuiQtCommon
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtEncPass - конструктор класса состояния запроса пароля
     * @param main_window - главное окно
     */
    CGuiQtEncPass(QMainWindow* main_window);
    /**
     * @brief GetPass - получить пароль
     * @return класс пароля
     */
    CPassPtr GetPass() {return m_pass;}
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
     * @brief onEdtChange - изменение поля для ввода пароля
     */
    void onEdtChange();
    /**
     * @brief onChkSymbClick_upper_case - изменен чекбокс включения заглавных букв в набор символов
     * @param checked - статус чекбокса
     */
    void onChkSymbClick_upper_case(const bool checked);
    /**
     * @brief onChkSymbClick_lower_case - изменен чекбокс включения строчных букв в набор символов
     * @param checked - статус чекбокса
     */
    void onChkSymbClick_lower_case(const bool checked);
    /**
     * @brief onChkSymbClick_digits - изменен чекбокс включения цифр в набор символов
     * @param checked - статус чекбокса
     */
    void onChkSymbClick_digits(const bool checked);
    /**
     * @brief onChkSymbClick_minus - изменен чекбокс включения минуса в набор символов
     * @param checked - статус чекбокса
     */
    void onChkSymbClick_minus(const bool checked);
    /**
     * @brief onChkSymbClick_underline - изменен чекбокс включения подчеркивания в набор символов
     * @param checked - статус чекбокса
     */
    void onChkSymbClick_underline(const bool checked);
    /**
     * @brief onChkSymbClick_space - изменен чекбокс включения пробела в набор символов
     * @param checked - статус чекбокса
     */
    void onChkSymbClick_space(const bool checked);
    /**
     * @brief onChkSymbClick_special - изменен чекбокс включения специальных знаков в набор символов
     * @param checked - статус чекбокса
     */
    void onChkSymbClick_special(const bool checked);
    /**
     * @brief onChkSymbClick_brackets - изменен чекбокс включения скобок в набор символов
     * @param checked - статус чекбокса
     */
    void onChkSymbClick_brackets(const bool checked);
signals:
    /**
     * @brief AnamnesisStateEnd - сигнал завершения работы состояния
     */
    void AnamnesisStateEnd();
private:
    virtual void CreateWidgets() override final;
    virtual bool CheckProperties() override final;
    CPass::sSymbolClass SymbolsFromCheckboxes();

    QLabel*         m_lbl_main = nullptr;
    QLabel*         m_lbl_status = nullptr;
    QPushButton*    m_btn_abort = nullptr;
    QPushButton*    m_btn_done = nullptr;
    QLineEdit*      m_edt_pass = nullptr;
    QCheckBox*      m_chk_symb_upper_case = nullptr;
    QCheckBox*      m_chk_symb_lower_case = nullptr;
    QCheckBox*      m_chk_symb_digits = nullptr;
    QCheckBox*      m_chk_symb_minus = nullptr;
    QCheckBox*      m_chk_symb_underline = nullptr;
    QCheckBox*      m_chk_symb_space = nullptr;
    QCheckBox*      m_chk_symb_special = nullptr;
    QCheckBox*      m_chk_symb_brackets = nullptr;

    CPassPtr        m_pass;
};

#endif // CGUIQTENCPASS_H
