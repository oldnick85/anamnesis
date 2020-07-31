#include "cguiqtenccombinepermutation.h"

#include "../resources/textresult.h"
using namespace TRM_TXT_RES;

CGuiQtEncCombinePermutation::CGuiQtEncCombinePermutation(QMainWindow *main_window, ISetgenPtr setgen)
    : CGuiQtCommon(main_window)
    , m_setgen(setgen)
{
    m_permutation = CCombinePermutationPtr(new CCombinePermutation());
}

void CGuiQtEncCombinePermutation::onBtnAbortClick()
{
    HideWidgets();
    emit AnamnesisStateEnd();
}

void CGuiQtEncCombinePermutation::onBtnDoneClick()
{
    if (not CheckProperties()) return;
    HideWidgets();
    emit AnamnesisStateEnd();
}

void CGuiQtEncCombinePermutation::onAnamnesisElementChanged()
{
    CheckProperties();
}

void CGuiQtEncCombinePermutation::CreateWidgets()
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

    m_btn_done = new QPushButton(m_main_window);
    m_btn_done->setText(QString::fromUtf8(text(siDone).c_str()));
    m_btn_done->setGeometry(QRect(QPoint(160, 80), QSize(130, 50)));
    connect(m_btn_done, SIGNAL(released()), this, SLOT(onBtnDoneClick()));

    int i = 0;
    for (auto &e : m_elt_setgen)
    {
        auto rect = QRect(QPoint(10, 200+30*i), QSize(500, 20));
        switch (m_setgen->GetType())
        {
        case enSetgenType::stSingle:
            e = new CGuiQtSetgenElementSingle(m_main_window, std::dynamic_pointer_cast<CSetgenSingle>(m_setgen), rect);
            break;
        case enSetgenType::stDouble:
            e = new CGuiQtSetgenElementDouble(m_main_window, std::dynamic_pointer_cast<CSetgenDouble>(m_setgen), rect);
            break;
        default:
            assert(false);
            break;
        }
        e->Create();
        connect(e, SIGNAL(AnamnesisElementChanged()), this, SLOT(onAnamnesisElementChanged()));
        i++;
    }

    AddWidget(m_lbl_main);
    AddWidget(m_lbl_status);
    AddWidget(m_btn_abort);
    AddWidget(m_btn_done);
}

bool CGuiQtEncCombinePermutation::CheckProperties()
{
    m_permutation->SetParameters(m_setgen->VariantsCount());
    Sampling_t perm;
    for (const auto e : m_elt_setgen)
    {
        if (e->Check())
            perm.push_back(e->Value());
    }
    const auto res = perm.empty() ? Result_t(RES_NO_VARIANTS) : m_permutation->SetPermutation(perm);
    const bool permutation_ok = res.OK();
    m_btn_done->setEnabled(permutation_ok);
    std::string status_str = CTextResult(res).Text();
    if (permutation_ok)
    {
        char s[256];
        snprintf(s, sizeof(s), "%s=%s; %s=%zu%s;",
                 text(siVariantsCount).c_str(), m_permutation->VariantsCount().PrintDec().c_str(),
                 text(siEnthropy).c_str(), m_permutation->VariantsCount().BitsCount(), text(siBit).c_str());
        status_str += s;
    }
    m_lbl_status->setText(QString::fromUtf8(status_str.c_str()));
    return permutation_ok;
}

void CGuiQtEncCombinePermutation::ShowWidgets()
{
    CGuiQtCommon::ShowWidgets();
    for (auto &e : m_elt_setgen)
        e->Show();
}

void CGuiQtEncCombinePermutation::HideWidgets()
{
    CGuiQtCommon::HideWidgets();
    for (auto &e : m_elt_setgen)
        e->Hide();
}
