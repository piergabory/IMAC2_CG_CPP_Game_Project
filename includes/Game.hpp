#ifndef Game_hpp
#define Game_hpp

#include "Player.hpp"
#include "ImportedMesh.hpp"

enum class Controls : unsigned char {
    LEFT, RIGHT, UP, DOWN
};

class Game{
private:
    Player m_pPlayer;

    static std::shared_ptr<GraphicsEngine::Object3D> loadPlayerObject();

public:

    inline std::shared_ptr<GraphicsEngine::Object3D> playerModel() const {
        return m_pPlayer.model();
    }

    void callInput(Controls control) {
        switch(control) {
            case Controls::LEFT:
                m_pPlayer.translate(Direction::LEFT);
                break;

            case Controls::RIGHT:
                m_pPlayer.translate(Direction::RIGHT);
                break;

            case Controls::UP:
                //m_pPlayer.translate(Direction::RIGHT);
                break;

            case Controls::DOWN:
                //m_pPlayer.translate(Direction::RIGHT);
                break;

        }
    }

    Game();
    ~Game();
};

#endif /* Game_hpp */
