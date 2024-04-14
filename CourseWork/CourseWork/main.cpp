//
//  main.cpp
//  CourseWork
//
//  Created by Артём Астахов on 8.04.24.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct Buyer {
    int number;
    string name;
    string address;
    string accountingDate;
};

vector<Buyer> getData(vector<Buyer> buyers) {
    ifstream file("input.txt");
    
    if (file.is_open()) {
        string temp;

        while (!file.eof()) {
            Buyer buyer;
            
            getline(file, temp);
            temp.replace(0, 8, "");
            buyer.number = stoi(temp);
            
            getline(file, temp);
            temp.replace(0, 6, "");
            buyer.name = temp;
            
            getline(file, temp);
            temp.replace(0, 9, "");
            buyer.address = temp;
            
            getline(file, temp);
            temp.replace(0, 16, "");
            buyer.accountingDate = temp;
            
            buyers.push_back(buyer);
            
            getline(file, temp);
        }
        
    } else {
        cout << "Файл для чтения не открыт" << endl;
    }
    
    file.close();
    
    return buyers;
}

void putData(vector<Buyer> buyers) {
    ofstream file("output.txt");
    
    if (file.is_open()) {
        for (int i = 0; i < buyers.size(); i++) {
            file << "number: " << buyers[i].number << endl;
            file << "name: " << buyers[i].name << endl;
            file << "address: " << buyers[i].address << endl;
            file << "accounting date: " << buyers[i].accountingDate << endl;
            file << "\n";
        }
    } else {
        cout << "Файл для записи не открыт" << endl;
    }
    
    file.close();
}

vector<Buyer> bubbleSort_Date(vector<Buyer> buyers) {
    bool protect = true;
    
    while(protect) {
        protect = false;
        
        for (int i = 1; i < buyers.size(); i++) {
            int yearsOfFisrt, mounthOfFirst, daysOfFirst, yearsOfSecond, mounthOfSecond, daysOfSecond;
            
            daysOfFirst = stoi(buyers[i - 1].accountingDate.substr(0,2));
            mounthOfFirst = stoi(buyers[i - 1].accountingDate.substr(3,2));
            yearsOfFisrt = stoi(buyers[i - 1].accountingDate.substr(6,buyers[i].accountingDate.size() - 6));
            
            daysOfSecond = stoi(buyers[i].accountingDate.substr(0,2));
            mounthOfSecond = stoi(buyers[i].accountingDate.substr(3,2));
            yearsOfSecond = stoi(buyers[i].accountingDate.substr(6,buyers[i].accountingDate.size() - 6));
            
            if (yearsOfFisrt > yearsOfSecond) {
                swap(buyers[i - 1], buyers[i]);
                protect = true;
                continue;
            }
            
            if (yearsOfFisrt == yearsOfSecond) {
                
                if (mounthOfFirst > mounthOfSecond) {
                    swap(buyers[i - 1], buyers[i]);
                    protect = true;
                    continue;
                }
                
                if (mounthOfFirst == mounthOfSecond) {
                    
                    if (daysOfFirst > daysOfSecond) {
                        swap(buyers[i - 1], buyers[i]);
                        protect = true;
                        continue;
                    }
                }
                    
            }
        }
        
    }
    
    return buyers;
}


vector<Buyer> quickSort_Name(vector<Buyer> buyers) {
    
    vector<Buyer> left;
    vector<Buyer> right;
    
    for (int i = 1; i < buyers.size(); i++) {
        string bearingElementName, secondName;
        bearingElementName = buyers[0].name.substr(0, buyers[0].name.size() - buyers[0].name.find(" ") - 1);
        
        secondName = buyers[i].name.substr(0, buyers[i].name.size() - buyers[i].name.find(" ") - 1);
        
        if (bearingElementName < secondName) {
            right.push_back(buyers[i]);
            
        } else if (bearingElementName > secondName) {
            left.push_back(buyers[i]);
            
        } else {
            bearingElementName = buyers[0].name.substr(buyers[0].name.find(" "), buyers[0].name.size() - buyers[0].name.find(" ") - 1);
            
            secondName = buyers[i].name.substr(buyers[i].name.find(" "), buyers[i].name.size() - buyers[i].name.find(" ") - 1);
            
            
            if (bearingElementName <= secondName) {
                right.push_back(buyers[i]);
                
            } else if (bearingElementName < secondName) {
                left.push_back(buyers[i]);
            }
        }

    }
    
    if ( left.size() > 1)
        left = quickSort_Name(left);
    if (right.size() > 1)
        right = quickSort_Name(right);
    left.push_back(buyers[0]);
    
    for (int i = 0; i < right.size(); i++) {
        left.push_back(right[i]);
    }
        return left;
    
}


