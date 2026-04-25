#include <iostream>
#include <chrono>
#include "sensor.h"
#include "hashTable.h"

// g++ main.cpp HashTable.cpp Sensor.cpp -o main

void showMenu();
void showStatistics(HashTable ht);
int tryInsert1000(HashTable &ht);

int main(int argc, char* argv[]){
    HashTable ht;
    int option;

    // insert1000(ht);

    do {
        showMenu();
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            option = -1;
        }

        switch(option) {
            case 1: {
                short int id;
                std::string type, location;
                
                std::cout<<std::endl;
                std::cout << "*** Sensor Registration ****";
                std::cout<<std::endl;
                std::cout << "Sensor ID: ";
                std::cin >> id;
                std::cout << "Type (e.g., temperature, humidity): ";
                std::cin >> type;
                
                std::cin.ignore();
                std::cout << "Location: ";
                std::getline(std::cin, location);

                Sensor newSensor(id, type, location);
                auto startTime = std::chrono::high_resolution_clock::now();
                ht.insert(newSensor);
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> totalTime = endTime - startTime;
                std::cout << "Insertion single sensor time (sec): " << totalTime.count() << std::endl;
                break;
            }
            case 2: {
                int id;
                double newReading;
                
                std::cout<<std::endl;
                std::cout << "*** Update Reading ****";
                std::cout<<std::endl;
                std::cout << "Enter sensor ID: ";
                std::cin >> id;
                
                Sensor* s = ht.search(id);
                if (s != nullptr) {
                    std::cout << "Current value: " << s->getLastRead() << "\n";
                    std::cout << "Enter new reading: ";
                    std::cin >> newReading;
                    s->setLastRead(newReading);
                    std::cout << "Reading updated successfully!\n";
                } else {
                    std::cout << "Error: Cannot update. Sensor not found.\n";
                }
                break;
            }
            case 3: {
                int id;
                std::cout <<std::endl;
                std::cout << "*** Search Sensor ***";
                std::cout <<std::endl;
                std::cout << "Enter sensor ID: ";
                std::cin >> id;
                
                auto startTime = std::chrono::high_resolution_clock::now();
                Sensor* s = ht.search(id);
                auto endTime = std::chrono::high_resolution_clock::now();
                if (s != nullptr) {
                    std::cout << "\n>> Sensor Found:\n";
                    s->show();
                }
                std::chrono::duration<double> totalTime = endTime - startTime;
                std::cout << "Search single sensor time (sec): " << totalTime.count() << std::endl;
                break;
            }
            case 4: {
                int id;
                std::cout <<std::endl;
                std::cout << "*** Remove Sensor ***"<<std::endl;;
                std::cout << "Enter sensor ID: ";
                std::cin >> id;
                auto startTime = std::chrono::high_resolution_clock::now();
                ht._delete(id);
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> totalTime = endTime - startTime;
                std::cout << "Deletion time (sec): " << totalTime.count() << std::endl;
                break;
            }
            case 5: {
                ht.printHashTable();
                break;
            }
            case 6: {
                auto startTime = std::chrono::high_resolution_clock::now();
                int inserted = tryInsert1000(ht);
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> totalTime = endTime - startTime;
                std::cout <<inserted<<" insertion sensor time (sec): " << totalTime.count() << std::endl;
            }
            case 0:
                std::cout <<std::endl;    
                std::cout << "*** SYSTEM TERMINATED ***"; 
                std::cout <<std::endl;
                break;
            default:
                std::cout <<std::endl;
                std::cout <<"Invalid option! Try again.";
                std::cout <<std::endl;
        }
    } while(option != 0);

    return 0;
}

void showMenu() { // Função para exibir o menu de opções
    std::cout<<std::endl;
    std::cout <<std::endl<<"*** Menu Options ***"<<std::endl;
    std::cout << "1 - Register sensor"<<std::endl;
    std::cout << "2 - Update read from single sensor"<<std::endl;
    std::cout << "3 - Search single sensor"<<std::endl;
    std::cout << "4 - Remove single sensor"<<std::endl;
    std::cout << "5 - Show sensors"<<std::endl;
    std::cout << "6 - Insert 1000 sensors automatically"<<std::endl;
    std::cout << "0 - Exit"<<std::endl;
    std::cout << "Enter an option:"<<std::endl;
   std::cout<<std::endl;
}

void showStatistics(HashTable ht){
    std::cout<<std::endl;
    std::cout << "Number of colisions: " << ht.getNumberOfColisions() <<std::endl;
    std::cout<<std::endl;
}

/*
    Insere 1000 sensores automaticamente
    Assegura que o id de todos é positivo (unsigned)
*/
int tryInsert1000(HashTable& ht){
    srand(time(NULL));
    
    if(ht.getFreeSpaces() == 0){
        std::cout << "Hash table is full!" << std::endl;
        return 0;
    }
     if(ht.getFreeSpaces() < 1000){
        std::cout << "Only " << ht.getFreeSpaces() << " free spaces." << std::endl;
        std::cout << "Will insert " << ht.getFreeSpaces() << " sensors instead of 1000." << std::endl;
    }

    int inserted = 0;
    int limit = 0; 
    if(ht.getFreeSpaces() < 1000){
        limit = ht.getFreeSpaces();
    }else{
        limit = 1000;
    }
    for (int i = 0; i < limit; i++) {
        unsigned short int id = rand() % 100000 + 1; 

        while (ht.search(id) != nullptr) {
            id = rand() % 100000 + 1;
        }

        Sensor s(id, "auto_generated", "generated_location");
        ht.insert(s);
        inserted++;
    }

    std::cout << inserted << " inserted!" << std::endl;
    std::cout << "Collisions: " << ht.getNumberOfColisions() << std::endl;
    return inserted;
}