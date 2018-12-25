#include "Animation.hpp"

namespace GraphicsEngine {
    std::vector<Animation*> Animation::s_activeAnimations;
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
        
        std::shared_ptr<GraphicsEngine::Object3D> objectToMove = m_pObjectToMove.lock();
        m_interpolationFunction(objectToMove, m_targetPositon, 1.f / m_duration, 1.f - m_currentFrame /(float) m_duration);

        return true;
    }


    Animation makeLinearTranslation(const std::shared_ptr<Object3D> &object, const uint duration, const glm::vec3 &position) {
        return Animation(object, duration, position, [](const std::shared_ptr<Object3D> &object,const glm::vec3 &position, const float step, const float progress) -> void {
            glm::vec3 newPosition = (position - object->position()) * step;
            object->translate(newPosition);
        });
    }


    Animation makeBounceAnimation(const std::shared_ptr<Object3D> &object, const uint duration, const float height) {
        return Animation(object, duration, glm::vec3(0,height,0), [](const std::shared_ptr<Object3D> &object, const glm::vec3 &position, const float step, const float progress) {
            const float heightPosition = (1 - pow(-2 * progress + 1, 2)) * position.y;
            object->place(glm::vec3(object->position().x, heightPosition, object->position().z));
        });
    }


    Animation makeCrouchAnimation(const std::shared_ptr<Object3D> &object, const uint duration, const float toHeight) {
        return Animation(object, duration, glm::vec3(0,toHeight,0), [](const std::shared_ptr<Object3D> &object, const glm::vec3 &position, const float step, const float progress) {
            object->scale(glm::vec3(1, 1 - 0.01,1));
        });
    }


    Animation makeUnCrouchAnimation(const std::shared_ptr<Object3D> &object, const uint duration, const float fromHeight) {
        return Animation(object, duration, glm::vec3(0,fromHeight,0), [](const std::shared_ptr<Object3D> &object, const glm::vec3 &position, const float step, const float progress) {
            object->scale(glm::vec3(1, 1 + 0.01,1));
        });
    }


    Animation::Animation(const std::shared_ptr<Object3D> &object, const uint duration, const glm::vec3 &position, const std::function<void(const std::shared_ptr<Object3D>&,const glm::vec3&, const float, const float)> &interpolation):
    m_pObjectToMove(object),
    m_duration(duration),
    m_targetPositon(position),
    m_interpolationFunction(interpolation),
    m_callback([](void) -> void {})
    {}

}
