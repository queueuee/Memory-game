#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include "basescreen.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QSlider>

class SettingsScreen : public BaseScreen
{
    Q_OBJECT
private:
    // Отображение текущего времени на запоминание
    QLabel *difficultLabel;
    // Раскрасить цифры в цвета радуги
    QCheckBox* checkBoxRainbowNums;
    // Изменить время на запоминание
    QSlider *slider;
    // Подтверждение настроек
    QPushButton *confirmSettingsButton;
    // Значения настроек
    int difficultValue;
    bool rainbowNums;

public:
    SettingsScreen();
    int GetDifficultValue();
    // Чтобы при переходе в настройки отображались текущие значения
    void SyncTheValues();
    bool GetRainbowNums();

private slots:
    // Ползунок слайдера сдвинули
    void updateDifficult(int);
    // Настройки изменились
    void valuesChanged();
};

#endif // SETTINGSSCREEN_H
