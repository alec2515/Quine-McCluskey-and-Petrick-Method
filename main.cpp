#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>
#include "./pa_src/linkedlist.h"

using namespace std;

void parser(Linkedlist &, vector<string> &, vector<int> &, char *);
void quine_mccluskey(Linkedlist &);
void petrick(Linkedlist, vector<string>, vector<int>, char *);
bool check(int,vector<int>);

int main(int argc, char *argv[])
{

    vector<string> point;
    vector<int> all_col;
    Linkedlist qm_list;

    parser(qm_list, point, all_col, argv[1]);
    qm_list.sorting();
    quine_mccluskey(qm_list);
    petrick(qm_list, point, all_col, argv[2]);
    qm_list.Printlist();

    return 0;
}

void parser(Linkedlist &qm, vector<string> &point, vector<int> &allcol, char *argv)
{
    ifstream infile (argv, ios::in);
    vector<string> parser_in;
    vector<int> tmp, cov;

    if(!infile)
    {
        cerr << "File could not be opened" << endl;
        exit(1);

    }
    else
    {
        for(int i = 0; i < 3; i++)
        {
            string temp;
            getline(infile, temp);
            parser_in.push_back(temp);
        }

    }

    int alphabet_address = parser_in[0].find("=");

    while(parser_in[0].substr(alphabet_address+1, 1) != ";")
    {

        alphabet_address+=2;
        point.push_back(parser_in[0].substr(alphabet_address, 1));

    }

    int right_brackets = parser_in[2].find(")");
    int left_brackets = parser_in[2].find("(");

    while(right_brackets != parser_in[2].npos)
    {
        tmp.clear();
        cov.clear();
        int cover = 0;

        for(int i = 0; i < point.size(); i++)
        {
            if(parser_in[2].find(point[i], left_brackets) < right_brackets)
            {
                if(parser_in[2].substr(parser_in[2].find(point[i], left_brackets)-1,1) == "!")
                {
                    tmp.push_back(0);
                    cover = cover + 0*pow(2,point.size()-i-1);
                }
                else
                {
                    tmp.push_back(1);
                    cover = cover + 1*pow(2,point.size()-i-1);
                }
            }
        }

        cov.push_back(cover);
        allcol.push_back(cover);
        qm.Push_back(tmp, cov);
        right_brackets = parser_in[2].find(")", right_brackets+1);
        left_brackets = parser_in[2].find("(", left_brackets+1);
    }
}

