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
#include <iomanip>
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


void heapify(vector<Buyer>& buyers, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    
    if (left < n && buyers[left].number > buyers[largest].number) {
        largest = left;
    }
    
    
    if (right < n && buyers[right].number > buyers[largest].number) {
        largest = right;
    }
    
    
    if (largest != i) {
        swap(buyers[i], buyers[largest]);
        heapify(buyers, n, largest);
    }
}


void heapSort_Number(vector<Buyer>& buyers) {
    int n = (int)buyers.size();
    
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(buyers, n, i);
    }
    
    
    for (int i = n - 1; i > 0; i--) {
        swap(buyers[0], buyers[i]);
        
        heapify(buyers, i, 0);
    }
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

vector<Buyer> deleteDublicates(vector<Buyer> buyers) {
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

int binarySearch(vector<Buyer> buyers, int low, int high, int number) {
    
    while (high >= low) {
        
        int mid = (low + high) / 2;
        
        if (buyers[mid].number == number) {
            
            return mid;
        }
        
        if (buyers[mid].number > number)
            high = mid - 1;
        else
            low = mid + 1;
        
        
    }
    cout << "Запись не найдена" << endl;
    return -1;
}


void outputToConsole(vector<Buyer> buyers) {
    int lengthOfName = 0, lengthOfAddress = 0;
    
    cout << setw(9) << "Number" << "|" << setw(20) << "Name" << "|"
    << setw(40)<< "Address" << "|" << setw(8)<< "Acounting date" << endl;
    
    
    for(int i = 0; i < buyers.size(); i++) {
        
        for (int j = 0; j < 95; j++)
            cout << "_";
        cout << "\n";
        
        
        cout << setw(9) << buyers[i].number << "|";
        
        if (((buyers[i].name.substr(0,2) >= "а") && (buyers[i].name.substr(0,2) <= "я")) || (((buyers[i].name.substr(0,2) >= "А") && (buyers[i].name.substr(0,2) <= "Я")))) {
            int countOfSpaces = 0;
            
            for (int j = 0; j < buyers[i].name.length(); j++) {
                
                if (buyers[i].name.substr(j,1) == " ")
                    countOfSpaces++;
            }
            
            lengthOfName = ((int)buyers[i].name.length() - countOfSpaces) / 2;
            cout<< setw(20 + lengthOfName) << buyers[i].name << "|";
            
        } else {
            cout<< setw(20) << buyers[i].name << "|";
        }
        
        
        
        if (((buyers[i].address.substr(0,2) >= "а") && (buyers[i].address.substr(0,2) <= "я")) || (((buyers[i].address.substr(0,2) >= "А") && (buyers[i].address.substr(0,2) <= "Я")))) {
            int countOfOtherSymbols = 0;
            
            for (int j = 0; j < buyers[i].address.length(); j++) {
                
                if (buyers[i].address.substr(j,1) == " "  || buyers[i].address.substr(j,1) == "," || buyers[i].address.substr(j,1) == ".")
                    countOfOtherSymbols++;
            }
            
            lengthOfAddress = ((int)buyers[i].address.length() - countOfOtherSymbols) / 2;
            cout<< setw(39 + lengthOfAddress) << buyers[i].address << "|";
            
        } else {
            cout<< setw(40) << buyers[i].address << "|";
        }
        
        cout << setw(12) << buyers[i].accountingDate << endl;
    }
}


void outputToConsole(Buyer buyer) {
    int lengthOfName = 0, lengthOfAddress = 0;
    
    cout << setw(9) << "Number" << "|" << setw(20) << "Name" << "|"
    << setw(40)<< "Address" << "|" << setw(8)<< "Acounting date" << endl;
    
    
    for (int j = 0; j < 95; j++)
        cout << "_";
    cout << "\n";
    
    
    cout << setw(9) << buyer.number << "|";
    
    if (((buyer.name.substr(0,2) >= "а") && (buyer.name.substr(0,2) <= "я")) || (((buyer.name.substr(0,2) >= "А") && (buyer.name.substr(0,2) <= "Я")))) {
        int countOfSpaces = 0;
        
        for (int j = 0; j < buyer.name.length(); j++) {
            
            if (buyer.name.substr(j,1) == " ")
                countOfSpaces++;
        }
        
        lengthOfName = ((int)buyer.name.length() - countOfSpaces) / 2;
        cout<< setw(20 + lengthOfName) << buyer.name << "|";
        
    } else {
        cout<< setw(20) << buyer.name << "|";
    }
    
    
    
    
    if (((buyer.address.substr(0,2) >= "а") && (buyer.address.substr(0,2) <= "я")) || (((buyer.address.substr(0,2) >= "А") && (buyer.address.substr(0,2) <= "Я")))) {
        int countOfOtherSymbols = 0;
        
        for (int j = 0; j < buyer.address.length(); j++) {
            
            if (buyer.address.substr(j,1) == " "  || buyer.address.substr(j,1) == "," || buyer.address.substr(j,1) == ".")
                countOfOtherSymbols++;
        }
        
        lengthOfAddress = ((int)buyer.address.length() - countOfOtherSymbols) / 2;
        cout<< setw(39 + lengthOfAddress) << buyer.address << "|";
        
    } else {
        cout<< setw(40) << buyer.address << "|";
    }
    
    cout << setw(12) << buyer.accountingDate << endl;
}



void searchByDate(vector<Buyer> buyers, string date) {
    vector<Buyer> foundBuyers;
    
    for(int i = 0; i < buyers.size(); i++) {
        if (buyers[i].accountingDate == date)
            foundBuyers.push_back(buyers[i]);
    }
    
    outputToConsole(foundBuyers);
}


int main(int argc, const char * argv[]) {
    Buyer temp;
    vector<Buyer> buyers;
    buyers = getData(buyers);
    int choise, num;
    string dateForSearch;
    
    while (true) {
        
        cout << "Доступные операции:" << endl;
        cout << "1 - Сортировка по номеру заказа" << endl;
        cout << "2 - Сортировка по дате заказа" << endl;
        cout << "3 - Сортировка по имени заказчика" << endl;
        cout << "4 - Поиск заказа по номеру" << endl;
        cout << "5 - Поиск заказов по дате" << endl;
        cout << "6 - Вывести с учётом сортировки" << endl;
        cout << "7 - Добавить запись" << endl;
        cout << "8 - Удалить запись" << endl;
        cout << "9 - Удалить дубликаты" << endl;
        cout << "10 - Перезаписать выходной файл" << endl;
        cout << "11 - Выход" << endl;
        cout << "Введите номер операции:";
        cin >> choise;
        cout <<"\n";
        
        switch(choise) {
            case 1:
                heapSort_Number(buyers);
                
                break;
                
            case 2:
                buyers = bubbleSort_Date(buyers);
                
                break;
                
            case 3:
                buyers = quickSort_Name(buyers);
                
                break;
                
            case 4:
                heapSort_Number(buyers);
                cout << "Список отсортирован для поиска" << endl;
                
                cout << "Введите номер заказа для поиска:";
                cin >> num;
                cout << "\n";
                
                outputToConsole(buyers[binarySearch(buyers, 0, (int)buyers.size() - 1, num)]);
                
                break;
                
            case 5:
                cout << "Введите дату для поиска в формате ДД.ММ.ГГГГ:" << endl;
                cin >> dateForSearch;
                
                while (dateForSearch.length() != 10) {
                    cout << "Дата введена некорректно, введите ещё раз" << endl;
                    cin >> dateForSearch;
                }
                
                searchByDate(buyers, dateForSearch);
                
                break;
                
            case 6:
                outputToConsole(buyers);
                
                break;
                
            case 7:
                
                cout << "Введите номер заказа" << endl;
                cin >> temp.number;
                
                fflush(stdin);
                cout << "\nВведите ФИО заказчика" << endl;
                getline(cin, temp.name);
                
                cout << "\nВведите дату заказа (ДД.ММ.ГГГГ)" << endl;
                getline(cin, temp.accountingDate);
                
                cout << "\nВведите адрес заказчика" << endl;
                getline(cin, temp.address);
                buyers.push_back(temp);
                
                break;
                
            case 8:
                cout << "Введите номер заказа для удаления" << endl;
                cin >> num;
                
                heapSort_Number(buyers);
                cout << "\nСписок отсортирован для поиска" << endl;
                
                if (binarySearch(buyers, 0, (int)buyers.size() - 1, num) != -1) {
                    buyers.erase(buyers.begin() + binarySearch(buyers, 0, (int)buyers.size() - 1, num));
                } else {
                    cout << "Запись с таким номером не обнаружена" << endl;
                }
                
                break;
                
            case 9:
                buyers = deleteDublicates(buyers);
                cout << "Дубликаты удалены" << endl;
                
                break;
                
            case 10:
                putData(buyers);
                cout << "Файлы записаны в выходной файл" << endl;
                
                break;
                
            case 11:
                return 1;
                break;
                
            default:
                cout << "Некорректный номер операции" << endl;
                break;
        }
    }
    
    return 0;
}
