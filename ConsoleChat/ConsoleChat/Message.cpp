#include "Message.h"
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

Message::Message(const string& sender, const string& receiver, const string& text)
    : sender(sender), receiver(receiver), text(text) {
    // Получаем текущее время системы
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);

    tm localTime{};
    localtime_s(&localTime, &time); 

    stringstream ss;
    ss << put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    timestamp = ss.str();
}

const string Message::getSender() const { return sender; }
const string Message::getReceiver() const { return receiver; }
const string Message::getText() const { return text; }
const string& Message::getTimestamp() const { return timestamp; }

// Представление сообщения в строке
string Message::toString() const {
    return sender + ";" + receiver + ";" + text;
}