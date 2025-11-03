/**
 * HashTableDebug.cpp
 *
 * Write your tests in this file
 */
#include <iostream>
#include <memory>

#include "HashTable.h"

using namespace std;

int main() {
    srand(time(0));
    cout << "Hello, World!" << endl;
    HashTable s1;;

    s1.insert("Hii", 23);
    s1.insert("Hello", 34);
    s1.insert("Hlo", 45);
    s1.insert("Hllo", 45);

    s1.remove("Hello");
    s1.remove("Hlo");


    cout << s1.contains("re");

    for (const auto& k : s1.keys()) {
        std::cout << k << " ";
    }
    cout << endl;


    cout << s1 << endl;



}
