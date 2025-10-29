#pragma once

#include <stdexcept>
#include <string>

/// Класс ChatException — собственный тип ошибок для чата.
/// Позволяет бросать исключения с понятными сообщениями пользователю.
class ChatException : public std::runtime_error {
public:
    explicit ChatException(const std::string& message)
        : std::runtime_error(message) {}
};