vector<Buyer> heapify(vector<Buyer> buyers, int n, int i) {

    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
 
    if (l < n && buyers[l].number > buyers[largest].number)
        largest = l;
 
    if (r < n && buyers[r].number > buyers[largest].number)
        largest = r;
 
    if (largest != i) {
        swap(buyers[i], buyers[largest]);
        heapify(buyers, n, largest);

    } else {
        return buyers;
    }

   return buyers;
}
 

vector<Buyer> heapSort_Number(vector<Buyer> buyers, int n) {

    for (int i = n / 2 - 1; i >= 0; i--)
     heapify(buyers, n, i);
 

    for (int i=n-1; i>=0; i--) {
     swap(buyers[0], buyers[i]);
 
     heapify(buyers, i, 0);
    } 

    Buyer temp;
    temp = buyers[0];

    
    for (int i = 1; i < buyers.size(); i++) {
        buyers[i - 1] = buyers[i];
    }

    buyers[buyers.size() - 1] = temp;
    
    return buyers;
}

vector<int> linearSearch(vector<Buyer> buyers, int startIndex, Buyer obj) {
    vector<int> indexesToDelete;

    for (int i = startIndex; i < buyers.size(); i++) {
        if (obj.name == buyers[i].name && obj.address == buyers[i].address)
            indexesToDelete.push_back(i);
        else
            break;
    }

    return indexesToDelete;
}

vector<Buyer> deleteDuplicate(vector<Buyer> buyers) {
    buyers = quickSort_Name(buyers);
    vector<int> indexesToDelete;

    for (int i = 0; i < buyers.size(); i++) {
        if (buyers[i].name == buyers[i + 1].name && buyers[i].address == buyers[i + 1].address)
            indexesToDelete = linearSearch(buyers, i + 1, buyers[i]);

        while (!indexesToDelete.empty()) {
            buyers.erase(buyers.begin() + indexesToDelete[0]);
            indexesToDelete.pop_back();
        }
    }

    return buyers;
}

void binarySearch(vector<Buyer> buyers, int low, int high, int number) { 

    if (high >= low) { 
 
        int mid = low + (high - low) / 2; 
  
        if (buyers[mid].number == number) {
            cout << "number: " << buyers[mid].number << endl;
            cout << "name: " << buyers[mid].name << endl;
            cout << "address: " << buyers[mid].address << endl;
            cout << "accounting date: " << buyers[mid].accountingDate << endl;
        }

        if (buyers[mid].number > number) 
            binarySearch(buyers, low, mid - 1, number); 
  
        binarySearch(buyers, mid + 1, high, number); 
    }  

    cout << "Запись не найдена" << endl;
} 


int main(int argc, const char * argv[]) {

        setlocale(LC_ALL, "RUS");
        vector<Buyer> buyers;
        buyers = getData(buyers);
        buyers = deleteDuplicate(buyers);
        int choise;

        while (true) {

        cout << "Доступные операции:" << endl;
        cout << "1 - Сортировка по номеру заказа" << endl;
        cout << "2 - Сортировка по дате заказа" << endl;
        cout << "3 - Сортировка по имени заказчика" << endl;
        cout << "4 - поиск заказа по номеру" << endl;
        cout << "5 - вывести с учётом сортировки" << endl;
        cout << "6 - выход" << endl;
        cout << "Введите номер заказа:";
        cin >> choise;
        cout <<"\n";

            switch(choise) {
                case 1:
                    buyers = heapSort_Number(buyers, buyers.size());
                    break;
                case 2:
                    buyers = bubbleSort_Date(buyers);
                    break;
                case 3:
                    buyers = quickSort_Name(buyers);
                    break;
                case 4:
                    cout << "Введите номер заказа для поиска:";
                    int num;
                    cin >> num;
                    cout << "\n";

                    binarySearch(buyers, 0, buyers.size() - 1, num);
                    break;
                case 5:
                    for (int i = 0; i < buyers.size(); i++) {
                        cout << "number: " << buyers[i].number << endl;
                        cout << "name: " << buyers[i].name << endl;
                        cout << "address: " << buyers[i].address << endl;
                        cout << "accounting date: " << buyers[i].accountingDate << endl;
                        cout << "\n";
                    }
                    break;
                case 6:
                    return 1;
                default:
                    cout << "Некорректный номер заказа" << endl;
                    break;
            }
        }

        return 0;
}
