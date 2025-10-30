#pragma once

using namespace std;

#include <string>
#include "User.h"
#include "Message.h"
#include <stdexcept>
#include "ChatException.h"
#include "Storage.h"

// Класс Chat управляет пользователями и обменом сообщениями
// Реализует меню, регистрацию, вход, отправку и просмотр сообщений

class Chat {
private:
    Storage<User> users;                // Хранилище пользователей
    Storage<Message> messages;          // Хранилище сообщений
    User* currentUser = nullptr;        // Текущий пользователь

    // Поиск пользователя по логину
    User* findUserByLogin(const string& login);

public:
    Chat();
    ~Chat();

    void start();                   // Основное меню программы
    void registerUser();            // Регистрация нового пользователя
    void loginUser();               // Авторизация
    void logout();                  // Выход из аккаунта
    void sendMessage();             // Отправка сообщения
    void showMessages();            // Просмотр сообщений
};