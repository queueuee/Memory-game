#include "SettingsScreen.h"

void SettingsScreen::updateDifficult(int value)
    {
        difficultLabel->setText("Секунд на запоминание цифр: " + QString::number(value));
    }
    void SettingsScreen::valuesChanged()
    {
        if (difficultValue != slider->value() || rainbowNums != checkBoxRainbowNums->isChecked())
            confirmSettingsButton->setEnabled(true);
        else
            confirmSettingsButton->setEnabled(false);
    }
SettingsScreen::SettingsScreen()
{
    // Значения по умолчанию
    rainbowNums = false;
    difficultValue = 1;
    int MIN_SECONDS = 1;
    int MAX_SECONDS = 4;

    centralWidget = new QWidget(this);
    QWidget *buttHolderWidget = new QWidget(this);
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

    QWidget *groupBoxSpacer = new QWidget();
    groupBoxSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    // Настройки игры
    QGroupBox *groupBoxSettings = new QGroupBox("Настройки", this);
    QVBoxLayout *settingsLayout = new QVBoxLayout(groupBoxSettings);
    QFont *groupBoxFont = new QFont(fontName, 14);
    groupBoxSettings->setFont(*groupBoxFont);

    // Переключение разноцветных чисел
    checkBoxRainbowNums = new QCheckBox("Разноцветные цифры",this);

    // Ползунок выбора сложности
    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(MIN_SECONDS);
    slider->setMaximum(MAX_SECONDS);

    // Отображение значения ползунка
    difficultLabel = new QLabel("Секунд на запоминание цифр: " + QString::number(difficultValue));
    connect(slider, &QSlider::valueChanged, this, &SettingsScreen::updateDifficult);        

    // Применитб настройки
    QFont buttonsFont(fontName, BUTTONS_FONT);
    confirmSettingsButton = new QPushButton("Применить");
    confirmSettingsButton->setFont(buttonsFont);
    confirmSettingsButton->setEnabled(false);

    // Если значения настроек изменились, то кнопка активна
    connect(checkBoxRainbowNums, &QCheckBox::stateChanged, this, &SettingsScreen::valuesChanged);
    connect(slider, &QSlider::valueChanged, this, &SettingsScreen::valuesChanged);

    // При нажатии на кнопку применяются настройки
    connect(confirmSettingsButton, &QPushButton::clicked, this, [=](){
        difficultValue = slider->value();
        rainbowNums = checkBoxRainbowNums->isChecked();
        confirmSettingsButton->setEnabled(false);
    });


    // Кнопки меню
    // Старт игры
    QPushButton *startButton = new QPushButton("Начать игру");
    startButton->setFont(buttonsFont);
    connect(startButton, &QPushButton::clicked, this, [=]() {
        emit MenuButtonClicked(BUTTONS::START);
    });

    // Посмотреть правила
    QPushButton *rulesButton = new QPushButton("Правила игры");
    rulesButton->setFont(buttonsFont);
    connect(rulesButton, &QPushButton::clicked, this, [=]() {
        emit MenuButtonClicked(BUTTONS::MAIN_MENU);
    });

    // Закрыть окно
    QPushButton *exitButton = new QPushButton("Выйти из игры");
    exitButton->setFont(buttonsFont);
    connect(exitButton, &QPushButton::clicked, this, [=]() {
        emit MenuButtonClicked(BUTTONS::EXIT);
    });


    // ???
    settingsLayout->addWidget(checkBoxRainbowNums);
    settingsLayout->addWidget(difficultLabel);
    settingsLayout->addWidget(slider);
    settingsLayout->addWidget(groupBoxSpacer);
    settingsLayout->addWidget(confirmSettingsButton);

    mainLayout->addSpacerItem(horizontalSpacer1);
    mainLayout->addWidget(groupBoxSettings);
    mainLayout->addSpacerItem(horizontalSpacer2);
    mainLayout->addSpacerItem(horizontalSpacer3);

    buttHolderLayout->addSpacerItem(verticalSpacer1);
    buttHolderLayout->addWidget(startButton);
    buttHolderLayout->addSpacerItem(verticalSpacer2);
    buttHolderLayout->addWidget(rulesButton);
    buttHolderLayout->addSpacerItem(verticalSpacer3);
    buttHolderLayout->addSpacerItem(verticalSpacer4);
    buttHolderLayout->addWidget(exitButton);
    buttHolderLayout->addSpacerItem(verticalSpacer5);

    mainLayout->addWidget(buttHolderWidget);
    mainLayout->addSpacerItem(horizontalSpacer4);

}

void SettingsScreen::SyncTheValues()
{
    checkBoxRainbowNums->setChecked(rainbowNums);
    slider->setValue(difficultValue);
}

int SettingsScreen::GetDifficultValue()
{
    return difficultValue;
}

bool SettingsScreen::GetRainbowNums()
{
    return rainbowNums;
}
