#include <stdio.h>
#include "raylib.h"


#define width 800
#define height 600



const char *gateImg[] = {
    "./img/and128x64.png",
    "./img/nand128x54.png",
    "./img/nor128x64.png",
    "./img/xnor128x64.png",
    "./img/or128x64.png",
    "./img/not128x64.png",
    "./img/xor128x64.png",
};

//Se define la logitud por si se agregan las compuertas de diferente tamanio.
#define gImgLen sizeof(gateImg) / sizeof(gateImg[0])


typedef struct {
    Texture2D *t;
    Vector2 pos;
} gate_gph;


//TODO: implementar movimiendo de la commpuerta.
//TODO: Conexiones de las compuertas.

/*Aca la pregunta es: Me combiene cargar todas las compuertas al iniciar los graficos?
  o es preferible cargarlos la primera vez que se quiera generar una instancia de la compuerta?*/
void load_array_texture(Texture2D *t)
{
    //NOTE: Por el momento vamos a cargar todas las imagenes de las compuertas al comienzo
    //Si se llegara a agregar variantes de diferentes tamanios esto va a cambiar.
    for (int i = 0; i < gImgLen; i++) t[i] = LoadTexture(gateImg[i]);
}

void unload_array_texture(Texture2D *t)
{
    //NOTE: Por el momento vamos a cargar todas las imagenes de las compuertas al comienzo
    //Si se llegara a agregar variantes de diferentes tamanios esto va a cambiar.
    for (int i = 0; i < gImgLen; i++) UnloadTexture(t[i]);
}



int main()
{
    InitWindow(width,height,"Simulador de Circuitos");
    Texture2D arrayT[gImgLen];
    load_array_texture(arrayT);
    //TODO: corroborar si las texturar fueron cargadas, averiguar como funciona IsTextureValid
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(arrayT[2], 0, 100, RAYWHITE);
        EndDrawing();
    }
    unload_array_texture(arrayT);
    CloseWindow();
    return 0;
}
