#include "statistics.h"
#include <iostream>

void Statistics::readFile()
{
    if(QFile::exists("record.txt")){
        QFile f("record.txt");
        f.open(QIODevice::ReadOnly);
        QTextStream fin(&f);
        for(;!fin.atEnd();){
        QString name;
        int score;
        fin >> score;
        fin >> name;
        st.insert(std::make_pair(score, name));
        }
    }
}

bool Statistics::isTop(int steps)
{
    int i = 0;
    for(auto [steps_m, name_m]:st)
    {
        if(i >= 10) return false;
        if(steps_m >= steps)
        {
            return true;
        }
        i++;
    }
    return st.size() < 10;
}

std::set <std::pair<int, QString>> Statistics::getInfo() const{
    return st;
}

void Statistics::refile(int score, QString name)
{
    st.insert(std::make_pair(score, name));\
    if(st.size() > 10){
        std::set<std::pair<int, QString>>::iterator it = st.end();
        it--;
        st.erase(it);
    }
    writeFile();
}

void Statistics::writeFile()
{
    int cnt = 0;
    QFile f("record.txt");
    f.open(QIODevice::WriteOnly);
    QTextStream fout(&f);
    for(auto [steps, name]:st)
    {
        fout << steps << " " << name;
        if(cnt + 1 != st.size()) fout << "\n";
        cnt++;
    }
    f.close();
}
