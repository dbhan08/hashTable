#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <fstream>
using namespace std;






struct student {
    char* firstName;
    char* lastName;
    int id;
    float gpa;
};

struct node {
    student* student;
    node* next;
    int index;
};


int val(int id, int size) {
    int value = 0;
    while(id!= 0) {
        value += id%10;
        id =id/10;
    }
    
    int multiple = trunc(size/10);
    int val = (value*multiple) % size;
    return val;
}


bool add(node* table[], int hIndex, student* student) {
    
    
    if (table[hIndex] == NULL) {
        node* temp = new node();
        temp -> student = student;
        table[hIndex] = temp;
        return true;
    }
    
    
    node* temp = table[hIndex];
    int count = 0;
    while(temp!= NULL) {
        temp = temp->next;
        count++;
    }
    
    if(count > 3) {
        return false;
    } else {
        return true;
    }
}

void re(node* hash[], node* old[], int &size) {
    
    for (int i = 0; i < (size * 2); i++) {
        hash[i] = NULL;
    }
    int resize = size*2;
    for(int i = 0; i < size; i ++) {
        if(old[i] != NULL) {
            node* temp = old[i];
            while(temp != NULL) {
                student* stud = temp->student;
                int newInd = val(stud->id,resize);
                add(hash,newInd,stud);
                
                temp = temp->next;
            }
        }
    }
    
    size = resize;
}

void print(node* hash[], int size) {
    node* temp;
    for(int i = 0; i < size; i++) {
        if(hash[i] != NULL) {
            temp = hash[i];
            while(temp != NULL) {
                cout << "First name: " << temp->student->firstName << endl;
                cout << "Last name: "  << temp->student->lastName << endl;
                cout << "Gpa: "  << fixed << setprecision(2)<< temp->student->gpa << endl;
                cout << "ID: "  << temp->student->id << endl;
                temp = temp->next;
            }
        }
    }
    
}


void remove(node* hash[], int size, int id) {
    int value = val(id,size);
    node* temp = hash[value];
    node* prev = NULL;
    if(temp != NULL) {
        while(temp != NULL) {
            if(temp->student->id == id) {
                if(prev == NULL) {
                    hash[value] = temp->next;
                } else {
                    prev-> next = temp->next;
                }
                return;
            }
            prev = temp;
            temp = temp->next;
                
            }
        }
    return;
    }


void randomGen(node* table[], vector<int> &IDs, int &size) {
    ifstream inFile;
    vector<char*> firstNames;
    vector<char*> lastNames;
    char* input = new char[10000];
    char firstInput[10000];
     char secondInput[10000];
    char* temp;
    char* temp2;
    
    int amount;
    cout << "How many students would you like to add?" << endl;
    cin >> amount;
    cin.get();
    inFile.open(first);
    inFile.getline(firstInput, 1000);
    temp = strtok(firstInput, " ");
    
    while (temp != NULL) {
        firstNames.push_back(temp);
        temp = strtok(NULL, " ");
    }
    inFile.close();
    
    
    inFile.open(last);
    inFile.getline(secondInput, 1000);
    temp2 = strtok(secondInput, " ");
    while (temp2 != NULL) {
        lastNames.push_back(temp2);
        temp2 = strtok(NULL, " ");
    }
    inFile.close();
    
    for(int i = 0; i < amount; i++) {
        char* firstName = new char();
        char* lastName = new char();
        int fIndex = rand() % (firstNames.size()+1);
        int lIndex = rand() % (firstNames.size() +1);
         float random = (((float) rand()) / (float) RAND_MAX)*4; // From https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats/5289624
        
        firstName = firstNames.at(fIndex-1);
        firstName = lastNames.at(lIndex-1);
        int id = 0;
        vector<int>::iterator j;
        for (j = IDs.begin(); j != IDs.end();j++) {
            if((*j) >id ) {
                id = (*j);
            }
        }
        IDs.push_back(id + 2);
        student* stud = new student();
        stud->firstName = firstName;
        stud->lastName = lastName;
        stud->gpa = random;
        stud->id = id+2;
        int ind = val(id+2,size);
        bool valid = add(table, id, stud);
        if (valid == false) {
            node** newHash = new node*[size*2];
            re(newHash, table, size);
            delete [] table;
            table = newHash;
        }
    }
    
    
    }








int main() {
    int size = 100;
    char input[50];
    node** table = new node*[100];
    vector <int> IDs;
    
    for(int i = 0; i< 100; i++) {
        table[i] = NULL;
    }
    
    bool run = true;
    
    while(run) {
        
        cout << "Would you like to generate,add, print, delete, or quit?" << endl;
        cout << "To Add enter 1, to generate enter 2, to print enter 3, to delete enter 4, to quit enter 5" << endl;
        cin.getline(input,50);
        if (strcmp(input, "1") == 0) {
            int id;
            float gpa;
            char* fName = new char();
            char* lName = new char();
            cout << "Firstname? \n";
            cin.getline(fName, 20);
            cout << "Lastname? \n";
            cin.getline(lName, 20);
            cout << "ID? \n";
            cin >> id;
            cin.get();
            cout << "GPA? \n";
            cin >> gpa;
            cin.get();
            //Checks to see if duplicate, if not, adds it
            bool there = false;
            vector<int>:: iterator i;
            for ( i= IDs.begin(); i != IDs.end(); i++) {
                if((*i) == id) {
                    there = true;
                }
            }
            if (there == false) {
                IDs.push_back(id);
                //Creates new student
                student* temp = new student();
                temp -> firstName = fName;
                temp -> lastName = lName;
                temp -> id = id;
                temp -> gpa = gpa;
                int index = val(id, size);
                bool valid = add(table, index, temp);
                if (valid == false) {
                    node** newHash = new node*[size*2];
                    re(newHash, table, size);
                    delete [] table;
                    table = newHash;
                }
            }
            else {
                cout << "Already a student with that ID \n";
            }
        }
        //Random student generation
        else if (strcmp(input, "2") == 0) {
            void randomGen(table, IDs, size);
        }
        else if (strcmp(input, "3") == 0) {
         print(table, size);
        }
        else if (strcmp(input, "4") == 0) {
            
            int id;
            cout << "Enter the ID" << endl;
            cin >> id;
            cin.get();
            IDs.push_back(id);
            remove(table, size, id);
            
        }
        else if (strcmp(input, "5") == 0) {
            run = false;
        }
        else {
            cout << "Give a valid input";
        }
    }
    
    
    
}