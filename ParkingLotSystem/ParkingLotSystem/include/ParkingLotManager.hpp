#ifndef PARKING_LOT_MANAGER_H
#define PARKING_LOT_MANAGER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Vehicles.hpp"
#include "IParkingLotDataManager.hpp"

using namespace std;

namespace ParkingLotSystem
{
    class ParkingLotManager
    {
        private:
            unordered_map<string, vector<Vehicle*>> ParkingSpacesVectors;
            unordered_map<string, size_t> ParkingSpacesCapacities;
            IParkingLotDataManager* dataManager;

            void AddVehicleType(const string& vehicleType, size_t capacity);
            bool AddVehicle(Vehicle* vehicle);
            Vehicle* RemoveVehicle(const string& licensePlate);
            void ResetParkingLot();

        public:
            ParkingLotManager(IParkingLotDataManager* dataManager);
            ~ParkingLotManager();

            void DisplayParkingLotStatus();
            bool SaveParkingLotState(const string& fileName);
            bool LoadParkingLotState(const string& fileName);

            bool VehicleEntry(Vehicle* Vehicle);
            ParkingLotManager& operator+(Vehicle* Vehicle);
            
            bool VehicleExit(const string& licensePlate);
            ParkingLotManager& operator-(Vehicle* Vehicle);
    };
}
#endif // PARKING_LOT_MANAGER_H
