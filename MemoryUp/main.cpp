#include "mainwindow.h"
#include "memorygame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // размер окна
    w.setMinimumSize(800, 400);
    w.setMaximumSize(1000, 500);

    GameScreen gameScreen;
    MainMenuScreen mainScreen;
    SettingsScreen settingsScreen;
    MemoryGame game(&w, &gameScreen, &mainScreen, &settingsScreen);

    w.show();
    return a.exec();
}
