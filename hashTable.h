#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "hashTableDS.h"
#include "sensor.h"

#define BUFFER_SIZE 7

class HashTable: public HashTableDS<Sensor>{
    private:
        Sensor* data[BUFFER_SIZE];
        int number_of_colisions = 0;
    public:
        HashTable();
        void insert(Sensor& sensor) override;
        Sensor* search(int key) override;
        void _delete(int key) override;
        int getNumberOfColisions();

};

#endif