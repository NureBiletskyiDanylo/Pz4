#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Patient {
    string fullname;
    string homeAddress;
    string medCardNumber;
    string medPoliceNumber;
};

void createFile(Patient * mas, int n);
void readFile();
bool isInFile(Patient * mas, int n, string targetNum);
Patient* deletePatients(Patient* mas, int n, string targetNum);
Patient* addPatients(Patient* mas, int n, int k);
int main()
{
    Patient* mas;
    int n;
    cout << "Enter the size of patients list: ";
    cin >> n;
    mas = new Patient[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter fullname for patient: ";
        cin.ignore(); // Очищаємо буфер перед використанням getline()
        getline(cin, mas[i].fullname);

        cout << "Enter home address for patient: ";
        getline(cin, mas[i].homeAddress);

        cout << "Enter medical card number for patient: ";
        cin >> mas[i].medCardNumber;

        cout << "Enter medical police number for patient: ";
        cin >> mas[i].medPoliceNumber;

        cout << endl;
    }


    for (int i = 0; i < n; i++) {
        cout << mas[i].fullname;
        cout << endl;
        cout << mas[i].homeAddress;
        cout << endl;
        cout << mas[i].medCardNumber;
        cout << endl;
        cout << mas[i].medPoliceNumber;
        cout << endl;
    }

    createFile(mas, n);
    readFile();
    string targetNum;
    cin >> targetNum;
    if (isInFile(mas, n, targetNum)) {
        n -= 1;
        mas = deletePatients(mas, n, targetNum);
    }
    else {
        cout << "THIS VALUE IS NOT PRESENT IN FILE" << "\n";
    }

    int howManyAdd;
    cout << "How many patients do you want to add to the begining? ";
    cin >> howManyAdd;

    mas = addPatients(mas, n, howManyAdd);
    n += howManyAdd;

    createFile(mas, n);
    readFile();
    return 0;
}


void createFile(Patient* mas, int n) {
    fstream f("f.dat", ios::out);


    for (int i = 0; i < n; i++) {
        f << mas[i].fullname; f << "\n";
        f << mas[i].homeAddress; f << "\n";
        f << mas[i].medCardNumber; f << "\n";
        f << mas[i].medPoliceNumber; f << "\n";
    }

    f.close();
}

void readFile() {
    cout << "READING FILE" << "\n";
    int n = 1;
    Patient p;
    fstream f("f.dat", ios::in);
    if (!f.is_open()) {
        f.open("f.dat", ios::in);
    }
    while (getline(f, p.fullname)) {
        if (!getline(f, p.homeAddress)) break;
        if (!(f >> p.medCardNumber)) break;
        if (!(f >> p.medPoliceNumber)) break;
        cout << "Patient number " << n << "\n";
        n += 1;
        cout << p.fullname << " " << p.homeAddress << " " << p.medCardNumber << " " << p.medPoliceNumber << "\n";

        f.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    f.close();
}

bool isInFile(Patient* mas, int n, string targetNum) {
    for (int i = 0; i < n; i++) {
        if (mas[i].medCardNumber == targetNum) {
            return true;
        }
    }
    return false;
}

Patient* deletePatients(Patient* mas, int n, string targetNum) {
    Patient* newMas = new Patient[n];
    
    int oldN = n + 1;
    
    int newI = 0;
    int oldI = 0;
    while (newI < n && oldI < oldN) {
        if (mas[oldI].medCardNumber == targetNum) {
            oldI += 1;
        }
        else {
            newMas[newI++] = mas[oldI++];
        }
    }
    delete[] mas;
    return newMas;
}

Patient* addPatients(Patient* mas, int n, int k) {
    int newLen = n + k;
    Patient* newMas = new Patient[newLen];


    for (int i = 0; i < k; i++) {
        cout << "Enter fullname for patient: ";
        cin.ignore(); // Очищаємо буфер перед використанням getline()
        getline(cin, newMas[i].fullname);

        cout << "Enter home address for patient: ";
        getline(cin, newMas[i].homeAddress);

        cout << "Enter medical card number for patient: ";
        cin >> newMas[i].medCardNumber;

        cout << "Enter medical police number for patient: ";
        cin >> newMas[i].medPoliceNumber;

        cout << endl;
    }

    int j = 0;
    for (int i = k; i < newLen; i++) {
        newMas[i] = mas[j++];
    }

    delete[] mas;
    return newMas;
}