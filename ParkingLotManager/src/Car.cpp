#include "../include/Vehicles.hpp"

namespace ParkingLotSystem
{
    Car::Car(string licensePlate) : Vehicle(licensePlate, "Car")
    {
        //use only base ctor
    }

    Car::~Car()
    {
        //empty detor
    }

    unsigned int Car::PaymentCalculation()
    {
        if (GetEntryTime() == 0 ||  GetExitTime() == 0 || GetEntryTime() > GetExitTime())
        {
            cout << "Parking time is invalid; EntryTime = " << GetEntryTimeHumanReadable()
                                << ",  ExitTime = " << GetExitTimeHumanReadable() << endl;
        }

        time_t parkingTimeElapsedInHours = (difftime(GetExitTime(), GetEntryTime()) /
                                            NUMBER_OF_SECONDS_IN_ONE_HOUR) + 1;
                                            
        return parkingTimeElapsedInHours * PricePerHour;
    }
    
    unsigned int Car::GetPricePerHour()
    {
        return PricePerHour;
    }
}