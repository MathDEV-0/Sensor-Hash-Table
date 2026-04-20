#include <iostream>
#include "sensor.h"
#include "hashTable.h"

// g++ main.cpp HashTable.cpp Sensor.cpp -o main

void showMenu();
int main(int argc, char* argv[]){
    HashTable ht;

    Sensor s1(1, "ph", "Porto Alegre");
    Sensor s400(1, "ph", "Porto Alegre");
    Sensor s2(2, "temperatura", "Sao Leopoldo");
    Sensor s3(3, "umidade", "Canoas");
    Sensor s4(4, "pressao", "Gravatai");
    Sensor s5(5, "velocidade", "Novo Hamburgo");
    Sensor s6(6, "direcao", "Sapucaia");
    Sensor s7(7, "radiacao", "Esteio");
    Sensor s8(8, "ruido", "Cachoeirinha");
    Sensor s9(9, "vibracao", "Alvorada");
    Sensor s10(10, "nivel", "Viamao");
    
    ht.insert(s1);
    ht.insert(s400);
    ht.insert(s2);
    ht.insert(s3);
    ht.insert(s4);
    ht.insert(s5);
    ht.insert(s6);
    ht.insert(s7);
    ht.insert(s8);
    ht.insert(s9);
    ht.insert(s10);

    std::cout << "Number of colisions: " << ht.getNumberOfColisions() << "\n";
    
    Sensor* found = ht.search(3);
    Sensor* found1 = ht.search(4);
    Sensor* found2 = ht.search(400);

    ht._delete(5);

    for(int i = 1; i <= 10; i++){
        Sensor* s = ht.search(i);
    }

    return 0;
}