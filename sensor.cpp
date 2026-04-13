#include "sensor.h"
#define ZERO 0.0
#include <string>
Sensor::Sensor(short int id, std::string type, std::string location){
    this->id = id;
    this->type = type;
    this->location =location;
    this->lastRead = ZERO;
}

short int Sensor::getId(){
    return id;
}

std::string Sensor::getLocation(){
    return location;
}

std::string Sensor::getType(){
    return type;
}


double Sensor::getLastRead(){
    return lastRead;
}

void Sensor::setId(int id){
    this->id = id;
}

void Sensor::setType(std::string type){
    this->type = type;
}

void Sensor::setLocation(std::string location){
    this->location = location;
}

void Sensor::setLastRead(double lastRead){
    this->lastRead = lastRead;
}

void Sensor::show(){
    std::cout<<"id = "<<id<<"| type = "<<type<<"| location = "<<location<<"| last read = "<<lastRead<<std::endl;
}