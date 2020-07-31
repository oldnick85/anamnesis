#include "cguiqtencpass.h"

#include "../resources/textresult.h"

using namespace TRM_TXT_RES;

CGuiQtEncPass::CGuiQtEncPass(QMainWindow* main_window)
    : CGuiQtCommon(main_window)
{
    m_pass = CPassPtr(new CPass());
}

void CGuiQtEncPass::onBtnAbortClick()
{
    HideWidgets();
    emit AnamnesisStateEnd();
}

void CGuiQtEncPass::onBtnDoneClick()
{
    auto res = m_pass->Valid(enPurpose::pEncode);
    if (not CheckProperties()) return;
    HideWidgets();
    emit AnamnesisStateEnd();
}

void CGuiQtEncPass::CreateWidgets()
{
    m_lbl_main = new QLabel(m_main_window);
    m_lbl_main->setAlignment(Qt::AlignCenter);
    m_lbl_main->setText(QString::fromUtf8(text(siEncodeQuerySetPass).c_str()));
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

    m_edt_pass = new QLineEdit(m_main_window);
    m_edt_pass->setGeometry(QRect(QPoint(10, 130), QSize(300, 20)));
    connect(m_edt_pass, SIGNAL(textChanged(const QString&)), this, SLOT(onEdtChange()));

    m_chk_symb_upper_case = new QCheckBox(m_main_window);
    m_chk_symb_upper_case->setText(QString::fromUtf8(text(siPassSymbUpper).c_str()));
    m_chk_symb_upper_case->setGeometry(QRect(QPoint(50, 160), QSize(180, 20)));
    connect(m_chk_symb_upper_case, SIGNAL(clicked(bool)), this, SLOT(onChkSymbClick_upper_case(bool)));

    m_chk_symb_lower_case = new QCheckBox(m_main_window);
    m_chk_symb_lower_case->setText(QString::fromUtf8(text(siPassSymbLower).c_str()));
    m_chk_symb_lower_case->setGeometry(QRect(QPoint(50, 180), QSize(180, 20)));
    connect(m_chk_symb_lower_case, SIGNAL(clicked(bool)), this, SLOT(onChkSymbClick_lower_case(bool)));

    m_chk_symb_digits = new QCheckBox(m_main_window);
    m_chk_symb_digits->setText(QString::fromUtf8(text(siPassSymbDigits).c_str()));
    m_chk_symb_digits->setGeometry(QRect(QPoint(50, 200), QSize(180, 20)));
    connect(m_chk_symb_digits, SIGNAL(clicked(bool)), this, SLOT(onChkSymbClick_digits(bool)));

    m_chk_symb_minus = new QCheckBox(m_main_window);
    m_chk_symb_minus->setText("minus");
    m_chk_symb_minus->setGeometry(QRect(QPoint(50, 220), QSize(180, 20)));
    connect(m_chk_symb_minus, SIGNAL(clicked(bool)), this, SLOT(onChkSymbClick_minus(bool)));

    m_chk_symb_underline = new QCheckBox(m_main_window);
    m_chk_symb_underline->setText("underline");
    m_chk_symb_underline->setGeometry(QRect(QPoint(50, 240), QSize(180, 20)));
    connect(m_chk_symb_underline, SIGNAL(clicked(bool)), this, SLOT(onChkSymbClick_underline(bool)));

    m_chk_symb_space = new QCheckBox(m_main_window);
    m_chk_symb_space->setText("space");
    m_chk_symb_space->setGeometry(QRect(QPoint(50, 260), QSize(180, 20)));
    connect(m_chk_symb_space, SIGNAL(clicked(bool)), this, SLOT(onChkSymbClick_space(bool)));

    m_chk_symb_special = new QCheckBox(m_main_window);
    m_chk_symb_special->setText("special");
    m_chk_symb_special->setGeometry(QRect(QPoint(50, 280), QSize(180, 20)));
    connect(m_chk_symb_special, SIGNAL(clicked(bool)), this, SLOT(onChkSymbClick_special(bool)));

    m_chk_symb_brackets = new QCheckBox(m_main_window);
    m_chk_symb_brackets->setText(QString::fromUtf8(text(siPassSymbBraces).c_str()));
    m_chk_symb_brackets->setGeometry(QRect(QPoint(50, 300), QSize(180, 20)));
    connect(m_chk_symb_brackets, SIGNAL(clicked(bool)), this, SLOT(onChkSymbClick_brackets(bool)));

    AddWidget(m_lbl_main);
    AddWidget(m_lbl_status);
    AddWidget(m_btn_abort);
    AddWidget(m_btn_done);
    AddWidget(m_edt_pass);
    AddWidget(m_chk_symb_upper_case);
    AddWidget(m_chk_symb_lower_case);
    AddWidget(m_chk_symb_digits);
    AddWidget(m_chk_symb_minus);
    AddWidget(m_chk_symb_underline);
    AddWidget(m_chk_symb_space);
    AddWidget(m_chk_symb_special);
    AddWidget(m_chk_symb_brackets);
}

