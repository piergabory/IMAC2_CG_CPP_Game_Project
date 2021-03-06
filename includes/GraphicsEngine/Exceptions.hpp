
#ifndef Exceptions_h
#define Exceptions_h
#pragma once

#include <exception>
#include <iostream>
#include <string>

#include "Frameworks.hpp"

/// \todo doc
namespace GraphicsEngine
{
    
    class InitialisationException : public std::exception
    {
        
    private:
        std::string m_message;
        std::string m_info;
        
    public:
        
        const char* what() const throw() override;
        
        InitialisationException(const char* message, const char* info);
        
        InitialisationException(const char* message, GLuint identifier);
        
        InitialisationException() = default;
        
        ~InitialisationException() throw() {}
    };
}

#endif /* Exceptions_h */
