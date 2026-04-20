#include "hashTable.h"

int M = BUFFER_SIZE;

HashTable::HashTable(){
    for(int i = 0; i < BUFFER_SIZE; i++)data[i] = nullptr;
}

void HashTable::insert(Sensor& sensor){
    
    int key = sensor.getId();

    // K%M & 1 + (K % (M-1)) = double hash
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
    // K%M & 1 + (K % (M-1)) = double hash
    // K%M & 1 + (K % (M-1)) = double hash
    int hash1 = key % M; int hash2 = 1 + (key % (M-1));

    for(int i =0; i< BUFFER_SIZE;i++){
        int index = (hash1 + i * hash2) % M;
        std::cout<<"Searching "<< key<<" at index ["<<index<<"]"<<std::endl;
        if(data[index] == nullptr){
            std::cout<<"Element with key "<<key<<"doesn't exists at the calculated index ["<<index<<"]"<<std::endl;
            return nullptr;
        }
        if (data[index]->getId() == key){
            std::cout<<"Element with key "<<key<<"found at the calculated index ["<<index<<"]"<<std::endl;
            return data[index];
        }
    }
    std::cout<<"Tabela cheia"<<std::endl;
    return nullptr; //tabela com tamanho máximo
}

void HashTable::_delete(int key){
    int hash1 = key % M; int hash2 = 1 + (key % (M-1));

    for(int i =0; i< BUFFER_SIZE;i++){
        int index = (hash1 + i * hash2) % M;
        std::cout<<"Deleting "<< key<<" at index ["<<index<<"]"<<std::endl;
        if(data[index] == nullptr){
            std::cout<<"Element with key "<<key<<"already empty or deleted ["<<index<<"]"<<std::endl;
        }
        if (data[index]->getId() == key){
            data[index] = nullptr;
            std::cout<<"Element with key "<<key<<"already deleted ["<<index<<"] sucessefully"<<std::endl;
        }
    }
}

int HashTable::getNumberOfColisions(){
    return number_of_colisions;
}