CPass::sSymbolClass CGuiQtEncPass::SymbolsFromCheckboxes()
{
    CPass::sSymbolClass sb;
    sb.upper_case = m_chk_symb_upper_case->checkState();
    sb.lower_case = m_chk_symb_lower_case->checkState();
    sb.digits = m_chk_symb_digits->checkState();
    sb.minus = m_chk_symb_minus->checkState();
    sb.underline = m_chk_symb_underline->checkState();
    sb.space = m_chk_symb_space->checkState();
    sb.special = m_chk_symb_special->checkState();
    sb.brackets = m_chk_symb_brackets->checkState();
    return sb;
}

void CGuiQtEncPass::onChkSymbClick_upper_case(const bool checked)
{
    std::string pass = m_edt_pass->text().toUtf8().constData();
    auto sb = m_pass->SymbolsFromPassword(pass);
    if ((not checked) and (sb.upper_case))
        m_chk_symb_upper_case->setCheckState(Qt::CheckState::Checked);
    m_pass->SetSymbols(SymbolsFromCheckboxes());
}

void CGuiQtEncPass::onChkSymbClick_lower_case(const bool checked)
{
    std::string pass = m_edt_pass->text().toUtf8().constData();
    auto sb = m_pass->SymbolsFromPassword(pass);
    if ((not checked) and (sb.lower_case))
        m_chk_symb_lower_case->setCheckState(Qt::CheckState::Checked);
    m_pass->SetSymbols(SymbolsFromCheckboxes());
}

void CGuiQtEncPass::onChkSymbClick_digits(const bool checked)
{
    std::string pass = m_edt_pass->text().toUtf8().constData();
    auto sb = m_pass->SymbolsFromPassword(pass);
    if ((not checked) and (sb.digits))
        m_chk_symb_digits->setCheckState(Qt::CheckState::Checked);
    m_pass->SetSymbols(SymbolsFromCheckboxes());
}

void CGuiQtEncPass::onChkSymbClick_minus(const bool checked)
{
    std::string pass = m_edt_pass->text().toUtf8().constData();
    auto sb = m_pass->SymbolsFromPassword(pass);
    if ((not checked) and (sb.minus))
        m_chk_symb_minus->setCheckState(Qt::CheckState::Checked);
    m_pass->SetSymbols(SymbolsFromCheckboxes());
}

void CGuiQtEncPass::onChkSymbClick_underline(const bool checked)
{
    std::string pass = m_edt_pass->text().toUtf8().constData();
    auto sb = m_pass->SymbolsFromPassword(pass);
    if ((not checked) and (sb.underline))
        m_chk_symb_underline->setCheckState(Qt::CheckState::Checked);
    m_pass->SetSymbols(SymbolsFromCheckboxes());
}

void CGuiQtEncPass::onChkSymbClick_space(const bool checked)
{
    std::string pass = m_edt_pass->text().toUtf8().constData();
    auto sb = m_pass->SymbolsFromPassword(pass);
    if ((not checked) and (sb.space))
        m_chk_symb_space->setCheckState(Qt::CheckState::Checked);
    m_pass->SetSymbols(SymbolsFromCheckboxes());
}

void CGuiQtEncPass::onChkSymbClick_special(const bool checked)
{
    std::string pass = m_edt_pass->text().toUtf8().constData();
    auto sb = m_pass->SymbolsFromPassword(pass);
    if ((not checked) and (sb.special))
        m_chk_symb_special->setCheckState(Qt::CheckState::Checked);
    m_pass->SetSymbols(SymbolsFromCheckboxes());
}

void CGuiQtEncPass::onChkSymbClick_brackets(const bool checked)
{
    std::string pass = m_edt_pass->text().toUtf8().constData();
    auto sb = m_pass->SymbolsFromPassword(pass);
    if ((not checked) and (sb.brackets))
        m_chk_symb_brackets->setCheckState(Qt::CheckState::Checked);
    m_pass->SetSymbols(SymbolsFromCheckboxes());
}

bool CGuiQtEncPass::CheckProperties()
{
    auto res = m_pass->Valid(enPurpose::pEncode);
    m_btn_done->setEnabled(res.OK());
    m_lbl_status->setText(QString::fromUtf8(CTextResult(res).Text().c_str()));
    return res.OK();
}

void CGuiQtEncPass::onEdtChange()
{
    std::string pass = m_edt_pass->text().toUtf8().constData();
    auto sb = m_pass->SymbolsFromPassword(pass);

    if (sb.upper_case) m_chk_symb_upper_case->setCheckState(Qt::CheckState::Checked);
    if (sb.lower_case) m_chk_symb_lower_case->setCheckState(Qt::CheckState::Checked);
    if (sb.digits) m_chk_symb_digits->setCheckState(Qt::CheckState::Checked);
    if (sb.minus) m_chk_symb_minus->setCheckState(Qt::CheckState::Checked);
    if (sb.underline) m_chk_symb_underline->setCheckState(Qt::CheckState::Checked);
    if (sb.space) m_chk_symb_space->setCheckState(Qt::CheckState::Checked);
    if (sb.special) m_chk_symb_special->setCheckState(Qt::CheckState::Checked);
    if (sb.brackets) m_chk_symb_brackets->setCheckState(Qt::CheckState::Checked);

    m_pass->SetSymbols(sb);
    m_pass->SetPassword(pass);
    CheckProperties();
}
