#include "../src/Vehicle.cpp"
#include "../src/Car.cpp"
#include "../src/Motorcycle.cpp"
#include "../src/Truck.cpp"
#include "../src/ParkingLotFilesDataManager.cpp"
#include "../Include/IParkingLotDataManager.hpp"
#include <algorithm>

using namespace ParkingLotSystem;
using namespace std;

void AreParkingSpacesVectorsEqual(const unordered_map<string, vector<Vehicle*>>& map1,
                                  const unordered_map<string, vector<Vehicle*>>& map2);
bool CompareVehicles(Vehicle* v1, Vehicle* v2);

int main()
{
    IParkingLotDataManager *dataManager = new ParkingLotFilesDataManager("data.test.txt"); 
    unordered_map<string, vector<Vehicle*>> *ParkingSpacesVectors = new unordered_map<string, vector<Vehicle*>>();
    
    for (const auto& [vehicleType, capacity] : dataManager->GetDataMap())
    {
        cout << "Parking spaces available for " << vehicleType << "s : " << capacity << endl;
        (*ParkingSpacesVectors)[vehicleType] = vector<Vehicle*>();
     }

    Vehicle* car1 = new Car("ABC123");
    Vehicle* car2 = new Car("XYZ789");
    Vehicle* bike1 = new Motorcycle("MOTO456");
    Vehicle* Truck1 = new Truck("TRK852");
    
    (*ParkingSpacesVectors)["Car"].push_back(move(car1));
    (*ParkingSpacesVectors)["Car"].push_back(move(car2));
    (*ParkingSpacesVectors)["Motorcycle"].push_back(move(bike1));
    (*ParkingSpacesVectors)["Truck"].push_back(move(Truck1));

    if (!dataManager->SaveParkingLotState(*ParkingSpacesVectors, "ParkingLotDataManagerTests_stateSavedFile.txt"))
    {
        cerr << "Failed to write to file." << endl;
    }
    else
    {
        unordered_map<string, vector<Vehicle*>> result = dataManager->LoadParkingLotState("ParkingLotDataManagerTests_stateSavedFile.txt");
        AreParkingSpacesVectorsEqual(*ParkingSpacesVectors, result);
    }
    return 1;
}

void AreParkingSpacesVectorsEqual(const unordered_map<string, vector<Vehicle*>>& map1,
                                  const unordered_map<string, vector<Vehicle*>>& map2)
{
    if (map1.size() != map2.size())
    {
        cerr << "The maps are of different sizes." << endl;
        return;
    }

    for (const auto& [vehicleType, currentVector] : map1) 
    {
        auto iterator = map2.find(vehicleType);
        if (iterator == map2.end())
        {
            cerr << "Vehicle type " << vehicleType << " not found in the map loaded from file" << endl;
            return;
        }

        if (currentVector.size() != iterator->second.size()) {
            cerr << "The vectors of vehicle type " << vehicleType << " are of different sizes." << endl;
            return;
        }

        if (!is_permutation(currentVector.begin(), currentVector.end(), 
                            iterator->second.begin(), iterator->second.end(), 
                            CompareVehicles))
        {
            cerr << "Found different vehicles." << endl;
            return;
        }
    }

    cout << "Maps are equal." << endl;
}

bool CompareVehicles(Vehicle* v1, Vehicle* v2)
{
    return *v1 == *v2;
}