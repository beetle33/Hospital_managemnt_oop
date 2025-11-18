#include <iostream>
#include <fstream>
#include <string>
#include<cstddef>
using namespace std;

// Patient Module 
struct Patient {
    int id;
    string name;
    int age;
    string gender;
    string disease;
};

void addPatient() {
    system("cls");
    Patient p;
    cout << "Enter patient ID: ";
    cin >> p.id;
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, p.name);
    cout << "Enter age: ";
    cin >> p.age;
    cin.ignore();
    cout << "Enter gender: ";
    getline(cin, p.gender);
    cout << "Enter disease: ";
    getline(cin, p.disease);

    ofstream f("patients.txt", ios::app);
    f << p.id << "," << p.name << "," << p.age << "," << p.gender << "," << p.disease << endl;
    f.close();
    cout << "\nPatient added!\n";
    system("pause");
}

void showPatients() {
    system("cls");
    ifstream f("patients.txt");
    if(!f) { cout << "No patients found.\n"; system("pause"); return; }

    cout << "ID\tName\tAge\tGender\tDisease\n";
    cout << "----------------------------------\n";

    int id, age;
    string name, gender, disease;
    while(f >> id) {
        f.ignore();
        getline(f, name, ',');
        f >> age; f.ignore();
        getline(f, gender, ',');
        getline(f, disease);
        cout << id << "\t" << name << "\t" << age << "\t" << gender << "\t" << disease << endl;
    }
    f.close();
    system("pause");
}

void searchPatient() {
    system("cls");
    int id;
    cout << "Enter patient ID to search: ";
    cin >> id;

    ifstream f("patients.txt");
    if(!f) { cout << "No patients found.\n"; system("pause"); return; }

    int pid, age;
    string name, gender, disease;
    bool found = false;
    while(f >> pid) {
        f.ignore();
        getline(f, name, ',');
        f >> age; f.ignore();
        getline(f, gender, ',');
        getline(f, disease);
        if(pid == id) {
            cout << "Patient found:\n";
            cout << pid << "\t" << name << "\t" << age << "\t" << gender << "\t" << disease << endl;
            found = true;
            break;
        }
    }

    if(!found) cout << "Patient not found!\n";
    f.close();
    system("pause");
}

void editPatient() {
    system("cls");
    int id;
    cout << "Enter patient ID to edit: ";
    cin >> id;

    ifstream f("patients.txt");
    ofstream temp("temp.txt");
    if(!f) { cout << "No patients found.\n"; system("pause"); return; }

    int pid, age;
    string name, gender, disease;
    bool found = false;

    while(f >> pid) {
        f.ignore();
        getline(f, name, ',');
        f >> age; f.ignore();
        getline(f, gender, ',');
        getline(f, disease);

        if(pid == id) {
            found = true;
            Patient p;
            cout << "Enter new name: "; cin.ignore(); getline(cin, p.name);
            cout << "Enter new age: "; cin >> p.age; cin.ignore();
            cout << "Enter new gender: "; getline(cin, p.gender);
            cout << "Enter new disease: "; getline(cin, p.disease);
            temp << pid << "," << p.name << "," << p.age << "," << p.gender << "," << p.disease << endl;
        } else {
            temp << pid << "," << name << "," << age << "," << gender << "," << disease << endl;
        }
    }

    f.close();
    temp.close();
    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if(found) cout << "Patient updated!\n";
    else cout << "Patient not found!\n";
    system("pause");
}

void deletePatient() {
    system("cls");
    int id;
    cout << "Enter patient ID to delete: ";
    cin >> id;

    ifstream f("patients.txt");
    ofstream temp("temp.txt");
    if(!f) { cout << "No patients found.\n"; system("pause"); return; }

    int pid, age;
    string name, gender, disease;
    bool found = false;

    while(f >> pid) {
        f.ignore();
        getline(f, name, ',');
        f >> age; f.ignore();
        getline(f, gender, ',');
        getline(f, disease);

        if(pid == id) found = true;
        else temp << pid << "," << name << "," << age << "," << gender << "," << disease << endl;
    }

    f.close();
    temp.close();
    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if(found) cout << "Patient deleted!\n";
    else cout << "Patient not found!\n";
    system("pause");
}

