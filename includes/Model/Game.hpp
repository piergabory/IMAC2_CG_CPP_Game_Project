/**
 * \file Game.hpp
 *
 * IMAC 2 Project CG CPP
 */
#ifndef Game_hpp
#define Game_hpp
#pragma once

#include "Player.hpp"
#include "Terrain.hpp"

#include "ImportedMesh.hpp"

namespace GameModel {

    /// game controls, to be mapped on keyboard or game controller in GameController
    enum class Controls { LEFT, RIGHT, UP, DOWN };

    /**
     * GAME CLASS
     *
     * \brief Central controller class, Handles communication between Model classes and the GameController
     */
    class Game{

    private:
        /// \brief Player instance
        Player m_player;

        /// \brief Terrain instance
        Terrain m_terrain;

        /// \brief Static method generating the player's character object.
        static std::shared_ptr<GraphicsEngine::Object3D> loadPlayerObject();

    public:
        /// \brief getter on the character model
        inline std::shared_ptr<GraphicsEngine::Object3D> playerModel() const { return m_player.model(); }

        /// \brief getter on the terrain
        inline Terrain& terrain() { return m_terrain; }
        inline const Terrain& terrain() const { return m_terrain; }


        /// \brief shifts the terrain to the next chunk.
        /// Moves the player back to the center on each turn.
        void nextChunk();


        /// \brief Redirects controller inputs on player movements, attacks, bonuses etc...
        void callInput(Controls control);
        

        /// \brief constructor
        Game();

        /// \brief destructor
        ~Game();
    };

}

#endif /* Game_hpp */
