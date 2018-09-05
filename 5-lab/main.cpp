#include<iostream>
#include<string>
#include<vector>
using namespace std;

/*
 * i used a vector of nodes for my program. 
 *
 * L1, L2, and free are all index pointers.
 *
 * insert assigns the new list object at the current free index
 *
 * delete alters the .next values so that the list will skip the deleted number
 *
 * collect garbage marks all elements that exist in L1 amd L2
 * then it finds the first non-marked element and runs a loop linking all the following "unmarked" elements into the free list.
 *
 * at the end of garbage collect, everything is unmarked.
 *
 * also i would like to note that deleted numbers are reset to "0" in the collect garbage function, not delete.
 *
*/

//create node that will be used in list
class node{
public:
    int data;
    int next;
    bool mark;
    //constructor
    node(int d = 0, int n = -1) {
        data = d;
        next = n;
        mark = false;
    }
    //getter and setter functions.
};

class marklist {
public:
    vector<node> list;
    int L1;
    int L2;
    int free;
    marklist(){
        L1 = -1;
        L2 = -1;
        free = 0;
        list.reserve(10);
        for (int i = 0; i < 10; i++) {
            node *nn = new node(0, i+1);
            list.push_back(*nn);
        }
        list.at(list.size()-1).next = -1; 
    }

    void insert(int a, int x) {
        //if there is no more free vector spots
        if (free == -1) {
            cout << "L" << a << "is full. can't insert " << x << " into the list." << endl;
            return;
        }
        //if user types invalid list
        if (a != 1 && a != 2) {
            cout << "your list selection is not valid" << endl;
            return;
        }
        int &_list = (a==1? L1:L2);
        //if this is the first insert into L1 or L2
        if (_list == -1) {
            _list = free;
            free = list.at(free).next;
            list.at(_list).next = -1;
            list.at(_list).data = x;
        }
        //if this isn't the first insert into L1 or L2
        else {
            int p = _list;
            while (list.at(p).next != -1) {p = list.at(p).next;}
            list.at(p).next = free;
            free = list.at(free).next;
            p = list.at(p).next;
            list.at(p).next = -1;
            list.at(p).data = x;
        }
    }

    void print_memory() {
        //prints everything in list 1
        cout << "L1 = {";
        int p = L1;
        while (p != -1) {
            cout << list.at(p).data << (list.at(p).next != -1? ",":"");
            p = list.at(p).next;
        }
        cout << "}" << endl;
        p = L2;
        cout << "L2 = {";
        while (p != -1) {
            cout << list.at(p).data << (list.at(p).next != -1? ",":"");
            p = list.at(p).next;
        }
        cout << "}" << endl;
        p = free;
        cout << "free = {";
        while (p != -1) {
            cout << list.at(p).data << (list.at(p).next != -1? ",":"");
            p = list.at(p).next;
        }
        cout << "}" << endl;
    }
    
    void delete_memory(int a, int x) {
        int &_list = (a==1? L1:L2);
        int p = _list;
        while (p != -1) {
            //if the first object must be deleted
            if (list.at(_list).data == x)
                _list = list.at(_list).next;
            //else
            else if (list.at(p).next != -1 && list.at(list.at(p).next).data == x) {
                list.at(p).next = list.at(list.at(p).next).next;
                continue; //if we delete list.at(p).next, then we have no need to move p. so we continue before we can jump p.
            }
            p = list.at(p).next;
        }
    }

    void garbage_collect() {
        int p1 = L1;
        int p2 = L2;
        int pf = free;
        //mark all values in list 1 and 2 as true;
        while (p1 != -1) {
            list.at(p1).mark = true;
            p1 = list.at(p1).next;
        }
        while (p2 != -1) {
            list.at(p2).mark = true;
            p2 = list.at(p2).next;
        }
        //set free to lowest non-marked element
        free = 0;
        while (list.at(free).mark == true) {
            free++;
            if (free == 10) { //return out if no garbage and no free nodes.
                free = -1;
                return;
            }
        }
        //set all garbage as 0 and link them in free list.
        list.at(free).next = -1;
        list.at(free).data = 0;
        for (int i = free; i < 10 && i != -1; ) {
            for (int j = i+1; j < 10; j++) {
                if (list.at(j).mark == false){
                    list.at(j).data = 0;
                    list.at(i).next = j;
                    break;
                }
            }
            i = list.at(i).next;
            if (i != -1) list.at(i).next = -1;
        }
        //reset all marks to false.
        for (int i = 0; i < 10; i++) {
            list.at(i).mark = false;
        }
    }
};

int main() {
    marklist *mylist = new marklist;
    while (true) {
        //read and accept menu options
        cout << "please type your option: 0 - quit, 1 - insert, 2 - print memory, 3 - delete memory, 4 - garbage collect" << endl;
        int option;
        cin >> option;
        //The 3 menu options
        if (option == 1) { //inserts (takes values and calls function)
            cout << "enter the list you wish to insert to (1 or 2): ";
            int list;
            cin >> list;
            cout << "enter the data you wish to insert (any integer): ";
            int data;
            cin >> data;
            mylist->insert(list, data);
        }
        else if (option == 2) mylist -> print_memory(); //prints
        else if (option == 3) {
            cout << "enter the list you wish to delete from (1 or 2): ";
            int list;
            cin >> list;
            cout << "enter the number you wish to delete (deletes every instance): ";
            int data;
            cin >> data;
            mylist -> delete_memory(list, data); //deletes matching key from list
        }
        else if (option == 4) mylist -> garbage_collect();
        else return 0; //quits
    }
}
