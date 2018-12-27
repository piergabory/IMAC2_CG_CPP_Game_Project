#ifndef Turn_hpp
#define Turn_hpp

#include "Entity.hpp"

enum class TurnDirection : int {
    LEFT = -90, RIGHT = 90
};

class Turn : public Entity {
private:
    static std::unique_ptr<GraphicsEngine::Object3D> s_turnObjectLeftVariant;
    static std::unique_ptr<GraphicsEngine::Object3D> s_turnObjectRightVariant;

    const TurnDirection m_direction;

public:
    void action() override {}
    static void loadObjects();

    Turn(TurnDirection direction): Entity(), m_direction(direction) {
        if (s_turnObjectLeftVariant == nullptr || s_turnObjectRightVariant == nullptr) loadObjects();

        switch (m_direction) {
            case TurnDirection::LEFT:
                m_entityObject = std::make_shared<GraphicsEngine::Object3D>(*s_turnObjectLeftVariant);
                break;

            case TurnDirection::RIGHT:
                m_entityObject = std::make_shared<GraphicsEngine::Object3D>(*s_turnObjectRightVariant);
                break;

            default: assert(false && "Bad turn direction");
        }
    }

    ~Turn() override {};
};

#endif /* Turn_hpp */
