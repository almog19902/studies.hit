#include "../include/ParkingLotFilesDataManager.hpp"
#include "../include/Vehicles.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace ParkingLotSystem
{
    ParkingLotFilesDataManager::ParkingLotFilesDataManager(const string& filePath)
    {
        unordered_map<string, size_t> dataMap = unordered_map<string, size_t>();
        if (!GetParkingLotData(filePath))
        {
            cerr << "Failed to read parking lot data from: " << filePath << endl;
            throw runtime_error("failed to create ParkingLotFilesDataManager");
        }
    }
    
    unordered_map<string, size_t> ParkingLotFilesDataManager::GetDataMap()
    {
        return dataMap;
    }

    bool ParkingLotFilesDataManager::SaveParkingLotState(unordered_map<string, vector<Vehicle*>> ParkingSpacesVectors,
                                                                                               const string& fileName)
    {
        ofstream outFile(fileName);
        
        if (!outFile.is_open()) 
        {
            cerr << "Failed to open file for saving parking lot state!" << endl;
            return false;
        }

        for (const auto& [vehicleType, parkingSpaceVector] : ParkingSpacesVectors)
        {
            for (const auto& vehicle : parkingSpaceVector)
            {
                outFile << vehicleType << " " 
                        << vehicle->LicensePlate << " " 
                        << vehicle->EntryTime << "\n";
            }
        }

        outFile.close();
        return true;
    }

    unordered_map<string, vector<Vehicle*>> ParkingLotFilesDataManager::LoadParkingLotState(const string& fileString)
    {
        unordered_map<string, vector<Vehicle*>> ParkingSpacesVectors;
        ifstream inFile(fileString);

        if (!inFile.is_open()) 
        {
            cerr << "Failed to open file for loading parking lot state." << endl;
            return ParkingSpacesVectors;
        }

        string vehicleType;
        string licensePlate;
        time_t entryTime;
        time_t exitTime;

        while (inFile >> vehicleType >> licensePlate >> entryTime)
        {
            Vehicle* vehicle = Utils::GetVehicleInstanceByVehicleType(vehicleType, licensePlate);
            
            if(vehicle == nullptr)
            {
                cerr << "Cant load vehicle with license plate " << licensePlate << "from file.\n"
                     << "vehicle type " << vehicleType << "is invalid." << endl;
                     continue;
            }

            vehicle->VehicleType = vehicleType;
            vehicle->EntryTime = entryTime;
            vehicle->ExitTime = 0;

            if (ParkingSpacesVectors[vehicleType].size() >= dataMap[vehicleType])
            {
                cout << "You have reached the limit of the " << vehicleType << " that can park in the parking lot."
                     << "A " << vehicle->VehicleType << " with license plate " << vehicle->LicensePlate 
                     << "did not enter." << endl;
            }
            else
            {
                ParkingSpacesVectors[vehicleType].push_back(vehicle);
            }
        }

        inFile.close();
        return ParkingSpacesVectors;
    }

    ParkingLotFilesDataManager::~ParkingLotFilesDataManager()
    {
        //empty dtor
    }

    bool ParkingLotFilesDataManager::GetParkingLotData(const string& filePath)
    {
        ifstream dataFile(filePath);
        if (!dataFile.is_open()) 
        {
            cerr << "ParkingLotFilesDataManager error: Could not open file " << filePath << endl;
            return false;
        }

        string line = "";
        while (getline(dataFile, line)) 
        {
            stringstream strStream(line);

            //The data file has the be in format - "key:value"
            size_t value = -1;
            string key = "";
            if (getline(strStream, key, ':')) {
                strStream >> value;
                key = Utils::Trim(key);
                dataMap[key] = value;
            }
        }

        dataFile.close();
        return true;
    }
}