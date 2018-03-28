#ifndef _TERM_H_
#define _TERM_H_

#include "Window.h"

class TermScreen : public Window {

private:
	static TermScreen* m_screen;

	TermScreen();
	TermScreen(const TermScreen&);
	TermScreen& operator=(const TermScreen&);

public:
	~TermScreen();

	static TermScreen* getInstance();
};

class Term {

public:
	static Window scr;

	static void init_curs();
	static void end_curs();

	static void save_state();
	static void load_state();

	static void cooked_mode(bool on);
	static void echo_key(bool on);

	static void curs_vis(int vis);
	
	static void wait(int ms);

/* pop/push an input for the next call to the input queue */
	static int pop_input();
	static void push_input(int input); 

/* Renvoie un chaine de character taper par l'untilisateur dans str */
	static void getline(std::string& str);

/* Pointeur vers la fonction scanw */
	//static int (*scan)(const char*, ...);

/* update the terminal displays */
	static void update();

};

#endif