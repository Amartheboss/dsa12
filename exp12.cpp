#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

class Student{
    typedef struct{
        int roll;
        char name[10];
        char div;
        char add[10];
    }Record;
    const char*filename="stud.dat";
    Record rec;

public:
    void create();
    void display();
    int search();
    void Delete();
};

void Student::create(){
    char ans;
    ofstream fout;
    fout.open(filename,ios::out|ios::binary);

    do{
        cout<<"\n\tEnter Roll no of Student: ";
        cin>>rec.roll;
        cout<<"\tEnter a Name of Student: ";
        cin>>rec.name;
        cout<<"\tEnter a Division of Student: ";
        cin>>rec.div;
        cout<<"\tEnter a Address of Student: ";
        cin>>rec.add;

        fout.seekp((rec.roll-1)*sizeof(Record));//Move the write pointer to the desired position
        fout.write((char*)&rec,sizeof(Record));

        cout<<"\n\tDo you want to Add more Records: ";
        cin>>ans;
    } while(ans=='y'||ans=='Y');
    fout.close();
}

void Student::display(){
    ifstream fin;
    fin.open(filename, ios::in | ios::binary);
    cout << "\nThe contents of file are : \n";
    cout << "\nR.No.\tName\tDiv\tAddress";
    while (fin.read((char *)&rec, sizeof(Record))){
        if (rec.roll != 0){
            cout << "\n" << rec.roll << "\t" << rec.name << "\t" << rec.div << "\t" << rec.add;
        }
    }
    fin.close();
}

int Student ::search(){
    ifstream fin;
    fin.open(filename, ios::binary);
    cout << "\nEnter Roll No.: ";
    int r;
    cin >> r;
    fin.seekg((r - 1) * sizeof(Record));
    fin.read((char *)&rec, sizeof(Record));
    if (rec.roll == r){
        cout << "\nRecord Found.\n ";
        cout << "\nR.No.\tName\tDiv\tAddress";
        cout << "\n" << rec.roll << "\t" << rec.name << "\t" << rec.div << "\t" << rec.add;
        return r;
    } else {
        cout << "\nRecord Not Found.";
    }
    fin.close();
    return -1;
}

void Student::Delete(){
    int pos=search();

    if (pos==-1){
        cout<<"\n\tRecord Not Found";
        return;
    }  

    fstream f;
    f.open(filename,ios::in|ios::out|ios::binary);

    f.seekp((pos-1)* sizeof(Record));
    rec.roll=-1;
    strcpy(rec.name,"NULL");
    rec.div='N';
    strcpy(rec.add,"NULL");
    f.write((char*)&rec,sizeof(Record));

    f.close();
    cout<<"\n\tRecord Deleted";
}

int main(){
    Student obj;
    int ch;
    char ans;
    while (1){
        cout<<"\n\t*Student Information";
        cout<<"\n\t1. Create \n\t2.Display\n\t3.Search\n\t4.Delete\n\t5.Exit";
        cout<<"\n\tEnter Your Choice: ";
        cin>>ch;

        switch(ch){
            case 1:
                obj.create();
                break;
            case 2: 
                obj.display();
                break;
            case 3:
                obj.search();
                break;
            case 4:
                obj.Delete();
                break;
            case 5:
                break;
        }
    }
    return 0;
}
