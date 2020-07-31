#include "cguiqtmain.h"

using namespace TRM_TXT_RES;

CGuiQtMain::CGuiQtMain(QMainWindow* main_window)
    : CGuiQtCommon(main_window)
{

}

void CGuiQtMain::Begin()
{
    CreateWidgets();
    ShowWidgets();
}

void CGuiQtMain::CreateWidgets()
{
    m_main_label = new QLabel(m_main_window);
    m_main_label->setAlignment(Qt::AlignCenter);
    m_main_label->setText(QString::fromUtf8(text(siMainQuestion).c_str()));
    m_main_label->setGeometry(QRect(QPoint(0, 20), QSize(600, 20)));

    m_btn_encode = new QPushButton(m_main_window);
    m_btn_encode->setText(QString::fromUtf8(text(siMainEncodePass).c_str()));
    m_btn_encode->setGeometry(QRect(QPoint(20, 80), QSize(200, 60)));
    connect(m_btn_encode, SIGNAL(released()), this, SLOT(onBtnEncodeClick()));

    m_btn_decode = new QPushButton(m_main_window);
    m_btn_decode->setText(QString::fromUtf8(text(siMainRestorePass).c_str()));
    m_btn_decode->setGeometry(QRect(QPoint(320, 80), QSize(200, 60)));
    connect(m_btn_decode, SIGNAL(released()), this, SLOT(onBtnDecodeClick()));

    AddWidget(m_main_label);
    AddWidget(m_btn_encode);
    AddWidget(m_btn_decode);
}

void CGuiQtMain::onAnamnesisStateEnd()
{
    m_gui_encode = nullptr;
    m_gui_decode = nullptr;
    ShowWidgets();
}

void CGuiQtMain::onBtnEncodeClick()
{
    m_gui_encode = new CGuiQtEncode(m_main_window);
    QObject::connect(m_gui_encode, SIGNAL(AnamnesisStateEnd()), this, SLOT(onAnamnesisStateEnd()));
    HideWidgets();
    m_gui_encode->Begin();
}

void CGuiQtMain::onBtnDecodeClick()
{
    m_gui_decode = new CGuiQtDecode(m_main_window);
    QObject::connect(m_gui_decode, SIGNAL(AnamnesisStateEnd()), this, SLOT(onAnamnesisStateEnd()));
    HideWidgets();
    m_gui_decode->Begin();
}
