#include "cguiqtencsetgen.h"

#include "../resources/textresult.h"
using namespace TRM_TXT_RES;

CGuiQtEncSetgen::CGuiQtEncSetgen(QMainWindow *main_window)
    : CGuiQtCommon(main_window)
{

}

void CGuiQtEncSetgen::onBtnAbortClick()
{
    HideWidgets();
    emit AnamnesisStateEnd();
}

void CGuiQtEncSetgen::onBtnDoneClick()
{
    if (CheckProperties())
    {
        HideWidgets();
        emit AnamnesisStateEnd();
    }
}

void CGuiQtEncSetgen::onBtnSetgenSingleClick()
{
    HideWidgets();
    m_gui_setgen_single = new CGuiQtEncSetgenSingle(m_main_window);
    QObject::connect(m_gui_setgen_single, SIGNAL(AnamnesisStateEnd()), this, SLOT(onAnamnesisStateEnd()));
    m_gui_setgen_single->Begin();
}

void CGuiQtEncSetgen::onBtnSetgenDoubleClick()
{
    HideWidgets();
    m_gui_setgen_double = new CGuiQtEncSetgenDouble(m_main_window);
    QObject::connect(m_gui_setgen_double, SIGNAL(AnamnesisStateEnd()), this, SLOT(onAnamnesisStateEnd()));
    m_gui_setgen_double->Begin();
}

void CGuiQtEncSetgen::CreateWidgets()
{
    m_lbl_main = new QLabel(m_main_window);
    m_lbl_main->setAlignment(Qt::AlignCenter);
    m_lbl_main->setText(QString::fromUtf8(text(siSetgenChoose).c_str()));
    m_lbl_main->setGeometry(QRect(QPoint(0, 20), QSize(600, 20)));

    m_lbl_status = new QLabel(m_main_window);
    m_lbl_status->setAlignment(Qt::AlignCenter);
    m_lbl_status->setText("");
    m_lbl_status->setGeometry(QRect(QPoint(0, 40), QSize(600, 20)));

    m_btn_abort = new QPushButton(m_main_window);
    m_btn_abort->setText(QString::fromUtf8(text(siAbort).c_str()));
    m_btn_abort->setGeometry(QRect(QPoint(10, 80), QSize(130, 50)));
    connect(m_btn_abort, SIGNAL(released()), this, SLOT(onBtnAbortClick()));

    m_btn_done = new QPushButton(m_main_window);
    m_btn_done->setText(QString::fromUtf8(text(siDone).c_str()));
    m_btn_done->setGeometry(QRect(QPoint(160, 80), QSize(130, 50)));
    connect(m_btn_done, SIGNAL(released()), this, SLOT(onBtnDoneClick()));

    m_btn_setgen_single = new QPushButton(m_main_window);
    m_btn_setgen_single->setText(QString::fromUtf8(text(siSetgenSingleQuery).c_str()));
    m_btn_setgen_single->setGeometry(QRect(QPoint(10, 200), QSize(400, 50)));
    connect(m_btn_setgen_single, SIGNAL(released()), this, SLOT(onBtnSetgenSingleClick()));

    m_btn_setgen_double = new QPushButton(m_main_window);
    m_btn_setgen_double->setText(QString::fromUtf8(text(siSetgenDoubleQuery).c_str()));
    m_btn_setgen_double->setGeometry(QRect(QPoint(10, 260), QSize(400, 50)));
    connect(m_btn_setgen_double, SIGNAL(released()), this, SLOT(onBtnSetgenDoubleClick()));

    AddWidget(m_lbl_main);
    AddWidget(m_lbl_status);
    AddWidget(m_btn_abort);
    AddWidget(m_btn_done);
    AddWidget(m_btn_setgen_single);
    AddWidget(m_btn_setgen_double);
}

bool CGuiQtEncSetgen::CheckProperties()
{
    bool setgen_ok = ((m_setgen) and (m_setgen->Valid(enPurpose::pEncode).OK()));
    m_btn_done->setEnabled(setgen_ok);
    std::string status_str;
    if (setgen_ok)
    {
        switch (m_setgen->GetType())
        {
        case enSetgenType::stSingle:
            status_str = text(siSetgenSingle);
            break;
        case enSetgenType::stDouble:
            status_str = text(siSetgenDouble);
            break;
        default:
            assert(false);
            break;
        }
        char s[64];
        snprintf(s, sizeof(s), ": %s %zu", text(siVariantsCount).c_str(), m_setgen->VariantsCount());
        status_str += s;
    }
    else
    {
        status_str = text(siNotSet);
    }
    m_lbl_status->setText(QString::fromUtf8(status_str.c_str()));
    return setgen_ok;
}

void CGuiQtEncSetgen::onAnamnesisStateEnd()
{
    ShowWidgets();
    if (m_gui_setgen_single)
    {
        m_setgen = m_gui_setgen_single->GetSetgen();
        m_gui_setgen_single = nullptr;
    }
    else if (m_gui_setgen_double)
    {
        m_setgen = m_gui_setgen_double->GetSetgen();
        m_gui_setgen_double = nullptr;
    }
    else
    {
        m_setgen = nullptr;
    }
    CheckProperties();
}
