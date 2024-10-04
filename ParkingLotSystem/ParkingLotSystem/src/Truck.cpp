#include "../include/Vehicles.hpp"

namespace ParkingLotSystem
{
    Truck::Truck(string licensePlate) : Vehicle(licensePlate, "Truck") 
    {
        //use only base ctor
    }

    Truck::~Truck()
    {
        //empty detor
    }

    unsigned int Truck::PaymentCalculation()
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
    
    unsigned int Truck::GetPricePerHour()
    {
        return PricePerHour;
    }
}