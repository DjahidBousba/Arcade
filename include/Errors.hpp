/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** Errors
*/

#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <string>
#include <exception>

class Errors : public std::exception {
    public:
        Errors(std::string const &message);
        ~Errors() throw();

        const char *what() const noexcept override;

    protected:
    private:
        std::string _message;
};

class LibraryError : public Errors {
    public:
        LibraryError(std::string const &message);
        virtual ~LibraryError() {};

    protected:
    private:
        std::string _message;
};

class GameError : public Errors {
    public:
        GameError(std::string const &message);
        virtual ~GameError() {};

    protected:
    private:
        std::string _message;
};

class ParsingError : public Errors {
    public:
        ParsingError(std::string const &message);
        virtual ~ParsingError() {};

    protected:
    private:
        std::string _message;
};

#endif /* !ERRORS_HPP_ */
