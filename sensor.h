#ifndef SENSOR_H
#define SENSOR_H
#include <iostream>
#include <string>
class Sensor{
    private:
        short int id;
        std::string type;
        std::string location;
        double lastRead;
    
        
    public:
        Sensor() = default;
        Sensor(short int id, std::string type,std::string location);

        short int getId(); void setId(int id);
        std::string getType(); void setType(std::string type);
        std::string getLocation(); void setLocation(std::string location);
        double getLastRead(); void setLastRead(double lastRead);

        void show();
};

#endif