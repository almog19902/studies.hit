#ifndef PARKING_LOT_DATA_MANAGER_H
#define PARKING_LOT_DATA_MANAGER_H

namespace ParkingLotManager
{
    class IParkingLotDataManager
    {
        virtual int SaveParkingLotState() = 0;
        virtual int LoadParkingLotState() = 0;
        virtual int GetParkingLotMetaData() = 0;
    };
}
#endif // PARKING_LOT_DATA_MANAGER_H
