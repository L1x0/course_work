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
 

vector<Buyer> heapSort(vector<Buyer> buyers, int n) {

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


int main(int argc, const char * argv[]) {
        vector<Buyer> buyers;
        buyers = getData(buyers);
//        buyers = bubbleSort_Date(buyers);
        
 //       buyers = quickSort_Name(buyers);
        buyers = heapSort(buyers, buyers.size());
        putData(buyers);
        return 0;
}
