#include "memorygame.h"

void MemoryGame::TableButtonClicked(int indexButton)
{
    numOfMoves += 1;
    OpenTheCell(indexButton);
    WinCondition(indexButton);
}
void MemoryGame::MenuButtonClicked(BUTTONS button)
{
    if (button == BUTTONS::RESTART)
        RestartGame();
    else if(button == BUTTONS::MAIN_MENU)
        stackedWidget->setCurrentIndex(MAIN_SCREEN);
    else if(button == BUTTONS::START)
    {
        StartGame();
    }
    else if(button == BUTTONS::OPTIONS)
    {
        stackedWidget->setCurrentIndex(SETTINGS_SCREEN);
        settingsScreen->SyncTheValues();
    }
    else if(button == BUTTONS::EXIT)
        ExitGame();
}

MemoryGame::MemoryGame(MainWindow *mainWindow, GameScreen *gs, MainMenuScreen *ms, SettingsScreen *ss)
{
    mainScreen = ms;
    gameScreen = gs;
    settingsScreen = ss;

    stackedWidget = new QStackedWidget(mainWindow);
    stackedWidget->addWidget(mainScreen->GetCentralWidget());
    stackedWidget->addWidget(gameScreen->GetCentralWidget());
    stackedWidget->addWidget(settingsScreen->GetCentralWidget());

    stackedWidget->setCurrentIndex(MAIN_SCREEN);
    mainWindow->setCentralWidget(stackedWidget);

    items.resize(N);
    ConnectWithScreens();
}

void MemoryGame::onTimeout()
{
    QVector<QPushButton*> buttons = gameScreen->GetButtons();
    for(int i = 0; i < N; i++)
    {
        buttons[i]->setText(items[i].second);
    }
    SetEnabledTable(true);
    SetEnabledMenu(true);
}

void MemoryGame::StartGame()
{
    stackedWidget->setCurrentIndex(GAME_SCREEN);
    rainbowNums = settingsScreen->GetRainbowNums();
    SECONDS_TO_REMEMBER = settingsScreen->GetDifficultValue();

    RestartGame();
}

void MemoryGame::RestartGame()
{
    numOfMoves = 0;
    FillInVector(items);
    FillInButtons();
}

void MemoryGame::FillInVector(QVector<std::pair<int, QString>>& vec)
{
    for (int i = 0; i < N; ++i)
    {
        vec[i].first = i+1;
        vec[i].second = "X";
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    shuffle(vec.begin(), vec.end(), gen);
}

void MemoryGame::FillInButtons()
{
    QVector<QPushButton*> buttons = gameScreen->GetButtons();

    for(int i = 0; i < N; i++)
    {
        buttons[i]->setText(QString::number(items[i].first));

        QPalette palette = buttons[i]->palette();
        if (!rainbowNums)
            palette.setColor(QPalette::ButtonText, QColorConstants::Svg::black);
        else
            palette.setColor(QPalette::ButtonText, rainbowColors[i]);

        buttons[i]->setPalette(palette);
    }

    SetEnabledTable(false);
    SetEnabledMenu(false);
    // Таймер с задержкой
    QTimer::singleShot(SECONDS_TO_REMEMBER * 1000, this, &MemoryGame::onTimeout);
}

void MemoryGame::ConnectWithScreens()
{
    connect(gameScreen, &GameScreen::TableButtonClicked, this, &MemoryGame::TableButtonClicked);
    connect(gameScreen, &GameScreen::MenuButtonClicked, this, &MemoryGame::MenuButtonClicked);
    connect(mainScreen, &MainMenuScreen::MenuButtonClicked, this, &MemoryGame::MenuButtonClicked);
    connect(settingsScreen, &SettingsScreen::MenuButtonClicked, this, &MemoryGame::MenuButtonClicked);
}

void MemoryGame::Win()
{
    int result = QMessageBox::question(gameScreen, "ХОРОШО! VERY GOOD!", "Хотите начать новую игру?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (result == QMessageBox::Yes)
        RestartGame();

    SetEnabledTable(false);
}

void MemoryGame::Lose()
{
    int result = QMessageBox::question(gameScreen, "Ну как уж так((", "Хотите начать новую игру?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (result == QMessageBox::Yes)
        RestartGame();

    SetEnabledTable(false);
}

void MemoryGame::OpenTheCell(int indexButton)
{
    QVector<QPushButton*> buttons = gameScreen->GetButtons();
    buttons[indexButton]->setText(QString::number(items[indexButton].first));
}

void MemoryGame::WinCondition(int indexButton)
{
    if(numOfMoves != items[indexButton].first)
        Lose();
    else if (numOfMoves == N)
        Win();
}

void MemoryGame::SetEnabledMenu(bool enable)
{
    QVector<QPushButton*> menuButtons = gameScreen->GetMenuButtons();
    if (enable)
        for(int i = 0; i < menuButtons.size(); i++)
            menuButtons[i]->setEnabled(true);
    else
        for(int i = 0; i < menuButtons.size(); i++)
            menuButtons[i]->setEnabled(false);
}

void MemoryGame::SetEnabledTable(bool enable)
{
    QVector<QPushButton*> buttons = gameScreen->GetButtons();
    if (enable)
        for(int i = 0; i < N; i++)
            buttons[i]->setEnabled(true);
    else
        for(int i = 0; i < N; i++)
            buttons[i]->setEnabled(false);
}

void MemoryGame::ExitGame()
{
    QCoreApplication::quit();
}
