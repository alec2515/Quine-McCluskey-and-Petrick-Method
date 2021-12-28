#include <iostream>
#include <vector>
#include "./pa_src/linkedlist.h"

using namespace std;

Listnode::Listnode(vector<int> a)
{
    data = a;
    number = get1 = get2 = match = 0;
    next = colnext = 0;
    label = '|';
}


void Linkedlist::Printlist()
{

    if (first == 0)
    {
        cout << "List is empty.\n";
        return;
    }

    Listnode *current = first;
    Listnode *colcurrent = first;
    int i=0;

    while(colcurrent != 0)
    {
        while (current != 0)
        {

            if(current->label == '*')
            {
                cout << i << " ";
                for(int i = 0; i < current->data.size(); i++)
                {
                    cout << current->data[i];
                }

                for(int j = 0; j < current->cover.size(); j++)
                {
                    cout << " " << current->cover[j];
                }
                cout <<  " " << current->label << endl;
                i++;
            }

            current = current->next;

        }

        colcurrent = colcurrent->colnext;
        current = colcurrent;
    }

}


vector<vector<int>> Linkedlist::Getprime()
{

    Listnode *current = first;
    Listnode *colcurrent = first;

    vector<vector<int>> prime;

    while(colcurrent != 0)
    {
        while (current != 0)
        {
            if(current->label == '*')
                prime.push_back(current->data);

            current = current->next;
        }

        colcurrent = colcurrent->colnext;
        current = colcurrent;
    }

    return prime;

}


vector<vector<int>> Linkedlist::Getprimecover()
{

    Listnode *current = first;
    Listnode *colcurrent = first;

    vector<vector<int>> primecov;

    while(colcurrent != 0)
    {
        while (current != 0)
        {
            if(current->label == '*')
                primecov.push_back(current->cover);

            current = current->next;
        }

        colcurrent = colcurrent->colnext;
        current = colcurrent;
    }

    return primecov;

}


void Linkedlist::sorting()
{

    Listnode *smallest = first;

    while(smallest->next != 0)
    {

        Listnode *current = smallest->next;

        while (current != 0)
        {
            if(current->number < smallest->number)
            {
                vector<int> data_tmp = smallest->data;
                vector<int> cover_tmp = smallest->cover;
                int number_tmp = smallest->number;

                smallest->data = current->data;
                smallest->cover = current->cover;
                smallest->number = current->number;

                current->data = data_tmp;
                current->cover = cover_tmp;
                current->number = number_tmp;

            }

            current = current->next;
        }

        smallest = smallest->next;
    }
}


void Linkedlist::startpoint(int x)
{

    Listnode *current = getdata;

    while(current != 0)
    {
        if(current->number == x)
        {
            getdata = current;
            return;
        }


        current = current->next;

    }
}


void Linkedlist::Change_label(vector<int> x)
{
    Listnode *current = getdata;
    while(current->next != 0)
    {
        if(x == current->data && current->match == 0)
        {
            current->label = '*';
            return;
        }

        current = current->next;
    }
}



void Linkedlist::match(vector<int> x)
{
    Listnode *current = getdata;

    while(current != 0)
    {
        if(x == current->data)
        {
            current->match = 1;
            return;

        }

        current = current->next;
    }


}


void Linkedlist::Push_col(vector<int> x, vector<int> cov)
{

    Listnode *newNode = new Listnode(x);
    newNode->cover = cov;

    for(int i = 0; i < x.size(); i++)
    {
        if(x[i] == 1)
            newNode->number++;
    }

    Listnode *current = curcol;
    while (current->colnext != 0)
    {
        current = current->colnext;
        getdata = current;
    }

    current->colnext = newNode;
    curcol = current->colnext;

}


void Linkedlist::Push_back(vector<int> x, vector<int> cov)
{

    Listnode *newNode = new Listnode(x);
    newNode->cover = cov;

    for(int i = 0; i < x.size(); i++)
    {
        if(x[i] == 1)
            newNode->number++;
    }

    if (first == 0)
    {
        first = newNode;
        curcol = first;
        getdata = first;
        return;
    }

    Listnode *current = curcol;
    while (current->next != 0)
    {
        current = current->next;
    }

    current->next = newNode;

}



vector<int> Linkedlist::Getlist(int x, int getting)
{

    Listnode *current = getdata;

    vector<int> err;
    err.push_back(-1);

    while(current != 0)
    {
        if(getting == 1)
        {
            if(current->number == x && current->get1 == 0)
            {
                current->get1 = 1;
                return current->data;
            }
        }
        else
        {
            if(current->number == x && current->get2 == 0)
            {
                current->get2 = 1;
                return current->data;
            }
        }

        current = current->next;
    }

    return err;

}


vector<int> Linkedlist::Getcover(vector<int> compare)
{

    Listnode *current = getdata;
    vector<int> newcover;

    while(current != 0)
    {
        if(compare == current->data)
        {
            return current->cover;
        }

        current = current->next;
    }

}


void Linkedlist::Restart(int mode)
{

    Listnode *current = getdata;

    while (current != 0)
    {
        if(mode == 2)
        {
            current->get1 = 0;
        }

        current->get2 = 0;
        current = current->next;
    }
}


void Linkedlist::Clear()
{

    while (first != 0)
    {
        Listnode *current = first;
        first = first->next;
        delete current;
        current = 0;
    }
}

bool Linkedlist::Redirection()
{
    getdata = curcol;

    Listnode *current = curcol;

    int n = 0;

    while(current->next != 0)
    {

        int bound = current->number;
        Listnode *check = curcol->next;

        while(check != 0 && check->number <= bound+1)
        {
            if(bound == check->number-1 && check->label != '*')
                n++;

            check = check->next;

        }

        current = current->next;

    }

    current = curcol;

    if(n == 0)
    {
        while(current != 0)
        {
            current->label = '*';
            current = current->next;
        }

        return true;

    }


    else
        return false;
}


int Linkedlist::Resize()
{
    Listnode *current = getdata;
    int temp = 0;

    while(current != 0)
    {
        if(temp < current->number)
            temp = current->number;

        current = current->next;
    }

    return temp;
}


void Linkedlist::Lastcheck(int Resize)
{
    Listnode *current = getdata;

    if(current->number != Resize)
    {
        return;
    }
    else
    {
        while(current != 0)
        {
            if(current->match == 0)
            {
                current->label = '*';
            }

            current = current->next;
        }

        return;

    }

}


void Linkedlist::DeleteDuplicate()
{
    Listnode *current = curcol;

    while(current != 0)
    {

        Listnode *p_curnext = current;
        Listnode *curnext = current->next;

        while(curnext != 0)
        {
            if(current->data == curnext->data)
            {
                Listnode *tmp = curnext;
                p_curnext->next = curnext->next;
                delete tmp;
                tmp = 0;
            }

            curnext =  curnext->next;
            p_curnext = p_curnext->next;
        }

        current = current->next;

    }

    return;

}
