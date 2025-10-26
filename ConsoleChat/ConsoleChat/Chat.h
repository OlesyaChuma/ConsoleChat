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

    const string usersFile = "users.txt";
    const string messagesFile = "messages.txt";

    // Поиск пользователя по логину
    User* findUserByLogin(const string& login);

    void saveUsers();               // Сохраняет всех зарегистрированных пользователей в файл
    void loadUsers();               // Загружает пользователей из файла при запуске программы
    void saveMessages();            // Сохраняет все сообщения в файл
    void loadMessages();            // Загружает историю сообщений из файла

public:
    Chat();                         // Загружает данные при запуске
    ~Chat();                        // Cохранение при завершении
    void start();                   // Основное меню программы
    void registerUser();            // Регистрация нового пользователя
    void loginUser();               // Авторизация
    void logout();                  // Выход из аккаунта
    void sendMessage();             // Отправка сообщения
    void showMessages();            // Просмотр сообщений
};