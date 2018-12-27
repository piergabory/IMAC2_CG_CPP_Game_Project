#ifndef Entity_hpp
#define Entity_hpp

#include <memory>

#include "Object3D.hpp"
#include "ImportedMesh.hpp"

namespace GameModel {
    
    class Entity {
    private:

        static std::unique_ptr<GraphicsEngine::Object3D> s_entityObject;

        std::shared_ptr<GraphicsEngine::Object3D> m_entityObject;

        // todo check for use?
        const glm::vec3 position() const { return m_entityObject->position(); }

        static GraphicsEngine::Object3D* makeObject(const char* meshPath, const char* texturePath, const char* vertexShaderProgram, const char* fragmentShaderProgram);

    public:

        inline const std::shared_ptr<GraphicsEngine::Object3D>& object() const { return m_entityObject; };

        virtual void action() {};

        static void loadObject();

        Entity(): m_entityObject(std::make_shared<GraphicsEngine::Object3D>(*s_entityObject)) {}

        virtual ~Entity() {}
    };
}
#endif /* Entity_hpp */