void quine_mccluskey(Linkedlist &qm)
{

    vector<int> compare, be_compared;
    vector<int> newcover1, newcover2;

    while(!qm.Redirection())
    {

        int n = 0;

        for(int i = 0; i <= qm.Resize(); i++)
        {

            qm.startpoint(i);
            qm.Lastcheck(qm.Resize());

            //if(qm.Getlist(i+1, 1)[0] == -1)
           // {
           //     qm.Change_label(qm.Getlist(i, 1));
           //     continue;
           // }

            do
            {
                int check = 0;

                compare = qm.Getlist(i, 1);

                if(compare[0] == -1)
                    break;

                do
                {
                    be_compared = qm.Getlist(i+1, 2);

                    if(be_compared[0] == -1)
                        break;

                    int counter = 0;
                    int bit;

                    for(int b = 0; b < be_compared.size(); b++)
                    {
                        if(compare[b] != be_compared[b])
                        {
                            counter++;
                            bit = b;
                        }

                    }

                    if(counter == 1)
                    {
                        newcover1 = qm.Getcover(compare);
                        newcover2 = qm.Getcover(be_compared);
                        newcover1.insert(newcover1.end(), newcover2.begin(), newcover2.end());

                        qm.match(be_compared);


                        check++;
                        n++;
                        be_compared[bit] = 5;

                        if(n == 1)
                            qm.Push_col(be_compared, newcover1);

                        else
                            qm.Push_back(be_compared, newcover1);

                    }

                }
                while(true);

                qm.Restart(1);


                if(check == 0)
                {
                    qm.Change_label(compare);

                }

            }
            while(true);

            qm.Restart(2);

        }

        qm.DeleteDuplicate();

    }

}
void petrick(Linkedlist qm, vector<string> point, vector<int> allcol, char *argv)
{

    ofstream outfile (argv, ios::out);

    vector<vector<int>> prime_list, primecover;
    vector<int> get_prime_address;

    int temp;

    prime_list = qm.Getprime();
    primecover = qm.Getprimecover();

    for(int i = 0; i < allcol.size(); i++)
    {
        int duplicate = 0;

        for(int j = 0; j < primecover.size(); j++)
        {
            for(int k = 0; k < primecover[j].size(); k++)
            {
                if(allcol[i] == primecover[j][k])
                {
                    duplicate++;
                    temp = j;
                }

            }

        }


        if(duplicate == 1)
        {
            int non_duplicate = 0;

            for(int x = 0; x < get_prime_address.size(); x++)
            {
                if(temp == get_prime_address[x])
                {
                    non_duplicate++;
                    break;
                }
            }

            if(non_duplicate == 0)
                get_prime_address.push_back(temp);

            allcol.erase(allcol.begin() + i);
            i--;

        }

    }


    for(int i = 0; i < get_prime_address.size(); i++)
    {

        for(int j = 0; j < primecover[get_prime_address[i]].size(); j++)
        {
            for(int k = 0; k < allcol.size(); k++)
            {
                if(primecover[get_prime_address[i]][j] == allcol[k])
                {
                    allcol.erase(allcol.begin() + k);
                    k--;
                }

            }
        }

    }

    /*for(int i=0; i<get_prime_address.size(); i++)
    {
        cout << get_prime_address[i] << " ";
    }

    cout << endl;

    for(int i=0; i<allcol.size(); i++)
    {
        cout << allcol[i] << " ";
    }

    cout << endl;*/


    while(!allcol.empty())
    {
        int max_address = 0;
        int maximum = 0;

        for(int i = 0; i < primecover.size(); i++)
        {
            int counter = 0;

            if(check(i, get_prime_address))
                continue;

            for(int j = 0; j < primecover[i].size(); j++)
            {
                for(int k = 0; k < allcol.size(); k++)
                {
                    if(primecover[i][j] == allcol[k])
                        counter++;
                }

            }

            if(maximum < counter)
            {
                maximum = counter;
                max_address = i;
                //cout << maximum << endl;
            }

        }

        get_prime_address.push_back(max_address);

        for(int i = 0; i < primecover[max_address].size(); i++)
        {
            for(int j = 0; j < allcol.size(); j++)
            {
                if(primecover[max_address][i] == allcol[j])
                {
                    allcol.erase(allcol.begin() + j);
                    j--;
                }

            }
        }

    }

    sort(get_prime_address.begin(), get_prime_address.end());

    outfile << "INORDER = ";

    for(int i = 0; i < point.size(); i++)
    {
        if(i == point.size()-1)
            outfile << point[i] << ";";

        else
            outfile << point[i] << " ";

    }

    outfile << endl << "OUTORDER = output;" << endl;

    outfile << "output = ";

    for(int i = 0; i < get_prime_address.size(); i++)
    {
        outfile << "(";

        for(int j = 0; j < prime_list[get_prime_address[i]].size(); j++)
        {

            if(prime_list[get_prime_address[i]][j] == 5)
                continue;

            else
            {
                if(prime_list[get_prime_address[i]][j] == 1)
                    outfile << point[j];

                else if(prime_list[get_prime_address[i]][j] == 0)
                    outfile << "!" << point[j];

            }

            for(int k = j + 1; k < prime_list[get_prime_address[i]].size(); k++)
            {
                if(prime_list[get_prime_address[i]][k] != 5)
                {
                    outfile << "*";
                    break;
                }
            }

        }

        outfile << ")";

        if(i != get_prime_address.size()-1)
            outfile << "+";
    }


}

bool check(int primecover_address, vector<int> get_prime_address)
{

    for(int i = 0; i < get_prime_address.size(); i++)
    {
        if(primecover_address == get_prime_address[i])
        {
            return true;
        }
    }

    return false;
}
