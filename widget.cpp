#include "widget.h"
#include "ui_widget.h"
#include "game.h"
#include "statistics.h"
#include <set>
Game game;
Statistics stats;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    stats.readFile();
    QGridLayout *g = new QGridLayout(this);
    g->addWidget(ui->check_button, 1, 2);
    g->addWidget(ui->input_line, 1, 1);
    g->addWidget(ui->start_game, 0, 0);
    g->addWidget(ui->game_list, 3, 0, 2, 0);
    g->addWidget(ui->label_input, 1, 0);
    g->addWidget(ui->stat_button, 0, 2);
    g->addWidget(ui->game_status_label, 0, 1);
    ui->game_list->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    ui->game_status_label->setText("Игра не началась");
    ui->check_button->blockSignals(true);
}

Widget::~Widget()
{
    stats.writeFile();
    delete ui;
}

bool Widget::isUnique()
{
    std::set <QChar> st;
    QString num = ui->input_line->text();
    for(int i = 0; i < num.size(); i++)
    {
        st.insert(num[i]);
    }
    if(st.size() != 4) return false;
    return true;
}

void Widget::gameStop()
{
    ui->game_status_label->setText("Игра не началась");
    ui->game_list->clear();
    ui->game_list->setRowCount(0);
    row = 0;
}

void Widget::on_check_button_clicked()
{

    if(!isUnique())
    {
        QMessageBox::about(this, "Ошибка", "Число должно состоять из 4 разных целых чисел");
        ui->input_line->clear();
    }
    else
    {
    QString a = ui->input_line->text();
    ui->game_list->insertRow(row);
    ui->game_list->setItem(row, 0, new QTableWidgetItem(a));
    auto [cows, bulls] = game.calc(a);
    ui->game_list->setItem(row, 1, new QTableWidgetItem("Bulls: " + QString::number(bulls) + " Cows: " + QString::number(cows)));
    ui->input_line->clear();
    row++;
    if(game.isEnd())
    {
        if(stats.isTop(row)){
            bool bOk;
            QMessageBox::about(this, "", "Рекорд!");
            QString name = QInputDialog::getText(0, "Рекорд", "Имя:", QLineEdit::Normal, "", &bOk);
            if(bOk){
                stats.refile(row, name);
            }
        }
        else{
            QMessageBox::about(this, "Победа", "Победа!");
        }
        gameStop();
    }
    }
}

void Widget::on_start_game_clicked()
{
    ui->check_button->blockSignals(false);
    ui->input_line->clear();
    ui->game_list->clear();
    ui->game_list->setRowCount(0);
    row = 0;
    game.gameStart();
    ui->game_status_label->setText("Игра идет");
}

void Widget::on_stat_button_clicked()
{
    QTableWidget *stats_table = new QTableWidget;
    stats_table->setColumnCount(2);
    stats_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    int row_stat = 0;
    std::set<std::pair<int, QString>> st_check = stats.getInfo();
    for(auto [steps, name]:st_check){
        stats_table->insertRow(row_stat);
        stats_table->setItem(row_stat, 0, new QTableWidgetItem(QString::number(steps)));
        stats_table->setItem(row_stat, 1, new QTableWidgetItem(name));
        row_stat++;
    }
    stats_table->show();
}
