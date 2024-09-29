#include "../include/Vehicle.hpp"

namespace ParkingLotSystem
{
    class Car : public Vehicle
    {
        private:
            static const unsigned int PricePerHour = 5;

        public:
            Car(string licensePlate) 
            {
                this->LicensePlate = licensePlate;
                this->VehicleType = "Car";
                time(&this->EntryTime);
                this->ExitTime = 0;
            }

            Car(Car& other) 
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