/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-luigi.gomes
** File description:
** DLLoader
*/

#ifndef DLLOADERGRAPHIC_HPP_
    #define DLLOADERGRAPHIC_HPP_

#include <iostream>
#include <dlfcn.h>
#include "Error.hpp"

template <typename T>

class DLLoaderGraphic {
    public:
        DLLoaderGraphic(const std::string &path) {
            handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!handle) {
                error = dlerror();
                throw Error(error);
            }
        }
        ~DLLoaderGraphic() {
            dlclose(handle);
        }
        T *getInstance() {
            using CreateFunc = T *(*)(); // équivaut à faire T *(*fonction)() pour utiliser dlsym
            CreateFunc library = (CreateFunc)dlsym(handle, "makeGraphic");
            return library();
        }
    private:
        void *handle;
        std::string error;
};

#endif /* !DLLOADERGRAPHIC_HPP_ */
