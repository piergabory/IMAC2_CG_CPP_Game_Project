/**
 * PerspectiveShaderProgram.hpp
 */
#include "PerspectiveShaderProgram.hpp"

namespace GraphicsEngine {
    
    PerspectiveShaderProgram::PerspectiveShaderProgram(
       LocalFilePath vertexShaderSourcePath,
       LocalFilePath fragmentShaderSourcePath,
       const char* uniformMVPName, 
       const char* uniformMVName, 
       const char* uniformNormName):

    // superclass constructor
        ShaderProgram(vertexShaderSourcePath, fragmentShaderSourcePath),

    // members init
        m_uniformModelViewMatrix(glGetUniformLocation(m_glProgramIdentifier, uniformMVName)),
        m_uniformNormalMatrix(glGetUniformLocation(m_glProgramIdentifier, uniformNormName)),
        m_uniformModelViewProjectionMatrix(glGetUniformLocation(m_glProgramIdentifier, uniformMVPName)),
        m_uniformSunPosition(glGetUniformLocation(m_glProgramIdentifier, "uSunPosition"))

    // nothing
    {}

    
    void PerspectiveShaderProgram::setUniformMatrices(const glm::mat4 &objectModel) const {
        // move the object modelView in the camera referenceframe
        glm::mat4 modelView, modelViewProjection;

        modelView = (*m_sceneModelViewMatrix) * objectModel;
        modelViewProjection = (*m_projectionMatrix) * modelView;

        // use program
        glUseProgram(m_glProgramIdentifier);

        // modelview = modelview
        glUniformMatrix4fv(m_uniformModelViewMatrix, 1, false, glm::value_ptr(modelView));
        
        // Normal = transversed( inverted( modelview ))
        // the 'true' parameter asks the method to do the transvertion of the input matrix.
        glUniformMatrix4fv(m_uniformNormalMatrix, 1, true, glm::value_ptr(glm::inverse(modelView)));
        
        // modelviewProjection = modelview * projection
        glUniformMatrix4fv(m_uniformModelViewProjectionMatrix, 1, false, glm::value_ptr(modelViewProjection));

        glm::vec3 sun = glm::vec3(*m_sceneModelViewMatrix * glm::vec4(2,4,-3,0));
        glUniform3fv(m_uniformSunPosition, 1, glm::value_ptr(sun));
    }

    void PerspectiveShaderProgram::setViewMatrices(const std::shared_ptr<glm::mat4> &projection,  const std::shared_ptr<glm::mat4> &sceneModel) {
        m_projectionMatrix = projection;
        m_sceneModelViewMatrix = sceneModel;
    }
}
