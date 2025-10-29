#pragma once
#include <string>
using namespace std;

// Класс User представляет пользователя чата
// Содержит логин, пароль и отображаемое имя

class User {
private:
    string login;       // Уникальный логин
    string password;    // Пароль
    string name;        // Имя пользователя

public:
    User(const string& login, const string& password, const string& name);
    string getLogin() const;
    string getName() const;
    // Проверка правильности пароля
    bool checkPassword(const string& pass) const;
    // Преобразование в строку для записи в файл
    string toString() const;  
    // Создание объекта из строки файла
    static User fromString(const string& line); 
};
