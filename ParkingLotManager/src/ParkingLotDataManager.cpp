#include "../include/IParkingLotDataManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace ParkingLotSystem
{
    class ParkingLotDataManager : public IParkingLotDataManager
    {
        private:
            unordered_map<string, int>* metadataDict;
            string Trim(const string& str);
            bool GetParkingLotMetaData(const string& filePath);

        public:
            ParkingLotDataManager(const string& filePath);
            ~ParkingLotDataManager();
            bool SaveParkingLotState() override;
            bool LoadParkingLotState() override;
            bool GetValue(const string& key, int& value_ref) override;
    };

    ParkingLotDataManager::ParkingLotDataManager(const string& filePath)
    {
        metadataDict = new unordered_map<string, int>();
        if (!GetParkingLotMetaData(filePath))
        {
            throw new runtime_error("failed to create ParkingLotDataManager");
        }
    }
    
    ParkingLotDataManager::~ParkingLotDataManager()
    {
        delete(metadataDict);
        metadataDict = NULL;
    }

    bool ParkingLotDataManager::GetValue(const string& key, int& value_ref)
    {
        try 
        {
            if (key.empty())
            {
                cerr << "ParkingLotDataManager GetValue error : empty key" << endl;
                return false;
            }

            value_ref = (*metadataDict)[key];
            return true;
        }
        catch (std::out_of_range& e)
        {
            cerr << "ParkingLotDataManager GetValue error : invalid key"<< e.what() << endl;
            return false;
        }
    }

    bool ParkingLotDataManager::SaveParkingLotState()
    {
        return 1;
    }

    bool ParkingLotDataManager::LoadParkingLotState()
    {
        return 1;
    }

    bool ParkingLotDataManager::GetParkingLotMetaData(const string& filePath)
    {
        ifstream metadataFile(filePath);
        if (!metadataFile.is_open()) 
        {
            cerr << "ParkingLotDataManager error: Could not open file " << filePath << endl;
            return false;
        }

        string line = "";
        while (getline(metadataFile, line)) 
        {
            stringstream strStream(line);

            //The metadata file has the be in format - "key:value"
            int value = 0;
            string key = "";
            if (getline(strStream, key, ':')) {
                strStream >> value;
                key = Trim(key);
                (*metadataDict)[key] = value;
            }
        }

        metadataFile.close();
        return true;
    }

    string ParkingLotDataManager::Trim(const string& str)
    {
        size_t first = str.find_first_not_of(" \t\n\r");
        size_t last = str.find_last_not_of(" \t\n\r");
        return (first == string::npos) ? "" : str.substr(first, last - first + 1);
    }
}