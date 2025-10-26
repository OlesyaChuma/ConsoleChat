#include "Message.h"
#include <sstream>

Message::Message(const string& sender, const string& receiver, const string& text)
    : sender(sender), receiver(receiver), text(text) {
}

string Message::getSender() const { return sender; }
string Message::getReceiver() const { return receiver; }
string Message::getText() const { return text; }

string Message::toString() const {
    return sender + ";" + receiver + ";" + text;
}

Message Message::fromString(const string& line) {
    stringstream ss(line);
    string sender, receiver, text;
    getline(ss, sender, ';');
    getline(ss, receiver, ';');
    getline(ss, text, ';');
    return Message(sender, receiver, text);
}
