#include "Message.h"
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

Message::Message(const string& sender, const string& receiver, const string& text)
    : sender(sender), receiver(receiver), text(text) {
    // Получаем текущее время системы
    auto now = chrono::system_clock::now();
    // Преобразуем время в формат time_t (количество секунд с 1 января 1970 г.)
    time_t time = chrono::system_clock::to_time_t(now);

    // Создаём структуру tm для хранения локального времени (часы, минуты, секунды и т.д.)
    tm localTime{};
    // Безопасная функция для преобразования времени в локное (в отличие от небезопасной localtime)
    localtime_s(&localTime, &time); 

    // Создаём поток для форматирования даты и времени
    stringstream ss;
    // Преобразуем структуру времени в удобный для чтения вид: "2025-10-30 18:42:55"
    ss << put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    // Сохраняем готовую строку в переменную timestamp
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