
#include "splashkit.h"
//https://youtu.be/l7cgDCjLSuk
#define NUM_VALS 20

void draw_values(const int values[], int size) 
{
    int x = 0;
    int y;
    int rect_height;
    int rect_width = screen_width() / size;

    for (int i = 0; i < size; i++)
    {
        rect_height = values[i];
        y = screen_height() - rect_height;

        fill_rectangle(COLOR_RED, x, y, rect_width, rect_height);
        draw_rectangle(COLOR_WHITE, x, y, rect_width, rect_height);

        x += rect_width;
    }
}

void draw_sort(int values[], int size)
{
    clear_screen(COLOR_WHITE);
    draw_values(values, size);
    refresh_screen(60);
}
void swap(int &value1, int &value2) //takes the address of two different integer values
{
    int temp = value1; //stores value1 into temporary position //so we haven't lost original value of value1 parameter.
    value1 = value2; //stores value2 into value1
    value2 = temp;  //and value2 into temp, effectively swapping value1 and value2.
}
void bubble_sort(int values[], int size)
{
    for(int j = 0; j < size; j++) //repeat a number of times = to the number of elements in array
    {
        for (int i = 0; i < size - 1; i++) // decrement looping toward the value BEFORE. loop through the array.
        {
            if (values[i] > values[i + 1]) //compares value w/ neighbour. iF CURRENT value in the array is larger than the NEXT value in the array
            {
                swap(values[i], values[i + 1]); //if value is larger, swap value at index [i] to the next position in array, [i+1]
                draw_sort(values, size);
            }
        }
    }
}
void quicksort(int values[], int size)
{
    int i = 0;
    int pivot = 0; //initialise pivot entry point, here first value in the array

    if (size <= 1) //if size of array is less than or equal to 1, array is already sorted!
        {
            return;
        }

    for (int i = 0; i < size; i++)
    {
        if (values[i] < values[size-1])// if value of current element is less than value of last element
        {
            swap(values[i],values[pivot++]);
            draw_sort(values, size); delay(500); //swaps current element to pivot point index increments pivot point, 
        }
    }
    swap(values[i + pivot], values[i + size-1]); //partitioning, swaps elements right of pivot with elements left of pivot point
    draw_sort(values, size); delay(500);
    quicksort(values, pivot++); //recursive sort for elements to the left
    draw_sort(values, size); delay(500);
    quicksort(values + pivot,  size - pivot); //recursive sort for elements to the right
    draw_sort(values, size); delay(500);
}
void random_fill_array(int values[], int size)
{
    for (int i = 0; i < size; i++)
    {
        values[i] = rnd(screen_height()) + 1;
    }
}

void handle_input(int values[], int size)
{
    if (key_typed(R_KEY))
    {
        random_fill_array(values, size);
    }
    else if(key_typed(S_KEY))
    {
        bubble_sort(values, size);
    }
    else if(key_typed(D_KEY))
    {
        quicksort(values, size);
    }
}

int main()
{
    int values[NUM_VALS];

    open_window("Sort Visualiser", 800, 600);

    random_fill_array(values, NUM_VALS);

    while ( not quit_requested() )
    {
        process_events();
        handle_input(values, NUM_VALS);

        draw_sort(values, NUM_VALS);
    }

    return 0;
}