#ifndef Frameworks_hpp
#define Frameworks_hpp

#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
    // Mac OS
    #include <SDL2/SDL.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLKit/GLKMatrix4.h>
#else
    // Linux
    #include <GL/glew.h>
    #include <SDL2/SDL.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#endif
