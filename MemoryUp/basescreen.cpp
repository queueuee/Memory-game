#include "basescreen.h"

void BaseScreen::SetFont(QLabel* text, int font)
{
    QFont* qfont = new QFont(fontName, font);
    text->setWordWrap(true);
    text->setFont(*qfont);
}


QWidget* BaseScreen::GetCentralWidget()
{
    return centralWidget;
}
