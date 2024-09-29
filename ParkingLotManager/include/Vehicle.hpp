#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <ctime>
using namespace std;

namespace ParkingLotSystem
{
    static const unsigned int NUMBER_OF_SECONDS_IN_ONE_HOUR = 3600;
    
    class Vehicle
    {
        public:
            string LicensePlate;
            string VehicleType;
            time_t EntryTime;
            time_t ExitTime;

            virtual unsigned int PaymentCalculation() = 0;
            virtual unsigned int GetPricePerHour() = 0;
            friend ostream& operator<<(ostream& outstream, const Vehicle& vehicle);
    };

    ostream& operator<<(ostream& outstream, const Vehicle& vehicle) 
    {
        outstream << vehicle.VehicleType << ": " << vehicle.LicensePlate << "\n"
        << "Entry time: " << ctime(&(vehicle.EntryTime));

        if (vehicle.ExitTime != 0) 
        {
            outstream << "Exit time: " << ctime(&(vehicle.ExitTime));
        } 
        else 
        {
            outstream << "Exit time: Not exited yet";
        }

        outstream << endl;
        return outstream;
    }
}

#endif // VEHICLE_H