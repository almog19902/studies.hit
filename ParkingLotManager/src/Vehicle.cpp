#include "../include/Vehicles.hpp"

namespace ParkingLotSystem
{
    Vehicle::~Vehicle()
    {
        // empty dtor
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
            outstream << "Still parked";
        }

        outstream << endl;
        return outstream;
    }

    bool Vehicle::operator==(const Vehicle& other) const
    {
        return (this->LicensePlate.compare(other.LicensePlate) == 0 &&
                this->VehicleType.compare(other.VehicleType) == 0 &&
                this->EntryTime == other.EntryTime &&
                this->ExitTime == other.ExitTime);
    }
}