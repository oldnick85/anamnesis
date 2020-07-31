#include "cguiqtdecquestion.h"

#include "../resources/textresult.h"
using namespace TRM_TXT_RES;

CGuiQtDecQuestion::CGuiQtDecQuestion(QMainWindow* main_window, CSetCombPtr setcomb)
    : CGuiQtCommon(main_window)
    , m_setcomb(setcomb)
{
    auto combine = m_setcomb->GetCombine();
    switch (combine->GetType())
    {
    case enCombineType::ctCombination:
        m_combination = std::dynamic_pointer_cast<CCombineCombination>(combine);
        break;
    case enCombineType::ctPermutation:
        m_permutation = std::dynamic_pointer_cast<CCombinePermutation>(combine);
        break;
    default:
        assert(false);
        break;
    }
}

void CGuiQtDecQuestion::onBtnAbortClick()
{
    HideWidgets();
    emit AnamnesisStateEnd(enResultStateEnd::seOK);
}

void CGuiQtDecQuestion::onBtnNextClick()
{
    HideWidgets();
    emit AnamnesisStateEnd(enResultStateEnd::seNext);
}

void CGuiQtDecQuestion::onAnamnesisElementChanged()
{
    CheckProperties();
}

void CGuiQtDecQuestion::CreateWidgets()
{
    m_lbl_main = new QLabel(m_main_window);
    m_lbl_main->setAlignment(Qt::AlignCenter);
    m_lbl_main->setText(QString::fromUtf8(text(siCombinePermutSetPerm).c_str()));
    m_lbl_main->setGeometry(QRect(QPoint(0, 20), QSize(600, 20)));

    m_lbl_status = new QLabel(m_main_window);
    m_lbl_status->setAlignment(Qt::AlignCenter);
    m_lbl_status->setText("");
    m_lbl_status->setGeometry(QRect(QPoint(0, 40), QSize(600, 20)));

    m_btn_abort = new QPushButton(m_main_window);
    m_btn_abort->setText(QString::fromUtf8(text(siAbort).c_str()));
    m_btn_abort->setGeometry(QRect(QPoint(10, 80), QSize(130, 50)));
    connect(m_btn_abort, SIGNAL(released()), this, SLOT(onBtnAbortClick()));

    m_btn_next = new QPushButton(m_main_window);
    m_btn_next->setText(QString::fromUtf8(text(siNextQuestion).c_str()));
    m_btn_next->setGeometry(QRect(QPoint(160, 80), QSize(130, 50)));
    connect(m_btn_next, SIGNAL(released()), this, SLOT(onBtnNextClick()));

    m_lbl_description = new QLabel(m_main_window);
    m_lbl_description->setAlignment(Qt::AlignCenter);
    m_lbl_description->setText(QString::fromUtf8(m_setcomb->GetDescription().c_str()));
    m_lbl_description->setGeometry(QRect(QPoint(10, 120), QSize(600, 20)));

    int i = 0;
    for (auto &e : m_elt_setgen)
    {
        auto rect = QRect(QPoint(10, 200+30*i), QSize(500, 20));
        e = MakeSetgenElement(m_setcomb->GetSetgen(), rect);
        e->Create();
        connect(e, SIGNAL(AnamnesisElementChanged()), this, SLOT(onAnamnesisElementChanged()));
        i++;
    }

    AddWidget(m_lbl_main);
    AddWidget(m_lbl_status);
    AddWidget(m_btn_abort);
    AddWidget(m_btn_next);
    AddWidget(m_lbl_description);
}

CGuiQtSetgenElement* CGuiQtDecQuestion::MakeSetgenElement(const ISetgenPtr setgen, const QRect rect) const
{
    CGuiQtSetgenElement* e = nullptr;
    switch (setgen->GetType())
    {
    case enSetgenType::stSingle:
        e = new CGuiQtSetgenElementSingle(m_main_window, std::dynamic_pointer_cast<CSetgenSingle>(setgen), rect);
        break;
    case enSetgenType::stDouble:
        e = new CGuiQtSetgenElementDouble(m_main_window, std::dynamic_pointer_cast<CSetgenDouble>(setgen), rect);
        break;
    default:
        break;
    }
    return e;
}

bool CGuiQtDecQuestion::CheckProperties()
{
    Sampling_t comb;
    for (const auto e : m_elt_setgen)
    {
        if (e->Check())
            comb.push_back(e->Value());
    }
    Result_t res;
    if (comb.empty())
    {
        res = Result_t(RES_NO_VARIANTS);
    }
    else
    {
        if (m_combination)
            res = m_combination->SetCombination(comb, false);
        else if (m_permutation)
            res = m_permutation->SetPermutation(comb, false);
    }
    const bool combination_ok = res.OK();
    m_btn_next->setEnabled(combination_ok);
    m_lbl_status->setText(QString::fromUtf8(CTextResult(res).Text().c_str()));
    return combination_ok;
}

void CGuiQtDecQuestion::ShowWidgets()
{
    CGuiQtCommon::ShowWidgets();
    for (auto &e : m_elt_setgen)
        if (e) e->Show();
}

void CGuiQtDecQuestion::HideWidgets()
{
    CGuiQtCommon::HideWidgets();
    for (auto &e : m_elt_setgen)
        if (e) e->Hide();
}
