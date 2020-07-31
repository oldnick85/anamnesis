#include "cguiqtcommon.h"

CGuiQtCommon::CGuiQtCommon(QMainWindow *main_window)
    : m_main_window(main_window)
{

}

void CGuiQtCommon::Begin()
{
    CreateWidgets();
    CheckProperties();
    ShowWidgets();
}

void CGuiQtCommon::AddWidget(QWidget* widget)
{
    m_widgets.push_back(widget);
}

void CGuiQtCommon::ShowWidgets()
{
    for (auto w : m_widgets)
        w->show();
}

void CGuiQtCommon::HideWidgets()
{
    for (auto w : m_widgets)
        w->hide();
}
