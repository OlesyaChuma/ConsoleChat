#include "Chat.h"
#include <iostream>
#include <fstream>
#include <limits>   // для очистки потока ввода
using namespace std;

User* Chat::findUserByLogin(const string& login) {
    for (auto& user : users) {
        if (user.getLogin() == login)
            return &user;
    }
    return nullptr;
}

void Chat::saveUsers()
{
    try
    {
        ofstream out(usersFile);
        if (!out.is_open()) throw ChatException("Ошибка при сохранении файла пользователей.");
        for (const auto& user : users)
            out << user.toString() << "\n";
    }
    catch (const exception& e)
    {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void Chat::loadUsers()
{
    try {
        ifstream in(usersFile);
        if (!in.is_open()) return;
        string line;
        while (getline(in, line)) {
            if (!line.empty())
                users.push_back(User::fromString(line));
        }
    }
    catch (...) {
        cerr << "Ошибка при чтении файла пользователей. Возможно, он повреждён.\n";
    }
}

void Chat::saveMessages()
{
    try {
        ofstream out(messagesFile);
        if (!out.is_open()) throw ChatException("Ошибка при сохранении файла сообщений.");
        for (const auto& msg : messages)
            out << msg.toString() << "\n";
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void Chat::loadMessages()
{
    try {
        ifstream in(messagesFile);
        if (!in.is_open()) return;
        string line;
        while (getline(in, line)) {
            if (!line.empty())
                messages.push_back(Message::fromString(line));
        }
    }
    catch (...) {
        cerr << "Ошибка при чтении файла сообщений.\n";
    }
}

void Chat::registerUser() {
    try {
        string login, password, name;
        cout << "Введите логин: ";
        cin >> login;

        if (findUserByLogin(login))
            throw ChatException("Пользователь с таким логином уже существует!");

        cout << "Введите пароль: ";
        cin >> password;
        cout << "Введите имя: ";
        cin >> name;

        users.emplace_back(login, password, name);
        saveUsers();
        cout << "Регистрация успешна!\n";
    }
    catch (const ChatException& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void Chat::loginUser() {
    try {
        string login, password;
        cout << "Логин: ";
        cin >> login;
        cout << "Пароль: ";
        cin >> password;

        User* user = findUserByLogin(login);
        if (!user)
            throw ChatException("Пользователь не найден!");

        if (!user->checkPassword(password))
            throw ChatException("Неверный пароль!");

        currentUser = user;
        cout << "Добро пожаловать, " << currentUser->getName() << "!\n";
    }
    catch (const ChatException& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void Chat::logout() {
    if (currentUser) {
        cout << "Вы вышли из аккаунта " << currentUser->getName() << "\n";
        currentUser = nullptr;
    }
}

void Chat::sendMessage() {
    try {
        if (!currentUser)
            throw ChatException("Вы не вошли в систему!");

        string receiver, text;
        cout << "Введите логин получателя (или 'all'): ";
        cin >> receiver;
        cout << "Введите сообщение: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, text);

        messages.emplace_back(currentUser->getLogin(), receiver, text);
        saveMessages();
        cout << "Сообщение отправлено!\n";
    }
    catch (const ChatException& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void Chat::showMessages() {
    try {
        if (!currentUser)
            throw ChatException("Вы не вошли в систему!");

        cout << "\nВаши сообщения:\n";
        for (const auto& msg : messages) {
            if (msg.getReceiver() == "all" || msg.getReceiver() == currentUser->getLogin()) {
                cout << "[" << msg.getSender() << "] -> "
                    << (msg.getReceiver() == "all" ? "всем" : msg.getReceiver())
                    << ": " << msg.getText() << "\n";
            }
        }
    }
    catch (const ChatException& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }

}

Chat::Chat()
{
    loadUsers();
    loadMessages();
}

Chat::~Chat()
{
    saveUsers();
    saveMessages();
}

void Chat::start() {
    int choice;
    while (true) {
        try {
            if (!currentUser) {
                cout << "\n1. Регистрация\n2. Вход\n3. Выход\nВыбор: ";
                if (!(cin >> choice)) {
                    throw ChatException("Некорректный ввод! Введите число.");
                }
                switch (choice) {
                case 1: registerUser(); break;
                case 2: loginUser(); break;
                case 3: return;
                default: cout << "Неверный выбор!\n";
                }
            }
            else {
                cout << "\n1. Отправить сообщение\n2. Просмотреть сообщения\n3. Выйти из аккаунта\nВыбор: ";
                if (!(cin >> choice)) {
                    throw ChatException("Некорректный ввод! Введите число.");
                }
                switch (choice) {
                case 1: sendMessage(); break;
                case 2: showMessages(); break;
                case 3: logout(); break;
                default: cout << "Неверный выбор!\n";
                }
            }

            // Очистка ошибок ввода, если были
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        catch (const ChatException& e) {
            cerr << "Ошибка: " << e.what() << "\n";
        }
    }
}
