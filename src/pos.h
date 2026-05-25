#pragma once
struct Pos {
    int fila;
    int col;

    Pos(int f, int c) : fila(f), col(c) {} 
    Pos() : fila(-1), col(-1) {} 
    bool esValida() const { return fila >= 0 && col >= 0; }
};