# Project 4 - HashTable

Project description can be found [in the repo](Project4_HashTable.pdf)

Place your complexity analysis below.

---

I would say for every insert, remove, contains, get and operator[] the best case is o(1) and the worst case is o(n).

In insert, computes hash, then probes randomly until an empty slot is found. In average it will happen collision so in worst case is o(n).
In remove, it is similar as insert first computes hash, then probes until it's found normal so in worst case is o(n).
In get, searches for a key using the probing sequence. Return value for according to key but in worst case it will go to o(n).
In contains, Checks whether a key exists. Same behavior as get(), but stops early after finding the key. but in worst case it will go to o(n).
In operator, this is same as get as well, in worst case it can go o(n).
