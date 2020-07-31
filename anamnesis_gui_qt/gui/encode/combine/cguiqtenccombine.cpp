#include "cguiqtenccombine.h"

#include "../resources/textresult.h"
using namespace TRM_TXT_RES;

CGuiQtEncCombine::CGuiQtEncCombine(QMainWindow *main_window, ISetgenPtr setgen)
    : CGuiQtCommon(main_window)
    , m_setgen(setgen)
{

}

void CGuiQtEncCombine::onBtnAbortClick()
{
    HideWidgets();
    emit AnamnesisStateEnd();
}

void CGuiQtEncCombine::onBtnDoneClick()
{
    if (CheckProperties())
    {
        HideWidgets();
        emit AnamnesisStateEnd();
    }
}

void CGuiQtEncCombine::onBtnCombineCombinationClick()
{
    HideWidgets();
    m_gui_combine_combination = new CGuiQtEncCombineCombination(m_main_window, m_setgen);
    QObject::connect(m_gui_combine_combination, SIGNAL(AnamnesisStateEnd()), this, SLOT(onAnamnesisStateEnd()));
    m_gui_combine_combination->Begin();
}

void CGuiQtEncCombine::onBtnCombinePermutationClick()
{
    HideWidgets();
    m_gui_combine_permutation = new CGuiQtEncCombinePermutation(m_main_window, m_setgen);
    QObject::connect(m_gui_combine_permutation, SIGNAL(AnamnesisStateEnd()), this, SLOT(onAnamnesisStateEnd()));
    m_gui_combine_permutation->Begin();
}

void CGuiQtEncCombine::CreateWidgets()
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

    m_btn_combine_combination = new QPushButton(m_main_window);
    m_btn_combine_combination->setText(QString::fromUtf8(text(siCombineCombination).c_str()));
    m_btn_combine_combination->setGeometry(QRect(QPoint(10, 200), QSize(400, 50)));
    connect(m_btn_combine_combination, SIGNAL(released()), this, SLOT(onBtnCombineCombinationClick()));

    m_btn_combine_permutation = new QPushButton(m_main_window);
    m_btn_combine_permutation->setText(QString::fromUtf8(text(siCombinePermut).c_str()));
    m_btn_combine_permutation->setGeometry(QRect(QPoint(10, 260), QSize(400, 50)));
    connect(m_btn_combine_permutation, SIGNAL(released()), this, SLOT(onBtnCombinePermutationClick()));

    AddWidget(m_lbl_main);
    AddWidget(m_lbl_status);
    AddWidget(m_btn_abort);
    AddWidget(m_btn_done);
    AddWidget(m_btn_combine_combination);
    AddWidget(m_btn_combine_permutation);
}

bool CGuiQtEncCombine::CheckProperties()
{
    bool combine_ok = ((m_combine) and (m_combine->Valid(enPurpose::pEncode).OK()));
    m_btn_done->setEnabled(combine_ok);
    std::string status_str = combine_ok ? text(siOK) : text(siNotSet);
    m_lbl_status->setText(QString::fromUtf8(status_str.c_str()));
    return combine_ok;
}

void CGuiQtEncCombine::onAnamnesisStateEnd()
{
    ShowWidgets();
    if (m_gui_combine_combination)
    {
        m_combine = m_gui_combine_combination->GetCombine();
        m_gui_combine_combination = nullptr;
    }
    else if (m_gui_combine_permutation)
    {
        m_combine = m_gui_combine_permutation->GetCombine();
        m_gui_combine_permutation = nullptr;
    }
    else
    {
        m_combine = nullptr;
    }
    CheckProperties();
}
