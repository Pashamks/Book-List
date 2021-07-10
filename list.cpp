#include "list.h"
List::Node::Node(QString author_name, QString author_surname,
     QString book_name, int year, int pages, double price, Node *pNext=nullptr)
{
    m_author_name=author_name;
    m_author_surname=author_surname;
    m_book_name=book_name;
    m_year=year;m_pages=pages;m_price=price;
    p_next= pNext;
}
List::Node::Node()
 {
    m_author_name="";
    m_author_surname="";
    m_book_name="";
    m_year=0;m_pages=0;m_price=0;
    p_next = nullptr;
 }
List::List()
{
     Sum = 0;
     p_head= nullptr;
     m_size = 0;
}
List::~List()
{
    Node *temp = p_head;
   for(int i =0 ;i < m_size; i++){
       temp = p_head;
       delete temp;
       p_head=p_head->p_next;
   }
}

void List::Del_books()
{
    double AverPrice = Sum/m_size;
    Node *pp_current_book = p_head;
    if(p_head==nullptr){
        return;
    }
    while(true) {
        Node *p_temp =(pp_current_book);
        (pp_current_book) = (pp_current_book)->p_next;
        //if list is empty end the work
        if(!(pp_current_book)) {
          break;
        }
        if((pp_current_book)->m_price < AverPrice) {
          if(!(pp_current_book)->p_next) {
            Sum-=pp_current_book->m_price;
            p_temp->p_next=nullptr;
            m_size--;
            break;
          }
          p_temp->p_next = (pp_current_book)->p_next;
          Sum-=pp_current_book->m_price;
          delete pp_current_book;
          m_size--;
          (pp_current_book)=p_temp;
        }
      }
      (pp_current_book)=(p_head);
      // check first element of list
      if((pp_current_book)->m_price < AverPrice) {
        if((pp_current_book)->p_next) {
          (p_head) = (pp_current_book)->p_next;
            Sum-=pp_current_book->m_price;
            m_size--;
        } else {
          (p_head) = nullptr;
        }
      }
}
QString List::Del_Formal()
{
    QString text="";
    double AverPrice = Sum/m_size;
    Node *pp_current_book = p_head;
    if(p_head==nullptr){
        return "Empty";
    }
    while(true) {
        //Node *p_temp =(pp_current_book);
        (pp_current_book) = (pp_current_book)->p_next;
        //if list is empty end the work
        if(!(pp_current_book)) {
          break;
        }
        if((pp_current_book)->m_price < AverPrice) {
          if(!(pp_current_book)->p_next) {
            (pp_current_book) = (pp_current_book)->p_next;
            break;
          }
          (pp_current_book) = (pp_current_book)->p_next;
        }
        text+="Author: "+pp_current_book->m_author_name+" "+pp_current_book->m_author_surname+
       " | Book title: \""+ pp_current_book->m_book_name+"\" | Year: " +
        QString::number(pp_current_book->m_year)+" | Pages : | "+QString::number(pp_current_book->m_pages)+
        " | Price: " + QString::number(pp_current_book->m_price) + " |\n";
      }
      (pp_current_book)=(p_head);
      // check first element of list
      if((pp_current_book)->m_price < AverPrice) {
          return text;
      }
      text+="Author: "+pp_current_book->m_author_name+" "+pp_current_book->m_author_surname+
     " | Book title: \""+ pp_current_book->m_book_name+"\" | Year: " +
      QString::number(pp_current_book->m_year)+" | Pages : | "+QString::number(pp_current_book->m_pages)+
      " | Price: " + QString::number(pp_current_book->m_price) + " |\n";
      return text;
}
QString List::Find_A()
{
    QString temp="";
    Node *p_run = p_head;
    bool my_bool=false;
       if(p_head) {
          while(p_run) {
            if(p_run->m_author_surname[0]=='A') {
                temp+= "Author: "+p_run->m_author_name+" "+p_run->m_author_surname+
                " | Book title: \""+ p_run->m_book_name+"\" | Year: " +
                QString::number(p_run->m_year)+" | Pages : | "+QString::number(p_run->m_pages)+
                 " | Price: " + QString::number(p_run->m_price) + " |\n";
              my_bool=true;
            }
            p_run=p_run->p_next;
          }
          if(!my_bool) {
           temp += "\nTHERE IS NO ATHOUR WITH A IN SURNAME\n";
          }
        }else {
          temp += "\nTHERE IS NO ATHOUR WITH A IN SURNAME\n";
        }
      return temp;
}
void List::Sort()
{
    Node *p_change_root = nullptr;
    // going arcoss the list till the end
    while ((p_head) != NULL) {
        Node *pTemp = p_head;
        p_head = p_head->p_next;
        //if price of current book bigger then privious one we go to next element
        //or there is no previous book
        if (p_change_root == NULL || pTemp->m_price < p_change_root->m_price) {
          pTemp->p_next = p_change_root;
          p_change_root = pTemp;
        } else {
        //if price of current book less then previous one we swap this books
          Node *p_current = p_change_root;
          while (p_current->p_next != NULL && (pTemp->m_price >= p_current->p_next->m_price)) {
            p_current = p_current->p_next;
          }
          pTemp->p_next = p_current->p_next;
          p_current->p_next = pTemp;
        }
      }
      p_head = p_change_root;
}
QString List::Print()
{
    Node *val = p_head;
    QString temp="";
    int i=1;
    if(p_head==nullptr)
    {
        return "Empty";
    }
    while(val!=nullptr){
        temp+= QString::number(i)+". Author: "+val->m_author_name+" "+val->m_author_surname+
        " | Book title: \""+ val->m_book_name+"\" | Year: " +
        QString::number(val->m_year)+" | Pages : | "+QString::number(val->m_pages)+
         " | Price: " + QString::number(val->m_price) + " |\n";
        val=val->p_next;
        ++i;
    }
    return temp;
}
 double List::Get_size()
 {
     return m_size;
 }
void List::push_back(QString author_name, QString author_surname,
 QString book_name, int year, int pages, double price)
{
    if(p_head==nullptr){
        p_head = new Node(author_name, author_surname,book_name,
            year, pages , price);
        m_size++;
        Sum += price;
        return;
    }
    else {
        Node *temp = p_head;
        while((temp)->p_next!=nullptr){
            (temp) = (temp)->p_next;
        }
        (temp)->p_next = new Node(author_name, author_surname,book_name,
                year, pages, price);
        m_size++;
        Sum += price;
    }
}
void List::Del_number(int val)
{
    Node *pp_current_book = p_head;
    if(p_head==nullptr){
        return;
    }
    int i=1;
    while(true) {
        ++i;
        Node *p_temp =(pp_current_book);
        (pp_current_book) = (pp_current_book)->p_next;
        //if list is empty end the work
        if(!(pp_current_book)) {
          break;
        }
        if(i== val) {
          if(!(pp_current_book)->p_next) {
            p_temp->p_next=nullptr;
            m_size--;
            break;
          }
          p_temp->p_next = (pp_current_book)->p_next;
          delete pp_current_book;
          m_size--;
          (pp_current_book)=p_temp;
        }
      }
      (pp_current_book)=(p_head);
      // check first element of list
      if(val==1) {
        if((pp_current_book)->p_next) {
          (p_head) = (pp_current_book)->p_next;
            m_size--;
        } else {
          (p_head) = nullptr;
        }
      }
      m_size--;
}
