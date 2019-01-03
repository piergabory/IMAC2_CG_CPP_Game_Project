/**
 * \file Terrain.hpp
 */
#include "Terrain.hpp"

namespace GameModel {

    Entity* Terrain::entityAt(Position playerPosition) {
        return activeChunk()->entityAt(playerPosition);
    }


    void Terrain::loadChunk(Chunk *chunkToLoad) {
        chunkToLoad->rotate(m_nextLoadedChunkOrientation);
        chunkToLoad->translate(m_nextLoadedChunkPosition);

        // updates coordinates for the next chunk
        // based on the output of the new chunk
        m_nextLoadedChunkPosition += glm::vec3(glm::rotate(glm::mat4(1), m_nextLoadedChunkOrientation, glm::vec3(0.f,1.f,0.f)) * glm::vec4(chunkToLoad->exitPosition(), 1.f));
        m_nextLoadedChunkOrientation += chunkToLoad->exitOrientation();
        m_chunks.emplace_back(chunkToLoad);
    }



    glm::vec3 Terrain::progress(const float progress){
        // creates a rotation matrix from the front's chunk orientation and creates the translation vector
        glm::vec3 translationVector = glm::vec3(glm::rotate(glm::mat4(1), m_chunks.front()->orientation(), glm::vec3(0,1,0)) * glm::vec4(-progress * m_chunks.front()->exitPosition(), 1.f));

        // applies translation on all entities
        for (std::deque<std::unique_ptr<Chunk>>::iterator chunkIterator = m_chunks.begin(); chunkIterator != m_chunks.end(); ++chunkIterator) {
            (*chunkIterator)->translate(translationVector);
        }

        m_nextLoadedChunkPosition += translationVector;
        return translationVector;
    }


    
    std::set< std::shared_ptr<GraphicsEngine::Object3D> > Terrain::preloadInitialChunks() {
        std::set< std::shared_ptr<GraphicsEngine::Object3D> > objectsToBeAddedInScene;
        std::set< std::shared_ptr<GraphicsEngine::Object3D> > objectsInNewChunk;
        Chunk* newChunkPointer;

        for (int i = -m_CHUNK_COUNT_AFTER_PLAYER; i < m_CHUNK_COUNT_BEFORE_PLAYER; ++i) {
            newChunkPointer = new Chunk();
            // collect 3D objects and insert them in the set
            objectsInNewChunk = newChunkPointer->objects();
            for (std::shared_ptr<GraphicsEngine::Object3D> object : objectsInNewChunk) {
                objectsToBeAddedInScene.insert(object);
            }

            // insert new chunk
            loadChunk(newChunkPointer);

            // if there isn't enough chunks behind the player, move the terrain forward one chunk.
            if (i < 0) progress(1.0);
        }

        return objectsToBeAddedInScene;
    }




    const CardinalDirections Terrain::facing() const {
        int orientation = ((int) glm::degrees(activeChunk()->orientation()) % 180);
        return CardinalDirections(orientation);
    }

}
