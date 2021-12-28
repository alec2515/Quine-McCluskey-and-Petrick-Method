#include <vector>
#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

using namespace std;

class Linkedlist;

class Listnode
{
public:
    Listnode(vector<int>);

private:
    vector<int> data;
    vector<int> cover;
    int number;
    int get1, get2;
    int match;
    char label;
    Listnode *next;
    Listnode *colnext;

    friend class Linkedlist;
};

class Linkedlist
{
public:
     Linkedlist():first(0),curcol(0),getdata(0){};
     void Printlist();
     void Push_col(vector<int>, vector<int>);
     void Push_back(vector<int>, vector<int>);
     void match(vector<int>);
     void Change_label(vector<int>);
     void Restart(int);
     void Lastcheck(int);
     void startpoint(int);
     bool Redirection();
     int Resize();
     void Clear();
     void DeleteDuplicate();
     void sorting();
     vector<int> Getlist(int , int);
     vector<int> Getcover(vector<int>);
     vector<vector<int>> Getprime();
     vector<vector<int>> Getprimecover();

private:
    Listnode *first;
    Listnode *curcol;
    Listnode *getdata;
};

#endif // LINKEDLIST_H_INCLUDED
