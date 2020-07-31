#include "cguiqtencquestion.h"

#include "../resources/textresult.h"

using namespace TRM_TXT_RES;

CGuiQtEncQuestion::CGuiQtEncQuestion(QMainWindow* main_window)
    : CGuiQtCommon(main_window)
{
    m_setcomb = CSetCombPtr(new CSetComb());
}

void CGuiQtEncQuestion::onAnamnesisStateEnd()
{
    if (m_gui_enc_setgen)
    {
        m_setcomb->SetSetgen(m_gui_enc_setgen->GetSetgen());
        m_gui_enc_setgen = nullptr;
    }
    if (m_gui_enc_combine)
    {
        m_setcomb->SetCombine(m_gui_enc_combine->GetCombine());
        m_gui_enc_combine = nullptr;
    }
    CheckProperties();
    ShowWidgets();
}

void CGuiQtEncQuestion::CreateWidgets()
{
    m_lbl_main = new QLabel(m_main_window);
    m_lbl_main->setAlignment(Qt::AlignCenter);
    m_lbl_main->setText(QString::fromUtf8(text(siEncodeQueryAdd).c_str()));
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

    m_edt_description = new QLineEdit(m_main_window);
    m_edt_description->setGeometry(QRect(QPoint(10, 130), QSize(300, 20)));
    connect(m_edt_description, SIGNAL(textChanged(const QString&)), this, SLOT(onEdtChange()));

    m_btn_setgen_add = new QPushButton(m_main_window);
    m_btn_setgen_add->setText(QString::fromUtf8(text(siSetgenChoose).c_str()));
    m_btn_setgen_add->setGeometry(QRect(QPoint(10, 180), QSize(240, 50)));
    connect(m_btn_setgen_add, SIGNAL(released()), this, SLOT(onBtnSetgenAddClick()));

    m_btn_combine_add = new QPushButton(m_main_window);
    m_btn_combine_add->setText(QString::fromUtf8(text(siCombineChoose).c_str()));
    m_btn_combine_add->setGeometry(QRect(QPoint(10, 240), QSize(240, 50)));
    connect(m_btn_combine_add, SIGNAL(released()), this, SLOT(onBtnCombineAddClick()));

    AddWidget(m_lbl_main);
    AddWidget(m_lbl_status);
    AddWidget(m_btn_abort);
    AddWidget(m_btn_done);
    AddWidget(m_edt_description);
    AddWidget(m_btn_setgen_add);
    AddWidget(m_btn_combine_add);
}

bool CGuiQtEncQuestion::CheckProperties()
{
    m_setcomb->SetDescription(m_edt_description->text().toUtf8().constData());
    auto res = m_setcomb->Valid(enPurpose::pEncode);
    m_btn_done->setEnabled(res.OK());
    m_btn_combine_add->setEnabled(m_setcomb->GetSetgen() and m_setcomb->GetSetgen()->Valid(enPurpose::pEncode).OK());
    m_lbl_status->setText(QString::fromUtf8(CTextResult(res).Text().c_str()));
    return res.OK();
}

void CGuiQtEncQuestion::onBtnAbortClick()
{
    HideWidgets();
    emit AnamnesisStateEnd();
}

void CGuiQtEncQuestion::onBtnDoneClick()
{
    if (not CheckProperties()) return;
    HideWidgets();
    emit AnamnesisStateEnd();
}

void CGuiQtEncQuestion::onEdtChange()
{
    CheckProperties();
}

void CGuiQtEncQuestion::onBtnSetgenAddClick()
{
    m_gui_enc_setgen = new CGuiQtEncSetgen(m_main_window);
    QObject::connect(m_gui_enc_setgen, SIGNAL(AnamnesisStateEnd()), this, SLOT(onAnamnesisStateEnd()));
    HideWidgets();
    m_gui_enc_setgen->Begin();
}

void CGuiQtEncQuestion::onBtnCombineAddClick()
{
    m_gui_enc_combine = new CGuiQtEncCombine(m_main_window, m_setcomb->GetSetgen());
    QObject::connect(m_gui_enc_combine, SIGNAL(AnamnesisStateEnd()), this, SLOT(onAnamnesisStateEnd()));
    HideWidgets();
    m_gui_enc_combine->Begin();
}
