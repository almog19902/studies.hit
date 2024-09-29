#ifndef PARKING_LOT_DATA_MANAGER_H
#define PARKING_LOT_DATA_MANAGER_H
#include <string>
#include <unordered_map>

using namespace std;

namespace ParkingLotSystem
{
    class IParkingLotDataManager
    {
        public:
            virtual bool SaveParkingLotState() = 0;
            virtual bool LoadParkingLotState() = 0;
            virtual bool GetValue(const string& key, int& value_ref) = 0;
    };
}
#endif // PARKING_LOT_DATA_MANAGER_H
