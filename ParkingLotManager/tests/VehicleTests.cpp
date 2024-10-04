#include "../src/Car.cpp"
#include "../src/Motorcycle.cpp"
#include "../src/Truck.cpp"
#include "../src/Vehicle.cpp"


using namespace ParkingLotSystem;

int main()
{
    Car car("00-000-01");
    Motorcycle motorcycle("00-000-02");
    Truck truck("00-000-03");

    car.SetExitTime(time(nullptr));
    motorcycle.SetExitTime(time(nullptr));
    truck.SetExitTime(time(nullptr));

    int time_difference_seconds = 10 * 3600 + 32 * 60; // 10 houres and 32 minets in seconds

    car.SetExitTime(car.GetExitTime() + time_difference_seconds);
    
    cout << "car bill : " << car.PaymentCalculation() << endl;

    cout << "car: \n" << car << endl;

    motorcycle.SetExitTime(motorcycle.GetExitTime() + time_difference_seconds);
    
    cout << "motorcycle bill : " << motorcycle.PaymentCalculation() << endl;

    cout << "motorcycle: \n" << motorcycle << endl;

    truck.SetExitTime(truck.GetExitTime() + time_difference_seconds);
    
    cout << "truck bill : " << truck.PaymentCalculation() << endl;

    cout << "truck: \n" << truck << endl;

    return 1;
}