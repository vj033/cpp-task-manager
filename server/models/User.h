#pragma once
#include <string>

enum class Role
{
	MANAGER,
	EMPLOYEE
};

class User
{
private:
	int id;
	std::string username;
	std::string password;
	Role role;
public:
	User(int id, const std::string& username, const std::string& password, Role role);

	int getId() const;
	std::string getUserName() const;
	std::string getPassword() const;
	Role getRole() const;
};