/**
 * \file Animation.cpp
 */

#include "Animation.hpp"

namespace GraphicsEngine {

    // static animation container
    std::vector<Animation*> Animation::s_activeAnimations;

    // static
    // calls nxt frame on each animation
    void Animation::updateAnimations() {
        size_t i = 0;
        while(i < s_activeAnimations.size()) {
            if (s_activeAnimations[i]->animateNextFrame()) i++;
        }
    };



    bool Animation::animateNextFrame() {
        if (m_currentFrame == 0) {
            cancel();
            return false;
        }
        
        m_currentFrame--;
        m_interpolationFunction(*m_pObjectToMove, m_targetPositon, 1.f / m_duration, 1.f - m_currentFrame / (float) m_duration);

        return true;
    }



    void Animation::begin() {
        m_currentFrame = m_duration;
        s_activeAnimations.push_back(this);
    }



    void Animation::cancel() {
        if (m_callback) m_callback();
        m_currentFrame = 0;
        for (size_t i = 0; i < s_activeAnimations.size(); i++) {
            if (s_activeAnimations[i] == this)
                s_activeAnimations.erase(s_activeAnimations.begin() + i);
        }
    }


    // constructor
    Animation::Animation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const glm::vec3 &position, const std::function<void(Animatable&,const glm::vec3&, const float, const float)> &interpolation):
    m_pObjectToMove(object),
    m_duration(duration),
    m_targetPositon(position),
    m_interpolationFunction(interpolation),
    m_callback([](void) -> void {})
    { assert(m_interpolationFunction); }




    // factories

    Animation makeLinearPlace(const std::shared_ptr<Animatable> &object, const unsigned int duration, const glm::vec3 &newPosition) {
        return Animation(object, duration, newPosition, [](Animatable& object, const glm::vec3 &newPosition, const float step, const float progress) -> void {
            object.place(object.position() * ( 1 - progress) + newPosition * progress);
        });
    }



    Animation makeLinearTranslation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const glm::vec3 &translation) {
        return Animation(object, duration, translation, [](Animatable& object, const glm::vec3 &translation, const float step, const float progress) -> void {
            object.translate(translation * step);
        });
    }



    Animation makeBounceAnimation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const float height) {
        return Animation(object, duration, glm::vec3(0,height,0), [](Animatable &object, const glm::vec3 &position, const float step, const float progress) {
            const float heightPosition = (1 - pow(-2 * progress + 1, 2)) * position.y;
            object.place(glm::vec3(object.position().x, heightPosition, object.position().z));
        });
    }



    Animation makeCrouchAnimation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const float toHeight) {
        return Animation(object, duration, glm::vec3(toHeight), [](Animatable &object, const glm::vec3 &position, const float step, const float progress) {
            object.scale(glm::vec3(1, 1 - 0.03,1));
        });
    }



    Animation makeUnCrouchAnimation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const float fromHeight) {
        return Animation(object, duration, glm::vec3(fromHeight), [](Animatable &object, const glm::vec3 &position, const float step, const float progress) {
            object.scale(glm::vec3(1, 1 + 0.03,1));
        });
    }



    Animation makeTurnAnimation(const std::shared_ptr<Animatable> &camera, unsigned int duration, const float angle) {
        return Animation(camera, duration, glm::vec3(angle), [](Animatable &camera, const glm::vec3 &angle, const float step, const float progress) {
            camera.rotate(angle.x * step, glm::vec3(0.f,1.f,0.f));
        });
    }


    Animation makeDeathFallAnimation(const std::shared_ptr<Animatable> &object, unsigned int duration) {
        return Animation(object, duration, glm::vec3(), [](Animatable &object, const glm::vec3 &unused, const float step, const float progress) {
            const float FALL_DISTANCE = 32.0;
            const float START_FALLING = 0.3;

            glm::vec3 movement;
            movement = (progress < START_FALLING)? glm::vec3(0,0,step) : glm::vec3(0, -step * 2 * (progress - START_FALLING), step);
            object.translate(FALL_DISTANCE * movement);
        });
    }


    Animation makeDamageBlinkAnimation(const std::shared_ptr<Animatable> &object, unsigned int duration) {
        return Animation(object, duration, glm::vec3(), [](Animatable &object, const glm::vec3 &unused, const float step, const float progress) {
            const glm::vec3 HIDE_TRANSLATION(1000);
            unsigned int frameIndex = round(progress / step);
            if (frameIndex % 3 == 0) {
                const float direction = (frameIndex % 6 == 0) ? 1.f : -1.f;
                object.globalTranslate(direction * HIDE_TRANSLATION);
            }
        });
     }
}

