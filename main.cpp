#include <iostream>
#include "sensor.h"
#include "hashTable.h"

void showMenu();
int main(int argc, char* argv[]){
    HashTable ht;

    Sensor s1(1, "ph", "Porto Alegre");
    Sensor s2(2, "temperatura", "São Leopoldo");
    Sensor s3(3, "umidade", "Canoas");
    Sensor s4(10008, "pressao", "Gravataí");
    Sensor s5(10008, "pressao", "Gravataí");
    Sensor s6(10009, "pressao", "Gravataí");
    Sensor s7(10019, "pressao", "Gravataí");
    
    ht.insert(s1);
    ht.insert(s2);
    ht.insert(s3);
    ht.insert(s4);
    ht.insert(s5);
    ht.insert(s6);
    ht.insert(s7);

    std::cout << "Number of colisions: " << ht.getNumberOfColisions() << "\n";
    
    return 0;
}