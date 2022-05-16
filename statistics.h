#ifndef STATISTICS_H
#define STATISTICS_H
#include <set>
#include <QString>
#include <QInputDialog>
#include <QFile>
#include "widget.h"
#include <QTextStream>

class Statistics
{
public:
    bool isTop(int);
    void refile(int, QString);
    void writeFile();
    void readFile();
    std::set<std::pair<int, QString>> getInfo() const;
private:
    std::set <std::pair<int, QString>> st;
    void add(int, QString);
    int row = 0;
    QInputDialog* dialog;
};

#endif // STATISTICS_H
