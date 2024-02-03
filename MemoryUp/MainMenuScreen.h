#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include "basescreen.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFile>
#include <QTextStream>

class MainMenuScreen : public BaseScreen
{
    Q_OBJECT
private:
    QLabel* rules;
    // Шрифт текста для правил
    const int RULES_FONT = 12;

public:
    MainMenuScreen();
};


#endif // MAINMENUSCREEN_H
