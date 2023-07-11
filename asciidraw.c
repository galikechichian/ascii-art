#include <stdio.h>
#include <string.h>
#include <math.h>

int main() 
{
	char line[100], command[100], canvas[1000][1000];
	int width, height;
	char poz[100] = "Only CHAR command is allowed before the grid size is set.\n";
	char pen = '*';

	while(fgets(line, 100, stdin) != NULL) {
		sscanf(line, "%s", command);
		// printf("Command extracted is: %s\n", command);
		
		if (strcmp(command, "END") == 0) break;

		if(strcmp(command, "GRID") == 0) {
			// printf("GRID command\n");
			if ((width != 0) || (height != 0)) { // if canvas hasn't been set
				printf("GRID was already set to %d,%d\n", width, height);			
			}
			else {
				sscanf(line, "%s %d %d", command, &width, &height);
				// printf("Width and height are: %d %d\n", width, height);
			}
		}

		else if(strcmp(command, "CHAR") == 0) {
			sscanf(line, "%s %c", command, &pen);
		}

		else if(strcmp(command, "DISPLAY") == 0) {
                        // printf("show me da creation\n");
                        if ((width == 0) || (height == 0)) {
                                printf("%s", poz);
                        }
			int i,j;
			for (j = height-1; j >= 0; j--) {
				printf("%d", (j%10));
			       	for (i = 0; i < width; i++) {
					if (canvas[i][j] != 0 ) printf("%c", canvas[i][j]);
					else printf(" "); // bc it doesn't print the 'empty' array slots
				}
				printf("\n");
			}
			printf(" ");
			for(i = 0; i < width; i++) {
				printf("%d", (i%10));
			}
			printf("\n");
		}

		else if(strcmp(command, "RECTANGLE") == 0) {
			if ((width == 0) || (height == 0)) {
				printf("%s", poz);		
			}
			int x1, y1, x2, y2;
			sscanf(line, "%s %d,%d %d,%d", command, &x1, &y1, &x2, &y2);
			
			int i,j;
			for (i = x1; i <= x2; i++) {
				for (j = y2; j <= y1; j++) {
					if ((i == x1) || (i == x2) || (j == y1) || (j == y2)) {
						// check if i and j are within bounds
						// add to the canvas only if it's true
						if ((i >= 0) && (i < width) && (j >= 0) && (j < height)) canvas[i][j] = pen;
					}
				}
			}
		}

		else if(strcmp(command, "LINE") == 0) {
			// printf("LINE command\n");
			if ((width == 0) || (height == 0)) {
                                printf("%s", poz);
                        }
			float x1, y1, x2, y2;
			sscanf(line, "%s %f,%f %f,%f", command, &x1, &y1, &x2, &y2);

			float m  = (y2 - y1)/(x2 - x1);
			// printf("Slope of the line is %f\n", m);

			float c;		// we know y = mx + c
						// so 	   c = y - mx
			c = y1 - (m * x1);
			// printf("Equation of the line is y = %fx + %f\n", m, b);
			int a,b; // to define the increasing interval
				 // between the x-values

			if (x1 < x2) a = x1, b = x2;
			else a = x2, b = x1;
			
			// truncate the bounds a and b to fit the grid width
			if (a < 0) a = 0;
			if (a >= width) a = width - 1;
			if (b < 0) b = 0;
			if (b >= width) b = width - 1;

			int xValue;
			double yfValue;			// float y-value
							// the one we're using
			double  prevY = m * a + c;	// previous y-value, used to
							// ontinuities
			int yValue;
			double yDiff;

			// two  edge cases: 
			// 1. same sets of coords
			if ((x1 == x2) && (y1 == y2)) {
				if ((x1 >= 0) && (x1 < width) && (y1 >= 0) && (y1 < height)) {
					int x = x1;
					int y = y1;
					canvas[x][y] = pen;
				}
				continue;
			}

			// 2. vertical line
			if (x1 == x2) {
				// check if the line's gonna be in the 1st quadrant
				// if not, direcly skip to the next command
				if (x1 < 0) continue;

				if (y1 > y2) {
					// swap values
					int tmp = y1;
					y1 = y2, y2 = tmp;
				}
				int y;
				int x = x1;
				for (y = y1; y <= y2; y++) {
					if ((y >= 0) && (y < height)) canvas[x][y] = pen;
				}
				continue;
			}


			// regular case
			for (xValue = a; xValue <= b; xValue++) {
				yfValue = m * xValue + c;
				yValue = round(yfValue);

				// look for discontinuitues between the y-values
				yDiff = fabs(yValue - prevY);
				int start, end;
				if (yDiff > 1) { // discrete y-values
						 // draw a vertical line
						 // using a loop
					// int start, end;
					// 2 cases: slope either positive or negative
					if (prevY < yValue) {

						start = prevY + 1, end = yValue;
						int y;
                                        	// for (y = start; y <= end; y++) {
                                        	for (y = start; y < end; y++) {
                                                if ((y >= 0) && (y < height)) {
                                                        canvas[xValue][y] = pen;
                                                }
                                                yValue = y;
						}
					}
					else {
						start = prevY - 1, end = yValue;
						int y;
						// for (y = start; y <= end; y++) {
						for (y = start; y >=  end; y--) {
							if ((y >= 0) && (y < height)) {
								canvas[xValue][y] = pen;
							}
						yValue = y;
						}
					}
				}

				else  if ((yValue >= 0) && (yValue < height)) canvas[xValue][yValue] = pen;
				prevY = yValue ;

			}


		}
		else if(strcmp(command, "CIRCLE") == 0) {
			if (((width == 0) || (height == 0))) {
                                printf("%s", poz);
                        }
			int x,y,r;
			sscanf(line, "%s %d,%d %d", command, &x, &y, &r);
			
			int xValue = x;
			int yValue = y + r;
			
			int c1x, c2x, c3x, c1y, c2y, c3y;
                        double width1, height1, width2, height2, width3, height3;
    			double dist1, dist2, dist3;

			int curX = xValue, curY = yValue;

			int topY, bottomY, leftX, rightX;

			while (!((curX == x + r) && (curY == y))) {
				// printf("current x-value is %d\n", curX);
				// curX = xValue;
				// int topY, bottomY, leftX, rightX;
                                topY = curY;
                                bottomY = y - fabs(curY - y);
                                leftX = x - fabs(curX - x);
                                rightX = curX;

                                // 1st quadrant we have: (rightX, topY)
                                // 2nd                   (leftX, topY)
                                // 3rd                   (leftX, bottomY)
                                // 4th                   (rightX, bottomY)

                                if ((rightX >= 0) && (rightX < width) && (topY >= 0) && (topY < height)) canvas[rightX][topY] = pen;
                                if ((leftX >= 0) && (leftX < width) && (topY >= 0) && (topY < height)) canvas[leftX][topY] = pen;
                                if ((leftX >= 0) && (leftX < width) && (bottomY >= 0) && (bottomY < height)) canvas[leftX][bottomY] = pen;
                                if ((rightX >= 0) && (rightX < width) && (bottomY >= 0) && (bottomY < height)) canvas[rightX][bottomY] = pen;
				

				// canvas is now marked.
				// we'll set up the coords of the following pixel
				
				c1x = curX + 1;
				c1y = curY;
				width1 = fabs(c1x - x);
				height1 = fabs(c1y - y);
				dist1 = sqrt((pow((width1), 2)) + (pow((height1), 2)));
				// printf("c1 coords are (%d, %d)\n", c1x, c1y);
				// printf("distance from c1 to origin is %f\n", dist1);

				c2x = curX + 1;
				c2y = curY - 1;
				width2 = fabs(c2x - x);
				height2 = fabs(c2y - y);
				dist2 = sqrt((pow((width2), 2)) + (pow((height2), 2)));
				// printf("distance from c2 to origin is %f\n", dist2);
				// printf("c2 coords are (%d, %d)\n", c2x, c2y);

				c3x = curX;
				c3y = curY - 1;
				width3 = fabs(c3x - x);
				height3 = fabs(c3y - y);
				dist3 = sqrt((pow((width3), 2)) + (pow((height3), 2)));
				// printf("distance from c3 to origin is %f\n", dist3);
				// printf("c3 coords are (%d, %d)\n", c3x, c3y);

				double c[3][3] = {{c1x, c1y, dist1},{c2x, c2y, dist2}, {c3x, c3y, dist3}};
				double minDiff = r + 1;
				for (int i = 0; i < 3; i++) {
					if (fabs(c[i][2] - r) < minDiff) {
						curX = c[i][0];
						curY = c[i][1];
						minDiff = fabs(c[i][2] - r);
					}
				
				}
				// now we found the c point (x and y coords)
				// printf("next c coords are then (%d, %d)\n", curX, curY);
					
				// printf("\n");
				
			}

			// we want to mark the last two remaining points
			// (x+r, y) and (x-r, y)
			if ((x + r >= 0) && (x + r < width) && (curY >= 0) && (curY < height)) canvas[x + r][curY] = pen;
			if ((x - r >= 0) && (x - r < width) && (curY >= 0) && (curY < height)) canvas[x  - r][curY] = pen;
	
		}
		
		else { // invalid command
			printf("Error did not understand %s", line);
		}


	}

	return 0;

}

