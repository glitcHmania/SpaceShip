#include "Rock.h"
#include "Ship.h"

void Rock::Init(float in_x, float in_y)
{
	x = in_x;
	y = in_y;
}

void Rock::Draw(Graphics& gfx)
{
	if (
		x + width < gfx.ScreenWidth &&
		x>0 &&
		y + height < gfx.ScreenHeight &&
		y>0
		)
	{
		int x_int = int(x);
		int y_int = int(y);
		gfx.PutPixel(6 + x_int, 0 + y_int, 33, 27, 8);
		gfx.PutPixel(7 + x_int, 0 + y_int, 88, 74, 23);
		gfx.PutPixel(8 + x_int, 0 + y_int, 81, 68, 21);
		gfx.PutPixel(9 + x_int, 0 + y_int, 81, 68, 21);
		gfx.PutPixel(10 + x_int, 0 + y_int, 81, 68, 21);
		gfx.PutPixel(11 + x_int, 0 + y_int, 83, 70, 22);
		gfx.PutPixel(12 + x_int, 0 + y_int, 84, 70, 22);
		gfx.PutPixel(13 + x_int, 0 + y_int, 22, 18, 6);
		gfx.PutPixel(4 + x_int, 1 + y_int, 46, 39, 11);
		gfx.PutPixel(5 + x_int, 1 + y_int, 55, 46, 14);
		gfx.PutPixel(6 + x_int, 1 + y_int, 65, 54, 17);
		gfx.PutPixel(7 + x_int, 1 + y_int, 85, 72, 22);
		gfx.PutPixel(8 + x_int, 1 + y_int, 82, 69, 21);
		gfx.PutPixel(9 + x_int, 1 + y_int, 82, 68, 21);
		gfx.PutPixel(10 + x_int, 1 + y_int, 81, 68, 21);
		gfx.PutPixel(11 + x_int, 1 + y_int, 82, 69, 21);
		gfx.PutPixel(12 + x_int, 1 + y_int, 82, 69, 21);
		gfx.PutPixel(13 + x_int, 1 + y_int, 60, 50, 16);
		gfx.PutPixel(14 + x_int, 1 + y_int, 57, 48, 15);
		gfx.PutPixel(15 + x_int, 1 + y_int, 42, 35, 10);
		gfx.PutPixel(2 + x_int, 2 + y_int, 13, 11, 3);
		gfx.PutPixel(3 + x_int, 2 + y_int, 42, 34, 11);
		gfx.PutPixel(4 + x_int, 2 + y_int, 84, 70, 21);
		gfx.PutPixel(5 + x_int, 2 + y_int, 92, 77, 24);
		gfx.PutPixel(6 + x_int, 2 + y_int, 83, 71, 22);
		gfx.PutPixel(7 + x_int, 2 + y_int, 75, 63, 19);
		gfx.PutPixel(8 + x_int, 2 + y_int, 77, 65, 20);
		gfx.PutPixel(9 + x_int, 2 + y_int, 80, 68, 21);
		gfx.PutPixel(10 + x_int, 2 + y_int, 81, 69, 21);
		gfx.PutPixel(11 + x_int, 2 + y_int, 81, 68, 21);
		gfx.PutPixel(12 + x_int, 2 + y_int, 81, 68, 21);
		gfx.PutPixel(13 + x_int, 2 + y_int, 87, 73, 23);
		gfx.PutPixel(14 + x_int, 2 + y_int, 94, 79, 25);
		gfx.PutPixel(15 + x_int, 2 + y_int, 80, 68, 21);
		gfx.PutPixel(16 + x_int, 2 + y_int, 39, 33, 9);
		gfx.PutPixel(17 + x_int, 2 + y_int, 2, 2, 1);
		gfx.PutPixel(0 + x_int, 3 + y_int, 2, 1, 0);
		gfx.PutPixel(1 + x_int, 3 + y_int, 10, 9, 3);
		gfx.PutPixel(2 + x_int, 3 + y_int, 51, 44, 13);
		gfx.PutPixel(3 + x_int, 3 + y_int, 91, 77, 23);
		gfx.PutPixel(4 + x_int, 3 + y_int, 83, 69, 21);
		gfx.PutPixel(5 + x_int, 3 + y_int, 78, 67, 21);
		gfx.PutPixel(6 + x_int, 3 + y_int, 68, 59, 17);
		gfx.PutPixel(7 + x_int, 3 + y_int, 61, 52, 15);
		gfx.PutPixel(8 + x_int, 3 + y_int, 66, 56, 16);
		gfx.PutPixel(9 + x_int, 3 + y_int, 75, 65, 20);
		gfx.PutPixel(10 + x_int, 3 + y_int, 81, 69, 21);
		gfx.PutPixel(11 + x_int, 3 + y_int, 81, 68, 21);
		gfx.PutPixel(12 + x_int, 3 + y_int, 81, 68, 21);
		gfx.PutPixel(13 + x_int, 3 + y_int, 81, 68, 21);
		gfx.PutPixel(14 + x_int, 3 + y_int, 81, 68, 21);
		gfx.PutPixel(15 + x_int, 3 + y_int, 84, 71, 22);
		gfx.PutPixel(16 + x_int, 3 + y_int, 88, 74, 23);
		gfx.PutPixel(17 + x_int, 3 + y_int, 29, 25, 8);
		gfx.PutPixel(18 + x_int, 3 + y_int, 5, 4, 1);
		gfx.PutPixel(0 + x_int, 4 + y_int, 11, 9, 3);
		gfx.PutPixel(1 + x_int, 4 + y_int, 53, 45, 14);
		gfx.PutPixel(2 + x_int, 4 + y_int, 86, 71, 22);
		gfx.PutPixel(3 + x_int, 4 + y_int, 82, 69, 21);
		gfx.PutPixel(4 + x_int, 4 + y_int, 82, 69, 21);
		gfx.PutPixel(5 + x_int, 4 + y_int, 71, 60, 18);
		gfx.PutPixel(6 + x_int, 4 + y_int, 58, 49, 14);
		gfx.PutPixel(7 + x_int, 4 + y_int, 54, 46, 13);
		gfx.PutPixel(8 + x_int, 4 + y_int, 58, 49, 14);
		gfx.PutPixel(9 + x_int, 4 + y_int, 70, 59, 18);
		gfx.PutPixel(10 + x_int, 4 + y_int, 79, 67, 21);
		gfx.PutPixel(11 + x_int, 4 + y_int, 82, 68, 21);
		gfx.PutPixel(12 + x_int, 4 + y_int, 81, 68, 21);
		gfx.PutPixel(13 + x_int, 4 + y_int, 81, 68, 21);
		gfx.PutPixel(14 + x_int, 4 + y_int, 81, 68, 21);
		gfx.PutPixel(15 + x_int, 4 + y_int, 81, 68, 21);
		gfx.PutPixel(16 + x_int, 4 + y_int, 81, 68, 21);
		gfx.PutPixel(17 + x_int, 4 + y_int, 85, 71, 22);
		gfx.PutPixel(18 + x_int, 4 + y_int, 38, 32, 10);
		gfx.PutPixel(0 + x_int, 5 + y_int, 5, 4, 1);
		gfx.PutPixel(1 + x_int, 5 + y_int, 57, 48, 15);
		gfx.PutPixel(2 + x_int, 5 + y_int, 93, 77, 24);
		gfx.PutPixel(3 + x_int, 5 + y_int, 81, 68, 21);
		gfx.PutPixel(4 + x_int, 5 + y_int, 82, 69, 21);
		gfx.PutPixel(5 + x_int, 5 + y_int, 70, 59, 18);
		gfx.PutPixel(6 + x_int, 5 + y_int, 57, 47, 14);
		gfx.PutPixel(7 + x_int, 5 + y_int, 53, 44, 12);
		gfx.PutPixel(8 + x_int, 5 + y_int, 57, 48, 14);
		gfx.PutPixel(9 + x_int, 5 + y_int, 70, 58, 18);
		gfx.PutPixel(10 + x_int, 5 + y_int, 80, 67, 22);
		gfx.PutPixel(11 + x_int, 5 + y_int, 82, 69, 21);
		gfx.PutPixel(12 + x_int, 5 + y_int, 81, 69, 21);
		gfx.PutPixel(13 + x_int, 5 + y_int, 81, 69, 21);
		gfx.PutPixel(14 + x_int, 5 + y_int, 81, 69, 21);
		gfx.PutPixel(15 + x_int, 5 + y_int, 82, 69, 21);
		gfx.PutPixel(16 + x_int, 5 + y_int, 81, 68, 21);
		gfx.PutPixel(17 + x_int, 5 + y_int, 95, 79, 24);
		gfx.PutPixel(18 + x_int, 5 + y_int, 39, 33, 11);
		gfx.PutPixel(0 + x_int, 6 + y_int, 40, 33, 10);
		gfx.PutPixel(1 + x_int, 6 + y_int, 67, 56, 17);
		gfx.PutPixel(2 + x_int, 6 + y_int, 86, 72, 22);
		gfx.PutPixel(3 + x_int, 6 + y_int, 81, 68, 21);
		gfx.PutPixel(4 + x_int, 6 + y_int, 82, 69, 21);
		gfx.PutPixel(5 + x_int, 6 + y_int, 75, 63, 20);
		gfx.PutPixel(6 + x_int, 6 + y_int, 65, 54, 17);
		gfx.PutPixel(7 + x_int, 6 + y_int, 62, 51, 14);
		gfx.PutPixel(8 + x_int, 6 + y_int, 65, 56, 17);
		gfx.PutPixel(9 + x_int, 6 + y_int, 76, 63, 20);
		gfx.PutPixel(10 + x_int, 6 + y_int, 81, 68, 21);
		gfx.PutPixel(11 + x_int, 6 + y_int, 79, 66, 20);
		gfx.PutPixel(12 + x_int, 6 + y_int, 77, 65, 20);
		gfx.PutPixel(13 + x_int, 6 + y_int, 75, 64, 20);
		gfx.PutPixel(14 + x_int, 6 + y_int, 77, 65, 20);
		gfx.PutPixel(15 + x_int, 6 + y_int, 79, 66, 20);
		gfx.PutPixel(16 + x_int, 6 + y_int, 80, 67, 21);
		gfx.PutPixel(17 + x_int, 6 + y_int, 86, 72, 22);
		gfx.PutPixel(18 + x_int, 6 + y_int, 57, 48, 15);
		gfx.PutPixel(19 + x_int, 6 + y_int, 33, 28, 9);
		gfx.PutPixel(0 + x_int, 7 + y_int, 87, 73, 23);
		gfx.PutPixel(1 + x_int, 7 + y_int, 83, 70, 22);
		gfx.PutPixel(2 + x_int, 7 + y_int, 80, 67, 21);
		gfx.PutPixel(3 + x_int, 7 + y_int, 81, 68, 21);
		gfx.PutPixel(4 + x_int, 7 + y_int, 81, 68, 21);
		gfx.PutPixel(5 + x_int, 7 + y_int, 80, 67, 21);
		gfx.PutPixel(6 + x_int, 7 + y_int, 76, 63, 20);
		gfx.PutPixel(7 + x_int, 7 + y_int, 74, 61, 18);
		gfx.PutPixel(8 + x_int, 7 + y_int, 76, 66, 21);
		gfx.PutPixel(9 + x_int, 7 + y_int, 81, 69, 21);
		gfx.PutPixel(10 + x_int, 7 + y_int, 79, 66, 20);
		gfx.PutPixel(11 + x_int, 7 + y_int, 72, 60, 18);
		gfx.PutPixel(12 + x_int, 7 + y_int, 67, 56, 17);
		gfx.PutPixel(13 + x_int, 7 + y_int, 65, 54, 16);
		gfx.PutPixel(14 + x_int, 7 + y_int, 67, 56, 16);
		gfx.PutPixel(15 + x_int, 7 + y_int, 72, 60, 18);
		gfx.PutPixel(16 + x_int, 7 + y_int, 77, 64, 21);
		gfx.PutPixel(17 + x_int, 7 + y_int, 79, 66, 21);
		gfx.PutPixel(18 + x_int, 7 + y_int, 85, 71, 22);
		gfx.PutPixel(19 + x_int, 7 + y_int, 88, 74, 23);
		gfx.PutPixel(0 + x_int, 8 + y_int, 81, 68, 21);
		gfx.PutPixel(1 + x_int, 8 + y_int, 81, 68, 21);
		gfx.PutPixel(2 + x_int, 8 + y_int, 81, 68, 21);
		gfx.PutPixel(3 + x_int, 8 + y_int, 81, 68, 21);
		gfx.PutPixel(4 + x_int, 8 + y_int, 81, 68, 21);
		gfx.PutPixel(5 + x_int, 8 + y_int, 81, 68, 21);
		gfx.PutPixel(6 + x_int, 8 + y_int, 81, 68, 21);
		gfx.PutPixel(7 + x_int, 8 + y_int, 80, 68, 21);
		gfx.PutPixel(8 + x_int, 8 + y_int, 81, 68, 21);
		gfx.PutPixel(9 + x_int, 8 + y_int, 79, 67, 21);
		gfx.PutPixel(10 + x_int, 8 + y_int, 73, 61, 18);
		gfx.PutPixel(11 + x_int, 8 + y_int, 63, 53, 15);
		gfx.PutPixel(12 + x_int, 8 + y_int, 57, 48, 14);
		gfx.PutPixel(13 + x_int, 8 + y_int, 56, 47, 13);
		gfx.PutPixel(14 + x_int, 8 + y_int, 57, 48, 14);
		gfx.PutPixel(15 + x_int, 8 + y_int, 63, 53, 16);
		gfx.PutPixel(16 + x_int, 8 + y_int, 73, 62, 18);
		gfx.PutPixel(17 + x_int, 8 + y_int, 80, 67, 21);
		gfx.PutPixel(18 + x_int, 8 + y_int, 81, 68, 21);
		gfx.PutPixel(19 + x_int, 8 + y_int, 79, 66, 20);
		gfx.PutPixel(0 + x_int, 9 + y_int, 81, 68, 21);
		gfx.PutPixel(1 + x_int, 9 + y_int, 81, 68, 21);
		gfx.PutPixel(2 + x_int, 9 + y_int, 81, 68, 21);
		gfx.PutPixel(3 + x_int, 9 + y_int, 81, 68, 21);
		gfx.PutPixel(4 + x_int, 9 + y_int, 81, 68, 21);
		gfx.PutPixel(5 + x_int, 9 + y_int, 81, 68, 21);
		gfx.PutPixel(6 + x_int, 9 + y_int, 81, 68, 21);
		gfx.PutPixel(7 + x_int, 9 + y_int, 82, 68, 21);
		gfx.PutPixel(8 + x_int, 9 + y_int, 81, 68, 21);
		gfx.PutPixel(9 + x_int, 9 + y_int, 78, 65, 20);
		gfx.PutPixel(10 + x_int, 9 + y_int, 67, 56, 17);
		gfx.PutPixel(11 + x_int, 9 + y_int, 57, 47, 13);
		gfx.PutPixel(12 + x_int, 9 + y_int, 54, 45, 13);
		gfx.PutPixel(13 + x_int, 9 + y_int, 54, 45, 13);
		gfx.PutPixel(14 + x_int, 9 + y_int, 53, 44, 13);
		gfx.PutPixel(15 + x_int, 9 + y_int, 57, 47, 14);
		gfx.PutPixel(16 + x_int, 9 + y_int, 67, 56, 16);
		gfx.PutPixel(17 + x_int, 9 + y_int, 76, 64, 20);
		gfx.PutPixel(18 + x_int, 9 + y_int, 80, 67, 21);
		gfx.PutPixel(19 + x_int, 9 + y_int, 79, 66, 20);
		gfx.PutPixel(0 + x_int, 10 + y_int, 81, 68, 21);
		gfx.PutPixel(1 + x_int, 10 + y_int, 81, 68, 21);
		gfx.PutPixel(2 + x_int, 10 + y_int, 81, 68, 21);
		gfx.PutPixel(3 + x_int, 10 + y_int, 81, 68, 21);
		gfx.PutPixel(4 + x_int, 10 + y_int, 81, 68, 21);
		gfx.PutPixel(5 + x_int, 10 + y_int, 81, 68, 21);
		gfx.PutPixel(6 + x_int, 10 + y_int, 81, 68, 21);
		gfx.PutPixel(7 + x_int, 10 + y_int, 81, 68, 21);
		gfx.PutPixel(8 + x_int, 10 + y_int, 81, 68, 21);
		gfx.PutPixel(9 + x_int, 10 + y_int, 77, 63, 20);
		gfx.PutPixel(10 + x_int, 10 + y_int, 65, 54, 17);
		gfx.PutPixel(11 + x_int, 10 + y_int, 55, 45, 13);
		gfx.PutPixel(12 + x_int, 10 + y_int, 54, 45, 13);
		gfx.PutPixel(13 + x_int, 10 + y_int, 54, 45, 13);
		gfx.PutPixel(14 + x_int, 10 + y_int, 53, 44, 13);
		gfx.PutPixel(15 + x_int, 10 + y_int, 55, 45, 13);
		gfx.PutPixel(16 + x_int, 10 + y_int, 63, 53, 16);
		gfx.PutPixel(17 + x_int, 10 + y_int, 74, 62, 20);
		gfx.PutPixel(18 + x_int, 10 + y_int, 80, 67, 21);
		gfx.PutPixel(19 + x_int, 10 + y_int, 80, 67, 20);
		gfx.PutPixel(0 + x_int, 11 + y_int, 82, 69, 22);
		gfx.PutPixel(1 + x_int, 11 + y_int, 82, 69, 21);
		gfx.PutPixel(2 + x_int, 11 + y_int, 81, 68, 21);
		gfx.PutPixel(3 + x_int, 11 + y_int, 81, 68, 21);
		gfx.PutPixel(4 + x_int, 11 + y_int, 81, 68, 21);
		gfx.PutPixel(5 + x_int, 11 + y_int, 81, 68, 21);
		gfx.PutPixel(6 + x_int, 11 + y_int, 81, 67, 21);
		gfx.PutPixel(7 + x_int, 11 + y_int, 81, 68, 21);
		gfx.PutPixel(8 + x_int, 11 + y_int, 81, 68, 21);
		gfx.PutPixel(9 + x_int, 11 + y_int, 77, 65, 20);
		gfx.PutPixel(10 + x_int, 11 + y_int, 67, 56, 17);
		gfx.PutPixel(11 + x_int, 11 + y_int, 57, 47, 13);
		gfx.PutPixel(12 + x_int, 11 + y_int, 54, 45, 13);
		gfx.PutPixel(13 + x_int, 11 + y_int, 54, 45, 13);
		gfx.PutPixel(14 + x_int, 11 + y_int, 53, 44, 13);
		gfx.PutPixel(15 + x_int, 11 + y_int, 56, 46, 13);
		gfx.PutPixel(16 + x_int, 11 + y_int, 65, 55, 16);
		gfx.PutPixel(17 + x_int, 11 + y_int, 75, 62, 20);
		gfx.PutPixel(18 + x_int, 11 + y_int, 82, 69, 21);
		gfx.PutPixel(19 + x_int, 11 + y_int, 83, 70, 22);
		gfx.PutPixel(0 + x_int, 12 + y_int, 84, 70, 22);
		gfx.PutPixel(1 + x_int, 12 + y_int, 82, 69, 21);
		gfx.PutPixel(2 + x_int, 12 + y_int, 81, 68, 21);
		gfx.PutPixel(3 + x_int, 12 + y_int, 81, 68, 21);
		gfx.PutPixel(4 + x_int, 12 + y_int, 81, 68, 21);
		gfx.PutPixel(5 + x_int, 12 + y_int, 79, 65, 21);
		gfx.PutPixel(6 + x_int, 12 + y_int, 77, 64, 21);
		gfx.PutPixel(7 + x_int, 12 + y_int, 79, 66, 21);
		gfx.PutPixel(8 + x_int, 12 + y_int, 81, 68, 21);
		gfx.PutPixel(9 + x_int, 12 + y_int, 79, 67, 21);
		gfx.PutPixel(10 + x_int, 12 + y_int, 71, 61, 18);
		gfx.PutPixel(11 + x_int, 12 + y_int, 60, 51, 15);
		gfx.PutPixel(12 + x_int, 12 + y_int, 56, 46, 13);
		gfx.PutPixel(13 + x_int, 12 + y_int, 55, 45, 13);
		gfx.PutPixel(14 + x_int, 12 + y_int, 55, 46, 13);
		gfx.PutPixel(15 + x_int, 12 + y_int, 59, 50, 15);
		gfx.PutPixel(16 + x_int, 12 + y_int, 70, 59, 18);
		gfx.PutPixel(17 + x_int, 12 + y_int, 78, 65, 20);
		gfx.PutPixel(18 + x_int, 12 + y_int, 82, 69, 21);
		gfx.PutPixel(19 + x_int, 12 + y_int, 84, 70, 22);
		gfx.PutPixel(0 + x_int, 13 + y_int, 22, 18, 6);
		gfx.PutPixel(1 + x_int, 13 + y_int, 60, 50, 16);
		gfx.PutPixel(2 + x_int, 13 + y_int, 88, 74, 22);
		gfx.PutPixel(3 + x_int, 13 + y_int, 81, 68, 21);
		gfx.PutPixel(4 + x_int, 13 + y_int, 79, 66, 21);
		gfx.PutPixel(5 + x_int, 13 + y_int, 68, 57, 17);
		gfx.PutPixel(6 + x_int, 13 + y_int, 61, 51, 15);
		gfx.PutPixel(7 + x_int, 13 + y_int, 67, 55, 17);
		gfx.PutPixel(8 + x_int, 13 + y_int, 78, 64, 21);
		gfx.PutPixel(9 + x_int, 13 + y_int, 81, 68, 22);
		gfx.PutPixel(10 + x_int, 13 + y_int, 78, 66, 19);
		gfx.PutPixel(11 + x_int, 13 + y_int, 70, 59, 18);
		gfx.PutPixel(12 + x_int, 13 + y_int, 64, 54, 16);
		gfx.PutPixel(13 + x_int, 13 + y_int, 62, 51, 15);
		gfx.PutPixel(14 + x_int, 13 + y_int, 63, 52, 15);
		gfx.PutPixel(15 + x_int, 13 + y_int, 69, 58, 18);
		gfx.PutPixel(16 + x_int, 13 + y_int, 76, 63, 20);
		gfx.PutPixel(17 + x_int, 13 + y_int, 86, 72, 22);
		gfx.PutPixel(18 + x_int, 13 + y_int, 52, 44, 14);
		gfx.PutPixel(19 + x_int, 13 + y_int, 22, 18, 6);
		gfx.PutPixel(1 + x_int, 14 + y_int, 55, 45, 15);
		gfx.PutPixel(2 + x_int, 14 + y_int, 96, 81, 25);
		gfx.PutPixel(3 + x_int, 14 + y_int, 80, 67, 21);
		gfx.PutPixel(4 + x_int, 14 + y_int, 76, 64, 20);
		gfx.PutPixel(5 + x_int, 14 + y_int, 60, 51, 15);
		gfx.PutPixel(6 + x_int, 14 + y_int, 51, 44, 12);
		gfx.PutPixel(7 + x_int, 14 + y_int, 59, 49, 14);
		gfx.PutPixel(8 + x_int, 14 + y_int, 74, 62, 20);
		gfx.PutPixel(9 + x_int, 14 + y_int, 81, 68, 22);
		gfx.PutPixel(10 + x_int, 14 + y_int, 82, 68, 21);
		gfx.PutPixel(11 + x_int, 14 + y_int, 79, 66, 20);
		gfx.PutPixel(12 + x_int, 14 + y_int, 75, 64, 20);
		gfx.PutPixel(13 + x_int, 14 + y_int, 72, 61, 19);
		gfx.PutPixel(14 + x_int, 14 + y_int, 74, 62, 19);
		gfx.PutPixel(15 + x_int, 14 + y_int, 77, 65, 20);
		gfx.PutPixel(16 + x_int, 14 + y_int, 80, 67, 21);
		gfx.PutPixel(17 + x_int, 14 + y_int, 97, 81, 25);
		gfx.PutPixel(18 + x_int, 14 + y_int, 41, 35, 11);
		gfx.PutPixel(1 + x_int, 15 + y_int, 42, 35, 11);
		gfx.PutPixel(2 + x_int, 15 + y_int, 79, 67, 20);
		gfx.PutPixel(3 + x_int, 15 + y_int, 84, 71, 22);
		gfx.PutPixel(4 + x_int, 15 + y_int, 77, 65, 20);
		gfx.PutPixel(5 + x_int, 15 + y_int, 64, 54, 17);
		gfx.PutPixel(6 + x_int, 15 + y_int, 57, 49, 14);
		gfx.PutPixel(7 + x_int, 15 + y_int, 63, 53, 16);
		gfx.PutPixel(8 + x_int, 15 + y_int, 75, 64, 20);
		gfx.PutPixel(9 + x_int, 15 + y_int, 80, 68, 21);
		gfx.PutPixel(10 + x_int, 15 + y_int, 82, 68, 21);
		gfx.PutPixel(11 + x_int, 15 + y_int, 82, 69, 21);
		gfx.PutPixel(12 + x_int, 15 + y_int, 81, 69, 21);
		gfx.PutPixel(13 + x_int, 15 + y_int, 80, 68, 21);
		gfx.PutPixel(14 + x_int, 15 + y_int, 80, 68, 21);
		gfx.PutPixel(15 + x_int, 15 + y_int, 82, 69, 22);
		gfx.PutPixel(16 + x_int, 15 + y_int, 84, 70, 22);
		gfx.PutPixel(17 + x_int, 15 + y_int, 77, 64, 20);
		gfx.PutPixel(18 + x_int, 15 + y_int, 33, 28, 9);
		gfx.PutPixel(1 + x_int, 16 + y_int, 1, 1, 0);
		gfx.PutPixel(2 + x_int, 16 + y_int, 32, 27, 8);
		gfx.PutPixel(3 + x_int, 16 + y_int, 89, 75, 23);
		gfx.PutPixel(4 + x_int, 16 + y_int, 82, 69, 21);
		gfx.PutPixel(5 + x_int, 16 + y_int, 76, 65, 20);
		gfx.PutPixel(6 + x_int, 16 + y_int, 73, 62, 20);
		gfx.PutPixel(7 + x_int, 16 + y_int, 75, 64, 20);
		gfx.PutPixel(8 + x_int, 16 + y_int, 81, 68, 21);
		gfx.PutPixel(9 + x_int, 16 + y_int, 81, 68, 21);
		gfx.PutPixel(10 + x_int, 16 + y_int, 81, 68, 21);
		gfx.PutPixel(11 + x_int, 16 + y_int, 81, 68, 21);
		gfx.PutPixel(12 + x_int, 16 + y_int, 81, 68, 21);
		gfx.PutPixel(13 + x_int, 16 + y_int, 81, 68, 21);
		gfx.PutPixel(14 + x_int, 16 + y_int, 81, 68, 21);
		gfx.PutPixel(15 + x_int, 16 + y_int, 83, 70, 22);
		gfx.PutPixel(16 + x_int, 16 + y_int, 82, 69, 21);
		gfx.PutPixel(17 + x_int, 16 + y_int, 21, 18, 5);
		gfx.PutPixel(2 + x_int, 17 + y_int, 5, 4, 1);
		gfx.PutPixel(3 + x_int, 17 + y_int, 37, 30, 10);
		gfx.PutPixel(4 + x_int, 17 + y_int, 84, 70, 22);
		gfx.PutPixel(5 + x_int, 17 + y_int, 92, 78, 24);
		gfx.PutPixel(6 + x_int, 17 + y_int, 85, 72, 22);
		gfx.PutPixel(7 + x_int, 17 + y_int, 79, 67, 21);
		gfx.PutPixel(8 + x_int, 17 + y_int, 81, 68, 21);
		gfx.PutPixel(9 + x_int, 17 + y_int, 81, 68, 21);
		gfx.PutPixel(10 + x_int, 17 + y_int, 81, 68, 21);
		gfx.PutPixel(11 + x_int, 17 + y_int, 81, 68, 21);
		gfx.PutPixel(12 + x_int, 17 + y_int, 81, 68, 21);
		gfx.PutPixel(13 + x_int, 17 + y_int, 88, 74, 23);
		gfx.PutPixel(14 + x_int, 17 + y_int, 92, 77, 24);
		gfx.PutPixel(15 + x_int, 17 + y_int, 71, 60, 18);
		gfx.PutPixel(16 + x_int, 17 + y_int, 22, 19, 6);
		gfx.PutPixel(17 + x_int, 17 + y_int, 2, 2, 1);
		gfx.PutPixel(3 + x_int, 18 + y_int, 2, 1, 1);
		gfx.PutPixel(4 + x_int, 18 + y_int, 37, 31, 9);
		gfx.PutPixel(5 + x_int, 18 + y_int, 44, 37, 11);
		gfx.PutPixel(6 + x_int, 18 + y_int, 58, 48, 15);
		gfx.PutPixel(7 + x_int, 18 + y_int, 85, 71, 22);
		gfx.PutPixel(8 + x_int, 18 + y_int, 81, 68, 21);
		gfx.PutPixel(9 + x_int, 18 + y_int, 81, 68, 21);
		gfx.PutPixel(10 + x_int, 18 + y_int, 81, 68, 21);
		gfx.PutPixel(11 + x_int, 18 + y_int, 82, 69, 21);
		gfx.PutPixel(12 + x_int, 18 + y_int, 82, 69, 21);
		gfx.PutPixel(13 + x_int, 18 + y_int, 53, 44, 14);
		gfx.PutPixel(14 + x_int, 18 + y_int, 43, 36, 11);
		gfx.PutPixel(15 + x_int, 18 + y_int, 28, 24, 7);
		gfx.PutPixel(6 + x_int, 19 + y_int, 32, 27, 8);
		gfx.PutPixel(7 + x_int, 19 + y_int, 87, 73, 23);
		gfx.PutPixel(8 + x_int, 19 + y_int, 81, 68, 21);
		gfx.PutPixel(9 + x_int, 19 + y_int, 81, 68, 21);
		gfx.PutPixel(10 + x_int, 19 + y_int, 81, 68, 21);
		gfx.PutPixel(11 + x_int, 19 + y_int, 83, 70, 22);
		gfx.PutPixel(12 + x_int, 19 + y_int, 83, 69, 22);
		gfx.PutPixel(13 + x_int, 19 + y_int, 22, 18, 6);


	}
}

void Rock::Move(float v, float deltaTime)
{
	x -= v * deltaTime;
}

void Rock::ShipCollision(Ship& ship)
{
	if (
		(x<ship.GetX() + ship.GetWidth() &&
			x + width > ship.GetX() &&
			y + height > ship.GetY() &&
			y < ship.GetY() + ship.GetHeight()) ||
		x < 0
		)
	{
		shipCollision = true;
	}
}

bool Rock::GetIonRockCollision()
{
	return ionRockCollision;
}

void Rock::SetIonRockCollision(bool boolean)
{
	ionRockCollision = boolean;
}

float Rock::GetX()
{
	return x;
}

float Rock::GetY()
{
	return y;
}

float Rock::GetWidth()
{
	return width;
}

float Rock::GetHeight()
{
	return height;
}

bool Rock::GetShipColission()
{
	return shipCollision;
}
