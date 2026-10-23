#include <stdio.h>
#include "raylib.h"


#define WIDTH 800
#define HEIGHT 600



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

//Tenes que ponerle un mejor nombre.
//TODO: averiguar cual esa la convension de nombres, imagino que icon es solo para el icono de la app.
const char *img[] = {
    "./img/hambuger_black256.png",
    "./img/hambuger_white256.png",
};



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

//NOTE: Tengo muchas cosas sueltas, deberian ser encapsuladas en algo.
void side_bar(Texture2D t, bool *vf)
{
    float tw = t.width, th = t.height;
    Vector2 tp;
    tp.x = 0;
    tp.y = 0;
    DrawTexturePro(t,(Rectangle) {tp.x,tp.y,tw,th},(Rectangle){0,0,64,52},
                   (Vector2){0,0},0.f,RAYWHITE);
    Vector2 mp = GetMousePosition();
    if (mp.x >= tp.x && mp.x <= tp.x + 64 && mp.y >= tp.y && mp.y <= tp.y + 52) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) *vf = !(*vf);

        if (*vf) DrawRectangle(0,0,WIDTH*0.2,HEIGHT,BROWN);
    }
}



int main()
{
    InitWindow(WIDTH,HEIGHT,"Simulador de Circuitos");
    Texture2D arrayT[gImgLen];
    load_array_texture(arrayT);
    Texture2D t = LoadTexture(img[0]);
    bool vf = false;
    SetTextureFilter(t, TEXTURE_FILTER_BILINEAR);
    //TODO: corroborar si las texturar fueron cargadas, averiguar como funciona IsTextureValid
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        side_bar(t,&vf);
        printf("%d\n",vf);
        DrawTexture(arrayT[2], 75, 100, RAYWHITE);

        EndDrawing();
    }
    unload_array_texture(arrayT);
    CloseWindow();
    return 0;
}
