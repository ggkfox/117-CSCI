//
//// Interpreter simplified infix expression with {+,-,*,/} operations;
//// Keyboard input, single digit number only and no spaces are allowed;
//// compile: $>g++ prog1.cpp
//// run with: >2+3*4/2+3+4*2

#include <cstdlib> //for atoi()
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

ifstream fin;
string prog, s1; //string for reading 1-line input expression (program)

int Exp(), Term(), Exp2(int), Term2(int), Fact();
int indexx = 0; //global index for program string
int main(int argc, const char **argv) {
    string path1 = argv[1];
    fin.open(path1.c_str()); //open data file

    getline(fin, prog); //read 1 line into string s1

    cout<<">";
    cout<<"result= "<<Exp()<<endl;
}
int Exp() {
    cout << "exp > ";
    return Exp2(Term());
}
int Term() {
    cout << "term > ";
    return Term2(Fact());
}
int Exp2(int inp) {
    cout << "exp2 > ";
    int result = inp;
    if (indexx < prog.length()) {  //if not the end of program string
        char a = prog.at(indexx++); //get one chr from program string
        while (a == ' ' && indexx < prog.length())
            a = prog.at(indexx++);
        if (indexx > prog.length()) return result;
        if (a == '+')
            result = Exp2(result + Term()); //handles T+T
        else if (a == '-')
            result = Exp2(result - Term()); //handles T-T
    }
    return result;
}
int Term2(int inp) {
    cout << "term2 > ";
    int result = inp;
    if (indexx < prog.length()) {  //if not the end of program string
        char a = prog.at(indexx++); //get one chr from program string
        while (a == ' ' && indexx < prog.length())
            a = prog.at(indexx++);
        if (indexx > prog.length()) return result;
        if (a == '*')
            result = Term2(result * Fact()); //handles consecutive * operators
        else if (a == '/')
            result = Term2(result / Fact()); //handles consecutive / operators
        else if (a == '+' || a == '-') //if + or -, get back one position
            indexx--;
    }
    return result;
}
int Fact() {
    cout << "fact > ";
    char a = prog.at(indexx++); //get one chr from program string
    while (a == ' ' && indexx < prog.length())
        a = prog.at(indexx++);
    return atoi(&a); //converts a char to a numeric number and return
}
