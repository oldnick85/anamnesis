#include "cguiqtsetgenelementsingle.h"

CGuiQtSetgenElementSingle::CGuiQtSetgenElementSingle(QMainWindow *main_window, CSetgenSinglePtr setgen_single, QRect rect)
    : CGuiQtSetgenElement(main_window)
    , m_setgen_single(setgen_single)
    , m_rect(rect)
{

}

void CGuiQtSetgenElementSingle::Create()
{
    m_cbx_variant = new QComboBox(m_main_window);
    m_cbx_variant->setGeometry(m_rect);
    QStringList texts;
    texts.push_back("");
    const auto &vars = m_setgen_single->GetVariants();
    for (const auto &var : vars)
    {
        texts.push_back(QString::fromUtf8(var.c_str()));
    }
    m_cbx_variant->addItems(texts);
    connect(m_cbx_variant, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged()));
}

void CGuiQtSetgenElementSingle::onCurrentIndexChanged()
{
    emit AnamnesisElementChanged();
}

void CGuiQtSetgenElementSingle::Show()
{
    m_cbx_variant->show();
}

void CGuiQtSetgenElementSingle::Hide()
{
    m_cbx_variant->hide();
}

bool CGuiQtSetgenElementSingle::Check() const
{
    return (m_cbx_variant->currentIndex() != 0);
}

uint64 CGuiQtSetgenElementSingle::Value() const
{
    return static_cast<uint64>(m_cbx_variant->currentIndex() - 1);
}
