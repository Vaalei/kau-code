#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>

//
// Private
//
static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0) {
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i=0; i<num_options; i++) {
		printf("    %c) %s\n", 'a'+i, options[i]);
	}
}

static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort average case\n",
		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort average case\n",
		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort average case\n",
		"Linear search best case",
		"Linear search worst case",
		"Linear search average case\n",
		"Binary search best case",
		"Binary search worst case",
		"Binary search average case"
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

//
// Public
//
void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];
	
	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice()) {
			// House keeping
			case 'a':
				show_menu = true;
				break;

			// Exit
			case 'b':
				running = false;
				break;

			// Bubble sort best case
			case 'c':
				benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
				printf("todo> implemenet BE + present results in FE\n");
				break;

			// Bubble sort worst case
			case 'd':
				break;
				
			// Bubble sort average case\n
			case 'e':
				break;

			// Insertion sort best case
			case 'f':
				break;

			// Insertion sort worst case
			case 'g':
				break;

			// Insertion sort average case\n
			case 'h':
				break;

			// Quick sort best case
			case 'i':
				break;

			// Quick sort worst case
			case 'j':
				break;

			// Quick sort average case\n
			case 'k':
				break;

			// Linear search best case
			case 'l':
				break;

			// Linear search worst case
			case 'm':
				break;

			// Linear search average case\n
			case 'n':
				break;

			// Binary search best case
			case 'o':
				break;

			// Binary search worst case
			case 'p':
				break;

			// Binary search average cas
			case 'q':
				break;

			// Invalid input
			default:
				show_menu = false;
				ui_invalid_input();
				break;
		}
	}
	ui_exit();
}
