/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** main.cpp
*/

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

void display_h()
{
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\t ./arcade <library>" << std::endl;
    exit(0);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "usage ./arcade <library>" << std::endl;
        exit (1);
    } else if (ac == 2 && strcmp(av[1], "-h") == 0) {
        display_h();
    }
    try {
        Core *core = new Core(av[1]);
        core->LoadLibs();
    }
    catch (std::exception const &exc) {
        std::cerr << exc.what() << std::endl;
        return 84;
    }
    return (0);
}