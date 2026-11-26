#include "AlerteEcran.h"

#include <iostream>

void AlerteEcran::notifier(const std::string& message)
{
    std::cout << "[Écran] " << message << '\n';
}
