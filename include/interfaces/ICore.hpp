/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-pierre.pruvost
** File description:
** ICore.hpp
*/

#ifndef ICORE_HPP_
    #define ICORE_HPP_

    #include <string>

class ICore {

    public:
        virtual ~ICore() = default;
        virtual int run(std::string graphPath) = 0;
        virtual int load(std::string gamePath, std::string graphPath) = 0;

    private:

};

#endif
