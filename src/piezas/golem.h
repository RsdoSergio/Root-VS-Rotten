#pragma once
#include "piezaTierra.h"

// Pieza lenta y muy resistente, golpe fuerte cuerpo a cuerpo
class Golem : public PiezaTierra {
public:
    Golem(Bando b, Pos pos)
        : PiezaTierra(
            24.0, // vida muy alta
            10.0,  // fuerza alta
            4.0,   // velocidad baja
           1.2,   // recarga lenta
            1, //rad de mov
            b, pos) 
            {
                radioGolpe = 6.5;  // golpe más grande que el Peón
                tiempoAnimAtaque = 0.7;
            }

    

    std::string getNombre() const override {
        return bando == Bando::planta ? "Bonk Choy" : "Yeti";
    }
    void usarAtaqueSecundario() override {};
    
    std::string getRutaSprite() const override;
    
    bool esMelee() const override { return true; }
    

};