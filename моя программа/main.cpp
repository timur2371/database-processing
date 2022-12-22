/* ����� �������� 2021 */
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip> // ������ � ��������������� �������
#include <cstdlib> // ��������� ��������� �����
#include <Windows.h> // ���������� ����������� ������������� �������
using namespace std;

// ���������� ����������
int menuChoice = 0; // ����� ���������� ������ ����
string menuItem[15] = {""}; // �������� ���� ������� ����
struct sweet
{
    string name; // ������������ ��������
    string productionMethod; // ������ ������������
    int price; // ����, ���
    int storageLife; // ���� ��������, ���
    int calorificValue; // ������������, ����
};
struct sweetNameNum
{
    string name;
    int num;
};
const int rowNumMax = 1000; // ������������ ���-�� ����� � ���� ������
int rowNum = 0; // ������� ���-�� ����� � ���� ������
sweet sweetDb[rowNumMax]; // ���� ������ �� ������������ �������
sweetNameNum sweetList[rowNumMax];


// 1.  �������� ���������� �� ������������ ���� ������ (����� �� �����).
void inputDb(bool fillRand) // ���� true, ��������� ���� ������ ���������� ����������
{
    string fileName;
    string name, productionMethod; int price, storageLife, calorificValue;

    cout << "������� �������� ����� ����� (input.txt): "; cin >> fileName; // ������ � input.txt
    cout << "���� ������" << endl;
    if (fillRand)
    {
        ofstream fout;
        fout.open("input.txt");
        for (int i=0; i<20; i++) // ��������� ���� ������ �� 20 �����
        {
            name = "������������_�������_" + std::to_string(i+1) + " ";
            if ((rand()%2) == 0) {
                productionMethod = "������ ";
            }
            else {
                productionMethod = "��������� ";
            }
            price = rand()%1000 + 100;
            storageLife = rand()%40 + 3;
            calorificValue = rand()%1000 + 200;
            fout << name << productionMethod << price << " " << storageLife << " " << calorificValue << endl;
        }
        // ������� ����������� �����
        fout.close();
    }

    ifstream fin;
    fin.open("input.txt");
    do
    {
        // ����� ������ � ���� ������
        fin >> sweetDb[rowNum].name >> sweetDb[rowNum].productionMethod >> sweetDb[rowNum].price >> sweetDb[rowNum].storageLife >> sweetDb[rowNum].calorificValue;
        rowNum++;
    }
    while (sweetDb[rowNum-1].name != ""); // ���� ������� ������ (������������� � ������) ��������, �� ������� ��������� ������ �����
    rowNum--; // ��������� ���� ������ ������ ������
    fin.close();
}

