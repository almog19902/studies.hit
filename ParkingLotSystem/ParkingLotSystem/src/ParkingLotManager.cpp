#include <vector>
#include <chrono>
#include <iomanip>

#include "../include/Vehicles.hpp"
#include "../include/IParkingLotDataManager.hpp"
#include "../include/ParkingLotManager.hpp"

using namespace std;

namespace ParkingLotSystem
{
    ParkingLotManager::ParkingLotManager(IParkingLotDataManager* dataManager)
    {
        try
        {
            ParkingSpacesVectors = unordered_map<string, vector<Vehicle*>>();
            ParkingSpacesCapacities = unordered_map<string, size_t>();
            this->dataManager = dataManager;

            for (const auto& [type, capacity] : dataManager->GetDataMap()) 
            {
                AddVehicleType(type, capacity);
            }
        }
        catch(const runtime_error& e)
        {
            cerr << "Failed to create ParkingLotManager"<< e.what() << '\n';
        }
    }

    ParkingLotManager::~ParkingLotManager()
    {
        ResetParkingLot();
    }

    void ParkingLotManager::ResetParkingLot()
    {
        for (auto& [type, vector] : ParkingSpacesVectors) 
        {
            for (Vehicle* vehicle : vector) 
            {
                delete vehicle;
                vehicle = nullptr;
            }
        }
    }

    void ParkingLotManager::DisplayParkingLotStatus()
    {
        int numberOfVehicleInTheParkingLot = 0;
        int totalCurrentProfit = 0;
        int totalParkingTime = 0;
        int currentVectorParkingTime = 0;
        int cuurentVehiclePricePerHour = 0;

        time_t currentTime = time(nullptr);
        struct tm localTimeStruct; 
        localtime_s(&localTimeStruct, &currentTime);

        cout << "\n****************** Status ********************" << endl;
        cout << "Parking lot manager status - in time " 
             << put_time(&localTimeStruct, "%Y-%m-%d %H:%M:%S");

        for (const auto& [type, parkingSpacesVector] : ParkingSpacesVectors) 
        {
            cout << "Number of Available " << type << " parking spaces : " 
                 << ParkingSpacesCapacities[type] - parkingSpacesVector.size()
                 << " from " << ParkingSpacesCapacities[type] << endl;

            for (int i = 0; i < parkingSpacesVector.size() ; i++)
            {
                currentVectorParkingTime += (difftime(currentTime, parkingSpacesVector[i]->GetEntryTime()) /
                                                                    NUMBER_OF_SECONDS_IN_ONE_HOUR) + 1;
                cuurentVehiclePricePerHour = parkingSpacesVector[i]->GetPricePerHour();
            }

            totalParkingTime += currentVectorParkingTime;
            totalCurrentProfit += currentVectorParkingTime * cuurentVehiclePricePerHour;

            numberOfVehicleInTheParkingLot += parkingSpacesVector.size();

            currentVectorParkingTime = 0;
            cuurentVehiclePricePerHour = 0;
        }

        cout << "Number of vehicle in the parking lot : " <<  numberOfVehicleInTheParkingLot << endl;
        cout << "Total parking time : " <<  totalParkingTime << endl;
        cout << "Current profit : " <<  totalCurrentProfit << endl;
        cout << "**************************************" << endl;
    }

    bool ParkingLotManager::SaveParkingLotState(const string& fileName)
    {
        return (dataManager->SaveParkingLotState(ParkingSpacesVectors, fileName));
    }

    bool ParkingLotManager::LoadParkingLotState(const string& fileName)
    {
        auto tempVectorMap = dataManager->LoadParkingLotState(fileName);
        if (tempVectorMap.empty())
        {
            return false;
        }

        ResetParkingLot();
        ParkingSpacesVectors = tempVectorMap;
        return true;
    }

    bool ParkingLotManager::VehicleEntry(Vehicle* Vehicle)
    {
        return AddVehicle(Vehicle);
    }

    ParkingLotManager& ParkingLotManager::operator+(Vehicle* Vehicle)
    {
        VehicleEntry(Vehicle);
        return *this;
    }

    bool ParkingLotManager::VehicleExit(const string& licensePlate)
    {
        Vehicle* removedVehicle = RemoveVehicle(licensePlate);
        if (removedVehicle == nullptr)
        {
            cerr << "Vehicle with license plate " << licensePlate
                 << " not found in the parking lot." << endl;

            return false;
        }
        
        removedVehicle->SetExitTime(time(nullptr));
        cout << "\n******************* Vehicle Exit *******************" << endl;
        cout << *removedVehicle << "Pay : " << removedVehicle->PaymentCalculation() << endl;
        cout << "**************************************" << endl;

        delete removedVehicle;
        removedVehicle = nullptr;
        return true;
    }

    ParkingLotManager& ParkingLotManager::operator-(Vehicle* Vehicle)
    {
        VehicleExit(Vehicle->GetLicensePlate());
        return *this;
    }

    void ParkingLotManager::AddVehicleType(const string& vehicleType, size_t capacity)
    {
        ParkingSpacesVectors[vehicleType] = vector<Vehicle*>();
        ParkingSpacesCapacities[vehicleType] = capacity;
    }

    bool ParkingLotManager::AddVehicle(Vehicle* vehicle)
    {
        const string& vehicleType = vehicle->GetVehicleType();
        const string& licensePlate = vehicle->GetLicensePlate();

        if (ParkingSpacesVectors.find(vehicleType) == ParkingSpacesVectors.end())
        {
            cerr << "Unknown vehicle type: " << vehicleType << endl;
            return false;
        }


        for (auto& [type, vector] : ParkingSpacesVectors) 
        {
            for (auto iterator = vector.begin(); iterator != vector.end(); ++iterator)
            {
                if ((*iterator)->GetLicensePlate().compare(licensePlate) == 0)
                {
                    cerr << "Parking failed: " << (*iterator)->GetVehicleType() << " with license plate "
                         << licensePlate << " already parked in the parking lot." << endl;
                    return false;
                }
            }
        }

        if (ParkingSpacesVectors[vehicleType].size() < ParkingSpacesCapacities[vehicleType])
        {
            ParkingSpacesVectors[vehicleType].push_back(move(vehicle));
            cout << vehicleType << " with license plate : " << licensePlate << " parked." << endl;
            return true;
        }

        cerr << "Parking failed: No available space for " << vehicleType << endl;
        return false;
    }

    Vehicle* ParkingLotManager::RemoveVehicle(const string& licensePlate) 
    {
        for (auto& [type, vector] : ParkingSpacesVectors) 
        {
            for (auto iterator = vector.begin(); iterator != vector.end(); ++iterator)
            {
                if ((*iterator)->GetLicensePlate().compare(licensePlate) == 0)
                {
                    Vehicle* removedVehicle = *iterator;
                    vector.erase(iterator);
                    return removedVehicle;
                }
            }
        }

        return nullptr;
    }
}