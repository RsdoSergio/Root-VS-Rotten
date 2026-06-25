#include "valquiria.h"
#include "gestorTexturas.h"



void Valquiria::iniciarRafaga(int dx, int dy)
{
    golpesPendientes = 3;
    timerEntreGolpes = 0.3;
    dirX = dx;
    dirY = dy;
}

std::vector<Proyectil*> Valquiria::recogerProyectiles()
{
    std::vector<Proyectil*> tmp = proyectilesPendientes;
    proyectilesPendientes.clear();
    return tmp;
}

void Valquiria::actualizarEfectos(double dt)
{
    if (golpesPendientes <= 0) return;

    timerEntreGolpes += dt;
    if (timerEntreGolpes < DELAY_ENTRE_GOLPES) return;
    timerEntreGolpes = 0.0;

    // Qué golpe es (3 pendientes = primero, 2 = segundo, 1 = tercero)
    int numGolpe = 3 - golpesPendientes; // 0, 1, 2

    // Perpendicular a la dirección de ataque
    // Si va en X (ESTE/OESTE), la perpendicular es Y, y viceversa
    double perpX = (double)dirY; // perpendicular al eje de avance
    double perpY = (double)dirX;

    double offsetPerp = 0.0;
    if (numGolpe == 1) offsetPerp = +OFFSET_PERPENDICULAR;
    else if (numGolpe == 2) offsetPerp = -OFFSET_PERPENDICULAR;
    // numGolpe == 0 → centro, offsetPerp = 0

    Vector2D pos(
        posArena.getX() + dirX * OFFSET_FRENTE + perpX * offsetPerp,
        posArena.getY() + dirY * OFFSET_FRENTE + perpY * offsetPerp
    );

    proyectilesPendientes.push_back(
        new Proyectil(pos, Vector2D(0.0, 0.0), fuerza, tiempoAnimAtaque)
    );

    golpesPendientes--;
    if (golpesPendientes > 0) iniciarAtaque(); // mantener sprite de ataque entre golpes
}

