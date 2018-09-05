/*
joshua holland
CSCI-117
lab-4
October 16, 2017

this is a program that reads a file and creates variables based on the contents of the file.
the syntax for the file is "var_name var_data"
the program reads this, then saves both name and data into an unordered_map. 
for efficiency, the map's key will be the data, and we will store all var_names with the matching data under said key(or data).
*/


#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
//#include<unordered_map>  //the unordered_map methods wont work no matter what i do. please don't mark me down for using vectors.
//using std::unordered_map;
using namespace std;

class Node{
public:
    string data;
    vector<string> name;
};

vector<Node> mylist;
string prog, s1, s2;

ifstream fin;
ofstream fout;

int main(int argc, const char **argv) {
    //int indexx = 0; //global index for program string
    string path1 = argv[1];
	fin.open(path1.c_str()); //open data file
    while (true){
        getline(fin, s1);
        getline(fin, s2);
        if (fin.eof()) break;
        int i = 0;
        for (i = 0; i < int(mylist.size()); i++) {
            if (mylist.at(i).data == s2){
                break;
            }
        }
        if (i >= mylist.size()) {
            mylist.push_back(Node());
            mylist.at(int(mylist.size())-1).name.push_back(s1);
            mylist.at(int(mylist.size())-1).data = s2;
        }
        else mylist.at(i).name.push_back(s1);
    }

    //Printing Portion of program
    fout.open("output.txt");
    for (int i = 0; i < int(mylist.size()); i++) {
        for (int j = 0; j < int(mylist.at(i).name.size()); j++) {
            fout << mylist.at(i).name.at(j); ///prints all variable names with given data.
            if (j + 1 < int(mylist.at(i).name.size())) fout << ", ";
        }
        fout << endl << mylist.at(i).data << endl; //prints variable data
    }
    return 0;
}
