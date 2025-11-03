#include "HashTable.h"

#include <iostream>
#include <random>


using namespace std;

std::ostream &operator<<(std::ostream &, const HashTableBucket &);


HashTable::HashTable(size_t initCapacity) {
    limit = initCapacity;
    table.resize(limit, HashTableBucket());

    while (offsets.size() < limit - 1) {
        bool duplicate = false;
        int random = 1 + rand() % limit;
        for (int i = 0; i < offsets.size(); i++) {
            if (random == offsets[i]) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            offsets.push_back(random);
        }
    }
}


bool HashTable::insert(const std::string key, const size_t &value) {
    int emptyIndex = -1;
    int hash = hashing(key);
    size_t index = hash;

    if (alpha() >= 0.5) {
        resize();
    }

    // //giving garbage value and empty string with bucket type ESS to vector
    // for ( i = 0; i < limit; i++ ) {
    //     table.push_back(HashTableBucket());
    // }
    //if bucket type is and EAS we store them in the indexes
    if (table.at(index).type == HashTableBucket::BucketType::ESS || table.at(index).type ==
        HashTableBucket::BucketType::EAR) {
        table.at(index).load(key, value);
        currentSize++;
        return true;
        }

    if (table.at(index).type == HashTableBucket::BucketType::Normal &&
        table.at(index).key == key) {
        return false; // Duplicate
        }

    for (int i = 0; i < offsets.size(); i++) {
        size_t probe = (hash + offsets.at(i)) % limit;

        switch (table.at(probe).type) {
            case HashTableBucket::BucketType::Normal:
                if (table.at(probe).key == key) {
                    return false;
                }
                break;
            case HashTableBucket::BucketType::ESS:
                table.at(probe).load(key, value);
                currentSize++;
                return true;
            case HashTableBucket::BucketType::EAR:
                if (emptyIndex == -1) {
                    emptyIndex = probe;
                }

                break;
        }
    }
    if (emptyIndex != -1) {
        table.at(emptyIndex).load(key, value);
        table.at(emptyIndex).type = HashTableBucket::BucketType::Normal;
        currentSize++;
        return true;
    }
    return false;
}



bool HashTable::remove(const std::string &key) {
    int i = 0;
    int hash = hashing(key);

    if (table.at(hash).type == HashTableBucket::BucketType::Normal && table.at(hash).key == key) {
        table.at(hash).key = "";
        table.at(hash).value = 0;
        table.at(hash).type = HashTableBucket::BucketType::EAR;
        currentSize--;
        return true;
    }

    for (int j = 0; j < offsets.size(); j++) {
        size_t probe = (hash + offsets[j]) % limit;

        switch (table.at(probe).type) {
            case HashTableBucket::BucketType::Normal:
                if (table.at(probe).key == key) {
                    table.at(probe).key = "";
                    table.at(probe).value = 0;
                    table.at(probe).type = HashTableBucket::BucketType::EAR;
                    currentSize--;
                    return true;
                }
                break;

            case HashTableBucket::BucketType::ESS:
                return false;

            case HashTableBucket::BucketType::EAR:
                break;
        }
    }
    return false;
}

//
bool HashTable::contains(const std::string &key) const {
    int hash = hashing(key);
    size_t probe = hash;

    if (table.at(probe).type == HashTableBucket::BucketType::Normal && table.at(probe).key == key) {
        return true;
    }

    for (int i = 0; i < offsets.size(); i++) {
        probe = (hash + offsets[i]) % limit;

    switch (table.at(probe).type) {
        case HashTableBucket::BucketType::Normal:
            if (table.at(probe).key == key) {
                return true;
            }
            break;
        case HashTableBucket::BucketType::ESS:
            return false;
        case HashTableBucket::BucketType::EAR:
            break;
    }
    }
    return false;
}

std::optional<size_t> HashTable::get(const std::string &key) const {
    int hash = hashing(key);
    size_t probe = hash ;

    if (table.at(probe).type == HashTableBucket::BucketType::Normal && table.at(probe).key == key) {
        return table.at(probe).value;
    }

    for (size_t i = 0; i < offsets.size(); i++) {
        size_t probe = (hash + offsets[i]) % limit;

        switch (table.at(probe).type) {
            case HashTableBucket::BucketType::Normal:
                if (table.at(probe).key == key) {
                    return  table.at(probe).value;
                }
                break;
            case HashTableBucket::BucketType::ESS:
                return std::nullopt;
            case HashTableBucket::BucketType::EAR:
                break;

        }
    }

    return std::nullopt;
}


size_t &HashTable::operator[](const std::string &key) {
    size_t hash = hashing(key);

    if (table.at(hash).type == HashTableBucket::BucketType::Normal && table.at(hash).key == key) {
        return table.at(hash).value;
    }

    for (size_t i = 0; i < offsets.size(); i++) {
        hash = (hash + offsets[i]) % limit;
        if (table.at(hash).type == HashTableBucket::BucketType::Normal && table.at(hash).key == key) {
            return table.at(hash).value;
        }
    }

    throw std::out_of_range("No such key");
}



std::vector<std::string> HashTable::keys() const {
    std::vector<std::string> keys;

    for (size_t i = 0; i < table.size(); i++) {
        if (table.at(i).type == HashTableBucket::BucketType::Normal) {
            keys.push_back(table.at(i).key);
        }
    }

    return keys;
}

double HashTable::alpha() const {
    return static_cast<double>(currentSize) / static_cast<double>(limit);
}

size_t HashTable::capacity() const {
    return limit;
}

size_t HashTable::size() const {
    return currentSize;
}

size_t HashTable::hashing(const std::string key) const {
    size_t stringHash = 0;

    for (size_t i = 0; i < key.length(); ++i) {
        stringHash = stringHash * 33 + key[i];
    }
    stringHash = stringHash % limit;
    return stringHash;
}

ostream &operator <<(ostream &os, const HashTable &hashTable) {
    for (size_t i = 0; i < hashTable.table.size(); i++) {
        if (hashTable.table[i].type == HashTableBucket::BucketType::Normal) {
            os << "Bucket " << i << hashTable.table[i] << endl;
        }
    }

    return os;
}

void HashTable::resize() {
    limit*=2;

    std::vector<HashTableBucket> old_table = table;

    table.clear();
    table.resize(limit, HashTableBucket());

    offsets.clear();
    while (offsets.size() < limit-1) {
        bool duplicate = false;
        int random = 1 + rand() % limit;
        for (int i = 0; i < offsets.size(); i++) {
            if (random == offsets[i]) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            offsets.push_back(random);
        }

    }
    currentSize = 0;

    for (int i = 0; i < old_table.size(); i++) {
        if (old_table[i].type == HashTableBucket::BucketType::Normal) {
            insert(old_table[i].key,old_table[i].value);
        }
    }

}



/**
* The default constructor can simply set the bucket type to ESS.
 *
*/
HashTableBucket::HashTableBucket() {
    value = 0;
    key = "";
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
    this->type = BucketType::Normal;
    this->key = key;
}

/**
* This method would return whether the bucket is empty, regardless of
* if it has had data placed in it or not.
*/
bool HashTableBucket::isEmpty() const {

    return type == BucketType::ESS || type == BucketType::EAR;

}
/**
* The stream insertion operator could be overloaded to print the
* bucket's contents. Or if preferred, you could write a print method
* instead.
*/
std::ostream &operator<<(std::ostream &os, const HashTableBucket &bucket) {
    if (bucket.type == HashTableBucket::BucketType::Normal) {
        os << "  " << bucket.value << "  " << bucket.key;
    }
    return os;
}
