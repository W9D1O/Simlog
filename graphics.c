/* #include <stdio.h> */
/* #include "raylib.h" */


/* #define WIDTH 800 */
/* #define HEIGHT 600 */



/* const char *gateImg[] = { */
/*     "./img/and128x64.png", */
/*     "./img/nand128x54.png", */
/*     "./img/nor128x64.png", */
/*     "./img/xnor128x64.png", */
/*     "./img/or128x64.png", */
/*     "./img/not128x64.png", */
/*     "./img/xor128x64.png", */
/* }; */



/* //Se define la logitud por si se agregan las compuertas de diferente tamanio. */
/* #define gImgLen sizeof(gateImg) / sizeof(gateImg[0]) */

/* //Tenes que ponerle un mejor nombre. */
/* //TODO: averiguar cual esa la convension de nombres, imagino que icon es solo para el icono de la app. */
/* const char *img[] = { */
/*     "./img/hambuger_black256.png", */
/*     "./img/hambuger_white256.png", */
/* }; */



/* typedef struct { */
/*     Texture2D *t; */
/*     Vector2 pos; */
/* } gate_gph; */


/* //TODO: implementar movimiento de la commpuerta. */
/* //TODO: Conexiones de las compuertas. */

/* /\*Aca la pregunta es: Me combiene cargar todas las compuertas al iniciar los graficos? */
/*   o es preferible cargarlos la primera vez que se quiera generar una instancia de la compuerta?*\/ */
/* void load_array_texture(Texture2D *t) */
/* { */
/*     //NOTE: Por el momento vamos a cargar todas las imagenes de las compuertas al comienzo */
/*     //Si se llegara a agregar variantes de diferentes tamanios esto va a cambiar. */
/*     for (int i = 0; i < gImgLen; i++) t[i] = LoadTexture(gateImg[i]); */
/* } */

/* void unload_array_texture(Texture2D *t) */
/* { */
/*     //NOTE: Por el momento vamos a cargar todas las imagenes de las compuertas al comienzo */
/*     //Si se llegara a agregar variantes de diferentes tamanios esto va a cambiar. */
/*     for (int i = 0; i < gImgLen; i++) UnloadTexture(t[i]); */
/* } */


/* void sub_bar(int sep) */
/* { */
/*     DrawRectangle(0,sep,WIDTH*0.2,HEIGHT*0.05,YELLOW); */
/* } */


/* //NOTE: Tengo muchas cosas sueltas, deberian ser encapsuladas en algo. */
/* void side_bar(Texture2D t, bool *vf) */
/* { */
/*     float tw = t.width, th = t.height; */
/*     Vector2 tp; */
/*     tp.x = 0; */
/*     tp.y = 0; */
/*     DrawTexturePro(t,(Rectangle) {tp.x,tp.y,tw,th},(Rectangle){0,0,64,52}, */
/*                    (Vector2){0,0},0.f,RAYWHITE); */
/*     Vector2 mp = GetMousePosition(); */
/*     if (mp.x >= tp.x && mp.x <= tp.x + 64 && mp.y >= tp.y && mp.y <= tp.y + 52) { */
/*         if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) *vf = !(*vf); */


/*     } */
/*         if (*vf) { */
/*             DrawRectangle(0,0,WIDTH*0.2,HEIGHT,BROWN); */
/*             sub_bar(40); */
/*         } */
/* } */



/* int main() */
/* { */
/*     InitWindow(WIDTH,HEIGHT,"Simulador de Circuitos"); */
/*     Texture2D arrayT[gImgLen]; */
/*     load_array_texture(arrayT); */
/*     Texture2D t = LoadTexture(img[0]); */
/*     bool vf = false; */
/*     SetTextureFilter(t, TEXTURE_FILTER_BILINEAR); */
/*     //TODO: corroborar si las texturar fueron cargadas, averiguar como funciona IsTextureValid */
/*     SetTargetFPS(60); */
/*     while (!WindowShouldClose()) { */
/*         BeginDrawing(); */
/*         ClearBackground(RAYWHITE); */
/*         printf("%d\n",vf); */
/*         DrawTexture(arrayT[2], 75, 100, RAYWHITE); */
/*         side_bar(t,&vf); */

