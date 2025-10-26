#pragma once
using namespace std;
#include <vector>
#include <string>
#include "User.h"
#include "Message.h"

// Класс Chat — основной класс управления чатом
// Реализует меню, регистрацию, вход, отправку и просмотр сообщений

class Chat {
private:
    vector<User> users;             // Хранилище пользователей
    vector<Message> messages;       // Хранилище сообщений
    User* currentUser = nullptr;    // Текущий пользователь

    // Поиск пользователя по логину
    User* findUserByLogin(const string& login);

public:
    void start();                   // Основное меню программы
    void registerUser();            // Регистрация нового пользователя
    void loginUser();               // Авторизация
    void logout();                  // Выход из аккаунта
    void sendMessage();             // Отправка сообщения
    void showMessages();            // Просмотр сообщений
};