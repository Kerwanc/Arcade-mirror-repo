/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Error exception
*/

#pragma once
    #include <exception>
    #include <string>

	constexpr int RETURN_SUCCESS = 0;
	constexpr int RETURN_ERROR = 84;

class Error : public std::exception {
    public:
        explicit Error(const std::string &message) : msg(message)
        {}
        const char *what() const noexcept override
        {
            return msg.c_str();
        }
    private:
        std::string msg;
};

