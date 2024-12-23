#ifndef TABLE_HPP_INCLUDED
#define TABLE_HPP_INCLUDED


#include <vector>

using std::vector;

template<typename Key, typename Value>
struct TableCeil {
    Key key;
    Value value;
};


template<typename Key, typename Value>
class Table {
private:
    vector<TableCeil<Key, Value>> _table;
    vector<TableCeil<Key, Value>>& getTable() {
        return _table;
    }
public:
    void push(TableCeil<Key, Value> ceil) {
        unsigned int size = getTable().size();
        for (unsigned int i = 0; i < size; i++)
            if (getTable()[i].key == ceil.key)
                throw std::logic_error("Duplicate!");
        getTable().push_back(ceil);
    }
    Value getElement(Key key) {
        for (auto ceil : getTable())
            if (ceil.key == key)
                return ceil.value;
        throw std::logic_error("Undefined!");
    }
    TableCeil<Key, Value> getElement(int index) {
        if (index >= getTable().size())
            throw std::logic_error("Beyond the Limits");
        return getTable()[index];
    }
    std::vector<Value> getValues(Key key) {
        Value values;
        for (auto ceil : getTable())
            if (ceil.key == key)
                values.push(ceil.value);
        return values;
    }
    size_t getSize() {
        return getTable().size();
    }
};

template<typename Key, typename Value>
class TableChain {
private:
    vector<TableCeil<Key, vector<Value>>> _table;
    vector<TableCeil<Key, vector<Value>>>& getTable() {
        return _table;
    }
public:
    void push(TableCeil<Key, Value> ceil) {
        vector<TableCeil<Key, vector<Value>>>& table = getTable();
        unsigned int size = table.size();
        for (unsigned int i = 0; i < size; i++)
            if (table[i].key == ceil.key) {
                cout << "Here!" << endl;
                table[i].value.push_back(ceil.value);
                cout << ceil.key.first << ceil.key.second;
                cout << this->getElement({ceil.key.first, ceil.key.second}).size() << endl << endl;
                return;
            }
        vector<Value> temp{ceil.value};
        table.push_back({ceil.key, temp});
        cout << ceil.key.first << ceil.key.second;
        cout << this->getElement({ceil.key.first, ceil.key.second}).size() << endl << endl;
    }
    vector<Value> getElement(Key key) {
        vector<TableCeil<Key, vector<Value>>> table = getTable();
        for (auto ceil : table)
            if (ceil.key == key)
                return ceil.value;
        throw std::logic_error("Undefined!");
    }
    TableCeil<Key, vector<Value>> getElement(int index) {
        if (index >= getTable().size())
            throw std::logic_error("Beyond the Limits");
        return getTable()[index];
    }
    size_t getSize() {
        return getTable().size();
    }
};


#endif