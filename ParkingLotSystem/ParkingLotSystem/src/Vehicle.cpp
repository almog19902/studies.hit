#include <chrono>
#include <iomanip>

#include "../include/Vehicles.hpp"

namespace ParkingLotSystem
{
    Vehicle::Vehicle(const string& licensePlate, const string& vehicleType)
    {
        this->LicensePlate = licensePlate;
        this->VehicleType = vehicleType;
        this->SetEntryTime(time(nullptr)); // now
        this->SetExitTime(0);
    }

    Vehicle::~Vehicle()
    {
        //empty detor
    }

    string Vehicle::GetLicensePlate() const
    {
        return LicensePlate;
    }

    string Vehicle::GetVehicleType() const
    {
        return VehicleType;
    }

    time_t Vehicle::GetEntryTime() const
    {
        return EntryTime;
    }

    time_t Vehicle::GetExitTime() const
    {
        return ExitTime;
    }

    _Timeobj<char, const tm*> Vehicle::GetEntryTimeHumanReadable() const
    {
        struct tm localTimeStruct;
        localtime_s(&localTimeStruct, &EntryTime);

        return put_time(&localTimeStruct, "%Y-%m-%d %H:%M:%S");
    }

    _Timeobj<char, const tm*> Vehicle::GetExitTimeHumanReadable() const
    {
        struct tm localTimeStruct;
        localtime_s(&localTimeStruct, &ExitTime);

        return put_time(&localTimeStruct, "%Y-%m-%d %H:%M:%S");
    }

    void Vehicle::SetEntryTime(time_t time)
    {
        EntryTime = time;
    }

    void Vehicle::SetExitTime(time_t time)
    {
        ExitTime = time;
    }

    ostream& operator<<(ostream& outstream, const Vehicle& vehicle) 
    {
        outstream << vehicle.GetVehicleType() << ": " << vehicle.GetLicensePlate() << "\n"
        << "Entry time: " << vehicle.GetEntryTimeHumanReadable();

        if (vehicle.GetExitTime() != 0) 
        {
            outstream << "Exit time: " << vehicle.GetExitTimeHumanReadable();
        } 
        else 
        {
            outstream << "Still parked";
        }

        outstream << endl;
        return outstream;
    }

    bool Vehicle::operator==(const Vehicle& other) const
    {
        return (this->GetLicensePlate().compare(other.GetLicensePlate()) == 0 &&
                this->GetVehicleType().compare(other.GetVehicleType()) == 0 &&
                this->GetEntryTime() == other.GetEntryTime() &&
                this->GetExitTime() == other.GetExitTime());
    }
}