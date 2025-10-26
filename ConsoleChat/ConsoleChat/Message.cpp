#include "Message.h"

Message::Message(const string& sender, const string& receiver, const string& text)
    : sender(sender), receiver(receiver), text(text) {
}

string Message::getSender() const { return sender; }
string Message::getReceiver() const { return receiver; }
string Message::getText() const { return text; }
