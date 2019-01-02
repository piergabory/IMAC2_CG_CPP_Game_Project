/**
 * \file Turn.cpp
 */
#include "Turn.hpp"

namespace GameModel {

    void Turn::firstVisit(Player& player) {
        if ((player.status() == Status::TURNING_LEFT && m_direction == TurnDirection::LEFT)
        ||  (player.status() == Status::TURNING_RIGHT && m_direction == TurnDirection::RIGHT)) {
            m_playerTurnAnimation.begin();
            m_cameraTurnAnimation.begin();
        } else {
            player.incrementLife(-10000);
            callDamageAnimations();
        }
    }


    // static redefintions
    std::unique_ptr<GraphicsEngine::Object3D> Turn::s_turnObjectLeftVariant;
    std::unique_ptr<GraphicsEngine::Object3D> Turn::s_turnObjectRightVariant;

    Turn::Turn(TurnDirection direction, std::shared_ptr<GraphicsEngine::Animatable> &playerAnimatable, std::shared_ptr<GraphicsEngine::Animatable> &cameraAnimatable):
    Obstacle(playerAnimatable, cameraAnimatable), // superclass constructor
    m_direction(direction),
    m_playerTurnAnimation(GraphicsEngine::makeTurnAnimation(playerAnimatable, 20, glm::radians((float)direction))),
    m_cameraTurnAnimation(GraphicsEngine::makeTurnAnimation(cameraAnimatable, 20, glm::radians((float)direction)))
    {
        // load objects if not defined
        if (s_turnObjectLeftVariant == nullptr || s_turnObjectRightVariant == nullptr) loadObjects();


        switch (direction) {
            case TurnDirection::LEFT:
                m_entityObject = std::make_shared<GraphicsEngine::Object3D>(*s_turnObjectLeftVariant);
                break;

            case TurnDirection::RIGHT:
                m_entityObject = std::make_shared<GraphicsEngine::Object3D>(*s_turnObjectRightVariant);
                break;
        }
    }

    void Turn::loadObjects() {
        s_turnObjectLeftVariant = std::unique_ptr<GraphicsEngine::Object3D>(Entity::makeObject("assets/models/turn.obj", "assets/textures/cubemap_left_turn.png", "shaders/perspective.vs.glsl", "shaders/flatTexture.fs.glsl"));

        s_turnObjectRightVariant = std::unique_ptr<GraphicsEngine::Object3D>(Entity::makeObject("assets/models/turn.obj", "assets/textures/cubemap_right_turn.png", "shaders/perspective.vs.glsl", "shaders/flatTexture.fs.glsl"));
    }

}
