/**
 * \file CommonStructs.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */
#ifndef CommonStructs_hpp
#define CommonStructs_hpp
#pragma once

#include <string>
#include <iostream>
#include <glm/glm.hpp>

 namespace GraphicsEngine {
    
     /**
      * VERTEX STRUCT
      * holds vertex data for 3D meshes.
      */
     struct Vertex3D {
         // properties
         glm::vec3 m_position;
         glm::vec3 m_normal;
         glm::vec2 m_textureCoordinates;
         
         // constructor
         Vertex3D(glm::vec3 position, glm::vec3 normal, glm::vec2 texture):
            m_position(position), m_normal(normal), m_textureCoordinates(texture) {}

         Vertex3D(const Vertex3D& copy) = default;
     };


     /**
      * VERTEX STRUCT
      * holds vertex data for 2D meshes.
      */
     struct Vertex2D {
         // properties
         glm::vec2 m_position;
         glm::vec2 m_textureCoordinates;

         // constructor
         Vertex2D(glm::vec2 position, glm::vec2 texture):
         m_position(position), m_textureCoordinates(texture) {}
     };


     /**
      * LocalFilePath
      * Subclass to std::string allowing easy creation of absolutes paths relatives to the executable
      */
     class LocalFilePath : public std::string {
     private:
         static std::string s_absolutePathToExecutable;

     public:
         static void setLocation(std::string executablePath);

         LocalFilePath(std::string localPath) : std::string(s_absolutePathToExecutable + localPath) {
             assert(!s_absolutePathToExecutable.empty());
             std::cout << c_str() << std::endl;
         }
     };
 }

 #endif /* CommonStructs_hpp */
