#include "AuthController.h"

std::string AuthController::handleRegister(const std::string& username,
    const std::string& password,
    const std::string& roleStr)
{
    Role role;

    if (roleStr == "manager")
        role = Role::MANAGER;
    else if (roleStr == "employee")
        role = Role::EMPLOYEE;
    else
        return "ERROR Invalid role";

    bool success = authService.registerUser(username, password, role);

    if (!success)
        return "ERROR Username already exists";

    return "SUCCESS Registered";
}

std::string AuthController::handleLogin(const std::string& username,
    const std::string& password)
{
    User* user = authService.login(username, password);

    if (!user)
        return "ERROR Invalid credentials";

    if (user->getRole() == Role::MANAGER)
        return "SUCCESS Login manager";
    else
        return "SUCCESS Login employee";
}
