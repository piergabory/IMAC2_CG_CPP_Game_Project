/**
 * \file Object2D.cpp
 */


#include "Object2D.hpp"

namespace GraphicsEngine {

    std::shared_ptr<ShaderProgram> Object2D::s_2dShader;


    std::shared_ptr<Mesh2D> Object2D::createBoundingBox(const glm::vec2 &position, const glm::vec2 &size) {
        std::vector<Vertex2D> vertices;

        // top left corner
        vertices.push_back(Vertex2D(position, glm::vec2(0,0)));

        // top right corner
        vertices.push_back(Vertex2D(position + glm::vec2(size.x, 0), glm::vec2(1,0)));

        // bottom right corner
        vertices.push_back(Vertex2D(position + size, glm::vec2(1,1)));

        // bottom left corner
        vertices.push_back(Vertex2D(position + glm::vec2(0, size.y), glm::vec2(0,1)));


        return std::make_shared<Mesh2D>(vertices, GL_TRIANGLE_FAN);
    }


    std::shared_ptr<Material> Object2D::createMaterial(LocalFilePath textureImagePath) {
        // check if shader is defined
        assert(s_2dShader->identifier() != 0);

        // create texture
        std::shared_ptr<Texture> texture = std::make_shared<Texture>(textureImagePath);

        return std::make_shared<Material>(s_2dShader, texture);
    }


    std::shared_ptr<Material> Object2D::createMaterial(std::shared_ptr<Texture> &texture) {
        assert(s_2dShader->identifier() != 0);
        return std::make_shared<Material>(s_2dShader, texture);
    }
    
    void Object2D::texture(std::shared_ptr<Texture> newtex){
        m_material = createMaterial(newtex);
    };


    void Object2D::initialize2DShaderProgram(LocalFilePath vertexShaderPath, LocalFilePath fragementShaderPath) {
        s_2dShader = std::make_shared<ShaderProgram>(vertexShaderPath, fragementShaderPath);
    }
}
