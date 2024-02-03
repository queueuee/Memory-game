#include "GameScreen.h"

GameScreen::GameScreen()
{
    centralWidget = new QWidget(this);
    QWidget *buttHolderWidget = new QWidget(centralWidget);
    buttHolderWidget->setMinimumSize(200, 0);
    QWidget *infoHolderWidget = new QWidget(centralWidget);
    infoHolderWidget->setMinimumSize(500, 300);
    QFrame *gameFrame = new QFrame(infoHolderWidget);


    // Создание компоновок
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout *buttHolderLayout = new QVBoxLayout(buttHolderWidget);
    QHBoxLayout *gameLayout = new QHBoxLayout(gameFrame);
    QVBoxLayout *infoHolderLayout = new QVBoxLayout(infoHolderWidget);

    // Отступы
    QSpacerItem *horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *horizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *horizontalSpacer3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *horizontalSpacer4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    QWidget *infoSpacer1 = new QWidget();
    infoSpacer1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget *infoSpacer2 = new QWidget();
    infoSpacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Поле цифр
    gameFrame->setFrameShape(QFrame::Box);
    QLabel* goalLabel = new QLabel("Откройте числа в порядке возрастания");
    SetFont(goalLabel, 14);
    // Игровые кнопки
    for(int i =0; i < 7; i++)
    {
        QPushButton *button = new QPushButton(QString::number(i + 1));
        button->setFont(QFont(fontName, TABLE_BUTTONS_FONT));

        buttons.append(button);

        // Передача индекса кнопки в сигнал
        connect(buttons[i], &QPushButton::clicked, this, [=]() {
            emit TableButtonClicked(i);
        });
    }

    // Кнопки меню
    QFont buttonsFont(fontName, BUTTONS_FONT);
    QPushButton *startButton = new QPushButton("Начать заново");
    startButton->setFont(buttonsFont);
    connect(startButton, &QPushButton::clicked, this, [=]() {
        emit MenuButtonClicked(BUTTONS::RESTART);
    });
    menuButtons.append(startButton);

    QPushButton *exitButton = new QPushButton("Главное меню");
    exitButton->setFont(buttonsFont);
    connect(exitButton, &QPushButton::clicked, this, [=]() {
        emit MenuButtonClicked(BUTTONS::MAIN_MENU);
    });
    menuButtons.append(exitButton);

    // ???
    for (int i = 0; i < buttons.size(); i++)
        gameLayout->addWidget(buttons[i]);

    infoHolderLayout->addWidget(infoSpacer1);
    infoHolderLayout->addWidget(goalLabel);
    infoHolderLayout->addWidget(gameFrame);
    infoHolderLayout->addWidget(infoSpacer2);

    buttHolderLayout->addWidget(startButton);
    buttHolderLayout->addWidget(exitButton);

    mainLayout->addSpacerItem(horizontalSpacer1);
    mainLayout->addWidget(infoHolderWidget);
    mainLayout->addSpacerItem(horizontalSpacer2);
    mainLayout->addSpacerItem(horizontalSpacer3);
    mainLayout->addWidget(buttHolderWidget);
    mainLayout->addSpacerItem(horizontalSpacer4);
}

QVector<QPushButton*>& GameScreen::GetButtons()
{
    return buttons;
}

QVector<QPushButton*>& GameScreen::GetMenuButtons()
{
    return menuButtons;
}
