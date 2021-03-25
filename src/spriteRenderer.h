/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
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
    SpriteRenderer(Shader &shader, bool skew = false);

    // Destructor
    ~SpriteRenderer();

    // Renders a defined quad textured with given sprite
    void DrawSprite(Sprite *sp);

private:
    // Render state
    Shader shader;
    bool skew;
    unsigned int quadVAO{};

    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
    void bind();
};

#endif