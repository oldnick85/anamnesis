#ifndef CGUIQTSETGENELEMENT_H
#define CGUIQTSETGENELEMENT_H

#include <QMainWindow>
/**
 * @brief CGuiQtSetgenElement - класс кастомного виджета для генератора множества
 */
class CGuiQtSetgenElement
        : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief CGuiQtSetgenElement - конструктор класса кастомного виджета для генератора множества
     * @param main_window - главное окно
     */
    CGuiQtSetgenElement(QMainWindow* main_window);
    virtual ~CGuiQtSetgenElement() = default;
    /**
     * @brief Create
     */
    virtual void Create() = 0;
    /**
     * @brief Show - показать виджет
     */
    virtual void Show() = 0;
    /**
     * @brief Hide - скрыть виджет
     */
    virtual void Hide() = 0;
    /**
     * @brief Check - проверить корректность установленного значения
     * @return корректность установленного значения
     */
    virtual bool Check() const = 0;
    /**
     * @brief Value - получить текущее значение из множества
     * @return значение из множества
     */
    virtual uint64_t Value() const = 0;
signals:
    /**
     * @brief AnamnesisElementChanged - сигнал об изменении состояния виджета
     */
    void AnamnesisElementChanged();
protected:
    QMainWindow*        m_main_window;  ///< главное окно
};

#endif // CGUIQTSETGENELEMENT_H
