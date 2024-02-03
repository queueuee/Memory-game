#ifndef MEMORYGAME_H
#define MEMORYGAME_H

#include "mainwindow.h"
#include "GameScreen.h"
#include "MainMenuScreen.h"
#include "SettingsScreen.h"

#include <random>
#include <QMessageBox>
#include <QTimer>
#include <QStackedWidget>
#include <QApplication>
#include <QPalette>

class MemoryGame : public QObject
{
    Q_OBJECT
private:
    // Смена активного игрового экрана
    QStackedWidget *stackedWidget;

    // Игровые экраны
    GameScreen *gameScreen;
    MainMenuScreen *mainScreen;
    SettingsScreen *settingsScreen;

    // Удобство в переключении между экранами
    enum ScreenType
    {
        MAIN_SCREEN,
        GAME_SCREEN,
        SETTINGS_SCREEN
    };

    // Цвета радуги
    QVector<QColor> rainbowColors = {
         QColorConstants::Svg::red,
         QColorConstants::Svg::orange,
         QColorConstants::Svg::yellow,
         QColorConstants::Svg::green,
         QColorConstants::Svg::cyan,
         QColorConstants::Svg::blue,
         QColorConstants::Svg::magenta
    };

    // Размер табло
    const int N = 7;
    QVector<std::pair<int, QString>> items;
    // Время на запоминание
    int SECONDS_TO_REMEMBER;
    // Количество открытых клеток
    int numOfMoves;
    // Разноцветные ли числа
    bool rainbowNums;

    // Заполнить вектор случайными значениями
    void FillInVector(QVector<std::pair<int, QString>>&);
    // Заполнить клетки цифрами из вектора
    void FillInButtons();
    // Соединить слоты с сигналами игровых экранов
    void ConnectWithScreens();
    void Win();
    void Lose();
    // Открыть выбранную клетку
    void OpenTheCell(int);
    // Победил ли игрок
    void WinCondition(int);
    // Разблокировать/заблокировать взаимодействие с меню
    void SetEnabledMenu(bool);
    // Разблокировать/заблокировать взаимодействие с клетками
    void SetEnabledTable(bool);
    void StartGame();
    void RestartGame();
    void ExitGame();
public:
    MemoryGame(MainWindow *w, GameScreen*, MainMenuScreen*, SettingsScreen*);

public slots:
    void TableButtonClicked(int);
    void MenuButtonClicked(BUTTONS);
private slots:
    void onTimeout();
};

#endif // MEMORYGAME_H
