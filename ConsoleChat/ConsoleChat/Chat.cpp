#include "Chat.h"
#include <iostream>
#include <fstream>
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
    ofstream out(usersFile);
    for (const auto& user : users)
        out << user.toString() << "\n";
}

void Chat::loadUsers()
{
    ifstream in(usersFile);
    if (!in.is_open()) return;
    string line;
    while (getline(in, line)) {
        if (!line.empty())
            users.push_back(User::fromString(line));
    }
}

void Chat::saveMessages()
{
    ofstream out(messagesFile);
    for (const auto& msg : messages)
        out << msg.toString() << "\n";
}

void Chat::loadMessages()
{
    ifstream in(messagesFile);
    if (!in.is_open()) return;
    string line;
    while (getline(in, line)) {
        if (!line.empty())
            messages.push_back(Message::fromString(line));
    }
}

void Chat::registerUser() {
    string login, password, name;
    cout << "Введите логин: ";
    cin >> login;

    if (findUserByLogin(login)) {
        cout << "Пользователь с таким логином уже существует!\n";
        return;
    }

    cout << "Введите пароль: ";
    cin >> password;
    cout << "Введите имя: ";
    cin >> name;

    users.emplace_back(login, password, name);
    cout << "Регистрация успешна!\n";
}

void Chat::loginUser() {
    string login, password;
    cout << "Логин: ";
    cin >> login;
    cout << "Пароль: ";
    cin >> password;

    User* user = findUserByLogin(login);
    if (!user) {
        cout << "Пользователь не найден!\n";
        return;
    }

    if (!user->checkPassword(password)) {
        cout << "Неверный пароль!\n";
        return;
    }

    currentUser = user;
    cout << "Добро пожаловать, " << currentUser->getName() << "!\n";
}

void Chat::logout() {
    if (currentUser) {
        cout << "Вы вышли из аккаунта " << currentUser->getName() << "\n";
        currentUser = nullptr;
    }
}

void Chat::sendMessage() {
    if (!currentUser) {
        cout << "Сначала войдите в систему!\n";
        return;
    }

    string receiver, text;
    cout << "Введите логин получателя (или 'all'): ";
    cin >> receiver;
    cout << "Введите сообщение: ";
    cin.ignore();
    getline(cin, text);

    messages.emplace_back(currentUser->getLogin(), receiver, text);
    cout << "Сообщение отправлено!\n";
}

void Chat::showMessages() {
    if (!currentUser) {
        cout << "Сначала войдите в систему!\n";
        return;
    }

    cout << "\nВаши сообщения:\n";
    for (const auto& msg : messages) {
        if (msg.getReceiver() == "all" || msg.getReceiver() == currentUser->getLogin()) {
            cout << "[" << msg.getSender() << "] -> "
                << (msg.getReceiver() == "all" ? "всем" : msg.getReceiver())
                << ": " << msg.getText() << "\n";
        }
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
        if (!currentUser) {
            cout << "\n1. Регистрация\n2. Вход\n3. Выход\nВыбор: ";
            cin >> choice;
            switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: return;
            default: cout << "Неверный выбор!\n";
            }
        }
        else {
            cout << "\n1. Отправить сообщение\n2. Просмотреть сообщения\n3. Выйти из аккаунта\nВыбор: ";
            cin >> choice;
            switch (choice) {
            case 1: sendMessage(); break;
            case 2: showMessages(); break;
            case 3: logout(); break;
            default: cout << "Неверный выбор!\n";
            }
        }
    }
}
