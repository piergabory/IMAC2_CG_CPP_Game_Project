/**
 * \file Button.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Button_hpp
#define Button_hpp

#include <functional>

#include "Object2D.hpp"
#include "EventManager.hpp"

namespace GraphicsEngine {


    /**
     * BUTTON CLASS
     *
     * \brief Extension to Object2D, adds click observers and callback.
     * \version 0.1
     *
     * The button class takes a callback functor as constructor parameter,
     * it will be called when a mouse release event is fired inside the bounds of the object.
     *
     * The class needs to be initialised before use by calling initializeButtons() before any instanciations.
     *
     * Possible improvements: - Instead of heritage of Object 2D, wrapping the object inside the button, as a member.
     *                        - Use a pointer instead of vec2 to save the window size.
     */

    class Button : public Object2D, Events::MouseEventObserver {
    private:
        /// \brief Callback called on click inside the object's bounds
        /// Callback will take the button instance and the mouse button code
        std::function<void(Button*, unsigned char)> m_onClickCallback;

        /// Records the object's bounds defining points
        const glm::vec2 m_boundingBoxTopLeftCorner;
        const glm::vec2 m_boundingBoxBottomRightCorner;

        ///\brief  MouseUp handler, checks the bounds and calls the callback if true
        void mouseReleaseHandler(unsigned char button) override;

        ///\brief  returns true if the SDL mouse position is above the object
        bool checkBounds() const;

        /// Static integer vector keeping the window pixels dimentions, used to compute the mouse position.
        static glm::ivec2 s_windowPixelSize;

    public:
        ///\brief  constructor with image
        Button(const glm::vec2 &position, const glm::vec2 &size, const LocalFilePath image, const std::function<void(Button*, unsigned char)> &callback);

        ///\brief  constructor with texture
        Button(const glm::vec2 &position, const glm::vec2 &size, const std::shared_ptr<Texture> sprite, const std::function<void(Button*, unsigned char)> &callback);

        ///\brief  default constructor by copy
        Button(const Button &copy) = default;

        ///\brief  Sets the static member s_windowPixelSize, needs to be called before any instantiations
        static void initializeButtons(const glm::ivec2 &windowPixelSize);

    };
}


#endif /* Button_hpp */