#include "cguiqtdecode.h"

using namespace TRM_TXT_RES;

CGuiQtDecode::CGuiQtDecode(QMainWindow* main_window)
    : CGuiQtCommon(main_window)
{
    m_casket = nullptr;
}

void CGuiQtDecode::onAnamnesisStateEnd(const enResultStateEnd result)
{
    switch (result)
    {
    case seOK:
        break;
    case seNext:
        break;
    }
    ShowWidgets();
    CheckProperties();
}

void CGuiQtDecode::onBtnAbortClick()
{
    HideWidgets();
    emit AnamnesisStateEnd();
}

void CGuiQtDecode::onBtnNextClick()
{
    for (auto sc : m_casket->GetSetcombs())
    {
        if (sc->Valid(enPurpose::pEncode).ERROR())
        {
            HideWidgets();
            m_question = new CGuiQtDecQuestion(m_main_window, sc);
            QObject::connect(m_question, SIGNAL(AnamnesisStateEnd(const enResultStateEnd)), this, SLOT(onAnamnesisStateEnd(const enResultStateEnd)));
            m_question->Begin();
            return;
        }
    }
}

void CGuiQtDecode::onBtnOpenClick()
{
    QString str = QFileDialog::getOpenFileName(m_main_window, "Save password", "", "*.dat");
    std::string fname = str.toUtf8().constData();
    if (not fname.empty())
    {
        m_casket = CCasketPtr(new CCasket());
        const auto res = m_casket->LoadFileJSON(fname);
        if (not res.OK())
        {
            m_casket = nullptr;
            QMessageBox::warning(m_main_window, "Warning",  QString::fromUtf8(CTextResult(res).Text().c_str()));
        }
        else
        {
            m_question_num = 0;
            auto sc_it = m_casket->GetSetcombs().begin();
            m_question = new CGuiQtDecQuestion(m_main_window, *sc_it);
        }
    }
    CheckProperties();
}

void CGuiQtDecode::CreateWidgets()
{
    m_main_label = new QLabel(m_main_window);
    m_main_label->setAlignment(Qt::AlignCenter);
    m_main_label->setText(QString::fromUtf8(text(siMainEncodePass).c_str()));
    m_main_label->setGeometry(QRect(QPoint(0, 20), QSize(600, 20)));

    m_lbl_status = new QLabel(m_main_window);
    m_lbl_status->setAlignment(Qt::AlignCenter);
    m_lbl_status->setText("");
    m_lbl_status->setGeometry(QRect(QPoint(0, 40), QSize(600, 20)));

    m_btn_abort = new QPushButton(m_main_window);
    m_btn_abort->setText(QString::fromUtf8(text(siAbort).c_str()));
    m_btn_abort->setGeometry(QRect(QPoint(10, 80), QSize(130, 50)));
    connect(m_btn_abort, SIGNAL(released()), this, SLOT(onBtnAbortClick()));

    m_btn_open = new QPushButton(m_main_window);
    m_btn_open->setText(QString::fromUtf8(text(siOpenFile).c_str()));
    m_btn_open->setGeometry(QRect(QPoint(150, 80), QSize(130, 50)));
    connect(m_btn_open, SIGNAL(released()), this, SLOT(onBtnOpenClick()));

    m_btn_next = new QPushButton(m_main_window);
    m_btn_next->setText(QString::fromUtf8(text(siNextQuestion).c_str()));
    m_btn_next->setGeometry(QRect(QPoint(300, 80), QSize(130, 50)));
    connect(m_btn_next, SIGNAL(released()), this, SLOT(onBtnNextClick()));

    m_lst_questions = new QListWidget(m_main_window);
    m_lst_questions->setGeometry(QRect(QPoint(20, 160), QSize(300, 400)));

    AddWidget(m_main_label);
    AddWidget(m_lbl_status);
    AddWidget(m_btn_abort);
    AddWidget(m_btn_open);
    AddWidget(m_btn_next);
    AddWidget(m_lst_questions);
}

bool CGuiQtDecode::CheckPass() const
{
    for (auto sc : m_casket->GetSetcombs())
    {
        if (sc->Valid(enPurpose::pEncode).ERROR())
            return false;
    }
    return true;
}

bool CGuiQtDecode::CheckProperties()
{
    bool casket_ok = (m_casket != nullptr);

    m_lst_questions->clear();
    if (m_casket)
    {
        for (const auto &sc : m_casket->GetSetcombs())
        {
            m_lst_questions->addItem(QString::fromUtf8(sc->GetDescription().c_str()));
            auto row = m_lst_questions->count() - 1;
            QListWidgetItem* item = m_lst_questions->takeItem(row);
            if (sc->Valid(enPurpose::pEncode).OK())
                item->setTextColor(QColor(0, 0, 0));
            else
                item->setTextColor(QColor(255, 0, 0));
            m_lst_questions->insertItem(row, item);
        }
    }
    bool ready_to_pass = false;
    std::string status_str;
    if (casket_ok)
    {
        ready_to_pass = CheckPass();
        if (ready_to_pass)
        {
            m_casket->PassFromKeyhole();
            status_str = text(siPassResult) + ": " + m_casket->GetPass()->GetPasswordString();
        }
        else
        {
            status_str = text(siAnswerAllQuestions);
        }
    }
    else
    {
        status_str = text(siFileNotOpened);
    }
    m_lbl_status->setText(QString::fromUtf8(status_str.c_str()));
    m_btn_next->setEnabled(casket_ok and (not ready_to_pass));
    return false;
}
