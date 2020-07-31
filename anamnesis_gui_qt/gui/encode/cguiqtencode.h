#ifndef CGUIQTENCODE_H
#define CGUIQTENCODE_H

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QFileDialog>

#include "common.h"
#include "cguiqtencpass.h"
#include "cguiqtencquestion.h"
#include "../select/casket/ccasket.h"
#include "../resources/textresult.h"
#include "../cguiqtcommon.h"

/**
 * @brief CGuiQtEncode - класс состояния кодирования пароля
 */
class CGuiQtEncode
        : public QObject
        , public CGuiQtCommon
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtEncode - конструктор класса состояния кодирования пароля
     * @param main_window - главное окно
     */
    CGuiQtEncode(QMainWindow* main_window);
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
     * @brief onBtnSaveClick - нажатие на кнопку сохранения закодированного пароля
     */
    void onBtnSaveClick();
    /**
     * @brief onBtnSetPassClick - нажатие на кнопку установки пароля
     */
    void onBtnSetPassClick();
    /**
     * @brief onBtnAddQuestionClick - нажатие на кнопку добавления вопроса
     */
    void onBtnAddQuestionClick();
signals:
    /**
     * @brief AnamnesisStateEnd - сигнал завершения работы состояния
     */
    void AnamnesisStateEnd();
private:
    virtual void CreateWidgets() override final;
    virtual bool CheckProperties() override final;
    void ShowStatus();
    std::string PasswordStatus() const;
    std::string QuestionsStatus() const;

    QLabel*             m_main_label = nullptr;
    QLabel*             m_lbl_status = nullptr;
    QPushButton*        m_btn_abort = nullptr;
    QPushButton*        m_btn_save = nullptr;
    QPushButton*        m_btn_set_pass = nullptr;
    QPushButton*        m_btn_add_question = nullptr;
    QListWidget*        m_lst_questions = nullptr;

    CCasketPtr          m_casket;
    CGuiQtEncPass*        m_gui_pass = nullptr;
    CGuiQtEncQuestion*    m_gui_question = nullptr;
};

#endif // CGUIQTENCODE_H
