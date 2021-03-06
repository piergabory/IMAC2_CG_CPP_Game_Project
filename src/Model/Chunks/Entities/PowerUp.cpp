#include "PowerUp.hpp"

namespace GameModel
{
	void PowerUp::firstVisit(Player& player) {
        //Player regains life if he catches a power up
		//player.incrementLife(50);
	}


    std::unique_ptr<GraphicsEngine::Object3D> PowerUp::s_entityObject;

    void PowerUp::loadObject() {
        s_entityObject = std::unique_ptr<GraphicsEngine::Object3D>(makeObject("assets/models/road_boost.obj", "assets/textures/road_boost.png", "shaders/perspective.vs.glsl", "shaders/lighting.fs.glsl"));
    }
}