void patientMenu() {
    while(true) {
        system("cls");
        cout << "Patient Management\n";
        cout << "a- Add\nb- Edit\nc- Delete\nd- Search\ne- Show\nf- Back\nChoice: ";
        char ch; cin >> ch; cin.ignore();
        if(ch=='a') addPatient();
        else if(ch=='b') editPatient();
        else if(ch=='c') deletePatient();
        else if(ch=='d') searchPatient();
        else if(ch=='e') showPatients();
        else if(ch=='f') break;
    }
}

// Prescription Module
int preID[100], prePat[100];
string preMed[100];
int preCount = 0;

void loadPres() {
    ifstream f("prescriptions.txt");
    preCount = 0;
    while(f >> preID[preCount] >> prePat[preCount]) {
        f.ignore();
        getline(f, preMed[preCount]);
        preCount++;
    }
    f.close();
}

void savePres() {
    ofstream f("prescriptions.txt");
    for(int i=0;i<preCount;i++)
        f << preID[i] << " " << prePat[i] << " " << preMed[i] << endl;
    f.close();
}

void addPres() {
    if(preCount==0) preID[preCount]=1001;
    else preID[preCount]=preID[preCount-1]+1;

    cout << "Enter patient ID: ";
    cin >> prePat[preCount];
    cin.ignore();
    cout << "Enter medicines: ";
    getline(cin, preMed[preCount]);
    preCount++;
    savePres();
    cout << "Prescription added!\n";
    system("pause");
}

void showAllPres() {
    system("cls");
    cout << "PreID\tPatientID\tMedicines\n";
    for(int i=0;i<preCount;i++)
        cout << preID[i] << "\t" << prePat[i] << "\t" << preMed[i] << endl;
    system("pause");
}

void showPresByPat() {
    system("cls");
    int id;
    cout << "Enter patient ID: ";
    cin >> id;
    cout << "PreID\tMedicines\n";
    for(int i=0;i<preCount;i++)
        if(prePat[i]==id)
            cout << preID[i] << "\t" << preMed[i] << endl;
    system("pause");
}

void editPres() {
    system("cls");
    int id;
    cout << "Enter prescription ID to edit: ";
    cin >> id;
    cin.ignore();
    for(int i=0;i<preCount;i++)
        if(preID[i]==id) {
            cout << "New medicines: ";
            getline(cin, preMed[i]);
            savePres();
            cout << "Prescription updated!\n";
            system("pause");
            return;
        }
    cout << "Prescription not found!\n";
    system("pause");
}

void deletePres() {
    system("cls");
    int id;
    cout << "Enter prescription ID to delete: ";
    cin >> id;
    for(int i=0;i<preCount;i++)
        if(preID[i]==id) {
            for(int j=i;j<preCount-1;j++) {
                preID[j]=preID[j+1];
                prePat[j]=prePat[j+1];
                preMed[j]=preMed[j+1];
            }
            preCount--;
            savePres();
            cout << "Prescription deleted!\n";
            system("pause");
            return;
        }
    cout << "Prescription not found!\n";
    system("pause");
}

void presMenu() {
    while(true) {
        system("cls");
        cout << "Prescription Management\n";
        cout << "1- Add\n2- Edit\n3- Delete\n4- Show All\n5- Show by Patient\n6- Back\nChoice: ";
        int ch; cin >> ch; cin.ignore();
        if(ch==1) addPres();
        else if(ch==2) editPres();
        else if(ch==3) deletePres();
        else if(ch==4) showAllPres();
        else if(ch==5) showPresByPat();
        else if(ch==6) break;
    }
}

//  Medicine Module
struct Medicine {
    int id;
    string name;
    int qty;
    float price;
};

Medicine* loadMeds(int &count) {
    ifstream f("Medicines.txt");
    if(!f) { count=0; return NULL; }
    count=0; 
	Medicine temp;
    while(f >> temp.id) { f.ignore(); getline(f, temp.name, ' '); f >> temp.qty >> temp.price; count++; }
    f.close();
    Medicine* arr = new Medicine[count];
    f.open("Medicines.txt");
    for(int i=0;i<count;i++) { f >> arr[i].id; f.ignore(); getline(f, arr[i].name, ' '); f >> arr[i].qty >> arr[i].price; }
    f.close();
    return arr;
}

