#pragma once

#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

// Класс Message — хранит одно сообщение
// Содержит данные об отправителе, получателе, тексте

class Message {
private:
    string sender;      // Отправитель
    string receiver;    // Получатель ("all" — всем)
    string text;        // Текст сообщения
    string timestamp;   // время отправки

public:
    Message() = default;
    Message(const string& s, const string& r, const string& t);

    // Геттеры
    const string getSender() const;
    const string getReceiver() const;
    const string getText() const;
    const string& getTimestamp() const;

    // Преобразование в строку для записи в файл               
    string toString() const;    
};