/*         EndDrawing(); */
/*     } */
/*     unload_array_texture(arrayT); */
/*     CloseWindow(); */
/*     return 0; */
/* } */



/*Base chat GPT*/
#include "raylib.h"
#include <stdbool.h>
#include <math.h>
#define WIDTH 1000
#define HEIGHT 600

typedef struct {
    const char *title;
    bool expanded;
    const char **children;
    int childCount;
} MenuItem;

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Collapsible Sidebar");
    SetTargetFPS(60);

    Color bg = {25, 26, 32, 255};
    Color panel = {35, 37, 45, 255};
    Color hover = {52, 55, 65, 255};
    Color accent = {65, 110, 190, 255};

    const char *projectItems[] = {
        "Proyecto 1",
        "Proyecto 2",
        "Proyecto 3"
    };

    const char *settingsItems[] = {
        "General",
        "Apariencia",
        "Avanzado"
    };

    MenuItem menus[] = {
        {"Proyectos", false, projectItems, 3},
        {"Configuracion", false, settingsItems, 3}
    };

    bool sidebarOpen = true;

    float sidebarWidth = 230;
    float targetWidth = 230;

    int selectedPage = 0;

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        // Animacion de sidebar
        sidebarWidth += (targetWidth - sidebarWidth) * 0.15f;

        if (fabsf(targetWidth - sidebarWidth) < 0.5f)
            sidebarWidth = targetWidth;

        BeginDrawing();
        ClearBackground(bg);

        // SIDEBAR
        DrawRectangle(0, 0, (int)sidebarWidth,
                      HEIGHT, panel);

        // BOTON ABRIR / CERRAR
        Rectangle toggle = {10, 10, 35, 35};

        DrawRectangleRounded(toggle, 0.2f, 8, hover);
        DrawText("=", 20, 16, 24, RAYWHITE);

        if (CheckCollisionPointRec(mouse, toggle) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            sidebarOpen = !sidebarOpen;
            targetWidth = sidebarOpen ? 230 : 55;
        }

        // CONTENIDO SIDEBAR
        if (sidebarWidth > 180)
        {
            DrawText("MI APLICACION", 20, 65, 18, RAYWHITE);

            float y = 115;

            for (int i = 0; i < 2; i++)
            {
                Rectangle item = {10, y, 210, 40};

                bool over = CheckCollisionPointRec(mouse, item);

                DrawRectangleRounded(
                    item, 0.15f, 8,
                    over ? hover : panel
                );

                DrawText(menus[i].title, 22, y + 11,
                         16, RAYWHITE);

                DrawText(menus[i].expanded ? "v" : ">",
                         195, y + 11, 16, RAYWHITE);

                if (over && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    menus[i].expanded = !menus[i].expanded;

                y += 45;

                // SUBMENU
                if (menus[i].expanded)
                {
                    for (int j = 0; j < menus[i].childCount; j++)
                    {
                        Rectangle child = {
                            25, y, 185, 35
                        };

                        bool childOver =
                            CheckCollisionPointRec(mouse, child);

                        if (childOver)
                            DrawRectangleRounded(
                                child, 0.15f, 8, hover
                            );

                        DrawText(menus[i].children[j],
                                 40, y + 9, 14, LIGHTGRAY);

                        if (childOver &&
                            IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        {
                            selectedPage = i * 10 + j + 1;
                        }

                        y += 38;
                    }
                }
            }
        }

        // CONTENIDO PRINCIPAL
        DrawText("Contenido principal",
                 (int)sidebarWidth + 30, 35,
                 25, RAYWHITE);

        DrawText(TextFormat("Pagina seleccionada: %d",
                            selectedPage),
                 (int)sidebarWidth + 30, 85,
                 18, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
