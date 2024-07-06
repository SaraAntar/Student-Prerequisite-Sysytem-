#include <graphics.h>
#include <iostream>
#include <math.h>
#include <sstream>
using namespace std;

// Function that prints Tree using
// functions graphic.h header file
void printTree(int x, int y, int* array, int index, int numbers)
{

    // Base Case
    if (index >= numbers)
        return ;

    // Convert int value into string
    ostringstream str1;
    str1 << array[index];

    string str2 = str1.str();
    char* str = &str2[0u];

    // Set color of the boundary of circle as green
    setcolor(GREEN);

    // Draw the circle of radius 25 that represent node of Tree
    circle(x, y, 25);
    floodfill(x, y, GREEN);

    // Print the values of the node in the circle
    outtextxy(x - 2, y - 3, str);

    // Set the color of the line from parent to child as green
    setcolor(GREEN);

    // Evaluating left and right child
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Recursively draw the left subtree and the right subtree
    printTree(x - y / (index + 1), y + 50,
              array, left, numbers);

    printTree(x + y / (index + 1), y + 50,
              array, right, numbers);

    // Draw the line (or link) when the node is not the leaf node
    if (left < numbers) {
        line(x, y, x - y / (index + 1), y + 50);
    }

    if (right < numbers) {
        line(x, y, x + y / (index + 1), y + 50);
    }

    return ;
}

// Driver Code
int main()
{
    int tree[5];
    int t;
    int n;

    cout << "Enter the number of courses you took and want to take: " <<endl;
    cin>> t;

    for (int i =0; i < t; i++)
    {
        cout<< "Enter the courses you have took then the courses you wanted to take: " << i <<endl;
        cin >> tree[i];
    }


    // Initialize graphic driver
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "None");

 // Given array a Function Call
    printTree(300, 100, tree, 0, 5);
    getch();

    closegraph();
}