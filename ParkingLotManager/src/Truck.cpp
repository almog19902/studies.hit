#include "../include/Vehicles.hpp"

namespace ParkingLotSystem
{
    Truck::Truck(string licensePlate) 
    {
        this->LicensePlate = licensePlate;
        this->VehicleType = "Truck";
        time(&this->EntryTime);
        this->ExitTime = 0;
    }

    Truck::Truck(Truck& other) 
    {
        this->LicensePlate = other.LicensePlate;
        this->VehicleType = other.VehicleType;
        this->EntryTime = other.EntryTime;
        this->ExitTime = other.ExitTime;
    }

    Truck::~Truck()
    {
        // empty dtor
    };

    unsigned int Truck::PaymentCalculation()
    {
        if (EntryTime == 0 ||  ExitTime == 0 || EntryTime > ExitTime)
        {
            cout << "Parking time is invalid; EntryTime = " << ctime(&EntryTime)
                                << ",  ExitTime = " << ctime(&EntryTime) << endl;
        }

        double parkingTimeElapsedInSeconds = difftime(ExitTime, EntryTime);
        int parkingTimeElapsedInHours = (parkingTimeElapsedInSeconds / NUMBER_OF_SECONDS_IN_ONE_HOUR) + 1;
        return parkingTimeElapsedInHours * PricePerHour;
    }
    
    unsigned int Truck::GetPricePerHour()
    {
        return PricePerHour;
    }
}