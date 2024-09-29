#include "../include/Vehicle.hpp"

namespace ParkingLotSystem
{
    class Truck : public Vehicle
    {
        private:
            static const unsigned int PricePerHour = 100;
            
        public:
            Truck(string licensePlate) 
            {
                this->LicensePlate = licensePlate;
                this->VehicleType = "Truck";
                time(&this->EntryTime);
                this->ExitTime = 0;
            }

            Truck(Truck& other) 
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
                    cout << "Parking time is invalid; EntryTime = " << ctime(&EntryTime)
                                       << ",  ExitTime = " << ctime(&EntryTime) << endl;
                }

                double parkingTimeElapsedInSeconds = difftime(ExitTime, EntryTime);
                int parkingTimeElapsedInHours = (parkingTimeElapsedInSeconds / NUMBER_OF_SECONDS_IN_ONE_HOUR) + 1;
                return parkingTimeElapsedInHours * PricePerHour;
            }
            
            unsigned int GetPricePerHour() override
            {
                return PricePerHour;
            }
    };
}