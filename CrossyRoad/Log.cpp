#include "Log.h"

Log::Log() : WaterVehicle(), length(0) {}


Log::Log(int x, int y, int length, int velocity) : WaterVehicle(x, y, velocity), length(length) {}

void Log::draw()
{

}