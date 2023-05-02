#pragma once
#include <string>
#include <iostream>

class User
{
public:
    User(const std::string& name, const std::string& login, const std::string& pass) :
        _name(name),
        _login(login),
        _pass(pass) {}

    friend std::ostream& operator <<(std::ostream& os, const User& user_obj);

private:
    std::string _name;
    std::string _login;
    std::string _pass;
};

std::ostream& operator <<(std::ostream& os, const User& user_obj)
{
    os << user_obj._name;
    os << ';';
    os << user_obj._login;
    os << ';';
    os << user_obj._pass;
    return os;
}