#include "AuthService.h"

AuthService::AuthService()
{
    nextUserId = 1;
}

bool AuthService::registerUser(const std::string& username,
    const std::string& password,
    Role role)
{
    // check duplicate username
    for (auto& user : users)
    {
        if (user.getUserName() == username)
            return false;
    }

    users.emplace_back(nextUserId++, username, password, role);
    return true;
}

User* AuthService::login(const std::string& username,
    const std::string& password)
{
    for (auto& user : users)
    {
        if (user.getUserName() == username &&
            user.getPassword() == password)
        {
            return &user;
        }
    }
    return nullptr;
}
