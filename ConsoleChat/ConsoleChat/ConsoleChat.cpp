// ConsoleChat.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include "Chat.h"
#include <clocale>          // для setlocale

using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    system("chcp 65001 > nul");         // Устанавливаем кодировку UTF-8 в консоли
    Chat chat;
    chat.start();
    return 0;
}

