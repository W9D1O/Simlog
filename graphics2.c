#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//Tamanio ventana
#define WIDTH 800
#define HEIGHT 600

//Tamanio ventana sidebar
#define WIDTH_SB WIDTH*0.30

//Colores
#define BG         0x191A20FF
#define PANELCOLOR 0x23252DFF
#define HOVERCOLOR 0x343741FF
#define ACCENT     0x416EBE19

//Animation Velocity
#define SBA_VELOCITY 0.15f //SBA = side bar animation

typedef struct {
    const char  *title;
    bool         expanded;
    const char **children;
    int          childCount;
} menu_item;

#define MITEM_CAP 4
typedef struct {
    int count;
    menu_item items[MITEM_CAP];
    float width;
    float height;
} menu_bar;

menu_item init_menu_item(const char *title, const char *subtitle[], int lenST)
{

    menu_item menu = {
        .title = title,
        .expanded = false,
        .childCount = lenST
    };
    menu.children = malloc(menu.childCount * sizeof(char*));
    for (int i = 0; i < menu.childCount; i++) menu.children[i] = strdup(subtitle[i]);
    return menu;
}

void sidebar_animation(float *sidebarWidth, float targetWidth)
{
    //Estoy asumiendo que 0.15 es la velocidad.
    *sidebarWidth += (targetWidth - *sidebarWidth) * SBA_VELOCITY;
    if (fabsf(targetWidth - *sidebarWidth) < 0.5f) {
        *sidebarWidth = targetWidth;
    }
}

void draw_toggle_button(Vector2 mouse, float *targetWidth, float sidebarWidth, bool *sidebarOpen)
{
    //Estos valores son provisorios, no sirven para cuando haya diferentes resoluciones.
    float padding = 10;
    float size = 35;
    Rectangle toggle = {padding,padding,size,size};
    DrawRectangleRounded(toggle,0.2f,8, GetColor(HOVERCOLOR));
    if (CheckCollisionPointRec(mouse, toggle) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        *sidebarOpen = !*sidebarOpen;
        //Es evidente que chatgpt no entiende el terror de los literales.
        *targetWidth = *sidebarOpen ? WIDTH_SB : 55;
    }
}

int main()
{
    const char *subt[] = {"Compuertas", "Entradas", "Salidas"};
    int lST = sizeof(subt) / sizeof(subt[0]);
    printf("%d\n", lST);
    menu_bar sidebar = {
        .count = 1,
        .items[0] = init_menu_item("Componentes",subt,lST),
        .width = WIDTH_SB,
        .height = HEIGHT,
    };
    char *subt2[] = { "AND", "OR", "NOT"};
    sidebar.count = 2;
    lST = sizeof(subt2) / sizeof(subt2[0]);
    sidebar.items[1] = init_menu_item("Compuertas",subt,lST);
    bool sidebarOpen = true;
    int selectedPage = 0;
    float targetWidth = sidebar.width;
    InitWindow(WIDTH,HEIGHT,"Simulador de circuitos");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        Vector2 mouseP = GetMousePosition();
        BeginDrawing();
        sidebar_animation(&sidebar.width,targetWidth);
        ClearBackground(GetColor(BG));
        //Draw sidebar
        DrawRectangle(0,0,(int)sidebar.width,sidebar.height,GetColor(PANELCOLOR));
        draw_toggle_button(mouseP,&targetWidth,sidebar.width, &sidebarOpen);
        if (sidebar.width > 180) {
            DrawText("Ya tu sabes", 20, 65, 18, RAYWHITE);
            float y = 115;

            for (int i = 0; i < sidebar.count; i++) {
                Rectangle item = {10, y, 210, 40};
                bool over = CheckCollisionPointRec(mouseP, item);

                DrawRectangleRounded(item, 0.15f, 8, over ? GetColor(HOVERCOLOR) : GetColor(PANELCOLOR));
                DrawText(sidebar.items[i].title,22, y + 11, 16, RAYWHITE);
                DrawText(sidebar.items[i].expanded ? "v" : ">", 195, y + 11, 16, RAYWHITE);

                if (over && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) sidebar.items[i].expanded = !sidebar.items[i].expanded;

                y += 45;

                //Submenu
                if (sidebar.items[i].expanded) {
                    for (int j = 0; j < sidebar.items[i].childCount; j++) {
                        Rectangle child = { 25, y, 185, 35};

                        bool childOver = CheckCollisionPointRec(mouseP, child);
                        if (childOver) DrawRectangleRounded(child, SBA_VELOCITY/2, 8, GetColor(HOVERCOLOR));

                        DrawText(sidebar.items[i].children[j], 40, y + 9, 14, LIGHTGRAY);
                        if (childOver && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            selectedPage = i * 10 + j + 1;
                        }
                        y += 38;
                    }
                }
            }
        }


        // CONTENIDO PRINCIPAL
        DrawText("Contenido principal",
                 (int)sidebar.width + 30, 35,
                 25, RAYWHITE);

        DrawText(TextFormat("Pagina seleccionada: %d",
                            selectedPage),
                 (int)sidebar.width + 30, 85,
                 18, LIGHTGRAY);
        EndDrawing();

    }
    CloseWindow();
    return 0;
}
