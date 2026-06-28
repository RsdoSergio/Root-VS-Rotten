<img width="1280" height="640" alt="Diseño sin título (2)" src="https://github.com/user-attachments/assets/d8541843-4881-4720-9a0b-1d0bf32c47a5" />

# Root VS Rotten

**Root VS Rotten** es un videojuego inspirado en el clásico juego de estrategia **Archon: The Light and the Dark**, reinterpretado con una temática basada en el universo de **Plants vs. Zombies**.

En este proyecto, dos equipos enfrentados **Root** (plantas) y **Rotten** (zombies) compiten por el control del tablero mediante estrategia y combates directos entre unidades. Cada pieza representa un personaje con habilidades y características propias, combinando elementos de **juego de tablero** y **acción en tiempo real**.

## Objetivo del juego

El objetivo principal es **dominar el tablero y derrotar al equipo rival** mediante una combinación de:

* Estrategia en el movimiento de las piezas.
* Control de posiciones clave del tablero.
* Combates directos entre unidades cuando dos piezas se enfrentan.

El juego toma como base la mecánica de **Archon: The Light and the Dark**, donde el tablero funciona como un sistema estratégico mientras que los enfrentamientos se resuelven en una arena de combate.

## Características principales

* Sistema de **tablero estratégico** con movimiento de piezas.
* **Combates individuales** entre unidades cuando se produce un enfrentamiento.
* Dos equipos con identidades diferenciadas:
  * **Root** → plantas
  * **Rotten** → zombies
* Inspiración estética y temática en **Plants vs. Zombies**.

## Contexto académico
 
Este proyecto se desarrolla como trabajo de la asignatura **Informática Industrial y Comunicaciones** del **tercer curso del Grado en Ingeniería Electrónica Industrial y Automática**.
 
### Equipo de desarrollo
 
* Tomás Estevez
* Emmanuel Molina
* Pablo Paz
* Mauricio Quinchuela
* Sergio Rosado

---

## Cómo jugar

### Pantallas del juego

| Pantalla | Descripción |
|----------|-------------|
| **Menú principal** | Inicia partida |
| **Tablero** | Fase estratégica por turnos |
| **Arena** | Combate en tiempo real entre dos piezas |
| **Fin de partida** | Pantalla de victoria + registro de nombre |

---

### Tablero (fase estratégica)

Es un juego por turnos alternos: primero juegan las **Plantas (ROOT)**, luego los **Zombies (ROTTEN)**.

**Controles de cursor:**

| Acción | Plantas | Zombies |
|--------|-----------|-----------|
| Mover cursor | `WASD` o ratón | Flechas o ratón |

**Selección:** mueve el cursor a una casilla y pulsa `Enter` o clic. Primero selecciona tu pieza, luego la casilla destino. `ESC` cancela.

**Combate:** si mueves una pieza a una casilla ocupada por el enemigo, se inicia un combate en la Arena.

**Pausa:** pulsa `M` durante la partida.

---

### Arena (combate)

Dos piezas se enfrentan en tiempo real con obstáculos en el campo.

| Acción | Plantas | Zombies |
|--------|-----------|-----------|
| Mover | `WASD` | Flechas |
| Atacar | `Q` | `K` |

La pieza que gane el combate es la que vuelve al tablero conquistando la casilla disputada.

---

### Hechizos (solo el Mago)

Selecciona tu Mago en el tablero y pulsa `Espacio` para ver sus hechizos disponibles. Cada hechizo solo se puede usar **una vez por partida**.

| Tecla | Hechizo | Efecto |
|-------|---------|--------|
| `1` | Teleport | Teletransporta a un aliado a otra casilla |
| `2` | Heal | Cura a un aliado al máximo de vida |
| `3` | Revive | Revive una pieza eliminada junto al Mago |
| `4` | Imprison | Inmoviliza a un enemigo durante 3 turnos |
| `5` | Shift Time | Altera el orden del turno |
| `6` | Exchange | Intercambia posición entre dos piezas aliadas |
| `7` | Transform | Transforma al Mago a evolución superior |

---

### ¿Cómo se gana?

Gana el bando que logre uno de estos tres objetivos:

1. **Controlar los 5 puntos de poder** del tablero
2. **Eliminar todas las piezas** del rival
3. Que todas las piezas rivales restantes queden **aprisionadas**

---

### Casillas de poder

Hay **5 casillas especiales** en el tablero: el centro y los 4 extremos (en forma de cruz). Parpadean para distinguirse.

Mientras una pieza ocupa una casilla de poder, **entra al combate con +30% de cadencia de disparo** en la Arena.

Además, el número total de casillas controladas por un bando otorga bonificaciones acumulativas a **todas sus piezas en combate**:

| Casillas controladas | Bonus |
|----------------------|-------|
| 1 | +20% cadencia de ataque |
| 2 | +20% vida máxima |
| 3 | +20% daño |
| 4 | ×2 a todos los bonuses anteriores |
| 5 | ¡Victoria instantánea! |

---

### Ciclo de color del tablero

El color de las casillas neutrales cambia tras cada combate, rotando entre 4 fases. El color indica qué bando tiene **ventaja de terreno** en ese momento:

| Color | Ventaja para |
|-------|-------------|
| Morado | Zombies (ROTTEN) |
| Verde claro | Plantas (ROOT) |
| Rosa/magenta | Zombies (ROTTEN) |
| Verde oscuro | Plantas (ROOT) |

El bando con ventaja entra al siguiente combate con **+30% vida máxima** y **+30% velocidad de movimiento**.
