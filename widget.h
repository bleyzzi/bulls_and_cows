#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include "statistics.h"
#include <iostream>
#include <QGridLayout>
#include <QMessageBox>
#include <QtCore>
#include <QtWidgets>
#include <QPalette>
#include <QBrush>
#include <set>
#include <map>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_check_button_clicked();

    void on_start_game_clicked();

    void on_stat_button_clicked();

private:
    bool isUnique();
    void gameStop();
    int row = 0;
    Ui::Widget *ui;
};
#endif // WIDGET_H
