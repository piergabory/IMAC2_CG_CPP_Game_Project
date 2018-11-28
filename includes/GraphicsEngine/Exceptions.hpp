//
//  Exceptions.hpp
//  Project_Pasteque
//
//  Created by Pierre Gabory on 16/11/2018.
//

#ifndef Exceptions_h
#define Exceptions_h

#include <exception>
#include <iostream>
#include <string>

#include "Frameworks.hpp"

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
        
        InitialisationException() {}
        
        ~InitialisationException() throw() {}
    };
}

#endif /* Exceptions_h */