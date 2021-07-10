#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include <QMainWindow>
#include"list.h"
#include<QMessageBox>
#include<QFile>
#include<QFileDialog>
#include "dialog.h"
#include<QProgressDialog>
#include <QTimer>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class ListWindow; }
QT_END_NAMESPACE

class ListWindow : public QMainWindow
{
    Q_OBJECT

public:
    ListWindow(QWidget *parent = nullptr);
    ~ListWindow();
    void closeEvent (QCloseEvent *event);
private slots:
    void on_my_But_add_clicked();
    void Clear_line();
    bool Check_Word(QString text, bool title);
    bool Check_Number(QString text, bool integer);
    void on_my_But_sort_clicked();

    void on_my_But_find_A_clicked();

    void on_my_But_del_books_clicked();

    void on_my_But_read_file_clicked();

    bool Corect(QString author_name, QString author_surname,
    QString book_name, QString year, QString pages, QString price);

    void on_my_But_write_file_clicked();

    void Enabled(bool val);

    void on_my_But_one_del_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionAdd_triggered();

    void on_actionFind_triggered();

    void on_actionDelete_books_triggered();

    void on_actionAbout_program_triggered();

    void on_actionSort_triggered();

private:
    Ui::ListWindow *ui;
};
#endif // LISTWINDOW_H
