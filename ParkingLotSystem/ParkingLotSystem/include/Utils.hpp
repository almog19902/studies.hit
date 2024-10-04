#ifndef UTILS_H
#define UTILS_H

#include "Vehicles.hpp"

namespace Utils
{
    static string Trim(const string& str)
    {
        size_t first = str.find_first_not_of(" \t\n\r");
        size_t last = str.find_last_not_of(" \t\n\r");
        return (first == string::npos) ? "" : str.substr(first, last - first + 1);
    }

    static ParkingLotSystem::Vehicle* GetVehicleInstanceByVehicleType(string vehicleType, string licensePlate)
    {
        if (vehicleType.compare("Car") == 0)
        {
            return new ParkingLotSystem::Car(licensePlate);
        }
        else if (vehicleType.compare("Motorcycle") == 0)
        {
            return new ParkingLotSystem::Motorcycle(licensePlate);
        }
        else if (vehicleType.compare("Truck") == 0)
        {
            return new ParkingLotSystem::Truck(licensePlate);
        }

        cerr << "Can't create " << vehicleType << "instance with license plate " << licensePlate << endl;
        return nullptr;
    }
}

#endif // UTILS_H