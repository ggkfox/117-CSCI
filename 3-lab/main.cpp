// joshua holland | lab 3
// the program will take has a portain for declaration and a section for statements (commands).
// you can create variables in the declaration area, and assign values to those variables in the statements area.
// statements section is declared by "program".
// can assign the values of one variable to another
// can assign math expressions to a variable
// can print values of variales with syntax "print x".
// spits errors if u are missing syntax such as no '=', no ';', or just non supported syntax.
#include <cstdlib> //for atoi()
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

ifstream fin;
string prog, s1, s2;
int indexx = 0; //global index for program string
int sym_index = 0; //global for symbol table index

struct node { 
	char id; //single letter var name
	string type;
	double value;
};
struct node sym_table[100]; //symbol table with 100 entries

void declarations();
void declaration(string);
void statements();
void statement(string);
void assign_state(string);
void print_state();
int get_sym_index(char);
int Exp();
int Term();
int Pow();
int Exp2(int);
int Term2(int);
int Pow2(int);
int Fact();

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
int main(int argc, const char **argv) {
	string path1 = argv[1];
	fin.open(path1.c_str()); //open data file

	fin>>s1;
	if(s1 == "program") {
        declarations();
        statements();
        
        /****display symbol_table entries****/
        cout<<"++symbol table++"<<endl;
        for(int i=0; i<sym_index; i++)
            cout<<sym_table[i].id<<"   "<<sym_table[i].type<<"   "<<sym_table[i].value<<endl;
        /************************************/
    }
    else
        cout<<"usage: program {<declarations>} begin {<statements>} end"<<endl;

    fin.close();
    return 0;
}


void declarations() {   //recursively calls declaration()
    string word;
    fin>>word;

    if( word == "begin")
        return;
    else if(word=="int" || word=="double") 
        declaration(word); //for one line of declaration until ';' 
    else {
        cout<<"syntax error: usage: <type> <id> {,<id>} ;"<<endl;
        return; //or exit(1) to terminate the interpreter
    }
    declarations(); //recursion for next declaration
}    


void declaration(string word) {  //para is type (int or double)
    string s1;
    fin>>s1; //assume a, or a; cases
    while(s1.at(1) == ',') {
        sym_table[sym_index].id = s1.at(0); //id is char type
        sym_table[sym_index].type = word;
        sym_index++;
        fin>>s1;
    }
    if (s1.at(1) == ';') {
        sym_table[sym_index].id = s1.at(0); //id is char type
        sym_table[sym_index].type = word;
        sym_index++;
    }
    else {
        cout<<"syntax error: missing \';\'"<<endl;
        exit(1); //may use exit(1) to terminate the interpreter
    }
}


void statements() { 
    string word;
    fin>>word;
    if(word == "end")
        return;
    else
        statement(word); //for single statement

    statements(); //recursion for next single statement
}

void statement(string word) {
    if(word == "print")
        print_state();
    else if (word.length()==1 && isalpha(word.at(0)))
        assign_state(word);
    else {
        cout<<"syntax error: invalid statement"<<endl;
        exit(1); //may use exit(1); to terminate interpreter
    }
}


void assign_state(string word) {
    //cout<<"=== in assign_state()"<<endl;
    fin>>s1;
    getline(fin, s2); //reads entire line 
    if (s1[0] == '=') {
        if (isalpha(s2.at(1)) && s2.at(2)==';')
            sym_table[get_sym_index(word.at(0))].value = sym_table[get_sym_index(s2.at(1))].value;
        else {
            prog = s2.substr(0, s2.length()-1);
            indexx = 0;
            sym_table[get_sym_index(word.at(0))].value = Exp();
        }
    }
    else {
        cout<<"expected opporator after expression " << word.at(0) << ".\n";
        exit(1); //exit code.
    }
}

void print_state() {
    //cout<<"=== in print_state()"<<endl;
    getline(fin, s2); //reads entire line
    if (s2.at(s2.length()-1) != ';') {
        cout << "expected \';\' at end of line." << endl;
        exit(1);
    }
    cout<<"print "<< s2.substr(0, s2.length()-1) << endl;
    if (isalpha(s2.at(1))) {
        for (int i = 0; i < sym_index; i++) {
            if (sym_table[i].id == s2[1]) cout<< "    " << sym_table[i].value << endl;
        }
    }
    else {
        prog = s2.substr(0, s2.length()-1);
        indexx = 0;
        cout<< "    " << Exp() << endl;
    }
}

int get_sym_index(char word) {
    for (int i = 0; i < sym_index; i++) {
        if (sym_table[i].id == word) {
            return i;
        }
    }
}

int Exp() {
//  cout << "exp > ";
    return Exp2(Term());
}

int Term() {
//  cout << "term > ";
    return Term2(Pow());
}
int Pow() {
//  cout << "pow > ";
    return Pow2(Fact());
}
int Exp2(int inp) {
//  cout << "exp2 > ";
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
//  cout << "term2 > ";
    int result = inp;
    if (indexx < prog.length()) {  //if not the end of program string
        char a = prog.at(indexx++); //get one chr from program string
        while (a == ' ' && indexx < prog.length())
            a = prog.at(indexx++);
        if (indexx > prog.length()) return result;
        if (a == '*')
            result = Term2(result * Pow()); //handles consecutive * operators
        else if (a == '/')
            result = Term2(result / Pow()); //handles consecutive / operators
        else if (a == '+' || a == '-' || a == ')') //if + or -, get back one position
            indexx--;
    }
    return result;
}
//// all new function handles powers and parenthesis.
int Pow2(int inp) {
//  cout << "pow2 > ";
    int result = inp;
    if (indexx < prog.length()) {  //if not the end of program string
        char a = prog.at(indexx++); //get one chr from program string
        while (a == ' ' && indexx < prog.length())
            a = prog.at(indexx++);
        if (indexx > prog.length()) return result;
        if (a == '(') result = result * Pow2(Exp()); //short-hand or factoring. "2(2+3)" while also leaving following exponents pressidence: "2(4-2)^3"
        else if (a == '^')
            result = pow(result, Pow()); //handles consecutive ^ operators
        else if (a == '+' || a == '-' || a == '*' || a == '/' || a == ')') //if '+' or '-' or '*' or '/' or ')', get back one position
            indexx--;
    }
    return result;
}
int Fact() {
//  cout << "fact > ";
    char a = prog.at(indexx++); //get one chr from program string
    while (a == ' ' && indexx < prog.length())
        a = prog.at(indexx++);
    if (a == '(') return Exp(); //recursively starts everything over if it finds '('.
    return atoi(&a); //converts a char to a numeric number and return
}
