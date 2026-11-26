#include "NotificationDistante.h"

#include <iostream>

void NotificationDistante::notifier(const std::string& message)
{
    std::cout << "[Notification distante] " << message << '\n';
}
