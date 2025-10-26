#pragma once
#include <string>
using namespace std;

// Класс Message — хранит одно сообщение
// Содержит данные об отправителе, получателе, тексте

class Message {
private:
    string sender;      // Отправитель
    string receiver;    // Получатель ("all" — всем)
    string text;        // Текст сообщения
public:
    Message(const string& sender, const string& receiver, const string& text);
    // Геттеры
    string getSender() const;
    string getReceiver() const;
    string getText() const;
};

