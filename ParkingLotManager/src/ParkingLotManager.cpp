#include "../include/Vehicle.hpp"
#include "../include/IParkingLotDataManager.hpp"
#include "../src/ParkingLotDataManager.cpp"
#include <vector>

using namespace std;

namespace ParkingLotSystem
{
    class ParkingLotManager
    {
        private:
            unordered_map<string, vector<Vehicle*>> ParkingSpacesVectors;
            unordered_map<string, size_t> ParkingSpacesCapacities;
            void AddVehicleType(const string& vehicleType, size_t capacity);
            bool AddVehicle(Vehicle* vehicle);
            bool removeVehicle(Vehicle* vehicle);

        public:
            ParkingLotManager(unordered_map<string, size_t> ParkingVehiclesAndCapacies);
            void PrintParkingLotStatus();

            bool VehicleEntry(Vehicle* vehicle);
            ParkingLotManager& operator+(Vehicle* Vehicle);
            bool VehicleExit(Vehicle* vehicle);
            ParkingLotManager& operator-(Vehicle* Vehicle);
    }; 

    ParkingLotManager::ParkingLotManager(unordered_map<string, size_t> ParkingVehiclesAndCapacies)
    {
        try
        {
            ParkingSpacesVectors = unordered_map<string, vector<Vehicle*>>();
            ParkingSpacesCapacities = unordered_map<string, size_t>();

            for (const auto& [type, capacity] : ParkingVehiclesAndCapacies) 
            {
                AddVehicleType(type, capacity);
            }
        }
        catch(const runtime_error& e)
        {
            cerr << "Failed to create ParkingLotManager"<< e.what() << '\n';
        }
    }

    void ParkingLotManager::PrintParkingLotStatus()
    {
        int numberOfVehicleInTheParkingLot = 0;
        int totalCurrentProfit = 0;
        int totalParkingTime = 0;
        int currentVectorParkingTime = 0;
        int cuurentVehiclePricePerHour = 0;
        time_t currentTime = time(nullptr);

        cout << "\n****************** Status ********************" << endl;
        cout << "Parking lot manager status - in time " << ctime(&currentTime);

        for (const auto& [type, parkingSpacesVector] : ParkingSpacesVectors) 
        {
            cout << "Number of Available " << type << " parking spaces : " 
                 << ParkingSpacesCapacities[type] - parkingSpacesVector.size()
                 << " from " << ParkingSpacesCapacities[type] << endl;

            for (int i = 0; i < parkingSpacesVector.size() ; i++)
            {
                currentVectorParkingTime += (difftime(currentTime, parkingSpacesVector[i]->EntryTime) /
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

    bool ParkingLotManager::VehicleEntry(Vehicle* vehicle)
    {
        return AddVehicle(vehicle);
    }

    ParkingLotManager& ParkingLotManager::operator+(Vehicle* Vehicle)
    {
        VehicleEntry(Vehicle);
        return *this;
    }

    bool ParkingLotManager::VehicleExit(Vehicle* vehicle)
    {
        
        if (!removeVehicle(vehicle))
        {
            cerr << vehicle->VehicleType << " with license plate "
                 << vehicle->LicensePlate << " not found in the parking lot." << endl;
            return false;
        }
        
        time(&(vehicle->ExitTime));
        cout << "\n******************* Vehicle Exit *******************" << endl;
        cout << *vehicle << "Pay : " << vehicle->PaymentCalculation() << endl;
        cout << "**************************************" << endl;

        return true;
    }

    ParkingLotManager& ParkingLotManager::operator-(Vehicle* Vehicle)
    {
        VehicleExit(Vehicle);
        return *this;
    }

    void ParkingLotManager::AddVehicleType(const string& vehicleType, size_t capacity)
    {
        ParkingSpacesVectors[vehicleType] = vector<Vehicle*>();
        ParkingSpacesCapacities[vehicleType] = capacity;
    }

    bool ParkingLotManager::AddVehicle(Vehicle* vehicle)
    {
        const string& vehicleType = vehicle->VehicleType;
        if (ParkingSpacesVectors.find(vehicleType) == ParkingSpacesVectors.end())
        {
            cerr << "Unknown vehicle type: " << vehicleType << endl;
            return false;
        }

        if (ParkingSpacesVectors[vehicleType].size() < ParkingSpacesCapacities[vehicleType])
        {
            ParkingSpacesVectors[vehicleType].push_back(move(vehicle));
            cout << vehicleType << " with license plate : " << vehicle->LicensePlate << " parked." << endl;
            return true;
        }

        cerr << "Parking failed: No available space for " << vehicleType << endl;
        return false;
    }

    bool ParkingLotManager::removeVehicle(Vehicle* vehicle) 
    {
        string vehicleType = vehicle->VehicleType;

        if (ParkingSpacesVectors.find(vehicleType) != ParkingSpacesVectors.end())
        {
            vector<Vehicle*>& vector = ParkingSpacesVectors[vehicleType];
            
            for (auto iterator = vector.begin(); iterator != vector.end(); ++iterator)
            {
                if ((*iterator)->LicensePlate.compare(vehicle->LicensePlate) == 0)
                {
                    vector.erase(iterator);
                    return true;
                }
            }
        }

        return false;
    }
}