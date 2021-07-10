#ifndef LIST_H
#define LIST_H
#include"listwindow.h"

class List
{

public:
    List();
    ~List();
    class Node{
        public:
        QString m_author_name;
        QString m_author_surname;
        QString m_book_name;
        int m_year;
        int m_pages;
        double m_price;
        Node *p_next;

        Node();
        Node(QString author_name, QString author_surname,
             QString book_name, int year, int pages, double price, Node *pNext);
    };
    void push_back( QString author_name, QString author_surname,
    QString book_name, int year, int pages, double price);
    QString Print();
    void Sort();
    QString Find_A();
    void Del_books();
    double Sum;
    double Get_size();
    void Del_number(int val);
    QString Del_Formal();
private:

    int m_size;
    Node *p_head;
};

#endif // LIST_H
