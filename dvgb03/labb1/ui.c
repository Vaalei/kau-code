#include "ui.h"
#include "io.h"
#include "analyze.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARRAY_LENGTH 10
#define ENUM_COUNT 5

//
// Private
//

typedef enum {
	n_o,
	logn_o,
	nlogn_o,
	n2_o,
	n3_o
} big_o_name;


typedef struct {
	int size;
	big_o_name type;
	char* name;
	double mean_diff;
} big_o;

void changename(char* name, big_o_name big_o)
{
	switch (big_o)
	{
	case n_o:
		strcpy(name, "O(N)\t");
		break;
	case logn_o:
		strcpy(name, "O(logN)\t");
		break;
	case nlogn_o:
		strcpy(name, "O(NlogN)");
		break;
	case n2_o:
		strcpy(name, "O(N^2)\t");
		break;
	case n3_o:
		strcpy(name, "O(N^3)\t");
		break;
	}
}

double diff_from_avg(double input, double avg)
{
	return fabs(avg-input);
}

void swap_category(big_o *p1, big_o *p2)
{
	big_o t = *p1;
	*p1 = *p2;
	*p2 = t;
}

// Sorting categories with bubble sort
void sort_category(big_o *a, int n)
{
	int exp_a, exp_b;
	for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j< n-i-1; j++)
		{
			frexp(a[j].mean_diff, &exp_a);
			frexp(a[j+1].mean_diff, &exp_b);
			if ( fabs(exp_a) > fabs(exp_b)) {
				swap_category(&a[j], &a[j+1]);
			}
		}
	}
}

double calculate(double input, int size, big_o_name type)
{
	double x;
	switch (type)
		{
		case n_o:
			x = input/size;
			break;
		case logn_o:
			x = input/log2(size);
			break;
		case nlogn_o:
			x = input/(size*log2(size));
			break;
		case n2_o:
			x = input/pow(size,2);
			break;
		case n3_o:
			x = input/pow(size,3);
			break;
		default:
			break;
		}
	return x;
}

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
	big_o category[RESULT_ROWS];
	char choice;
	double sum;
	double temp;
	double mean;
	double calculated_result[RESULT_ROWS];

	show_menu = true;
	running = true;

	for (int i = 0; i < RESULT_ROWS; i++)
	{
		category[i].name = malloc(10 * sizeof(char));
	}
	

	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		choice = ui_get_choice();
		ui_line('*', MENU_WIDTH);
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

		ui_line('~', MENU_WIDTH);


		// calculate time / bigo
		// 
		//
		//

		// I is the enum for the different big o notations (big_o)
		for (int i = 0; i < ENUM_COUNT; i++)
		{
			if (false)
				printf("%d",category[i].size);	
				
			
			category[i].type = i;
			sum = 0;
			
			for (int j = 0; j < RESULT_ROWS; j++)
			{
				temp = calculate(result[j].time, result[j].size, i);
				sum += temp;
				calculated_result[j] = temp;
			}
			mean = sum/RESULT_ROWS;

			sum = 0;
			for (int j = 0; j < RESULT_ROWS; j++)
			{
				sum += diff_from_avg(calculated_result[j], mean);
			}
			category[i].mean_diff = sum/RESULT_ROWS;
			changename(category[i].name, i);
		}

		// Sort array of big_o's, lowest mean_diff comes first 
		sort_category(category, ENUM_COUNT);

		printf(
			"Size\tTime\t\t%s\t%s\t%s\n",
			category[0].name,
			category[1].name,
			category[2].name
		);
		for (int j = 0; j < RESULT_ROWS; j++)
		{
			printf(
				"%d\t%e\t%e\t%e\t%e\n",
				result[j].size, 
				result[j].time, 
				calculate(result[j].time, result[j].size, category[0].type),
				calculate(result[j].time, result[j].size, category[1].type),
				calculate(result[j].time, result[j].size, category[2].type)
			);
		}
		ui_line('~', MENU_WIDTH);
	}
	ui_exit();
}
