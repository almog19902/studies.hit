#include "include/Vehicle.hpp"
#include "src/ParkingLotManager.cpp"
#include "src/Car.cpp"
#include "src/Motorcycle.cpp"
#include <unistd.h>

using namespace ParkingLotSystem;

int main()
{
    unordered_map<string, size_t> parkingSpaces = {
        {"Car", 10},
        {"Motorcycle", 5},
        {"Truck", 3}
    };

    ParkingLotManager parkingLotManager(parkingSpaces);

    Car* car1 = new Car("ABC123");
    Car* car2 = new Car("XYZ789");
    Motorcycle* bike1 = new Motorcycle("MOTO456");


    parkingLotManager.VehicleEntry(car1);
    parkingLotManager.VehicleEntry(car2);
    parkingLotManager + bike1;
    
    sleep(5);

    parkingLotManager.PrintParkingLotStatus();

    parkingLotManager.VehicleExit(car2);

    parkingLotManager.PrintParkingLotStatus();

    parkingLotManager - bike1;

    parkingLotManager.PrintParkingLotStatus();

    delete car1;
    delete car2;
    delete bike1;

    return 0;
}
