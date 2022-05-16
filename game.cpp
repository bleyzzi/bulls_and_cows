#include "game.h"
#include "ui_widget.h"
void Game::gameStart()
{
    bool flag = true;
    QString str;
    row = 0;
    int i = 3;
    while(i != -1){
        str = QString::number(rand() % 10);
        for(int j = 0; j < 4; j++){
            if(ran[j] == str) flag = false;
        }
        if(flag) {ran[i] = str; i--;}
        flag = true;
    }
}

std::pair <int, int> Game::calc(QString a){
    bulls = 0;
    cows = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if (ran[i] == a[j]){
                if(i == j) bulls++;
                else cows++; break;
            }
        }
    }
    return {cows, bulls};
}

bool Game::isEnd()
{
    if(bulls == 4) return true;
    return false;
}

