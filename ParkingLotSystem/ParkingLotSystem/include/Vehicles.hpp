#ifndef VEHICLES_H
#define VEHICLES_H

#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;

namespace ParkingLotSystem
{
    static const unsigned int NUMBER_OF_SECONDS_IN_ONE_HOUR = 3600;
    
    class Vehicle
    {
        private:
            string LicensePlate;
            string VehicleType;
            time_t EntryTime;
            time_t ExitTime;

        public:
            Vehicle(const string& licensePlate, const string& vehicleType);
            virtual ~Vehicle();

            virtual unsigned int PaymentCalculation() = 0;
            virtual unsigned int GetPricePerHour() = 0;

            string GetLicensePlate() const;
            string GetVehicleType() const;
            time_t GetEntryTime() const;
            time_t GetExitTime() const;
            _Timeobj<char, const tm*> GetEntryTimeHumanReadable() const;
            _Timeobj<char, const tm*> GetExitTimeHumanReadable() const;

            void SetEntryTime(time_t time);
            void SetExitTime(time_t time);

            friend ostream& operator<<(ostream& outstream, const Vehicle& vehicle);
            virtual bool operator==(const Vehicle& other) const;
    };

    class Car : public Vehicle
    {
        private:
            static const unsigned int PricePerHour = 5;

        public:
            Car(string licensePlate);
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
            ~Truck() override;

            unsigned int PaymentCalculation() override;
            unsigned int GetPricePerHour() override;
    };
}

#endif // VEHICLES_H