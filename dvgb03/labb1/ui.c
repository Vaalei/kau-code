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
	char choice;

	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		choice = ui_get_choice();
		ui_star('*', MENU_WIDTH);
		switch (choice) {
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
				printf("Bubble sort: best case\n");
				benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
				break;

			// Bubble sort worst case
			case 'd':
				printf("Bubble sort: Worst Case\n");
				benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
				break;
				
			// Bubble sort average case\n
			case 'e':
				printf("Bubble Sort: Average Case\n");
				benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
				break;

			// Insertion sort best case
			case 'f':
				printf("Insertion Sort: Best Case\n");
				benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
				break;

			// Insertion sort worst case
			case 'g':
				printf("Insertion Sort: Worst Case\n");
				benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
				break;

			// Insertion sort average case\n
			case 'h':
				printf("Insertion Sort: Average Case\n");
				benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
				break;

			// Quick sort best case
			case 'i':
				printf("Quick sort: Best Case\n");
				benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
				break;

			// Quick sort worst case
			case 'j':
				printf("Quick sort: Worst case\n");
				benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
				break;

			// Quick sort average case\n
			case 'k':
				printf("Quick sort: Average case\n");
				benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
				break;

			// Linear search best case
			case 'l':
				printf("Linear search: Best case\n");
				benchmark(linear_search_t, best_t, result, RESULT_ROWS);
				break;

			// Linear search worst case
			case 'm':
				printf("Linear search: worst case\n");
				benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
				break;

			// Linear search average case\n
			case 'n':
				printf("Linear search: Average case\n");
				benchmark(linear_search_t, average_t, result, RESULT_ROWS);
				break;

			// Binary search best case
			case 'o':
				printf("Binary search: Best case\n");
				benchmark(binary_search_t, best_t, result, RESULT_ROWS);
				break;

			// Binary search worst case
			case 'p':
				printf("Binary search: Worst case\n");
				benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
				break;

			// Binary search average cas
			case 'q':
				printf("Binary search: Average case\n");
				benchmark(binary_search_t, average_t, result, RESULT_ROWS);
				break;

			// Invalid input
			default:
				show_menu = false;
				ui_invalid_input();
				break;
		}

		ui_squiggly('~', MENU_WIDTH);
		printf("\n");

	}
	ui_exit();
}
