#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Key{
    string room;
    int id;
};
struct Employee{
    string name;
    int nKeysPossessed;
    Key keys[5];
};

bool reader(string filename, Employee employees[], int& nEmployees){
    ifstream input(filename);
    if (!input.is_open()){
        return false;
    }
    input >> nEmployees;
    input.ignore();
    for (int i = 0; i < nEmployees; i++){
        getline(input, employees[i].name);
        input.ignore();
        int nKeys = 0;
        input >> nKeys;
        for (int i2 = 0; i < nKeys; i++){
            input >> employees[i].keys[i2].room >> employees[i].keys[i2].id;
        }
    }

void writer(string output_filename, Employee employees[], int nEmployees);
bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey, int newID);
bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey);
int replaceAKey(Employee employees[], int nEmployees, string oldKey, string newKey);

int main();{
    cout << "Please enter key file name to start: " << endl;
    string filename;
    cin >> filename;
    return 0;

}