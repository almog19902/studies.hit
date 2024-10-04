#include "../include/Vehicles.hpp"

namespace ParkingLotSystem
{
    Motorcycle::Motorcycle(string licensePlate) : Vehicle(licensePlate, "Motorcycle")
    {
        //use only base ctor
    }

    Motorcycle::~Motorcycle()
    {
        //empty detor
    }

    unsigned int Motorcycle::PaymentCalculation()
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

    unsigned int Motorcycle::GetPricePerHour()
    {
        return PricePerHour;
    }
}