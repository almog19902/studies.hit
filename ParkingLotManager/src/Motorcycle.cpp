#include "../include/Vehicle.hpp"

namespace ParkingLotManager
{
    class Motorcycle : public Vehicle
    {
        private:
            static const unsigned int PricePerHour = 1;
            
        public:
            Motorcycle(string licensePlate) 
            {
                this->LicensePlate = licensePlate;
                this->VehicleType = "Motorcycle";
                time(&this->EntryTime);
                this->ExitTime = 0;
            }
            
            Motorcycle(Motorcycle& other) 
            {
                this->LicensePlate = other.LicensePlate;
                this->VehicleType = other.VehicleType;
                this->EntryTime = other.EntryTime;
                this->ExitTime = other.ExitTime;
            }

            unsigned int PaymentCalculation() override
            {
                if (EntryTime == 0 ||  ExitTime == 0 || EntryTime > ExitTime)
                {
                    cout << "Parking time is invalid; EntryTime = " << EntryTime
                                       << ",  ExitTime = " << EntryTime << endl;
                }

                double parkingTimeElapsedInSeconds = difftime(ExitTime, EntryTime);
                int parkingTimeElapsedInHours = (parkingTimeElapsedInSeconds / NUMBER_OF_SECONDS_IN_ONE_HOUR) + 1;
                return parkingTimeElapsedInHours * PricePerHour;
            }
    };
}