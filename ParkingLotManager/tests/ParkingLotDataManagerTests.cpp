#include "../src/ParkingLotDataManager.cpp"

using namespace ParkingLotSystem;

void PrintValueFromParkingLotDataManager(IParkingLotDataManager *dataManager, const string& key)
{
    int resultValue = 0;

    dataManager->GetValue(key, resultValue);

    if (resultValue == 0)
    {
        cout << "failed to get metadata for " << key << endl;
    }
    else
    {
        cout << "Parking spaces available for " << key << "s : " << resultValue << endl;
    }
}

int main()
{
    IParkingLotDataManager *dataManager = new ParkingLotDataManager("metadate.test.txt"); 
    
    PrintValueFromParkingLotDataManager(dataManager, "Car");
    PrintValueFromParkingLotDataManager(dataManager, "Motorcycle");
    PrintValueFromParkingLotDataManager(dataManager, "Truck");
    return 1;
}