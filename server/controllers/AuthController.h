#pragma once
#include <string>
#include "../services/AuthService.h"

class AuthController
{
private:
    AuthService authService;

public:
    std::string handleRegister(const std::string& username,
        const std::string& password,
        const std::string& roleStr);

    std::string handleLogin(const std::string& username,
        const std::string& password);
};
