#include "cguiqtsetgenelementdouble.h"

CGuiQtSetgenElementDouble::CGuiQtSetgenElementDouble(QMainWindow *main_window, CSetgenDoublePtr setgen_double, QRect rect)
    : CGuiQtSetgenElement(main_window)
    , m_setgen_double(setgen_double)
    , m_rect(rect)
{

}

void CGuiQtSetgenElementDouble::Create()
{
    {
        QRect rect_first = QRect(QPoint(m_rect.x(), m_rect.y()), QSize(m_rect.width()/2, m_rect.height()));
        m_cbx_variant_first = new QComboBox(m_main_window);
        m_cbx_variant_first->setGeometry(rect_first);
        QStringList texts_first;
        texts_first.push_back("");
        const auto &vars_f = m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbFirst);
        for (const auto &var : vars_f)
        {
            texts_first.push_back(QString::fromUtf8(var.c_str()));
        }
        m_cbx_variant_first->addItems(texts_first);
        connect(m_cbx_variant_first, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged()));
    }
    {
        QRect rect_second = QRect(QPoint(m_rect.x()+m_rect.width()/2, m_rect.y()), QSize(m_rect.width()/2, m_rect.height()));
        m_cbx_variant_second = new QComboBox(m_main_window);
        m_cbx_variant_second->setGeometry(rect_second);
        QStringList texts_second;
        texts_second.push_back("");
        const auto &vars_s = m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbSecond);
        for (const auto &var : vars_s)
        {
            texts_second.push_back(QString::fromUtf8(var.c_str()));
        }
        m_cbx_variant_second->addItems(texts_second);
        connect(m_cbx_variant_second, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged()));
    }
}

void CGuiQtSetgenElementDouble::onCurrentIndexChanged()
{
    emit AnamnesisElementChanged();
}

void CGuiQtSetgenElementDouble::Show()
{
    m_cbx_variant_first->show();
    m_cbx_variant_second->show();
}

void CGuiQtSetgenElementDouble::Hide()
{
    m_cbx_variant_first->hide();
    m_cbx_variant_second->hide();
}

bool CGuiQtSetgenElementDouble::Check() const
{
    const bool first_ok = (m_cbx_variant_first->currentIndex() != 0);
    const bool second_ok = (m_cbx_variant_second->currentIndex() != 0);
    return (first_ok and second_ok);
}

uint64 CGuiQtSetgenElementDouble::Value() const
{
    const auto v1 = static_cast<uint64>(m_cbx_variant_first->currentIndex() - 1);
    const auto v2 = static_cast<uint64>(m_cbx_variant_second->currentIndex() - 1);
    return (v1+m_setgen_double->GetVariants(CSetgenDouble::enVariantsBank::vbFirst).size()*v2);
}
