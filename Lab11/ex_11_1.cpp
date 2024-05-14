#include <iostream>
using namespace std;

/*
 * Exercise 1. User defined literals
Define user literals for time (ms, s, h) and distance (m, km, cm) they should convert literal to
seconds and meters correspondingly.
 */


/**
    Computes velocity in meters per seconds.
    @param distance  distance in meters
    @param time      time in seconds
    @return velocity in meters per seconds.
*/



constexpr long double operator"" _ms(long double time) {
    return time / 1000; // convert milliseconds to seconds
}

constexpr long double operator"" _s(long double time) {
    return time; // seconds
}

constexpr long double operator"" _h(long double time) {
    return time * 3600; // convert hours to seconds
}

constexpr long double operator"" _m(long double distance) {
    return distance; // meters
}

constexpr long double operator"" _km(long double distance) {
    return distance * 1000; // convert kilometers to meters
}

constexpr long double operator"" _cm(long double distance) {
    return distance / 100; // convert centimeters to meters
}

constexpr long double operator"" _ms(unsigned long long time) {
    return time / 1000.0; // convert milliseconds to seconds
}

constexpr long double operator"" _s(unsigned long long time) {
    return time; // seconds
}

constexpr long double operator"" _h(unsigned long long time) {
    return time * 3600.0; // convert hours to seconds
}

constexpr long double operator"" _m(unsigned long long distance) {
    return distance; // meters
}

constexpr long double operator"" _km(unsigned long long distance) {
    return distance * 1000.0; // convert kilometers to meters
}

constexpr long double operator"" _cm(unsigned long long distance) {
    return distance / 100.0; // convert centimeters to meters
}


double computeVelocity(double distance, double time){
    return distance/time;
}

int main(){
    cout << computeVelocity(100_m, 5_s) << endl;     //20
    cout << computeVelocity(360_km, 2.0_h) << endl;  //50
    cout << computeVelocity(3.6_km, 0.02_h) << endl; //50
    cout << computeVelocity(250_cm, 2.5_ms) << endl; //1000
    return 0;
}