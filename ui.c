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

typedef enum {
  VERTICAL,
  HORIZONTAL,
  NONE
} Orientation;

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
  Color background;
  float padding;

  //Si element sigue siendo un puntero es algo que esta por verse.
  Element *element;
  int count;
  int capacity;

 
} Container;



typedef struct {
  Container *items;
  int count;
  int capacity;

  float padding;
  float gap;

  Aling aling;
  Orientation ori;


} Wrapper;


Container* alloc_container()
{
  return (malloc(INITIAL_CAPACITY * sizeof(Container)));
}

Wrapper init_wrapper()
{
  Wrapper init = {
	.count = 0,
	.capacity = INITIAL_CAPACITY,
	.padding = 0.f,
	.gap = 0
  };
  
  init.items = alloc_container();
  return init;
}





int main()
{
  Wrapper layout = init_wrapper();
  InitWindow(WIDTH,HEIGHT,"Diseño UI");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
	BeginDrawing();
	ClearBackground(RED);
	EndDrawing();
  }
  CloseWindow();
  return 0;
}
