#ifndef PARKING_LOT_DATA_MANAGER_H
#define PARKING_LOT_DATA_MANAGER_H
#include <string>
#include <unordered_map>
#include <vector>
#include "../include/Vehicles.hpp"

using namespace std;

namespace ParkingLotSystem
{
    class IParkingLotDataManager
    {
        public:
            virtual ~IParkingLotDataManager() = 0;
            virtual bool SaveParkingLotState(unordered_map<string, vector<Vehicle*>> ParkingSpacesVectors,
                                                                              const string& fileName) = 0;
            virtual unordered_map<string, vector<Vehicle*>> LoadParkingLotState(const string& fileString) = 0;
            virtual unordered_map<string, size_t> GetDataMap() = 0;
    };

    IParkingLotDataManager::~IParkingLotDataManager()
    {
        //empty dtor
    }
}
#endif // PARKING_LOT_DATA_MANAGER_H
