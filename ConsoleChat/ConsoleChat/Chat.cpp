#include "Chat.h"
#include <iostream>

User* Chat::findUserByLogin(const std::string& login) {
    for (auto& user : users) {
        if (user.getLogin() == login)
            return &user;
    }
    return nullptr;
}

void Chat::registerUser() {
    std::string login, password, name;
    std::cout << "Введите логин: ";
    std::cin >> login;

    if (findUserByLogin(login)) {
        std::cout << "Пользователь с таким логином уже существует!\n";
        return;
    }

    std::cout << "Введите пароль: ";
    std::cin >> password;
    std::cout << "Введите имя: ";
    std::cin >> name;

    users.emplace_back(login, password, name);
    std::cout << "Регистрация успешна!\n";
}

void Chat::loginUser() {
    std::string login, password;
    std::cout << "Логин: ";
    std::cin >> login;
    std::cout << "Пароль: ";
    std::cin >> password;

    User* user = findUserByLogin(login);
    if (!user) {
        std::cout << "Пользователь не найден!\n";
        return;
    }

    if (!user->checkPassword(password)) {
        std::cout << "Неверный пароль!\n";
        return;
    }

    currentUser = user;
    std::cout << "Добро пожаловать, " << currentUser->getName() << "!\n";
}

void Chat::logout() {
    if (currentUser) {
        std::cout << "Вы вышли из аккаунта " << currentUser->getName() << "\n";
        currentUser = nullptr;
    }
}

void Chat::sendMessage() {
    if (!currentUser) {
        std::cout << "Сначала войдите в систему!\n";
        return;
    }

    std::string receiver, text;
    std::cout << "Введите логин получателя (или 'all'): ";
    std::cin >> receiver;
    std::cout << "Введите сообщение: ";
    std::cin.ignore();
    std::getline(std::cin, text);

    messages.emplace_back(currentUser->getLogin(), receiver, text);
    std::cout << "Сообщение отправлено!\n";
}

void Chat::showMessages() {
    if (!currentUser) {
        std::cout << "Сначала войдите в систему!\n";
        return;
    }

    std::cout << "\nВаши сообщения:\n";
    for (const auto& msg : messages) {
        if (msg.getReceiver() == "all" || msg.getReceiver() == currentUser->getLogin()) {
            std::cout << "[" << msg.getSender() << "] -> "
                << (msg.getReceiver() == "all" ? "всем" : msg.getReceiver())
                << ": " << msg.getText() << "\n";
        }
    }
}

void Chat::start() {
    int choice;
    while (true) {
        if (!currentUser) {
            std::cout << "\n1. Регистрация\n2. Вход\n3. Выход\nВыбор: ";
            std::cin >> choice;
            switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: return;
            default: std::cout << "Неверный выбор!\n";
            }
        }
        else {
            std::cout << "\n1. Отправить сообщение\n2. Просмотреть сообщения\n3. Выйти из аккаунта\nВыбор: ";
            std::cin >> choice;
            switch (choice) {
            case 1: sendMessage(); break;
            case 2: showMessages(); break;
            case 3: logout(); break;
            default: std::cout << "Неверный выбор!\n";
            }
        }
    }
}
