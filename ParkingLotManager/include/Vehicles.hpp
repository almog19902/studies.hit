#ifndef VEHICLES_H
#define VEHICLES_H

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

            virtual ~Vehicle();
            virtual unsigned int PaymentCalculation() = 0;
            virtual unsigned int GetPricePerHour() = 0;
            friend ostream& operator<<(ostream& outstream, const Vehicle& vehicle);
            virtual bool operator==(const Vehicle& other) const;
    };

    class Car : public Vehicle
    {
        private:
            static const unsigned int PricePerHour = 5;

        public:
            Car(string licensePlate);
            Car(Car& other);
            ~Car() override;
            unsigned int PaymentCalculation() override;
            unsigned int GetPricePerHour() override;
    };

    class Motorcycle : public Vehicle
    {
        private:
            static const unsigned int PricePerHour = 1;

        public:
            Motorcycle(string licensePlate);
            Motorcycle(Motorcycle& other);
            ~Motorcycle() override;
            unsigned int PaymentCalculation() override;
            unsigned int GetPricePerHour() override;
    };

    class Truck : public Vehicle
    {
        private:
            static const unsigned int PricePerHour = 100;

        public:
            Truck(string licensePlate);
            Truck(Truck& other);
            ~Truck() override;
            unsigned int PaymentCalculation() override;
            unsigned int GetPricePerHour() override;
    };
}

#endif // VEHICLES_H