#ifndef BASESCREEN_H
#define BASESCREEN_H

#include "buttons.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class BaseScreen : public QWidget
{
    Q_OBJECT
protected:
    // Хранилище виджетов окна
    QWidget *centralWidget;

    // Шрифт всех текстов
    const QString fontName = "Segoe";
    // Разрмер шрифта для кнопок меню
    const int BUTTONS_FONT = 15;
    // Хранилище кнопок меню
    QVector<QPushButton*> menuButtons;
    void SetFont(QLabel*, int);

    BaseScreen() {}
public:
    QWidget* GetCentralWidget();
signals:
    void MenuButtonClicked(BUTTONS buttonPressed);
};

#endif // BASESCREEN_H
