#include "../include/Vehicles.hpp"

namespace ParkingLotSystem
{
    Car::Car(string licensePlate)
    {
        this->LicensePlate = licensePlate;
        this->VehicleType = "Car";
        time(&this->EntryTime);
        this->ExitTime = 0;
    }

    Car::Car(Car& other)
    {
        this->LicensePlate = other.LicensePlate;
        this->VehicleType = other.VehicleType;
        this->EntryTime = other.EntryTime;
        this->ExitTime = other.ExitTime;
    }

    Car::~Car()
    {
        // empty dtor
    };

    unsigned int Car::PaymentCalculation()
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
    
    unsigned int Car::GetPricePerHour()
    {
        return PricePerHour;
    }
}