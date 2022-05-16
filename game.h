#ifndef GAME_H
#define GAME_H
#include "widget.h"
#include "ui_widget.h"

class Game{
public:
    void gameStart();
    bool isEnd();
    std::pair <int, int> calc(QString);
private:
    QString ran[4] = {};
    int bulls = 0;
    int cows = 0;
    int row = 0;
};

#endif // GAME_H
