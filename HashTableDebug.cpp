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
    cout << "Hello, World!" << endl;
    srand(time(0));
    HashTable s1;;

    s1.insert("Hii", 23);
    s1.insert("Hello", 34);
    s1.insert("Hlo", 45);
    s1.insert("Hllo", 45);

    s1.remove("Hello");
    s1.remove("Hlo");

    s1.contains("re");
    s1.get("nah");

    cout << s1 << endl;



}
