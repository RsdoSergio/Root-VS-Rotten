#include"peon.h"
#include "piezaTierra.h"
#include<ETSIDI.h>


void Peon :: dibujaTablero(float x, float y) const {
    constexpr float TAM = 1.5f;
    int frame = 0; // idle por defecto
    switch (getDireccion()) {
    case DirMovimiento::ESTE:  frame = 1; break;
    case DirMovimiento::OESTE: frame = 2; break;
    case DirMovimiento::NORTE: frame = 3; break;
    case DirMovimiento::SUR:   frame = 4; break;
    default:                   frame = 0; break;
    }

    float u0 = frame / 6.0f;
    float u1 = (frame + 1) / 6.0f;

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/sprites_plantas/seta_solar.png").id);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(u0, 1.0f); glVertex3f(x - TAM_PIEZA, y - TAM_PIEZA, 0);
    glTexCoord2f(u1, 1.0f); glVertex3f(x + TAM_PIEZA, y - TAM_PIEZA, 0);
    glTexCoord2f(u1, 0.0f); glVertex3f(x + TAM_PIEZA, y + TAM_PIEZA, 0);
    glTexCoord2f(u0, 0.0f); glVertex3f(x - TAM_PIEZA, y + TAM_PIEZA, 0);
    glEnd();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void Peon:: dibujaArena(float x, float y) const {
    constexpr float TAM = 1.4f; // más grande para la arena

    int frame = 0;
    switch (getDireccion()) {
    case DirMovimiento::ESTE:  frame = 1; break;
    case DirMovimiento::OESTE: frame = 2; break;
    case DirMovimiento::NORTE: frame = 3; break;
    case DirMovimiento::SUR:   frame = 4; break;
    default:                   frame = 0; break;
    }

    float u0 = frame / 6.0f;
    float u1 = (frame + 1) / 6.0f;

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/sprites_plantas/seta_solar.png").id);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(u0, 1.0f); glVertex3f(x - TAM, y - TAM, 0);
    glTexCoord2f(u1, 1.0f); glVertex3f(x + TAM, y - TAM, 0);
    glTexCoord2f(u1, 0.0f); glVertex3f(x + TAM, y + TAM, 0);
    glTexCoord2f(u0, 0.0f); glVertex3f(x - TAM, y + TAM, 0);
    glEnd();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}