void saveMeds(Medicine* arr, int count) {
    ofstream f("Medicines.txt");
    for(int i=0;i<count;i++) f << arr[i].id << " " << arr[i].name << " " << arr[i].qty << " " << arr[i].price << endl;
    f.close();
}

void addMed() {
    system("cls");
    int n; cout << "How many medicines to add? "; cin >> n; cin.ignore();
    Medicine* arr = new Medicine[n];
    for(int i=0;i<n;i++) {
        cout << "\nID: "; cin >> arr[i].id; cin.ignore();
        cout << "Name: "; getline(cin, arr[i].name);
        cout << "Qty: "; cin >> arr[i].qty;
        cout << "Price: "; cin >> arr[i].price; cin.ignore();
        ofstream f("Medicines.txt", ios::app); f << arr[i].id << " " << arr[i].name << " " << arr[i].qty << " " << arr[i].price << endl; f.close();
    }
    delete[] arr;
    cout << "Added!\n"; system("pause");
}

void showMeds() {
    system("cls");
    ifstream f("Medicines.txt"); if(!f) { cout << "No meds!\n"; system("pause"); return; }
    Medicine m;
    cout << "ID\tName\tQty\tPrice\n---------------------------\n";
    while(f >> m.id) { f.ignore(); getline(f, m.name, ' '); f >> m.qty >> m.price; cout << m.id << "\t" << m.name << "\t" << m.qty << "\t" << m.price << endl; }
    f.close(); system("pause");
}

void editMed() {
    int count; Medicine* arr = loadMeds(count);
    if(count==0) { cout << "No meds!\n"; system("pause"); return; }
    int id; cout << "Enter ID to edit: "; cin >> id; cin.ignore();
    bool found=false;
    for(int i=0;i<count;i++) {
        if(arr[i].id==id) {
            found=true; char ch='x';
            while(ch!='e') {
                cout << "a- ID\nb- Name\nc- Qty\nd- Price\ne- Save\nChoice: "; cin >> ch; cin.ignore();
                if(ch=='a'){ cout<<"New ID: "; cin>>arr[i].id; cin.ignore(); }
                else if(ch=='b'){ cout<<"New Name: "; getline(cin, arr[i].name); }
                else if(ch=='c'){ cout<<"New Qty: "; cin>>arr[i].qty; cin.ignore(); }
                else if(ch=='d'){ cout<<"New Price: "; cin>>arr[i].price; cin.ignore(); }
            }
            break;
        }
    }
    if(!found) cout<<"Not found!\n";
    else { saveMeds(arr,count); cout<<"Updated!\n"; }
    delete[] arr; system("pause");
}

void delMed() {
    int count; Medicine* arr = loadMeds(count);
    if(count==0) { cout << "No meds!\n"; system("pause"); return; }
    int id; cout<<"Enter ID to delete: "; cin>>id;
    bool found=false; Medicine* temp=new Medicine[count-1]; int idx=0;
    for(int i=0;i<count;i++) { if(arr[i].id==id){found=true; continue;} temp[idx++]=arr[i]; }
    if(!found){ cout<<"Not found!\n"; delete[] temp; delete[] arr; system("pause"); return; }
    saveMeds(temp,idx); cout<<"Deleted!\n"; delete[] temp; delete[] arr; system("pause");
}

void medMenu() {
    while(true) {
        system("cls"); cout<<"***** MEDICINE MENU *****\n";
        cout<<"a- Add\nb- Edit\nc- Delete\nd- Show\ne- Back\nChoice: ";
        char ch; cin>>ch; cin.ignore();
        if(ch=='a') addMed();
        else if(ch=='b') editMed();
        else if(ch=='c') delMed();
        else if(ch=='d') showMeds();
        else if(ch=='e') break;
    }
}

// Main Menuu
int main() {
    loadPres();
    int ch;
    do {
        system("cls");
        cout << "  HOSPITAL MANAGEMENT \n";
        cout << "1- Patient\n2- Prescription\n3- Medicine\n4- Exit\nChoice: ";
        cin >> ch; cin.ignore();
        if(ch==1) patientMenu();
        else if(ch==2) presMenu();
        else if(ch==3) medMenu();
    } while(ch!=4);
    return 0;
}
