#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>


//APR: Es por Aspect Ratio. w es WIDTH y h HEIGHT
#define APR_W 16
#define APR_H 9

#define FACTOR 80

//Resolucion inicial de la ventana.
#define WIDTH APR_W*FACTOR
#define HEIGHT APR_H*FACTOR

typedef enum {
    RIGHT,
    LEFT,
    CENTER,
    TOP,
    DOWN
} Aling;

/* typedef enum { */
/*   VERTICAL, */
/*   HORIZONTAL, */
/*   NONE */
/* } Orientation; */

typedef struct {
    Image *icon;
    //Tengo que ver si es que me conviene agregar un rectangulo para las colisiones.
    char *text;
} Element; //Tengo que encontrar un nombre mejor.

/*Teniendo en cuenta que esto pretende ser hojas para armado de circuitos me parece generoso. (Sacando el heco de que tengo que tener botones)
  Al final como voy a necesitar varios Element en el contexto de la "Hoja de circuitos" me conviene que INITIAL_CAPACITY sea util para element y conteiner
*/
#define INITIAL_CAPACITY 64
/*
  Esto es lo que imagino aca

  Rectangle
  ------------
  *P "Text"P *
  * P  Img  P*
  *----------*
  Tengo que tomar la decicion sobre si es necesario mas de un padding
  es decit padding width y padding height por el momento voy a dejar uno solo.
*/
typedef struct {
    Rectangle area;
    //  Color background;
    float padding;

    //Si element sigue siendo un puntero es algo que esta por verse.
    Element *element;
    int count;
    int capacity;

    Aling aling;
    //  Orientation ori;

} Container;



typedef struct {
    Container *items;
    /*La idea es que un Conteinter pueda contener conteiner
      para que sea el layout quien los ordene dentro de ese container.
      El punte area define el lugar donde voy a crear un nuevo layout.
      En caso de no necesitarlo lo dejare en nulo, para este proyecto
      el desperdicio no deberia ser tan grande, a lo sumo 8 bytes, es
      decir se tiene un solo layout con varios paneles, el layout ocupa
      el ancho y alto de la pantalla dividiso por sus paneles.
    */
    Rectangle *area;
    int count;
    int capacity;

    //float padding;
    float gap;


} Layout;


Container* alloc_container()
{
    //  return (malloc(INITIAL_CAPACITY * sizeof(Container)));
    return calloc(INITIAL_CAPACITY,sizeof(Container));
}


Layout init_layout(Rectangle *r)
{
    Layout init = {
        .count = 0,
        .capacity = INITIAL_CAPACITY,
        //.padding = 0.f,
        .gap = 0,
        .area = r,
        .items = alloc_container()
    };
    return init;
}


float calculate_posicion(float pAbs, float size)
{
    float aux;
    if (pAbs >= size) aux = pAbs  - size;
    else aux = size - pAbs;
    return aux;
}

Vector2 conteiner_position(Aling align, float w, float h, float wAbs, float hAbs, float x, float y)
{
    Vector2 pos;

    switch (align) {
    case RIGHT:
        pos.y = y + calculate_posicion(hAbs / 2,h / 2);
        pos.x = x + calculate_posicion(wAbs ,w );
        break;
    case LEFT:
        pos.y = y + calculate_posicion(hAbs /2 ,h / 2);
        pos.x = x;
        break;
    case TOP:
        pos.y = y;
        pos.x = x + calculate_posicion(wAbs / 2, w / 2);
        break;
    case DOWN:
        pos.y = y + calculate_posicion(hAbs,h) ;
        pos.x = x + calculate_posicion(wAbs / 2, w / 2);
        break;
    case CENTER:
        pos.y = y + calculate_posicion(hAbs / 2, h / 2);
        pos.x = x + calculate_posicion(wAbs / 2, w / 2);
        break;
    default:
        break;
    }
    return pos;
}



//TODO: Voy a necesitar calcular area restante para acomodar los layout
//TODO: Tengo que ver si tengo que definir un enum para tamaños customs o auto.


//NOTE: Puede que no necesite gap.
//pWdth y pHeight es por porcentaje, aceptando como valor 0..1
//Toma el ancho y alto disponible y lo multiplica por ese valor.
void add_container(Layout *layout, Aling aling,float padding, float gap, float pWidth, float pHeight)
{
    float h,w;
    Vector2 pos;
    if (layout->count < layout->capacity) {

        layout->items[layout->count].aling = aling;
        layout->items[layout->count].padding = padding;
        layout->gap = gap;

        if (layout->area == NULL) {
            //Obtengo la resolucion actual de la pantalla.
            h = GetScreenHeight();
            w = GetScreenWidth();
            layout->items[layout->count].area.width = w * pWidth;
            layout->items[layout->count].area.height = h * pHeight;

            pos = conteiner_position(layout->items[layout->count].aling,layout->items[layout->count].area.width,
                                     layout->items[layout->count].area.height,w,h,0,0);

            layout->items[layout->count].area.x = pos.x;
            layout->items[layout->count].area.y = pos.y;
            layout->count++;
        } else {
            h = layout->area->height;
            w = layout->area->width;

            layout->items[layout->count].area.width = w * pWidth;
            layout->items[layout->count].area.height = h * pHeight;
            pos = conteiner_position(layout->items[layout->count].aling,layout->items[layout->count].area.width,
                                     layout->items[layout->count].area.height,w,h,layout->area->x,layout->area->y);
            layout->items[layout->count].area.x = pos.x;
            layout->items[layout->count].area.y = pos.y;
            layout->count++;
        }
    }
}


int main()
{
    Rectangle a = {
        .x = WIDTH/2,
        .y = 200,
        .width = WIDTH /3,
        .height = HEIGHT /3
    };
    Layout layout = init_layout(NULL);


    InitWindow(WIDTH,HEIGHT,"Diseño UI");
    add_container(&layout,RIGHT,0,0,0.2,0.7);
    add_container(&layout,LEFT,0,0,0.2,0.7);
    add_container(&layout,DOWN,0,0,0.7,0.2);
    add_container(&layout,TOP,0,0,0.7,0.2);
    add_container(&layout,CENTER,0,0,0.7,0.2);
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RED);
        for (int i = 0; i < layout.count; i++) {
            DrawRectangleRec(layout.items[i].area,BLUE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
