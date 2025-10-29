#pragma once

#include <stdexcept>
#include <string>

/// ����� ChatException � ����������� ��� ������ ��� ����.
/// ��������� ������� ���������� � ��������� ����������� ������������.
class ChatException : public std::runtime_error {
public:
    explicit ChatException(const std::string& message)
        : std::runtime_error(message) {}
};
