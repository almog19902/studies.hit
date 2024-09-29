#include "../include/Vehicle.hpp"
#include "../src/Car.cpp"
#include "../src/Motorcycle.cpp"
#include "../src/Truck.cpp"

using namespace ParkingLotManager;

int main()
{
    Car car("00-000-01");
    Motorcycle motorcycle("00-000-02");
    Truck truck("00-000-03");

    time(&(car.ExitTime));
    time(&(motorcycle.ExitTime));
    time(&(truck.ExitTime));

    int time_difference_seconds = 10 * 3600 + 32 * 60;

    car.ExitTime += time_difference_seconds;
    
    cout << "car bill : " << car.PaymentCalculation() << endl;

    cout << "car: \n" << car << endl;

    motorcycle.ExitTime += time_difference_seconds;
    
    cout << "motorcycle bill : " << motorcycle.PaymentCalculation() << endl;

    cout << "motorcycle: \n" << motorcycle << endl;

    truck.ExitTime += time_difference_seconds;
    
    cout << "truck bill : " << truck.PaymentCalculation() << endl;

    cout << "truck: \n" << truck << endl;

    return 1;
}