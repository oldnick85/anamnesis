#ifndef CGUIDECODE_H
#define CGUIDECODE_H

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "common.h"
#include "../select/casket/ccasket.h"
#include "../resources/textresult.h"
#include "../cguiqtcommon.h"
#include "cguiqtdecquestion.h"

/**
 * @brief CGuiQtDecode - класс состояния декодирования пароля
 */
class CGuiQtDecode
        : public QObject
        , public CGuiQtCommon
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtDecode - конструктор класса состояния декодирования пароля
     * @param main_window - главное окно
     */
    CGuiQtDecode(QMainWindow* main_window);
public slots:
    /**
     * @brief onAnamnesisStateEnd - произошло завершение работы дочернего состояния
     */
    void onAnamnesisStateEnd(const enResultStateEnd result);
    /**
     * @brief onBtnAbortClick - нажатие на кнопку отмены
     */
    void onBtnAbortClick();
    /**
     * @brief onBtnOpenClick - нажатие на кнопку открытия файла
     */
    void onBtnOpenClick();
    /**
     * @brief onBtnNextClick - нажатие на кнопку перехода к следующему вопросу
     */
    void onBtnNextClick();
signals:
    /**
     * @brief AnamnesisStateEnd - сигнал завершения работы состояния
     */
    void AnamnesisStateEnd();
private:
    virtual void CreateWidgets() override final;
    virtual bool CheckProperties() override final;
    bool CheckPass() const;

    QLabel*             m_main_label = nullptr;
    QLabel*             m_lbl_status = nullptr;
    QPushButton*        m_btn_abort = nullptr;
    QPushButton*        m_btn_open = nullptr;
    QPushButton*        m_btn_next = nullptr;
    QListWidget*        m_lst_questions = nullptr;

    CCasketPtr          m_casket;
    int                 m_question_num = -1;
    CGuiQtDecQuestion*    m_question = nullptr;
};

#endif // CGUIQTDECODE_H