// 2.  �������� (����� �� �����) ������������ ���� ������.
void outputConsoleDb()
{
    cout << "| �    | ������������ ��������               | ������ ������������ | ����, ��� | ���� ��������, ��� | ������������, ���� |" << endl <<
            "--------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i=0; i<rowNum; i++)
    {
        cout << "| " << setw(4) << i+1 << " | " << setw(35) << sweetDb[i].name << " | " << setw(19) << sweetDb[i].productionMethod << " | " << setw(9) << sweetDb[i].price
             << " | " << setw(18) << sweetDb[i].storageLife << " |" << setw(19) <<  sweetDb[i].calorificValue << " | " << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
}

// 3.  ���������� ����� ������ � ���� ������.
void addRowDb()
{
    rowNum++;
    cout << "������� ������������ ��������: "; cin >> sweetDb[rowNum-1].name; // (rowNum-1) - ����� ��������� ������ � �������
    cout << "������� ������ ������������: ";   cin >> sweetDb[rowNum-1].productionMethod;
    cout << "������� ����, ���: ";             cin >> sweetDb[rowNum-1].price;
    cout << "������� ���� ��������, ���: ";    cin >> sweetDb[rowNum-1].storageLife;
    cout << "������� ������������, ����: ";    cin >> sweetDb[rowNum-1].calorificValue;
}

// 4.  �������� ������ �� ���� ������.
void deleteRowDb()
{
    int row;
    cout << "������� ����� ��������� ������: "; cin >> row;
    // ������ ����� ������ ������ �� ����� ����������
    for (int i=row; i<rowNum; i++)
    {
        sweetDb[i-1].name =             sweetDb[i].name;
        sweetDb[i-1].productionMethod = sweetDb[i].productionMethod;
        sweetDb[i-1].price =            sweetDb[i].price;
        sweetDb[i-1].storageLife =      sweetDb[i].storageLife;
        sweetDb[i-1].calorificValue =   sweetDb[i].calorificValue;
    }
    rowNum--;
}

// 5.  �������������� ������ � ���� ������.
void editRowDb()
{
    int row;
    cout << "������� ����� ���������� ������: "; cin >> row;
    cout << "������� ����� ������������ ��������: "; cin >> sweetDb[row-1].name;
    cout << "������� ����� ������ ������������: ";   cin >> sweetDb[row-1].productionMethod;
    cout << "������� ����� ����: ";                  cin >> sweetDb[row-1].price;
    cout << "������� ����� ���� ��������: ";         cin >> sweetDb[row-1].storageLife;
    cout << "������� ����� ������������: ";          cin >> sweetDb[row-1].calorificValue;
}

// 6.  ���������� ������� �� ��������� ����. - �� �����������
void sortNumDb()
{
    sweet temp;
    int submenuChoice;
    cout << "1. ����, ���" << endl;
    cout << "2. ���� ��������, ���" << endl;
    cout << "3. ������������, ����" << endl;
    cout << "�������� �� ������ ���� ����������� (1-3): "; cin >> submenuChoice;
    // ���������� ���������
    for (int i=0; i<rowNum-1; i++)
    {
        for (int j=i+1; j<rowNum; j++)
        {
            switch (submenuChoice)
            {
                case 1: if (sweetDb[j].price < sweetDb[i].price)                  {temp = sweetDb[j]; sweetDb[j] = sweetDb[i]; sweetDb[i] = temp;} break;
                case 2: if (sweetDb[j].storageLife < sweetDb[i].storageLife)      {temp = sweetDb[j]; sweetDb[j] = sweetDb[i]; sweetDb[i] = temp;} break;
                case 3: if (sweetDb[j].calorificValue < sweetDb[i].calorificValue){temp = sweetDb[j]; sweetDb[j] = sweetDb[i]; sweetDb[i] = temp;} break;
            }

        }
    }
    switch (submenuChoice)
    {
        case 1: cout << "���������� ��������� �� ����" << endl; break;
        case 2: cout << "���������� ��������� �� ����� ��������" << endl; break;
        case 3: cout << "���������� ��������� �� ������������" << endl; break;
        default: cout << "������ ������ ���� �� ����������, ���������� �� ���� ���������" << endl; break;
    }
}

// 7.  ���������� ������� �� ���������� ����. - �� �����������
void sortStringDb()
{
    sweet temp;
    int submenuChoice;
    cout << "1. ������������ ��������" << endl;
    cout << "2. ������ ������������" << endl;
    cout << "�������� �� ������ ���� ����������� (1-2): "; cin >> submenuChoice;
    // ���������� ���������
    for (int i=0; i<rowNum-1; i++)
    {
        for (int j=i+1; j<rowNum; j++)
        {
            switch (submenuChoice)
            {
                case 1: if (sweetDb[j].name < sweetDb[i].name)                              {temp = sweetDb[j]; sweetDb[j] = sweetDb[i]; sweetDb[i] = temp;} break;
                case 2: if (sweetDb[j].productionMethod < sweetDb[i].productionMethod)      {temp = sweetDb[j]; sweetDb[j] = sweetDb[i]; sweetDb[i] = temp;} break;
            }

        }
    }
    switch (submenuChoice)
    {
        case 1: cout << "���������� ��������� �� ������������ ��������" << endl; break;
        case 2: cout << "���������� ��������� �� ������� ������������" << endl; break;
        default: cout << "������ ������ ���� �� ����������, ���������� �� ���� ���������" << endl; break;
    }
}

// 8.  ���������� ����������� ��������� (������ � ����).
void outputFileDb()
{
    string fileName;
    ofstream fout;
    cout << "������� �������� ����� ������ (output.txt): "; cin >> fileName; // ������ � input.txt
    cout << "���� ������" << endl;
    fout.open("output.txt");
    fout << "| �    | ������������ ��������               | ������ ������������ | ����, ��� | ���� ��������, ��� | ������������, ���� |" << endl <<
            "--------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i=0; i<rowNum; i++)
    {
        fout << "| " << setw(4) << i+1 << " | " << setw(35) << sweetDb[i].name << " | " << setw(19) << sweetDb[i].productionMethod << " | " << setw(9) << sweetDb[i].price
             << " | " << setw(18) << sweetDb[i].storageLife << " |" << setw(19) <<  sweetDb[i].calorificValue << " | " << endl;
    }
    fout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
    fout.close();
}

// 9. ����� � ���� ������ (�� ������ � ���� ��������� ���������) � ������� �� ����� ��������� ������� ��� ��������� � ���������� ������. - �� ������������ ��������
void searchDb()
{
    int rowNumSearch=1;
    string name;
    cout << "������� ������������ ��������, ������� ����� �����: "; cin >> name;
    cout << "| �    | ������������ ��������               | ������ ������������ | ����, ��� | ���� ��������, ��� | ������������, ���� |" << endl <<
            "--------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i=0; i<rowNum; i++)
    {
        if (sweetDb[i].name == name) {
            cout << "| " << setw(4) << rowNumSearch << " | " << setw(35) << sweetDb[i].name << " | " << setw(19) << sweetDb[i].productionMethod << " | " << setw(9) << sweetDb[i].price
                 << " | " << setw(18) << sweetDb[i].storageLife << " |" << setw(19) <<  sweetDb[i].calorificValue << " | " << endl;
            rowNumSearch++;
        }
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
}

// 10. ������������ �������. - ��������
void createList()
{
    // ��������� ����� ������� sweetDb � ����� ���� ������ � ���, ����� �� "���������" �������� ������������ �������
    sweet sweetDbCopy[rowNumMax];
    for (int i=0; i<rowNum; i++) {
        sweetDbCopy[i] = sweetDb[i];
    }

    // ��� ��������� ������������� ������������ ��������� ���������, �������� �� ������ ����� �� ������� ������������
    for (int i=0; i<rowNum; i++) {
        sweetList[i].name = sweetDbCopy[i].name;
        sweetList[i].num = 1;
        for (int j=i+1; j<rowNum; j++) {
            if (sweetDbCopy[i].name == sweetDbCopy[j].name) {
                sweetDbCopy[j].name = "";
                sweetList[i].num++;
            }
        }
    }
    cout << "�������� �����������" << endl;
}

// 11. �������� (����� �� �����) �������.
void outputConsoleList()
{
    int row=0;
    cout << "| �    | ������������ ��������               | ���������� |" << endl <<
            "-----------------------------------------------------------" << endl;
    for (int i=0; i<rowNum; i++)
    {
        if (sweetList[i].name != "") {
            row++;
            cout << "| " << setw(4) << row << " | " << setw(35) << sweetList[i].name << " | " << setw(10) << sweetList[i].num << " |" << endl;
        }
    }
    cout << "-----------------------------------------------------------" << endl;
}

// 12. ���������� ������� �� �����.
void sortNumList()
{
    sweetNameNum temp;
    for (int i=0; i<rowNum-1; i++) {
        for (int j=i+1; j<rowNum; j++) {
            if (sweetList[j].num > sweetList[i].num) {
                temp = sweetList[j];
                sweetList[j] = sweetList[i];
                sweetList[i] = temp;
            }
        }
    }
    cout << "���������� ��������� �� ��������� ����" << endl;
}

// 13. ���������� ������� �� ������.
void sortStringList()
{
    sweetNameNum temp;
    for (int i=0; i<rowNum-1; i++) {
        for (int j=0; j<rowNum; j++) {
            if (sweetList[j].name > sweetList[i].name) {
                temp = sweetList[j];
                sweetList[j] = sweetList[i];
                sweetList[i] = temp;
            }
        }
    }
    cout << "���������� ��������� �� ���������� ����" << endl;
}

// 14. ���������� ������� � �����.
void outputFileList()
{
    string fileName;
    ofstream fout;
    cout << "������� �������� ����� ������ (outputList.txt): f"; cin >> fileName;
    cout << "���� ������" << endl;
    fout.open("outputList.txt");
    int row=0;
    fout << "| �    | ������������ ��������               | ���������� |" << endl <<
            "-----------------------------------------------------------" << endl;
    for (int i=0; i<rowNum; i++)
    {
        if (sweetList[i].name != "") {
            row++;
            fout << "| " << setw(4) << row << " | " << setw(35) << sweetList[i].name << " | " << setw(10) << sweetList[i].num << " |" << endl;
        }
    }
    fout << "-----------------------------------------------------------" << endl;
}

void menu()
{
    // ����� ����
    cout << "����:" << endl;
    for (int i=0; i<15;i++)
        cout << menuItem[i] << endl;
    cout << endl << "�������� ����� ���� (0-14): ";
    cin >> menuChoice;

    system("cls");
    if ((menuChoice >= 0) && (menuChoice <= 14))
        cout << menuItem[menuChoice] << endl << endl; // ������� ����� ����, ���� �� ����������
    switch(menuChoice)
    {
        case  0: exit(0); break;
        case  1: inputDb(false); break;
        case  2: outputConsoleDb(); break;
        case  3: addRowDb(); break;
        case  4: deleteRowDb(); break;
        case  5: editRowDb(); break;
        case  6: sortNumDb(); break;
        case  7: sortStringDb(); break;
        case  8: outputFileDb(); break;
        case  9: searchDb(); break;
        case 10: createList(); break;
        case 11: outputConsoleList(); break;
        case 12: sortNumList(); break;
        case 13: sortStringList(); break;
        case 14: outputFileList(); break;
        default: cout << "������ ������ ���� �� ����������, ���������� ������" << endl; break;
    }
    system("pause");
    system("cls");
    menu();
}

int main()
{
    SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������
    menuItem[ 0] = "0.  ����� �� ���������.";
    menuItem[ 1] = "1.  �������� ���������� �� ������������ ���� ������ (���� �� �����).";
    menuItem[ 2] = "2.  �������� (����� �� �����) ������������ ���� ������.";
    menuItem[ 3] = "3.  ���������� ����� ������ � ���� ������.";
    menuItem[ 4] = "4.  �������� ������ �� ���� ������.";
    menuItem[ 5] = "5.  �������������� ������ � ���� ������.";
    menuItem[ 6] = "6.  ���������� ������� �� ��������� ���� � ������� �����������.";
    menuItem[ 7] = "7.  ���������� ������� �� ���������� ���� � ���������� �������.";
    menuItem[ 8] = "8.  ���������� ����������� ��������� (������ � ����).";
    menuItem[ 9] = "9.  ����� � ���� ������ �� ������������ �������� � ������� �� ����� ��������� ������� ��� ��������� � ���������� ������.";
    menuItem[10] = "10. ������������ �������.";
    menuItem[11] = "11. �������� (����� �� �����) �������.";
    menuItem[12] = "12. ���������� ������� �� ��������� ���� � ������� ��������.";
    menuItem[13] = "13. ���������� ������� �� ���������� ���� � ���������� �������.";
    menuItem[14] = "14. ���������� ������� � �����.";
    menu();
    return 0;
}
