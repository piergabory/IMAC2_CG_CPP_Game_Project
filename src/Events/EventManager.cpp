/**
 * \file EventManager.hpp
 * \version 0.2
 *
 */

#include "EventManager.hpp"

namespace Events {
    // define instance in cpp file
    Manager* Manager::s_pEventManagerInstance = nullptr;

    // singleton instance getter
    Manager* Manager::instance() {
        // creates instance if doesn't exists
        if (s_pEventManagerInstance == nullptr)
            s_pEventManagerInstance = new Manager();

        return  s_pEventManagerInstance;
    }


    void Manager::pollEvents() {
        
        // temporary variable holding each event
        SDL_Event event;

        // fetches every event until there's none left
        while (SDL_PollEvent(&event)) {

            // check if observer is defined
            if (m_pQuitEventObserver[0]!= nullptr) {
                // check event type, calls the corresponding method.
                switch (event.type) {
                    case SDL_QUIT:
                      for(unsigned int i=0; i<m_pQuitEventObserver.size(); i++){
                        m_pQuitEventObserver[i]->quitEventHandler();
                      }
                      //m_pQuitEventObserver->quitEventHandler();
                      break;
                    case SDL_WINDOWEVENT:
                      for(unsigned int i=0; i<m_pQuitEventObserver.size(); i++){
                        m_pQuitEventObserver[i]->windowEventHandler();
                      }
                      //m_pQuitEventObserver->windowEventHandler();
                      break;
                    default: break;
                }
            }

            if (m_pMouseEventsObserver[0]!= nullptr) {
                switch (event.type) {
                    case SDL_MOUSEMOTION:
                      for(unsigned int i=0; i<m_pMouseEventsObserver.size(); i++){
                          m_pMouseEventsObserver[i]->mouseMoveHandler(event.motion.xrel,event.motion.yrel);
                           }
                      //m_pMouseEventsObserver->mouseMoveHandler(event.motion.xrel,event.motion.yrel);
                      break;
                    case SDL_MOUSEBUTTONDOWN:
                      for(unsigned int i=0; i<m_pMouseEventsObserver.size(); i++){
                        m_pMouseEventsObserver[i]->mouseDownHandler(event.button.button);
                      }
                      //m_pMouseEventsObserver->mouseDownHandler(event.button.button);
                      break;
                    case SDL_MOUSEBUTTONUP:
                      for(unsigned int i=0; i<m_pMouseEventsObserver.size(); i++){
                        m_pMouseEventsObserver[i]->mouseReleaseHandler(event.button.button);
                      }
                      //m_pMouseEventsObserver->mouseReleaseHandler(event.button.button);
                      break;
                    case SDL_MOUSEWHEEL:
                      for(unsigned int i=0; i<m_pMouseEventsObserver.size(); i++){
                        m_pMouseEventsObserver[i]->mouseWheelHandler(event.wheel.x, event.wheel.y);
                      }
                      //m_pMouseEventsObserver->mouseWheelHandler(event.wheel.x, event.wheel.y);
                      break;
                    default: break;
                }
            }

            if (m_pKeyboardEventsObserver[0]!= nullptr) {
                switch (event.type) {
                    case SDL_KEYDOWN:
                      for(unsigned int i=0; i<m_pKeyboardEventsObserver.size(); i++){
                        m_pKeyboardEventsObserver[i]->keyDownHandler(event.key.keysym.sym);
                      }
                      m_pressedKeys.insert(event.key.keysym.sym);
                      break;
                    case SDL_KEYUP:
                      for(unsigned int i=0; i<m_pKeyboardEventsObserver.size(); i++){
                        m_pKeyboardEventsObserver[i]->keyRealeaseHandler(event.key.keysym.sym);
                      }
                      m_pressedKeys.erase(event.key.keysym.sym);
                      break;
                    default: break;
                }
            }
        }
        // if the set isn't empty (key currently pressed) send the set to the observer
        if(!m_pressedKeys.empty()){
          for(unsigned int i=0; i<m_pKeyboardEventsObserver.size(); i++){
            m_pKeyboardEventsObserver[i]->keyPressHandler(m_pressedKeys);
          }
        }
    }



    // setters

    void Manager::subscribe(QuitEventObserver* quitObserver) {
        m_pQuitEventObserver.push_back(std::unique_ptr<QuitEventObserver>( quitObserver));
    }

    void Manager::subscribe(MouseEventObserver* mouseObserver) {
        m_pMouseEventsObserver.push_back(std::unique_ptr<MouseEventObserver>(mouseObserver));
    }
    
    
    void Manager::unsubscribe(MouseEventObserver* mouseObserver){
        size_t i = 0;
        while (i < m_pMouseEventsObserver.size()){
            if (m_pMouseEventsObserver[i].get()==mouseObserver){
                m_pMouseEventsObserver[i].release(); m_pMouseEventsObserver.erase(m_pMouseEventsObserver.begin() + i);
                
            } else {
                i++;
            }
        }
    }


    void Manager::subscribe(KeyboardEventObserver* keyboardObserver) {
        m_pKeyboardEventsObserver.push_back(std::unique_ptr<KeyboardEventObserver> (keyboardObserver));
    }
}
