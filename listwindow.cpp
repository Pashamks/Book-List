#include "listwindow.h"
#include "ui_listwindow.h"
List books;
ListWindow::ListWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ListWindow)
{
    ui->setupUi(this);
    Enabled(false);
    ui->my_But_one_del->setIcon(QIcon("C:/Users/38095/Desktop/garbage.png"));
    ui->my_But_one_del->setStyleSheet("border-radius: 25px;");

}
void ListWindow::Enabled(bool val)
{
    ui->my_But_del_books->setEnabled(val);
    ui->my_But_sort->setEnabled(val);
    ui->my_But_find_A->setEnabled(val);
    ui->my_But_write_file->setEnabled(val);
    ui->my_But_one_del->setEnabled(val);
    ui->line_to_del->setEnabled(val);
    ui->actionSave->setEnabled(val);
    ui->actionFind->setEnabled(val);
    ui->actionDelete_books->setEnabled(val);
    ui->actionSort->setEnabled(val);
    if(val==1){
        if(books.Get_size()<=1){
            ui->my_But_del_books->setEnabled(false);
            ui->my_But_sort->setEnabled(false);
            ui->actionDelete_books->setEnabled(false);
            ui->actionSort->setEnabled(false);
        }
    }
}
void ListWindow:: Clear_line()
{
    ui->line_name->setText("");
    ui->line_pages->setText("");
    ui->line_price->setText("");
    ui->line_surname->setText("");
    ui->line_title->setText("");
    ui->line_year->setText("");
}
bool ListWindow::Check_Word(QString text, bool title)
{
    bool temp = true;
    for(int i=0 ; i< text.size(); i++)
    {
        if(!text.at(i).isLetter()){
            if(title&&text.at(i)==' '){

            }
            else{
                temp = false;
                return temp;
            }
        }
    }
    return temp;
}
bool ListWindow::Check_Number(QString text, bool integer)
{
    bool temp = true, dot = false;
    for(int i=0 ; i< text.size(); i++)
    {
        if(!(text.at(i).toLatin1() >= 48 && text.at(i).toLatin1() <= 57)){
            if(!integer){
                if(i!=0 && text.at(i)=='.' && dot==false){
                dot = true;
                }
                else{
                    temp = false;
                    return temp;
                }
            }
            else{
                temp = false;
                return temp;
            }
         }
    }
    return temp;
}
ListWindow::~ListWindow()
{
    delete ui;
}
bool ListWindow::Corect(QString author_name, QString author_surname,
QString book_name, QString year, QString pages, QString price)
{
    bool temp = true;
    if(!Check_Word(author_name, 0)||author_name==""){
        QMessageBox mes;
        mes.critical(this, "Error!!",
        tr("Check your data! You have problem with author name."),QMessageBox::Close );
        temp = false;
        return temp;
    }
    if(!Check_Word(author_surname, 0)||author_surname==""){
        QMessageBox mes;
        mes.critical(this, "Error!!",
        tr("Check your data! You have problem with author surname."),QMessageBox::Close );
        temp = false;
        return temp;
    }
    if(!Check_Word(book_name, 1)||author_surname==""){
        QMessageBox mes;
        mes.critical(this, "Error!!",
        tr("Check your data! You have problem with book title."),QMessageBox::Close );
        temp = false;
        return temp;
    }
    if(!Check_Number(year, 1)||year==""){
        QMessageBox mes;
        mes.critical(this, "Error!!",
        tr("Check your data! You have problem with book year."),QMessageBox::Close );
        temp = false;
        return temp;
    }
    if(!Check_Number(pages, 1)||pages==""){
        QMessageBox mes;
        mes.critical(this, "Error!!",
        tr("Check your data! You have problem with book pages."),QMessageBox::Close );
        temp = false;
        return temp;
    }
    if(!Check_Number(price,0)||price==""){
        QMessageBox mes;
        mes.critical(this, "Error!!",
        tr("Check your data! You have problem with book price."),QMessageBox::Close );
        temp = false;
        return temp;
    }
    return temp;
}

void ListWindow::on_my_But_add_clicked()
{
    QString author_name=ui->line_name->text(), author_surname=ui->line_surname->text();
    QString book_name=ui->line_title->text();
    int year=(ui->line_year->text()).toInt(), pages = (ui->line_pages->text()).toInt();
    double price = (ui->line_price->text()).toDouble();
    if(!Corect(author_name,author_surname, book_name,
    ui->line_year->text(), ui->line_pages->text(),ui->line_price->text() )){

        return;
    }
    ui->label_info->setText("Your list after adding book:");
    books.push_back(author_name, author_surname, book_name,
    year,  pages, price  );
    ui->line_result->setText(books.Print());
    Enabled(true);
    //Clear_line();
}

void ListWindow::on_my_But_sort_clicked()
{
    books.Sort();
    ui->line_result->setText(books.Print());
    ui->label_info->setText("Your sorted list:");
}

