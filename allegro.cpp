#include "declarations.h"

extern ALLEGRO_FONT *arial;
extern ALLEGRO_DISPLAY *display;

// Legend
void DrawLegend(ALLEGRO_COLOR WHITE, ALLEGRO_COLOR GREEN ,ALLEGRO_COLOR RED, ALLEGRO_COLOR YELLOW, ALLEGRO_COLOR PINK, ALLEGRO_COLOR ORANGE) {
    int tempRow = ROWS + 36;
    int numOfSquares = 6;
    ALLEGRO_COLOR colour;

    al_draw_textf(arial, WHITE, columnS / 2, ROWS + 7,
                ALLEGRO_ALIGN_CENTRE, "___________________________________ NIFTY MOUNTAINS LEGEND ___________________________________");
    al_draw_text(arial, RED, 20, ROWS + 33, 0, "Greedy walk starting from at each row");
    for(int i = 0; i < numOfSquares; i++) {

        if(i == 0) {
            colour = RED;
        } else if (i == 1) {
            colour = GREEN;
        } else if (i == 2) {
            colour = PINK;
        } else if (i == 3) {
            colour = ORANGE;
        } else if (i == 4) {
            colour = WHITE;
        } else {
            colour = YELLOW;
        }

        al_draw_filled_rectangle(5, tempRow, 15, tempRow + 10, colour);
        tempRow += 23;
    }
    al_draw_text(arial, WHITE, 10, ROWS + 171, 0, "See console for detailed analysis");
    al_draw_text(arial, RED, columnS / 2, ROWS + 171, ALLEGRO_ALIGN_CENTER, "Press esc (escape) To Quit");
    al_draw_text(arial, WHITE, columnS - 10, ROWS + 171, ALLEGRO_ALIGN_RIGHT, "Program Created by Eric Karpovits");
}

int InitializeAllegro(int width, int height, const char title[]) {

    // Initialize Allegro
	al_init();

	// initialize display
	display = al_create_display(width, height);
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}
	al_set_window_title(display, title);

   	// Initialize keyboard routines
	if (!al_install_keyboard()) {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
   	}

   	// Font add on
    if (!al_init_font_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize font add on!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -1;
    }

    // initialize the ttf (True Type Font) addon
    if (!al_init_ttf_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize font ttf on!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -1;
    }

    arial = al_load_ttf_font("arial.ttf", 16, 0);
    if (!arial){
        al_show_native_message_box(display, "Error", "Error", "Could not load arial.ttf",
                                nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // Initialize primative add on
 	if (!al_init_primitives_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	al_flip_display();
	return 0;
}

// return true when escape key is pressed.
bool EscapeKeypress() {

	ALLEGRO_KEYBOARD_STATE key_state;
	al_get_keyboard_state(&key_state);

    if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE) == true) {
        return true;
    } else {
        return false;
    }
}

