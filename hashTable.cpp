#include "hashTable.h"

HashTable::HashTable(){
    for(int i = 0; i < BUFFER_SIZE; i++)data[i] = nullptr;
}
void HashTable::insert(Sensor& sensor){
    int M = BUFFER_SIZE;
    int key = sensor.getId();

    // K%M & 1 + (K % (M-1))
    int hash1 = key % M; int hash2 = 1 + (key % (M-1));

    for(int i =0; i< BUFFER_SIZE;i++){
        int index = (hash1 + i * hash2) % M;
        std::cout<<"Trying to insert "<< key<<" at index ["<<index<<"]"<<std::endl;
        if(data[index] == nullptr){
            data[index] = new Sensor(sensor);
            std::cout<<"Sucessfully inserted key "<<key<<" at index ["<<index<<"]"<<std::endl;
            return;
        }
        if (data[index]->getId() == key){
            std::cout<<"There is a sensor with same ID"<<std::endl;
            return;
        }
        number_of_colisions++;
    }
    std::cout<<"Hash Table is full!"<<std::endl;
}

Sensor* HashTable::search(int key){
    return nullptr;
}

void HashTable::_delete(int key){
    return ;
}

int HashTable::getNumberOfColisions(){
    return number_of_colisions;
}