void ListWindow::on_my_But_find_A_clicked()
{
    /*QMessageBox::information(this, "Information",
    "After this operation you will see authors with A in surname.",
    QMessageBox::Close);*/
    ui->line_result->setText(books.Find_A());
    ui->label_info->setText("Your list with authours\nwhose surname "
"started from A:");
}

void ListWindow::on_my_But_del_books_clicked()
{
    books.Del_books();
    ui->label_info->setText("Your list after delete:");
    ui->line_result->setText(books.Print());
    if(books.Get_size()<=1){
        ui->my_But_del_books->setEnabled(false);
        ui->my_But_sort->setEnabled(false);
    }
}
void ListWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Finish work",
                 tr("Save your list to file?\n"),
               QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

void ListWindow::on_my_But_read_file_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this,"Open the file ");
    QFile file(FileName);
    if(!file.open(QIODevice:: ReadOnly | QFile ::Text)){
        QMessageBox::critical(this, "Error!", "We can't open the file : " + file.errorString());
        return;
    }
    QTextStream in(&file);
    QString author_name="", author_surname="", book_name="",
    year="", pages="", price="" , temp="";
    temp = in.readAll();
    if(temp==""){
        ui->line_result->setText("File is empty");
        return;
    }
    QStringList val=temp.split(QLatin1Char('\n'));
    QStringList data ;
    for(int i =0; i < val.size(); i++){
        data =val[i].split(QLatin1Char(' '));
        if(data.size()<7){
            QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setInformativeText("There are some problems with data  in your file.");
                msgBox.setStandardButtons(QMessageBox::Close);
                msgBox.setDetailedText("You made mistake in line "+ QString::number(i+1)+
                                       "\n"+val[i]);
                msgBox.exec();
            return;
        }
        for(int j=0 ; j < data.size(); ++j){

              author_name = data[j]; ++j;
               author_surname = data[j]; ++j;
           ++j; book_name = data[j]; ++j;
           while(data[j]!="\""){
               book_name+=" " + data[j];
               ++j;
               if(j==data.size()-1){
                ui->line_result->setText("You made mistake in book title in line "+ QString::number(i+1)+
                           "\n"+val[i]);
                   return;
               }
           }
           ++j;
           year = data[j]; ++j;
           pages = data[j]; ++j;
           price = data[j];

        }
        if(!Corect(author_name,author_surname, book_name,
            year, pages,price)){
        ui->line_result->setText("You have error in line "+ QString::number(i+1)+
                "\n"+val[i]);
               return;
        }
        books.push_back(author_name,author_surname,
        book_name,year.toInt(), pages.toInt(), price.toDouble() );
    }

    file.close();
    ui->label_info->setText("Your list read from file:");
    ui->line_result->setText(books.Print());
    Enabled(true);
}

void ListWindow::on_my_But_write_file_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Write to"));
    QFile file(FileName);
    if(!file.open(QFile:: WriteOnly | QFile ::Text)){
        QMessageBox::critical(this, "Error!", "We can't open the file : " + file.errorString());
        return;
    }
    QTextStream out(&file);
    QString text = "Your sorted list:\n"+books.Print()+
    "\nAuthor whose surname started with A:\n" + books.Find_A()+
    "\nYour list after delete:\n" + books.Del_Formal();
    out << text;
    file.close();
    QMessageBox::information(this, "Success!", "Your data successfully written to file.", QMessageBox::Close);
}



void ListWindow::on_my_But_one_del_clicked()
{
    QString temp = ui->line_to_del->text();
    if(!(Check_Number(temp, 0)) || (temp.toInt()>books.Get_size() ||temp.toInt()<=0) )
    {
        QMessageBox mes; mes.critical(this, "Error!",
        tr("You made a mistake in number to delete."),QMessageBox::Close );
        return;
    }
    if(books.Get_size()==1){
        QMessageBox:: StandardButton val2 = QMessageBox::warning(this, "Warning!",
        tr("If you delete last book your list will be empty.\nAre you sure to delete this book?"),
                                       QMessageBox::Yes | QMessageBox::Close );
        if(val2 == QMessageBox::Close){
            ui->line_to_del->setText("");
            return;
        }
    }
    books.Del_number(temp.toInt());
    ui->line_result->setText(books.Print());
    if(books.Print()=="Empty")
         Enabled(false);
    ui->label_info->setText("Your list after delete:");
    ui->line_to_del->setText("");
}

void ListWindow::on_actionOpen_triggered()
{
    on_my_But_read_file_clicked();
}

void ListWindow::on_actionSave_triggered()
{
    on_my_But_write_file_clicked();
}

void ListWindow::on_actionAdd_triggered()
{
    on_my_But_find_A_clicked();
}

void ListWindow::on_actionFind_triggered()
{
    on_my_But_find_A_clicked();
}

void ListWindow::on_actionDelete_books_triggered()
{
    on_my_But_del_books_clicked();
}

void ListWindow::on_actionAbout_program_triggered()
{
    Dialog window;
    window.show();
    window.exec();
}

void ListWindow::on_actionSort_triggered()
{
    on_my_But_sort_clicked();
}
