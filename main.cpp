#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <cmath>

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
        cin.getline(input,50);
        if (strcmp(input, "ADD") == 0) {
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
        else if (strcmp(input, "GENERATE") == 0) {
            /*
            vector<char*> fNames;
            vector<char*> lNames;
            ifstream inFile;
            char* temp;
            char* temp2;
            int number = 0;
            char fileInput[1000];
            char fileInput2[1000];
            char fileName[100];
            //Takes in filenames for first and last names
            cout << "First File Name? \n";
            cin.getline(fileName, 100);
            inFile.open(fileName);
            inFile.getline(fileInput, 1000);
            temp = strtok(fileInput, " ");
            while (temp != NULL) {
                fNames.push_back(temp);
                temp = strtok(NULL, " ");
            }
            inFile.close();
            char fileName2[25];
            cout << "Second File Name? \n";
            cin.getline(fileName2, 100);
            inFile.open(fileName2);
            inFile.getline(fileInput2, 1000);
            temp2 = strtok(fileInput2, " ");
            while (temp2 != NULL) {
                lNames.push_back(temp2);
                temp2 = strtok(NULL, " ");
            }
            inFile.close();
            //Students to be generated
            cout << "How many students? \n";
            cin >> number;
            cin.get();
            for (int a = 0; a < number; a++) {
                char* firstName = new char();
                char* lastName = new char();
                int fIndex = 0;
                int lIndex = 0;
                float randGPA = 0;
                fIndex = rand() % fNames.size()+1;
                lIndex = rand() % lNames.size()+1;
                if (fIndex == 0) {
                    fIndex = 1;
                }
                firstName = fNames.at(fIndex - 1);
                lastName = lNames.at(lIndex - 1);
                randGPA = ((double) rand() / (RAND_MAX)) * 4;
                int lID = 0;
                for (vector<int>::iterator it = IDs.begin(); it != IDs.end(); ++it) {
                    if((*it) > lID) {
                        lID = (*it); 
                    }
                }
                IDs.push_back(lID + 1);
                Student* temp = new Student();
                temp -> fName = firstName;
                temp -> lName = lastName;
                temp -> GPA = randGPA;
                temp -> ID = lID + 1;
                int index = HVALUE(lID+1, size);
                bool valid = ADD(hashTable, index, temp);
                if (valid == false) {
                    Node** newHash = new Node*[size*2];
                    REHASH(newHash, hashTable, size);
                    hashTable = newHash; 
                }
            }
             */
        }
        else if (strcmp(input, "PRINT") == 0) {
         print(table, size);
        }
        else if (strcmp(input, "DELETE") == 0) {
            
            int id;
            cout << "Enter the ID" << endl;
            cin >> id;
            cin.get();
            IDs.push_back(id);
            remove(table, size, id);
            
        }
        else if (strcmp(input, "EXIT") == 0) {
            run = false;
        }
        else {
            cout << "Give a valid input";
        }
    }
    
    
    
}