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
    string number;
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
            buyer.number = temp;
            
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
            Buyer buyer = buyers.at(i);
            
            file << "number: " << buyer.number << endl;
            file << "name: " << buyer.name << endl;
            file << "address: " << buyer.address << endl;
            file << "accounting date: " << buyer.accountingDate << endl;
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

int main(int argc, const char * argv[]) {
    vector<Buyer> buyers;
    buyers = getData(buyers);
    buyers = bubbleSort_Date(buyers);
    putData(buyers);
    
    return 0;
}
