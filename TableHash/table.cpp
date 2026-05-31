#include "HashTable.h"
#include <sstream>

HashTable::HashTable(size_t size) noexcept {
  	_capacity = size;
	_filled = 0;
	 table.resize(_capacity);
}

HashTable::~HashTable() {
	_capacity = 0;
	_filled = 0;
	table.clear();
}

void HashTable::insert(const KeyType &key, const ValueType &value) {
    size_t index = hash_function(key);
    for (auto &it : table[index]) {
        if (it.first == key) {
            it.second = value;
            return;
        }
    }

    table[index].push_back(std::make_pair(key, value));
    ++_filled;
		
	if (getLoadFactor() > 0.75) {
		_capacity *= 2;
	}
}

bool HashTable::find(const KeyType &key, ValueType &value) const {
    size_t index = hash_function(key);
    for (auto &it : table[index]) {
        if (it.first == key) {
            value = it.second;
            return true;
        }
    }
    return false;
}

void HashTable::remove(const KeyType &key) {
    size_t index = hash_function(key);
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->first == key) {
            table[index].erase(it);
            --_filled;
            return;
        }
    }
}

ValueType& HashTable::operator[](const KeyType &key) {
    size_t index = hash_function(key);
    for (auto &pair : table[index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
	throw std::runtime_error("no find");
}

double HashTable::getLoadFactor(){
    if (_capacity == 0) {
		return 0;
    }
	return double(_filled) / _capacity;
}

size_t HashTable::hash_function(const KeyType &key) const {
	std::stringstream sstream(key);
	size_t result;
	sstream >> result;
    return result % _capacity;
}
