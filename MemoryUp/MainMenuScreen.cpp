#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen()
{
    centralWidget = new QWidget(this);
    QWidget *buttHolderWidget = new QWidget(centralWidget);
    buttHolderWidget->setMinimumSize(200, 0);

    // Создание компановок
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout *buttHolderLayout = new QVBoxLayout(buttHolderWidget);

    // Отступы
    QSpacerItem *horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *horizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *horizontalSpacer3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *horizontalSpacer4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    QSpacerItem *verticalSpacer1 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *verticalSpacer2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *verticalSpacer3 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *verticalSpacer4 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *verticalSpacer5 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

    // Правила игры
    // Добавить описание правил из файла
    const QString filePath = "Rules.txt";
    QFile file(filePath);
    QString fileInfo = "Правила не найдены";
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        fileInfo = in.readAll();
        file.close();
    }
    rules = new QLabel(fileInfo);
    QGroupBox *groupBoxRules = new QGroupBox("Правила игры", centralWidget);
    QVBoxLayout *groupBoxLayout = new QVBoxLayout(groupBoxRules);
    QFont*groupBoxFont = new QFont(fontName, BUTTONS_FONT);
    SetFont(rules, RULES_FONT);
    groupBoxRules->setFont(*groupBoxFont);


    // Кнопки меню
    QFont buttonsFont(fontName, BUTTONS_FONT);
    QPushButton *startButton = new QPushButton("Начать игру");
    startButton->setFont(buttonsFont);
    connect(startButton, &QPushButton::clicked, this, [=]() {
        emit MenuButtonClicked(BUTTONS::START);
    });
    menuButtons.append(startButton);

    QPushButton *settingsButton = new QPushButton("Настройки");
    settingsButton->setFont(buttonsFont);
    connect(settingsButton, &QPushButton::clicked, this, [=]() {
        emit MenuButtonClicked(BUTTONS::OPTIONS);
    });
    menuButtons.append(settingsButton);

    QPushButton *exitButton = new QPushButton("Выйти из игры");
    exitButton->setFont(buttonsFont);
    connect(exitButton, &QPushButton::clicked, this, [=]() {
        emit MenuButtonClicked(BUTTONS::EXIT);
    });
    menuButtons.append(exitButton);


    // Сохранить виджеты
    groupBoxLayout->addWidget(rules);

    mainLayout->addSpacerItem(horizontalSpacer1);
    mainLayout->addWidget(groupBoxRules);
    mainLayout->addSpacerItem(horizontalSpacer2);
    mainLayout->addSpacerItem(horizontalSpacer3);

    buttHolderLayout->addSpacerItem(verticalSpacer1);
    buttHolderLayout->addWidget(startButton);
    buttHolderLayout->addSpacerItem(verticalSpacer2);
    buttHolderLayout->addWidget(settingsButton);
    buttHolderLayout->addSpacerItem(verticalSpacer3);
    buttHolderLayout->addSpacerItem(verticalSpacer4);
    buttHolderLayout->addWidget(exitButton);
    buttHolderLayout->addSpacerItem(verticalSpacer5);

    mainLayout->addWidget(buttHolderWidget);
    mainLayout->addSpacerItem(horizontalSpacer4);
}
