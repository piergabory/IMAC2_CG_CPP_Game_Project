/**
 * \file Player.cpp
 */
#include "Player.hpp"

namespace GameModel {
    
    void Player::jump() {
        // Player can only jump when standing
        if (m_status != Status::STANDING) return;

        // when player reaches the ground, reset status to Standing
        m_jumpingAnimation.whenDone([=]() -> void { m_status = Status::STANDING; });

        // makes player
        m_status = Status::JUMPING;
        m_jumpingAnimation.begin();

        if (m_life > 0)
            m_score+=20;
    }


    // toggles crouching
    void Player::crouch() {
        // crouching
        if (m_status == Status::STANDING) {
            m_status = Status::CROUCHING;
            m_crouchingAnimation.begin();
        }

        if (m_life > 0)
            m_score+=100;

        // standing
        else if (m_status == Status::CROUCHING){
            m_status = Status::STANDING;
            m_standingAnimation.begin();
        }
    }



    void Player::move(const Direction &direction) {
        if (m_status == Status::TURNING_RIGHT || m_status == Status::TURNING_LEFT) return;

        // check if direction is a valid enumeration
        assert((direction != Direction::LEFT ||  direction != Direction::RIGHT) && "Unknown Position");

        // If in the middle move to the left/right
        // else move to the center or dont move.
        switch (m_position) {
            case Position::LEFT:
                if(direction == Direction::RIGHT) {
                    m_status = Status::TURNING_RIGHT;
                    m_moveToRightLaneAnimation.whenDone([=]()->void{
                        m_status = Status::STANDING;
                    });

                    m_position = Position::MIDDLE;
                    m_moveToRightLaneAnimation.begin();
                }
                break;

            case Position::MIDDLE:
                if(direction == Direction::LEFT) {
                    m_position = Position::LEFT;
                    m_status = Status::TURNING_LEFT;
                    m_moveToLeftLaneAnimation.whenDone([=]()->void{
                        m_status = Status::STANDING;
                    });
                    m_moveToLeftLaneAnimation.begin();
                }
                if(direction == Direction::RIGHT) {
                    m_position = Position::RIGHT;
                    m_status = Status::TURNING_RIGHT;
                    m_moveToRightLaneAnimation.whenDone([=]()->void{
                        m_status = Status::STANDING;
                    });
                    m_moveToRightLaneAnimation.begin();
                }
                break;

            case Position::RIGHT:
                if(direction == Direction::LEFT) {
                    m_position = Position::MIDDLE;
                    m_status = Status::TURNING_LEFT;
                    m_moveToLeftLaneAnimation.whenDone([=]()->void{
                        m_status = Status::STANDING;
                    });
                    m_moveToLeftLaneAnimation.begin();
                }
                break;

            // When position is a non-defined enum.
            default: assert(false && "Unknown Position");
        }
    }


    void Player::resetPosition() {
        m_position = Position::MIDDLE;
        m_resetPosition.begin();
    }


    void Player::incrementLife(int amount) {
        if(m_invicibility == 0)
            m_life += amount;
        if (m_life > 0)
            m_score+=30;
        if(amount < 0)
            m_invicibility = DAMAGE_INVICIBLITY_DURATION;
    };


    void Player::update() {
        if (m_invicibility > 0)
            m_invicibility--;
    }

    void Player::kill() {
        m_life = 0;
    }
    



    // constructor
    Player::Player(std::shared_ptr<GraphicsEngine::Object3D> obj):
    // init model
    m_characterModel(obj),

    // jumping animation
    m_jumpingAnimation(GraphicsEngine::makeBounceAnimation(m_characterModel, JUMP_FRAMETIME, JUMP_HEIGHT)),

    // crouching animations
    m_crouchingAnimation(GraphicsEngine::makeCrouchAnimation(m_characterModel, CROUCH_FRAMETIME, CROUCH_HEIGHT)),
    m_standingAnimation(GraphicsEngine::makeUnCrouchAnimation(m_characterModel, CROUCH_FRAMETIME, CROUCH_HEIGHT)),

    // movement animations
    m_moveToLeftLaneAnimation(GraphicsEngine::makeLinearTranslation(m_characterModel, TRANSLATE_FRAMETIME, glm::vec3(LANE_WIDTH,0.f,0.f))),
    m_moveToRightLaneAnimation(GraphicsEngine::makeLinearTranslation(m_characterModel, TRANSLATE_FRAMETIME, glm::vec3(-LANE_WIDTH,0.f,0.f))),

    m_resetPosition(GraphicsEngine::makeLinearPlace(m_characterModel, 10, glm::vec3(0,0,0)))
    {}

}
