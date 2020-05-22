/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** Errors
*/

#include "Errors.hpp"

Errors::Errors(std::string const &message)
{
    this->_message = message;
}

Errors::~Errors()
{

}

const char *Errors::what() const noexcept
{
    return (this->_message.data());
}

LibraryError::LibraryError(std::string const &message) : Errors(message)
{
}

GameError::GameError(std::string const &message) : Errors(message)
{
}

ParsingError::ParsingError(std::string const &message) : Errors(message)
{
}
