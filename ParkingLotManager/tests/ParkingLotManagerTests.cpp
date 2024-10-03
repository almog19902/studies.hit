#include "../src/ParkingLotManager.cpp"
#include "../src/ParkingLotFilesDataManager.cpp"
#include "../src/Vehicle.cpp"
#include "../src/Car.cpp"
#include "../src/Motorcycle.cpp"
#include "../src/Truck.cpp"

#include <unistd.h>

using namespace ParkingLotSystem;

int main()
{
    try
    {
        IParkingLotDataManager* parkingLotDataManager = new ParkingLotFilesDataManager("data.test.txt");
        ParkingLotManager* parkingLotManager = new ParkingLotManager(parkingLotDataManager);

        cout << "The parking lot contains:" << endl;

        for (const auto& [vehicleType, capacity] : parkingLotDataManager->GetDataMap())
        {  
            cout << capacity << " " << vehicleType << "s " << "Parking spaces." <<  endl;
        }
        cout << endl;

        Car* car1 = new Car("ABC123");
        Car* car2 = new Car("XYZ789");
        Motorcycle* bike1 = new Motorcycle("MOTO456");

        parkingLotManager->VehicleEntry(car1);
        parkingLotManager->VehicleEntry(car2);
        *parkingLotManager + bike1;
        
        sleep(5);

        parkingLotManager->DisplayParkingLotStatus();

        parkingLotManager->VehicleExit("XYZ789"); // car2

        parkingLotManager->DisplayParkingLotStatus();

        *parkingLotManager - bike1;

        parkingLotManager->DisplayParkingLotStatus();

        delete car1;
        delete car2;
        delete bike1;
    }
    catch(const runtime_error& rex)
    {
        cerr << rex.what() << '\n';
        return -1;
    }

    return 0;
}
