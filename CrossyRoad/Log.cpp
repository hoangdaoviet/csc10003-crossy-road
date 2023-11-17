#include "Log.h"

Log::Log() : Vehicle(), length(0) {}


Log::Log(int x, int y, int length, int velocity) : Vehicle(x, y, velocity), length(length) {}

void Log::draw()
{

}

std::string Log::getNameOfObject()
{
    return "Log";
}
