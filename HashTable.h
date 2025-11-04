// Name: Prince Patel
// Project: HashTable Implementation
//File: HashTable.h
#include <string>
#include <vector>
#include <optional>
//forward declaration
class HashTableBucket;
enum class BucketType;

class HashTable{

public:
 //table's limit
 size_t capacity_;
/**
* Only a single constructor that takes an initial capacity for the table is
* necessary. If no capacity is given, it defaults to 8 initially
*/
 HashTable(size_t initCapacity = 8);
//To generate random offsets for table
 void generateOffsets(size_t limit);

 /**
* Insert a new key-value pair into the table. Duplicate keys are NOT allowed. The
* method should return true if the insertion was successful. If the insertion was
* unsucessful, such as when a duplicate is attempted to be inserted, the method
* should return false
*/
bool insert(const std::string key, const size_t& value);
/**
* If the key is in the table, remove will “erase” the key-value pair from the
* table. This might just be marking a bucket as empty-after-remove
*/
bool remove(const std::string& key);
/**
* contains returns true if the key is in the table and false if the key is not in
* the table.
*/
bool contains(const std::string& key) const;
/**
* If the key is found in the table, find will return the value associated with
* that key. If the key is not in the table, find will return something called
* nullopt, which is a special value in C++. The find method returns an
* optional<int>, which is a way to denote a method might not have a valid value
* to return. This approach is nicer than designating a special value, like -1, to
* signify the return value is invalid. It's also much better than throwing an
* exception if the key is not found.
*/
std::optional<size_t> get(const std::string& key) const;
/**
* The bracket operator lets us access values in the map using a familiar syntax,
* similar to C++ std::map or Python dictionaries. It behaves like get, returnin
* the value associated with a given key:
 int idNum = hashTable[“James”];
* Unlike get, however, the bracker operator returns a reference to the value,
* which allows assignment:
 hashTable[“James”] = 1234;
 If the key is not
* in the table, returning a valid reference is impossible. You may choose to
* throw an exception in this case, but for our implementation, the situation
* results in undefined behavior. Simply put, you do not need to address attempts
* to access keys not in the table inside the bracket operator method.
*/
size_t& operator[](const std::string& key);

/**
* keys returns a std::vector (C++ version of ArrayList, or simply list/array)
* with all of the keys currently in the table. The length of the vector should be
* the same as the size of the hash table.
*/
std::vector<std::string> keys() const;
/**
* alpha returns the current load factor of the table, or size/capacity. Since
* alpha returns a double,make sure to properly cast the size and capacity, which
* are size_t, to avoid size_teger division. You can cast a size_t num to a double
* in C++ like:
 static_cast<double>(num)
 The time complexity
* for this method must be O(1).
*/
double alpha() const;
/**
* capacity returns how many buckets in total are in the hash table. The time
* complexity for this algorithm must be O(1).
*/
size_t capacity() const;
/**
* The size method returns how many key-value pairs are in the hash table. The
* time complexity for this method must be O(1)
*/
size_t size() const;
//Hash function
 size_t hashing(std::string key) const;
//Resize table when load factor high
 void resize();
//offsets random probing,
 std::vector<size_t> offsets;
 // Table of buckets
 std::vector<HashTableBucket> table;

 size_t currentSize = 0;

 //allow printing
 friend std::ostream &operator<<(std::ostream &os, const HashTable &hashTable);

};



class HashTableBucket {

 public:
 //marking types explicitly
 enum class BucketType {Normal, ESS , EAR};
//default construction
 HashTableBucket();
 // Used when directly inserting a key-value pair into a bucket
 HashTableBucket(const std::string &key, const size_t &value);
 //load function
 void load(const std::string &key, const size_t &value);
 //Checks if the bucket is empty
 bool isEmpty() const;

 std::string key;
 size_t value;
 BucketType type;
};

