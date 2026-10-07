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
        input >> employees[i].nKeysPossessed;
        for (int i2 = 0; i2 < employees[i].nKeysPossessed; i2++){
            input >> employees[i].keys[i2].room >> employees[i].keys[i2].id;
        }
        input.ignore();
    }
    input.close();
    return true;
}

void writer(string output_filename, Employee employees[], int nEmployees){
    ofstream output(output_filename);
    output << nEmployees << endl;
    for (int i = 0; i < nEmployees; i++){
        output << employees[i].name << endl << employees[i].nKeysPossessed;
        for (int i2 = 0; i2 < employees[i].nKeysPossessed; i2++){
            output << " " << employees[i].keys[i2].room << " " << employees[i].keys[i2].id;
        }
        output << endl;
    }
    output.close();
}
bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey, int newID){
    for (int i = 0; i < nEmployees; i++){
        if (employees[i].name == emp_name){
            if (employees[i].nKeysPossessed >= 5){
                cout << "This employee already has 5 keys!" << endl;
                return false;
            }
            for (int i2 = 0; i2 < employees[i].nKeysPossessed; i2++){
                if (employees[i].keys[i2].room == newKey){
                    cout << "This employee already has this key!" << endl;
                    return false;
                }
            }
            Key newKey1;
            newKey1.room = newKey;
            newKey1.id = newID;
            employees[i].keys[employees[i].nKeysPossessed] = newKey1;
            employees[i].nKeysPossessed += 1;
            return true;
        }
    }
    cout << "Cannot find the specified employee!" << endl;
    return false;
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
                    return true;
                }
            }
            cout << "This employee does not have the specified key!" << endl;
            return false;
        }
    }
    cout << "Cannot find the specified employee!" << endl;
    return false;
}
int replaceAKey(Employee employees[], int nEmployees, string oldKey, string newKey){
    int keysReplaced = 0;
    for (int i = 0; i < nEmployees; i++){
        for (int i2 = 0; i2 < employees[i].nKeysPossessed; i2++){
            if (employees[i].keys[i2].room == oldKey){
                employees[i].keys[i2].room = newKey;
                cout << "Enter a new ID for the key: ";
                cin >> employees[i].keys[i2].id;
                keysReplaced += 1;
            }
        }
    }
    return keysReplaced;
}

int main(){
    cout << "Please enter key file name to start: " << endl;
    string filename;
    Employee employees[100];
    int nEmployees = 0;
    cin >> filename;
    bool fileReader = reader(filename, employees, nEmployees);
    if (fileReader == false){
        cout << "File not found, exiting the program..." << endl;
        return 0;
    }
    else{
        int choice = 1;
        while (choice != 0){
            cout << "Please select from the following options: " << endl << "  1. show all employees and their keys" << endl << "  2. show the keys an employee possesses" << endl <<
            "  3. show which employees possess a specific key by name" << endl << "  4. show which employees possess a specific key by number" << endl << "  5. add a key to an employee" << endl <<
            "  6. return a key by an employee" << endl << "  7. replace a key" << endl << "  8. save the current key status" << endl << "  0. exit the program" << endl;
            cin >> choice;
            if (choice == 1){
                for (int i = 0; i < nEmployees; i++){
                    cout << "Name: " << employees[i].name << endl;
                    cout << "Keys possessed: ";
                    for (int i2 = 0; i2 < employees[i].nKeysPossessed; i2++){
                        cout << employees[i].keys[i2].room << " ";
                    }
                    cout << endl;
                }
            }
            else if (choice == 2){
                string name1;
                bool found = false;
                cout << "Please enter employee's name: " << endl;
                cin.ignore();
                getline(cin, name1);
                for (int i = 0; i < nEmployees; i++){
                    if (name1 == employees[i].name){
                        found = true;
                        cout << name1 << " possesses the following keys: ";
                        for (int i2 = 0; i2 < employees[i].nKeysPossessed; i2++){
                            cout << employees[i].keys[i2].room << " ";
                        }
                        cout << endl;
                    }
                }
                if (found == false){
                    cout << "Cannot find the specified employee!" << endl;
                }
            }
            else if (choice == 3){
                string keyName;
                cout << "Please enter a key name: " << endl;
                cin >> keyName;
                int count = 0;
                for (int i = 0; i < nEmployees; i++){
                    for (int i2 = 0; i2 < employees[i].nKeysPossessed; i2++){
                        if (employees[i].keys[i2].room == keyName){
                            cout << employees[i].name << ", ";
                            count += 1;
                        }
                    }
                }
                if (count > 0){
                    cout << "possess this key." << endl;
                }
                else{
                    cout << "No one possesses this key." << endl;
                }
            }
            else if (choice == 4){
                int keyNum = 0;
                bool found = false;
                cout << "Please enter a key number: " << endl;
                cin >> keyNum;
                for (int i = 0; i < nEmployees; i++){
                    for (int i2 = 0; i2 < employees[i].nKeysPossessed; i2++){
                        if (employees[i].keys[i2].id == keyNum){
                            cout << employees[i].name << " possess this key." << endl;
                            found = true;
                        }
                    }
                }
                if (found == false){
                    cout << "No one possesses this key." << endl;
                }
            }
            else if (choice == 5){
                string empName;
                string keyName;
                int newID;
                cout << "Please enter employee's name: " << endl;
                cin.ignore();
                getline(cin, empName);
                cout << "Please enter a new key name and ID: " << endl;
                cin >> keyName >> newID;
                if (addKeyForEmployee(employees,nEmployees, empName, keyName, newID)){
                    cout << "Key added successfully." << endl;
                }
            }
            else if (choice == 6){
                string empName;
                string returnedKey;
                cout << "Please enter employee's name: " << endl;
                cin.ignore();
                getline(cin, empName);
                cout << "Please enter the returned key name: " << endl;
                cin >> returnedKey;
                if (returnAKey(employees,nEmployees,empName,returnedKey)){
                    cout << "Key returned successfully." << endl;
                }
            }
            else if (choice == 7){
                string oldKey;
                string newKey;
                cout << "Enter old key: " << endl;
                cin >> oldKey;
                cout << "Enter new key: " << endl;
                cin >> newKey;
                int reissued = replaceAKey(employees, nEmployees, oldKey, newKey);
                cout << "Reissued " << reissued << " keys." << endl;
            }
            else if (choice == 8){
                string outputName;
                cout << "Please enter output file name: " << endl;
                cin >> outputName;
                writer(outputName,employees,nEmployees);
            }
            else if (choice == 0){
                writer("keys_updated.txt", employees, nEmployees);
                cout << "Thank you for using the system! Goodbye!" << endl;
            }
            else{
                cout << "Not a valid option. Please try again." << endl;
            }
        }
    }
    return 0;
}
