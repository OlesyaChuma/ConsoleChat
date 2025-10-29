#include "Chat.h"
#include <iostream>
#include <limits>   // для очистки потока ввода

using namespace std;

// Поиск пользователя по логину
User* Chat::findUserByLogin(const string& login) {
    const vector<User>& allUsers = users.getAll();
    for (auto& user : allUsers) {
        if (user.getLogin() == login)
            return &const_cast<User&>(user);
    }
    return nullptr;
}

Chat::Chat()
{
}

Chat::~Chat()
{
}

// Регистрация нового пользователя
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

        users.add(User(login, password, name));
        cout << "Регистрация успешна!\n";
    }
    catch (const ChatException& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

// Вход пользователя
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

// Выход из аккаунта
void Chat::logout() {
    if (currentUser) {
        cout << "Вы вышли из аккаунта " << currentUser->getName() << "\n";
        currentUser = nullptr;
    }
}

// Отправка сообщения
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

        if (text.empty())
            throw ChatException("Сообщение не может быть пустым!");

        messages.add(Message(currentUser->getLogin(), receiver, text));
        cout << "Сообщение отправлено!\n";
    }
    catch (const ChatException& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

// Просмотр сообщений
void Chat::showMessages() {
    try {
        if (!currentUser)
            throw ChatException("Вы не вошли в систему!");

        cout << "\n=====================================\n";
        cout << " Сообщения для пользователя: " << currentUser->getName() << "\n";
        cout << "=====================================\n";

        bool hasMessages = false;
        for (const auto& msg : messages.getAll()) {
            // Показываем сообщения, адресованные текущему пользователю или всем
            if (msg.getReceiver() == "all" || msg.getReceiver() == currentUser->getLogin()) {
                cout << msg.toString() << "\n";  // теперь с временем
                hasMessages = true;
            }
        }

        if (!hasMessages) {
            cout << "Нет новых сообщений.\n";
        }

        cout << "-------------------------------------\n";
    }
    catch (const ChatException& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void Chat::start() {
    int choice;
    while (true) {
        try {
            if (!currentUser) {
                cout << "\n=====================================\n";
                cout << " Добро пожаловать в консольный чат\n";
                cout << "=====================================\n";
                cout << "1. Регистрация\n2. Вход\n3. Выход\nВыбор: ";
                if (!(cin >> choice))
                {
                    cin.clear(); // сбрасываем флаг ошибки
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очищаем ввод до конца строки
                    throw ChatException("Некорректный ввод! Введите число от 1 до 3.");
                }

                switch (choice) {
                case 1: registerUser(); break;
                case 2: loginUser(); break;
                case 3: return;
                default: cout << "Неверный выбор!\n";
                }
            }
            else {
                cout << "\n=====================================\n";
                cout << " Меню пользователя: " << currentUser->getName() << "\n";
                cout << "=====================================\n";
                cout << "1. Отправить сообщение\n2. Просмотреть сообщения\n3. Выйти из аккаунта\nВыбор: ";
                if (!(cin >> choice))
                {
                    cin.clear(); // сбрасываем флаг ошибки
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очищаем ввод до конца строки
                    throw ChatException("Некорректный ввод! Введите число от 1 до 3.");
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
