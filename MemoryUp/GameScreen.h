#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "basescreen.h"

#include "QHBoxLayout"
#include "QVBoxLayout"


class GameScreen : public BaseScreen
{
    Q_OBJECT
private:
    // Хранилище клеток
    QVector<QPushButton*> buttons;
    // Размер шрифта клеток
    const int TABLE_BUTTONS_FONT = BUTTONS_FONT * 1.4;
public:
    GameScreen();
    QVector<QPushButton*>& GetButtons();
    QVector<QPushButton*>& GetMenuButtons();

signals:
    // При нажатии на клетку
    void TableButtonClicked(int index);
};


#endif // GAMESCREEN_H
