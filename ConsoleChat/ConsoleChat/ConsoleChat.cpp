// ConsoleChat.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include "Chat.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "");
    Chat chat;
    chat.start();
    return 0;
}

