#include "include/Utils.hpp"
#include "include/IParkingLotDataManager.hpp"
#include "src/ParkingLotManager.cpp"
#include "src/ParkingLotFilesDataManager.cpp"
#include "src/Vehicle.cpp"
#include "src/Car.cpp"
#include "src/Motorcycle.cpp"
#include "src/Truck.cpp"

#include <unistd.h>

using namespace ParkingLotSystem;

void ParkVehicleInTheParkingLot(ParkingLotManager *parkingLotManager, unordered_map<string, size_t> dataMap);
void ExitVehicleFromTheParkingLot(ParkingLotManager *parkingLotManager);
void DisplayParkingLotStatus(ParkingLotManager *parkingLotManager);
void SaveParkingLotStateToFile(ParkingLotManager *parkingLotManager);
void LoadParkingLotStateFromFile(ParkingLotManager *parkingLotManager);

int main()
{
    try
    {
        IParkingLotDataManager* parkingLotDataManager = new ParkingLotFilesDataManager("data.txt");
        unordered_map<string, size_t> dataMap = parkingLotDataManager->GetDataMap();

        if (dataMap.empty())
        {
            cerr << "dataFile empty the פarking not created properly." << endl;
            delete parkingLotDataManager;
            return -1;
        }

        ParkingLotManager* parkingLotManager = new ParkingLotManager(parkingLotDataManager);
        
        cout << endl;
        cout << "Hello, welcome to the smart parking lot management system.\n" << endl;
        cout << "The parking lot contains:" << endl;

        for (const auto& [vehicleType, capacity] : dataMap)
        {  
            cout << capacity << " " << vehicleType << "s " << "Parking spaces." <<  endl;
        }
        cout << endl;

        cout << "Here is the menu of actions that can be performed in the parking lot :\n" << endl;
        cout << "1. Entrance to the parking lot and parking of vehicles." << endl;
        cout << "2. Exiting the parking lot and paying." << endl;
        cout << "3. Displaying parking lot status." << endl;
        cout << "4. Saving parking lot state to a file." << endl;
        cout << "5. Uploading parking lot state from a file." << endl;
        cout << "6. Exiting the smart parking lot system.\n" << endl;
        cout << "Enter the number of the action you want to perform :" << endl;
        
        int userActionNumber = 0;
        cin >> userActionNumber;

        while (userActionNumber != 6)
        {
            switch (userActionNumber)
            {
                case 1:
                    ParkVehicleInTheParkingLot(parkingLotManager, dataMap);
                    break;

                case 2:
                    ExitVehicleFromTheParkingLot(parkingLotManager);
                    break;

                case 3:
                    DisplayParkingLotStatus(parkingLotManager);
                    break;

                case 4:
                    SaveParkingLotStateToFile(parkingLotManager);
                    break;

                case 5:
                    LoadParkingLotStateFromFile(parkingLotManager);
                    break;
                
                default:
                    cerr << "You entered an incorrect action number, "
                        << "The action number should be according to the menu - number from 1 to 6." << endl;
                    break;
            }

            cout << "Enter the number of the action you want to perform :" << endl;
            cin >> userActionNumber;
        }

        cout << "Bye ;)" << endl;

        delete parkingLotDataManager;
        delete parkingLotManager;

        return 0;
    }
    catch(const runtime_error& rex)
    {
        cerr << rex.what() << '\n';
        return -1;
    }
}

void ParkVehicleInTheParkingLot(ParkingLotManager *parkingLotManager, unordered_map<string, size_t> dataMap)
{
    string vehicleLicensePlate = "";

    cout << "Insert the license plate of the entered vehicle:" << endl;
    cin >> vehicleLicensePlate;

    if (vehicleLicensePlate.empty())
    {
        cout << "Invalid license plate string, we back to menu." << endl;
        return;
    }

    string vehicleType = "";

    cout << "Enter vehicle type: ";
    for (const auto& [vehicleType, capacity] : dataMap)
    {
         cout << vehicleType << " | ";
    }
    cout << endl;
    
    cin >> vehicleType;

    Vehicle* vehicle = Utils::GetVehicleInstanceByVehicleType(vehicleType, vehicleLicensePlate);

    if (vehicle == nullptr)
    {
        cout << "Invalid vehicle type string, we back to menu." << endl;
        return;
    }

    if (!parkingLotManager->VehicleEntry(vehicle))
    {
        delete vehicle;
    }
}

void ExitVehicleFromTheParkingLot(ParkingLotManager *parkingLotManager)
{
    string vehicleLicensePlate = "";

    cout << "Insert the license plate of the exiting vehicle:" << endl;
    cin >> vehicleLicensePlate;

    if (vehicleLicensePlate.empty())
    {
        cout<<"Invalid license plate string, we back to menu." << endl;
        return;
    }

    parkingLotManager->VehicleExit(vehicleLicensePlate);
}

void DisplayParkingLotStatus(ParkingLotManager *parkingLotManager)
{
    parkingLotManager->DisplayParkingLotStatus();
}

void SaveParkingLotStateToFile(ParkingLotManager *parkingLotManager)
{
    string fileName = "";
    cout << "Set name for file to save to :" << endl;
    cin >> fileName;

    if (fileName.empty())
    {
        cerr << "Invalid file name, return to menu." << endl;
        return;
    }

    if (!parkingLotManager->SaveParkingLotState(fileName))
    {
        cerr << "Failed to save parking lot state." << endl;
        return;
    }

    cout << "Save parking lot state." << endl;
}

void LoadParkingLotStateFromFile(ParkingLotManager *parkingLotManager)
{
    string fileName = "";
    cout << "Enter name of file to load to praking lot system:"
         << " (only files that saved by parking lot system)" << endl;

    cin >> fileName;

    if (fileName.empty())
    {
        cerr << "Invalid file name, return to menu." << endl;
        return;
    }

    if (!parkingLotManager->LoadParkingLotState(fileName))
    {
        cerr << "Failed to load parking lot state." << endl;
        return;
    }

    cout << "Load parking lot state." << endl;
}

