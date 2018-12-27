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
        m_interpolationFunction(*m_pObjectToMove, m_targetPositon, 1.f / m_duration, 1.f - m_currentFrame / (float) m_duration);

        return true;
    }


    Animation makeLinearTranslation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const glm::vec3 &position) {
        return Animation(object, duration, position, [](Animatable& object, const glm::vec3 &position, const float step, const float progress) -> void {
            glm::vec3 newPosition = (position - object.position()) * step;
            object.translate(newPosition);
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
            object.scale(glm::vec3(1, 1 - 0.01,1));
        });
    }


    Animation makeUnCrouchAnimation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const float fromHeight) {
        return Animation(object, duration, glm::vec3(fromHeight), [](Animatable &object, const glm::vec3 &position, const float step, const float progress) {
            object.scale(glm::vec3(1, 1 + 0.01,1));
        });
    }

    Animation makeTurnAnimation(const std::shared_ptr<Animatable> &camera, unsigned int duration, const float angle) {
        return Animation(camera, duration, glm::vec3(angle), [](Animatable &camera, const glm::vec3 &angle, const float step, const float progress) {
            camera.rotate(angle.x * step, glm::vec3(0.f,1.f,0.f));
        });
    }


    Animation::Animation(const std::shared_ptr<Animatable> &object, const unsigned int duration, const glm::vec3 &position, const std::function<void(Animatable&,const glm::vec3&, const float, const float)> &interpolation):
    m_pObjectToMove(object),
    m_duration(duration),
    m_targetPositon(position),
    m_interpolationFunction(interpolation),
    m_callback([](void) -> void {})
    { assert(m_interpolationFunction); }

}
