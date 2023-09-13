// Title: The GigaChad Way to Cut a Pizza
// Author: Smith
/* Purpose: Given a radius, this program will output how far one should cut parallel lines from the center
 *          of the pizza (one on either side) such that n slices of equal area are created. 
*/
// Inspiration: https://www.youtube.com/watch?v=IeCxjcMyY-M

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.14159265358979323846264338
#define STEP 0.000001 // step in x values used in numerically approximating distances to cut

int main(void)
{
    int n, nCuts;
    double r; // radius of pizza

    printf("Enter the diameter of the pizza: ");
    scanf("%lf", &r);
    r /= 2;

    printf("Enter the number of slices to cut: ");
    scanf("%d", &n);
    nCuts = n / 2;


    // Determine if n is even or odd
    bool evenSlices = n % 2 == 0? true: false;


    // In relation to a quarter of the pizza, each area value corresponds to the area of pizza below the ith cut
    // ("Below" means towards the center)
    double area[nCuts], cuts[nCuts];

    // if n is even, the first cut will be down the middle (at distance 0), making area[0] = 0
    if (evenSlices) {
        area[0] = 0;
        area[1] = (PI * r * r) / (2 * n);
    }
    else {
        area[0] = (PI * r * r) / (4 * n);
    }
    /* area[1] (if n is even)  and area[0] (if n is odd) differ by a factor of 1/2 because if n is odd,
     * the first area will be split across the middle of the pizza, meaning half of this area will not be 
     * present when calculating from the perspective of a quarter of the pizza.
    */

    // Determine remaining areas
    for (int i = 1; i < nCuts; i++) {
        area[i] = i * ((PI * r * r) / (2 * n)) + area[0];
    }
    
    // Determine remaining cuts 
    for (int i = 0; i < nCuts; i++) {
    double x = 0, y; 
    do 
    {
        y = ((r * r * asin(x / r)) / 2) + ((x * sqrt(r * r - x * x)) / 2);
        x += STEP;
    } 
    while (fabs(y - area[i]) > STEP * 10);

    cuts[i] =  x - STEP;

    }
    
    printf("Make cuts at the following distances from the center:\n");
    
    for (int i = nCuts - 1; i >= evenSlices? 1 : 0; i--) {
        printf("-%lf\n", cuts[i]);
    }
    for (int i = 0; i < nCuts; i++) {
        printf("%lf\n", cuts[i]);
    }

    return 0;
}
