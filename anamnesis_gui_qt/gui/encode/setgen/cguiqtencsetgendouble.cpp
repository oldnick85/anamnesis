#include "cguiqtencsetgendouble.h"

#include "../resources/textresult.h"
using namespace TRM_TXT_RES;

CGuiQtEncSetgenDouble::CGuiQtEncSetgenDouble(QMainWindow *main_window)
    : CGuiQtCommon(main_window)
{
    m_setgen_double = CSetgenDoublePtr(new CSetgenDouble());
}

void CGuiQtEncSetgenDouble::onBtnAbortClick()
{
    HideWidgets();
    emit AnamnesisStateEnd();
}

void CGuiQtEncSetgenDouble::onBtnDoneClick()
{
    if (not CheckProperties()) return;
    HideWidgets();
    emit AnamnesisStateEnd();
}

void CGuiQtEncSetgenDouble::CreateWidgets()
{
    m_lbl_main = new QLabel(m_main_window);
    m_lbl_main->setAlignment(Qt::AlignCenter);
    m_lbl_main->setText(QString::fromUtf8(text(siSetgenDoubleQuery).c_str()));
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

    int i;
    i = 0;
    for (auto &v : m_edt_variant_bank1)
    {
        v = new QLineEdit(m_main_window);
        v->setGeometry(QRect(QPoint(10, 200+30*i), QSize(150, 20)));
        connect(v, SIGNAL(textChanged(const QString&)), this, SLOT(onEdtChange()));
        AddWidget(v);
        i++;
    }

    i = 0;
    for (auto &v : m_edt_variant_bank2)
    {
        v = new QLineEdit(m_main_window);
        v->setGeometry(QRect(QPoint(300, 200+30*i), QSize(150, 20)));
        connect(v, SIGNAL(textChanged(const QString&)), this, SLOT(onEdtChange()));
        AddWidget(v);
        i++;
    }

    AddWidget(m_lbl_main);
    AddWidget(m_lbl_status);
    AddWidget(m_btn_abort);
    AddWidget(m_btn_done);
    AddWidget(m_edt_description);
}

bool CGuiQtEncSetgenDouble::CheckProperties()
{
    m_setgen_double->SetDescription(m_edt_description->text().toUtf8().constData());
    std::list<std::string> variants;
    variants.clear();
    for (auto &v : m_edt_variant_bank1)
    {
        if (not v) continue;
        std::string s = v->text().toUtf8().constData();
        if (not s.empty())
            variants.push_back(s);
    }
    m_setgen_double->SetVariants(variants, CSetgenDouble::enVariantsBank::vbFirst);

    variants.clear();
    for (auto &v : m_edt_variant_bank2)
    {
        if (not v) continue;
        std::string s = v->text().toUtf8().constData();
        if (not s.empty())
            variants.push_back(s);
    }
    m_setgen_double->SetVariants(variants, CSetgenDouble::enVariantsBank::vbSecond);

    auto res = m_setgen_double->Valid(enPurpose::pEncode);
    m_btn_done->setEnabled(res.OK());
    m_lbl_status->setText(QString::fromUtf8(CTextResult(res).Text().c_str()));
    return res.OK();
}

void CGuiQtEncSetgenDouble::onEdtChange()
{
    CheckProperties();
}
