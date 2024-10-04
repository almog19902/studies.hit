#ifndef PARKING_LOT_FILE_DATA_MANAGER_H
#define PARKING_LOT_FILE_DATA_MANAGER_H
#include <string>
#include <unordered_map>
#include <vector>
#include "../include/Vehicles.hpp"
#include "../include/IParkingLotDataManager.hpp"

using namespace std;

namespace ParkingLotSystem
{
    class ParkingLotFilesDataManager : public IParkingLotDataManager
    {
        private:
            unordered_map<string, size_t> dataMap;
            bool GetParkingLotData(const string& filePath);

        public:
            ParkingLotFilesDataManager(const string& filePath);
            ~ParkingLotFilesDataManager() override;

            bool SaveParkingLotState(unordered_map<string, vector<Vehicle*>>& ParkingSpacesVectors,
                                                                 const string& fileName) override;
            unordered_map<string, vector<Vehicle*>> LoadParkingLotState(const string& fileString) override;
            unordered_map<string, size_t>& GetDataMap() override;
    };
}
#endif // PARKING_LOT_FILE_DATA_MANAGER_H
