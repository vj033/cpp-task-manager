#include <iostream>
#include "controllers/AuthController.h"

int main()
{
    AuthController auth;

    std::cout << auth.handleRegister("alice", "123", "manager") << std::endl;
    std::cout << auth.handleRegister("bob", "456", "employee") << std::endl;

    std::cout << auth.handleLogin("alice", "123") << std::endl;
    std::cout << auth.handleLogin("bob", "456") << std::endl;
    std::cout << auth.handleLogin("bob", "wrong") << std::endl;

    return 0;
}
