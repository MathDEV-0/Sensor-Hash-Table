#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "hashTableDS.h"
#include "sensor.h"

#define BUFFER_SIZE 10037

/*
    Hash Estático Fechado
    Endereçamento aberto: double hashing
    Tamanho de M definido na constante BUFFER_SIZE = 10037, valor escolhido devido a seu fator de primo
    Herda de um TAD genérico e implementa T como Sensor
*/
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
        int getFreeSpaces();
        void printHashTable();
        void updateAllLastReadings();
};

#endif