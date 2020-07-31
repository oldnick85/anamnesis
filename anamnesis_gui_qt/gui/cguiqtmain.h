#ifndef CGUIQTMAIN_H
#define CGUIQTMAIN_H

#include <QObject>
#include <QCoreApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "../common.h"
#include "encode/cguiqtencode.h"
#include "decode/cguiqtdecode.h"

/**
 * @brief CGuiQtMain - класс начального состояния
 */
class CGuiQtMain
        : public QObject
        , public CGuiQtCommon
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtMain - конструктор класса начального состояния
     * @param main_window - главное окно
     */
    CGuiQtMain(QMainWindow* main_window);
    virtual ~CGuiQtMain() override = default;

    virtual void Begin() override;
public slots:
    /**
     * @brief onAnamnesisStateEnd - произошло завершение работы дочернего состояния
     */
    void onAnamnesisStateEnd();
    /**
     * @brief onBtnEncodeClick - нажата кнопка кодирования пароля
     */
    void onBtnEncodeClick();
    /**
     * @brief onBtnDecodeClick - нажата кнопка декодирования пароля
     */
    void onBtnDecodeClick();
private:
    virtual void CreateWidgets() override final;

    QLabel*         m_main_label;
    QPushButton*    m_btn_encode;
    QPushButton*    m_btn_decode;

    CGuiQtEncode*     m_gui_encode;
    CGuiQtDecode*     m_gui_decode;
};

#endif // CGUIQTMAIN_H
