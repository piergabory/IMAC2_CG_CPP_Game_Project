/**
 * Scene.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Scene_hpp
#define Scene_hpp

#include "Object3D.hpp"
#include "Camera.hpp"
#include "Context.hpp"

/**
 * SCENE CLASS
 *
 * Contains and manages the camera, objects and lights.
 * Has ADD methods to populate the scene
 * Has a DRAW method to project the scene on the camera.
 */

namespace GraphicsEngine
{
    
    class Scene : public Context<Object3D> {
    
    private:
        /// Camera
        std::shared_ptr<Camera> m_camera;

        void initializeObject(Object3D &newObject) override{
            newObject.setProjection(m_camera->projectionMatrix(), m_camera->modelMatrix());
        }

    public:
        
        // constructor
        // initialize camera
        Scene() : Context<Object3D>(), m_camera(std::make_shared<Camera>()) {}
        // takes an existing camera
        Scene(Camera &cameraPtr) : Context<Object3D>(), m_camera(std::make_shared<Camera>(cameraPtr)) {}
        
        
        // destructor
        // deletes memory allocated on each pointer in the object vector.
        ~Scene() {}
    };
    
}

#endif /* Scene_hpp */
