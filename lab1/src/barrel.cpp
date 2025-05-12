#include "barrel.hpp"
#include <algorithm>

using namespace std;

Barrel::Barrel(double init_volume, double init_concentration) 
    : volume(init_volume), concentration(init_concentration) {}

void Barrel::pourInto(Barrel &other, double amount) {
    double actual_amount = min(volume, amount);
    if (actual_amount <= 0) return;

    double alcohol = actual_amount * concentration;

    volume -= actual_amount;

    double total_alcohol_other = other.volume * other.concentration + alcohol;
    other.volume += actual_amount;
    other.concentration = (other.volume > 0) ? 
        total_alcohol_other / other.volume : 0;
}


double Barrel::getConcentration() const { return concentration; }
double Barrel::getVolume() const { return volume; }

