#pragma once
#include <vector>
#include <string>
#include "../models/User.h"

class AuthService
{
private:
	std::vector<User> users;
	int nextUserId;

public:
	AuthService();

	bool registerUser(const std::string& username, const std::string& password, Role role);
	User* login(const std::string& username, const std::string& password);
};