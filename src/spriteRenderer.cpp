/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "spriteRenderer.h"


SpriteRenderer::SpriteRenderer(Shader &shader, bool skew) {
    this->shader = shader;
    this->skew = skew;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
//    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Sprite *sp) {
    // prepare transformations
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = sp->transformation.Get();
//    model = glm::translate(model, glm::vec3(sp->position,
//                                            0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
//
//    model = glm::translate(model, glm::vec3(0.5f * sp->size.x, 0.5f * sp->size.y,
//                                            0.0f)); // move origin of rotation to center of quad
//    model = glm::rotate(model, glm::radians(sp->rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
//    model = glm::translate(model, glm::vec3(-0.5f * sp->size.x, -0.5f * sp->size.y, 0.0f)); // move origin back
//
//    model = glm::scale(model, glm::vec3(sp->size, 1.0f)); // last scale

    this->shader.SetMatrix4("model", model);

    // render textured quad
    this->shader.SetVector3f("spriteColor", sp->color);

    glActiveTexture(GL_TEXTURE0);
    sp->texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData() {
    // configure VAO/VBO
    unsigned int VBO;
    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    if (skew) {
        float vertices[] = {
                // pos      // tex
                0.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f,

                0.0f, 1.0f, 0.0f, 1.0f,
                -1.0f, 1.0f, -1.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 0.0f
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    } else {
        float vertices[] = {
                // pos      // tex
                0.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f,

                0.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 0.0f, 1.0f, 0.0f
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }
    bind();

}

void SpriteRenderer::bind() {
    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
