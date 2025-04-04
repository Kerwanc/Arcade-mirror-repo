/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-luigi.gomes
** File description:
** main
*/

#include <iostream>
#include "src/core/ArcadeCore.hpp"
#include "src/error/Error.hpp"

int main(int argc, char const *argv[])
{
    try {
        arcade::ArcadeCore core(argc, argv);
    } catch (const Error &error) {
        std::cerr << error.what() << std::endl;
        return RETURN_ERROR;
    }
    return RETURN_SUCCESS;
}
