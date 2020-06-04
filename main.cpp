#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;






struct student {
    char firstName[80];
    char lastName[80];
    int id;
    float gpa;
};

struct node {
    student* student;
    node* next;
    int index;
};