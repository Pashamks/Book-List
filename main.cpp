#include "listwindow.h"

#include <QApplication>
#include<QLabel>
#include<QMovie>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListWindow w;
    QFile stuleShitFile("C:/Users/38095/Desktop/Qt/lab_6/Obit.txt");
    stuleShitFile.open(QFile::ReadOnly);
    QString stuleShit1 = QLatin1String(stuleShitFile.readAll());
    a.setStyleSheet(stuleShit1);
    w.show();
    QLabel *lbl = new QLabel;
    QMovie *movie = new QMovie("C:/Users/38095/Desktop/loading.gif");
    lbl->setMovie(movie);
    lbl->setMinimumHeight(300);
    lbl->setMinimumWidth(800);
    lbl->show();
    movie->start();
    QTimer::singleShot(5450, lbl, SLOT(close()));

    return a.exec();
}
