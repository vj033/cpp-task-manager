#include "User.h"

User::User(int id,
    const std::string& username,
    const std::string& password,
    Role role)
    : id(id), username(username), password(password), role(role)
{
}

int User::getId() const
{
    return id;
}

std::string User::getUserName() const
{
    return username;
}

std::string User::getPassword() const
{
    return password;
}

Role User::getRole() const
{
    return role;
}
