#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"
#include "Sprite.h"


class SpriteRenderer {
public:
    // Constructor (inits shaders/shapes)
    SpriteRenderer(Shader &shader);

    // Destructor
    ~SpriteRenderer();

    // Renders a defined quad textured with given sprite
    virtual void DrawSprite(Sprite *sp);

protected:
    // Render state
    Shader shader;
    unsigned int quadVAO{};

    // Initializes and configures the quad's buffer and vertex attributes
    virtual void initRenderData();

    void bind();
};

#endif