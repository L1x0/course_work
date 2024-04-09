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

int main(int argc, const char * argv[]) {
    vector<Buyer> buyers;
    buyers = getData(buyers);
    putData(buyers);
    
    return 0;
}
