#include <cstdlib>
#include <cstdio>

#include "Turtle.h"

using namespace std;

void handler(int ch, Vector2i& position, IntRect& offset);

void draw_von_koch_rec(Turtle& T, float length, int prof){
	if(prof == 0){
		T.draw(length);
	}	
	else{
		draw_von_koch_rec(T, length/3, prof-1); T.turn(60);	
	    draw_von_koch_rec(T, length/3, prof-1); T.turn(-120);
	    draw_von_koch_rec(T, length/3, prof-1); T.turn(60);
	    draw_von_koch_rec(T, length/3, prof-1); 
	}
}

void draw_von_koch(Canvas& c, const Vector2i& pos, float length, int prof){
	Turtle T(&c);

	T.set_position(pos.x, pos.y);

	draw_von_koch_rec(T, length, prof);
}


void draw_poly_von_koch(Canvas& canvas, Vector2f center, int sides, float radius, float rotation, float prof){
	
	Turtle T(&canvas);

	float angle = float(360) / sides;
	float length = 2 * radius * sin(M_PI / float(sides));
	float inradius = radius * cos(M_PI / float(sides));
	Vector2f offset(length / 2.0, inradius);

	//canvas->set(round(center.x), round(center.y));

	T.set_position(center);
	T.turn(rotation);

	T.move(-length / 2.0);
	T.turn(90);
	T.move(-inradius);
	T.turn(-90);

	for(int i = 0 ; i < sides ; i++){
		draw_von_koch_rec(T, length, prof);
		T.turn(angle);
	}
}

int main(int argc, char** argv)
{

	int sides = 3;
	float radius = 46;
	float rotation = 0;
	int prof = 0;

	if(argc > 1)
		sides = atoi(argv[1]);

	if(argc > 2)
		radius = atof(argv[2]);

	if(argc > 3)
		rotation = atof(argv[3]);

	if(argc > 4)
		prof = atoi(argv[4]);

	Vector2f center(radius, radius);
    
	Term::init_curs();

    int k = radius * 2 + 1;
	Canvas canvas(k, k);

	//(radius * 2 + 1, radius * 2 + 1);
	canvas.set_on(ColorPair::Red);
	canvas.set(canvas.get_size() - Vector2i::one);
	canvas.set_off(ColorPair::Red);
	/*
	for(int i = 0 ; i < canvas.get_size().x; i++){
		for(int j = 0 ; j < canvas.get_size().y ; j++){
			canvas.set(i, j);
		}
	}
	*/
	

	mvwprintw(stdscr, 0, 0, "Canvas.size = (%d, %d)", canvas.get_size().x, canvas.get_size().y);
	mvwprintw(stdscr, 1, 0, "Canvas.dimension = (%d, %d)", canvas.get_dimension().x, canvas.get_dimension().y);

	canvas.set_color(ColorPair::Green);
	canvas.set_attr(Attr::Bright);

	Vector2i p1(10, 20);
	Vector2i p2(135, 97);


	//draw_von_koch(canvas, Vector2i(0, 100), 530, 4);
	
	draw_poly_von_koch(canvas, center, sides, radius, rotation, prof);

	//Turtle T(&canvas);

	//T.turn(45);
	//T.draw(1000);

	Vector2i printposition(0, 0);
	IntRect canvasoffset(Vector2i::zero, Term::scr.get_dimension());

	//canvas.fill(Cell('+'));
	int c = 0;

	canvas.display(Vector2i(0, 0));
	Term::update();

	//Term::pop_input();


	while((c = Term::pop_input()) != 'q'){
		Term::scr.clear();
		Term::scr.display();
		handler(c, printposition, canvasoffset);
		canvas.display(printposition, canvasoffset);
		Term::update();
	}

	Term::end_curs();
	
	return 0;
}

void handler(int ch, Vector2i& position, IntRect& offset){

	int spd = 5;

	if(ch == KEY_UP){
		position.y += -spd;
	}
	else if(ch == KEY_DOWN){
		position.y += spd;
	}	
	else if(ch == KEY_LEFT){
		position.x += -spd;
	}	
	else if(ch == KEY_RIGHT){
		position.x += spd;
	}	
	else if(ch == 'e'){ //up
		offset.y += -spd;
	}
	else if(ch == 'd'){ //down
		offset.y += spd;	
	}	
	else if(ch == 's'){ //left
		offset.x += -spd;
	}	
	else if(ch == 'f'){ //right
		offset.x += spd;
	}	
}