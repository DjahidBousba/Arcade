/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <dlfcn.h>
#include <vector>
#include <algorithm>
#include "Core.hpp"
#include "Errors.hpp"
#include <chrono>
#include <thread>

template <typename T>
class DLLoader {
    public:
        DLLoader(const std::string &libPath) {
            _handle = dlopen(libPath.c_str(), RTLD_LAZY);
            if (!_handle) {
                std::cerr << "dlopen() error : " << dlerror() << std::endl;
                exit(84);
            }
        };
        ~DLLoader();

        T *getInstance(const std::string &entryPoint) {
            T *(*ret)(void) = nullptr;
            *(void **) (&ret) = dlsym(_handle, entryPoint.c_str());
            return (ret());
        };

        void closeLib() {
            if (dlclose(_handle) != 0) {
                std::cerr << "dlclose() error : " << dlerror() << std::endl;
                exit(84);
            }
        }

    protected:
    private:
        void *_handle;
};

#endif /* !DLLOADER_HPP_ */
