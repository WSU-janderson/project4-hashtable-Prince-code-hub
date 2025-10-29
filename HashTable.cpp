#include "HashTable.h"

#include <iostream>
#include <random>


HashTable::HashTable(size_t initCapacity){
    limit = initCapacity;
}


bool HashTable::insert(const std::string key, const size_t &value) {

    int hash = hashing(key);
    size_t index = hash % limit;

    //giving garbage value and empty string with bucket type ESS to vector
    for (int i = 0; i < limit; i++ ) {
        table.push_back(HashTableBucket());
    }
    //if bucket type is EAR and EAS we store them in the indexes
    if (table.at(index).type == HashTableBucket::BucketType::EAR || table.at(index).type ==
        HashTableBucket::BucketType::ESS) {
        table.at(index).load(key, value);
        return true;
    }
}

inline bool HashTable::remove(const std::string &key) {

    int hash = hashing(key);
    size_t index = hash % limit;


     // if (table.at(index).type == HashTableBucket::BucketType::Normal) {
     //    table.pop_back();
     //     table.at(index).type = HashTableBucket::BucketType::EAR;
     // }else if (table.at(index).type == HashTableBucket::BucketType::ESS) {
     //     return false;
     // }

}

//
inline bool HashTable::contains(const std::string &key) const {
}

inline std::optional<size_t> HashTable::get(const std::string &key) const {
}

inline size_t &HashTable::operator[](const std::string &key) {
}

std::vector<std::string> HashTable::keys() const {
}

double HashTable::alpha() const {
}

size_t HashTable::capacity() const {
}

inline size_t HashTable::size() const {
}

double HashTable::hashing(const std::string key) {
    int stringHash = 0;

    for (size_t i = 0; i < key.length(); ++i) {
        stringHash = stringHash * 33 + key[i];
    }

    return stringHash;
}


/**
* The default constructor can simply set the bucket type to ESS.
 *
*/
HashTableBucket::HashTableBucket() {
    value = 0;
    key =  "";
    type = BucketType::ESS;
}

/**
* A parameterized constructor could initialize the key and value, as
* well as set the bucket type to NORMAL.
*/
HashTableBucket::HashTableBucket(const std::string &key, const size_t &value) : type(BucketType::Normal), key(key),
    value(value) {
}


/**
* A load method could load the key-value pair into the bucket, which
* should then also mark the bucket as NORMAL.
*/
void HashTableBucket::load(const std::string &key, const size_t &value) {
    this->value = value;
    this->type = BucketType::ESS;
    this->key = key;
}

/**
* This method would return whether the bucket is empty, regardless of
* if it has had data placed in it or not.
*/
// bool HashTableBucket::isEmpty() const {
//
// }
/**
* The stream insertion operator could be overloaded to print the
* bucket's contents. Or if preferred, you could write a print method
* instead.
*/
// friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {
//  return os;
// }
