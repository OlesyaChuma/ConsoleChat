#include "User.h"
#include <sstream>

User::User(const string& login, const string& password, const string& name)
    : login(login), password(password), name(name) {
}

string User::getLogin() const { return login; }

string User::getName() const { return name; }

bool User::checkPassword(const string& pass) const { return password == pass; }

string User::toString() const {
    return login + ";" + password + ";" + name;
}

User User::fromString(const string& line) {
    stringstream ss(line);
    string login, password, name;
    getline(ss, login, ';');
    getline(ss, password, ';');
    getline(ss, name, ';');
    return User(login, password, name);
}