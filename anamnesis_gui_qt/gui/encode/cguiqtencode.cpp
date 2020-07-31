#include "cguiqtencode.h"

using namespace TRM_TXT_RES;

CGuiQtEncode::CGuiQtEncode(QMainWindow* main_window)
    : CGuiQtCommon(main_window)
{
    m_casket = CCasketPtr(new CCasket());
}

void CGuiQtEncode::onAnamnesisStateEnd()
{
    if (m_gui_pass)
    {
        const auto pass = m_gui_pass->GetPass();
        if (pass->Valid(enPurpose::pEncode).OK())
            m_casket->SetPass(pass);
        m_gui_pass = nullptr;
    }
    if (m_gui_question)
    {
        const auto setcomb = m_gui_question->GetSetcomb();
        if (setcomb->Valid(enPurpose::pEncode).OK())
            m_casket->GetSetcombs().push_back(setcomb);
        m_gui_question = nullptr;
    }
    ShowWidgets();
    CheckProperties();
}

void CGuiQtEncode::onBtnAbortClick()
{
    HideWidgets();
    emit AnamnesisStateEnd();
}

void CGuiQtEncode::onBtnSaveClick()
{
    if (not m_casket->Valid(enPurpose::pEncode).OK())
        return;
    QString str = QFileDialog::getSaveFileName(m_main_window, "Save password", "", "*.dat");
    std::string fname = str.toUtf8().constData();
    if (fname.empty()) return;
    m_casket->KeyholeFromPass();
    m_casket->SaveFileJSON(fname);
}

void CGuiQtEncode::onBtnSetPassClick()
{
    m_gui_pass = new CGuiQtEncPass(m_main_window);
    QObject::connect(m_gui_pass, SIGNAL(AnamnesisStateEnd()), this, SLOT(onAnamnesisStateEnd()));
    HideWidgets();
    m_gui_pass->Begin();
}

void CGuiQtEncode::onBtnAddQuestionClick()
{
    m_gui_question = new CGuiQtEncQuestion(m_main_window);
    QObject::connect(m_gui_question, SIGNAL(AnamnesisStateEnd()), this, SLOT(onAnamnesisStateEnd()));
    HideWidgets();
    m_gui_question->Begin();
}

void CGuiQtEncode::CreateWidgets()
{
    m_main_label = new QLabel(m_main_window);
    m_main_label->setAlignment(Qt::AlignCenter);
    m_main_label->setText(QString::fromUtf8(text(siMainEncodePass).c_str()));
    m_main_label->setGeometry(QRect(QPoint(0, 20), QSize(600, 20)));

    m_lbl_status = new QLabel(m_main_window);
    m_lbl_status->setAlignment(Qt::AlignLeft);
    m_lbl_status->setText("");
    m_lbl_status->setGeometry(QRect(QPoint(0, 50), QSize(600, 40)));

    m_btn_abort = new QPushButton(m_main_window);
    m_btn_abort->setText(QString::fromUtf8(text(siAbort).c_str()));
    m_btn_abort->setGeometry(QRect(QPoint(10, 80), QSize(130, 50)));
    connect(m_btn_abort, SIGNAL(released()), this, SLOT(onBtnAbortClick()));

    m_btn_save = new QPushButton(m_main_window);
    m_btn_save->setText(QString::fromUtf8(text(siSave).c_str()));
    m_btn_save->setGeometry(QRect(QPoint(160, 80), QSize(130, 50)));
    m_btn_save->setEnabled(false);
    connect(m_btn_save, SIGNAL(released()), this, SLOT(onBtnSaveClick()));

    m_btn_set_pass = new QPushButton(m_main_window);
    m_btn_set_pass->setText(QString::fromUtf8(text(siEncodeQuerySetPass).c_str()));
    m_btn_set_pass->setGeometry(QRect(QPoint(310, 80), QSize(130, 50)));
    connect(m_btn_set_pass, SIGNAL(released()), this, SLOT(onBtnSetPassClick()));

    m_btn_add_question = new QPushButton(m_main_window);
    m_btn_add_question->setText(QString::fromUtf8(text(siEncodeQueryAdd).c_str()));
    m_btn_add_question->setGeometry(QRect(QPoint(460, 80), QSize(130, 50)));
    connect(m_btn_add_question, SIGNAL(released()), this, SLOT(onBtnAddQuestionClick()));

    m_lst_questions = new QListWidget(m_main_window);
    m_lst_questions->setGeometry(QRect(QPoint(20, 160), QSize(300, 400)));

    AddWidget(m_main_label);
    AddWidget(m_lbl_status);
    AddWidget(m_btn_abort);
    AddWidget(m_btn_save);
    AddWidget(m_btn_set_pass);
    AddWidget(m_btn_add_question);
    AddWidget(m_lst_questions);
}

std::string CGuiQtEncode::PasswordStatus() const
{
    std::string pass_status;
    std::string pass_entropy;
    const auto pass = m_casket->GetPass();
    if ((pass) and (pass->Valid(enPurpose::pEncode).OK()))
    {
        pass_status = text(siOK);
        auto variants = pass->VariantsCount();
        char s[128];
        snprintf(s, sizeof(s), "%lu %s", variants.BitsCount(), text(siBit).c_str());
        pass_entropy = s;
    }
    else
    {
        pass_status = text(siNotSet);
        pass_entropy = "---";
    }
    char pass_st[128];
    snprintf(pass_st, sizeof(pass_st), "%s: %s [%s]\n",
             text(siEncodeStatusPass).c_str(), pass_status.c_str(), pass_entropy.c_str());
    return pass_st;
}

std::string CGuiQtEncode::QuestionsStatus() const
{
    auto variants = m_casket->VariantsCount();
    char s[256];
    snprintf(s, sizeof(s), "%s %lu; %s=%lu %s",
             text(siQuestionsCount).c_str(), m_casket->GetSetcombs().size(),
             text(siEnthropy).c_str(), variants.BitsCount(), text(siBit).c_str());
    return s;
}

void CGuiQtEncode::ShowStatus()
{
    auto p_str = PasswordStatus();
    auto q_str = QuestionsStatus();
    std::string status_str;
    status_str.append(p_str);
    status_str.append(q_str);
    m_lbl_status->setText(QString::fromUtf8(status_str.c_str()));

    m_lst_questions->clear();
    for (const auto &sc : m_casket->GetSetcombs())
    {
        m_lst_questions->addItem(QString::fromUtf8(sc->GetDescription().c_str()));
    }

    const bool casket_ok = m_casket->Valid(enPurpose::pEncode).OK();
    m_btn_save->setEnabled(casket_ok);
}

bool CGuiQtEncode::CheckProperties()
{
    ShowStatus();
    return false;
}
