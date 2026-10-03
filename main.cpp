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
        input >> employees[i].nKeysPossessed;
        for (int i2 = 0; i < employees[i].nKeysPossessed; i++){
            input >> employees[i].keys[i2].room >> employees[i].keys[i2].id;
        }
    }
}

void writer(string output_filename, Employee employees[], int nEmployees){
    ofstream output(output_filename);
    for (int i = 0; i < nEmployees; i++){
        output << nEmployees << endl << employees[i].name << endl << employees[i].nKeysPossessed;
        for (int i2 = 0; i < employees[i].nKeysPossessed; i2++){
            output << employees[i].keys[i2].room << " " << employees[i].keys[i2].id << " "; 
        }
    }
}
bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey, int newID){
    for (int i = 0; i < nEmployees; i++){
        if (employees[i].name == emp_name){
            if (employees[i].nKeysPossessed >= 5){
                cout << "This employee already has 5 keys!" << endl;
                return false;
            }
            else{
                for (int i2 = 0; i2 < employees[i].nKeysPossessed; i2++){
                    if (employees[i].keys[i2].room == newKey){
                        cout << "This employee already has this key!" << endl;
                        return false;
                    }
                    else{
                        Key newKey1;
                        newKey1.room = newKey;
                        newKey1.id = newID;
                        employees[i].keys[employees[i].nKeysPossessed] = newKey1;
                        employees[i].nKeysPossessed += 1;
                        return true;
                    }
                }
            }
        }
        else{
            cout << "Cannot find the specified employee" << endl;
            return false;
        }
    }
}
bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey){
    for (int i = 0; i < nEmployees; i++){
        if (employees[i].name == emp_name){
            for (int i2 = 0; i2 < employees[i].nKeysPossessed; i2++){
                if (employees[i].keys[i2].room == returnKey){
                    for (int i3 = i2; i3 < employees[i].nKeysPossessed-1; i3++){
                        employees[i].keys[i3] = employees[i].keys[i3 + 1];
                    }
                    employees[i].nKeysPossessed -= 1;
                    return 1;
                }
            }
            cout << "This employee does not have the specified key!" << endl;
            return 0;
        }
    }
    cout << "Cannot find the specified employee!" << endl;
            return 0;
}
int replaceAKey(Employee employees[], int nEmployees, string oldKey, string newKey);

int main(){
    cout << "Please enter key file name to start: " << endl;
    string filename;
    cin >> filename;
    return 0;

}