#include "Rock.h"
#include "Ship.h"

void Rock::Init(int in_x, int in_y)
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
		gfx.PutPixel(6 + x, 0 + y, 33, 27, 8);
		gfx.PutPixel(7 + x, 0 + y, 88, 74, 23);
		gfx.PutPixel(8 + x, 0 + y, 81, 68, 21);
		gfx.PutPixel(9 + x, 0 + y, 81, 68, 21);
		gfx.PutPixel(10 + x, 0 + y, 81, 68, 21);
		gfx.PutPixel(11 + x, 0 + y, 83, 70, 22);
		gfx.PutPixel(12 + x, 0 + y, 84, 70, 22);
		gfx.PutPixel(13 + x, 0 + y, 22, 18, 6);
		gfx.PutPixel(4 + x, 1 + y, 46, 39, 11);
		gfx.PutPixel(5 + x, 1 + y, 55, 46, 14);
		gfx.PutPixel(6 + x, 1 + y, 65, 54, 17);
		gfx.PutPixel(7 + x, 1 + y, 85, 72, 22);
		gfx.PutPixel(8 + x, 1 + y, 82, 69, 21);
		gfx.PutPixel(9 + x, 1 + y, 82, 68, 21);
		gfx.PutPixel(10 + x, 1 + y, 81, 68, 21);
		gfx.PutPixel(11 + x, 1 + y, 82, 69, 21);
		gfx.PutPixel(12 + x, 1 + y, 82, 69, 21);
		gfx.PutPixel(13 + x, 1 + y, 60, 50, 16);
		gfx.PutPixel(14 + x, 1 + y, 57, 48, 15);
		gfx.PutPixel(15 + x, 1 + y, 42, 35, 10);
		gfx.PutPixel(2 + x, 2 + y, 13, 11, 3);
		gfx.PutPixel(3 + x, 2 + y, 42, 34, 11);
		gfx.PutPixel(4 + x, 2 + y, 84, 70, 21);
		gfx.PutPixel(5 + x, 2 + y, 92, 77, 24);
		gfx.PutPixel(6 + x, 2 + y, 83, 71, 22);
		gfx.PutPixel(7 + x, 2 + y, 75, 63, 19);
		gfx.PutPixel(8 + x, 2 + y, 77, 65, 20);
		gfx.PutPixel(9 + x, 2 + y, 80, 68, 21);
		gfx.PutPixel(10 + x, 2 + y, 81, 69, 21);
		gfx.PutPixel(11 + x, 2 + y, 81, 68, 21);
		gfx.PutPixel(12 + x, 2 + y, 81, 68, 21);
		gfx.PutPixel(13 + x, 2 + y, 87, 73, 23);
		gfx.PutPixel(14 + x, 2 + y, 94, 79, 25);
		gfx.PutPixel(15 + x, 2 + y, 80, 68, 21);
		gfx.PutPixel(16 + x, 2 + y, 39, 33, 9);
		gfx.PutPixel(17 + x, 2 + y, 2, 2, 1);
		gfx.PutPixel(0 + x, 3 + y, 2, 1, 0);
		gfx.PutPixel(1 + x, 3 + y, 10, 9, 3);
		gfx.PutPixel(2 + x, 3 + y, 51, 44, 13);
		gfx.PutPixel(3 + x, 3 + y, 91, 77, 23);
		gfx.PutPixel(4 + x, 3 + y, 83, 69, 21);
		gfx.PutPixel(5 + x, 3 + y, 78, 67, 21);
		gfx.PutPixel(6 + x, 3 + y, 68, 59, 17);
		gfx.PutPixel(7 + x, 3 + y, 61, 52, 15);
		gfx.PutPixel(8 + x, 3 + y, 66, 56, 16);
		gfx.PutPixel(9 + x, 3 + y, 75, 65, 20);
		gfx.PutPixel(10 + x, 3 + y, 81, 69, 21);
		gfx.PutPixel(11 + x, 3 + y, 81, 68, 21);
		gfx.PutPixel(12 + x, 3 + y, 81, 68, 21);
		gfx.PutPixel(13 + x, 3 + y, 81, 68, 21);
		gfx.PutPixel(14 + x, 3 + y, 81, 68, 21);
		gfx.PutPixel(15 + x, 3 + y, 84, 71, 22);
		gfx.PutPixel(16 + x, 3 + y, 88, 74, 23);
		gfx.PutPixel(17 + x, 3 + y, 29, 25, 8);
		gfx.PutPixel(18 + x, 3 + y, 5, 4, 1);
		gfx.PutPixel(0 + x, 4 + y, 11, 9, 3);
		gfx.PutPixel(1 + x, 4 + y, 53, 45, 14);
		gfx.PutPixel(2 + x, 4 + y, 86, 71, 22);
		gfx.PutPixel(3 + x, 4 + y, 82, 69, 21);
		gfx.PutPixel(4 + x, 4 + y, 82, 69, 21);
		gfx.PutPixel(5 + x, 4 + y, 71, 60, 18);
		gfx.PutPixel(6 + x, 4 + y, 58, 49, 14);
		gfx.PutPixel(7 + x, 4 + y, 54, 46, 13);
		gfx.PutPixel(8 + x, 4 + y, 58, 49, 14);
		gfx.PutPixel(9 + x, 4 + y, 70, 59, 18);
		gfx.PutPixel(10 + x, 4 + y, 79, 67, 21);
		gfx.PutPixel(11 + x, 4 + y, 82, 68, 21);
		gfx.PutPixel(12 + x, 4 + y, 81, 68, 21);
		gfx.PutPixel(13 + x, 4 + y, 81, 68, 21);
		gfx.PutPixel(14 + x, 4 + y, 81, 68, 21);
		gfx.PutPixel(15 + x, 4 + y, 81, 68, 21);
		gfx.PutPixel(16 + x, 4 + y, 81, 68, 21);
		gfx.PutPixel(17 + x, 4 + y, 85, 71, 22);
		gfx.PutPixel(18 + x, 4 + y, 38, 32, 10);
		gfx.PutPixel(0 + x, 5 + y, 5, 4, 1);
		gfx.PutPixel(1 + x, 5 + y, 57, 48, 15);
		gfx.PutPixel(2 + x, 5 + y, 93, 77, 24);
		gfx.PutPixel(3 + x, 5 + y, 81, 68, 21);
		gfx.PutPixel(4 + x, 5 + y, 82, 69, 21);
		gfx.PutPixel(5 + x, 5 + y, 70, 59, 18);
		gfx.PutPixel(6 + x, 5 + y, 57, 47, 14);
		gfx.PutPixel(7 + x, 5 + y, 53, 44, 12);
		gfx.PutPixel(8 + x, 5 + y, 57, 48, 14);
		gfx.PutPixel(9 + x, 5 + y, 70, 58, 18);
		gfx.PutPixel(10 + x, 5 + y, 80, 67, 22);
		gfx.PutPixel(11 + x, 5 + y, 82, 69, 21);
		gfx.PutPixel(12 + x, 5 + y, 81, 69, 21);
		gfx.PutPixel(13 + x, 5 + y, 81, 69, 21);
		gfx.PutPixel(14 + x, 5 + y, 81, 69, 21);
		gfx.PutPixel(15 + x, 5 + y, 82, 69, 21);
		gfx.PutPixel(16 + x, 5 + y, 81, 68, 21);
		gfx.PutPixel(17 + x, 5 + y, 95, 79, 24);
		gfx.PutPixel(18 + x, 5 + y, 39, 33, 11);
		gfx.PutPixel(0 + x, 6 + y, 40, 33, 10);
		gfx.PutPixel(1 + x, 6 + y, 67, 56, 17);
		gfx.PutPixel(2 + x, 6 + y, 86, 72, 22);
		gfx.PutPixel(3 + x, 6 + y, 81, 68, 21);
		gfx.PutPixel(4 + x, 6 + y, 82, 69, 21);
		gfx.PutPixel(5 + x, 6 + y, 75, 63, 20);
		gfx.PutPixel(6 + x, 6 + y, 65, 54, 17);
		gfx.PutPixel(7 + x, 6 + y, 62, 51, 14);
		gfx.PutPixel(8 + x, 6 + y, 65, 56, 17);
		gfx.PutPixel(9 + x, 6 + y, 76, 63, 20);
		gfx.PutPixel(10 + x, 6 + y, 81, 68, 21);
		gfx.PutPixel(11 + x, 6 + y, 79, 66, 20);
		gfx.PutPixel(12 + x, 6 + y, 77, 65, 20);
		gfx.PutPixel(13 + x, 6 + y, 75, 64, 20);
		gfx.PutPixel(14 + x, 6 + y, 77, 65, 20);
		gfx.PutPixel(15 + x, 6 + y, 79, 66, 20);
		gfx.PutPixel(16 + x, 6 + y, 80, 67, 21);
		gfx.PutPixel(17 + x, 6 + y, 86, 72, 22);
		gfx.PutPixel(18 + x, 6 + y, 57, 48, 15);
		gfx.PutPixel(19 + x, 6 + y, 33, 28, 9);
		gfx.PutPixel(0 + x, 7 + y, 87, 73, 23);
		gfx.PutPixel(1 + x, 7 + y, 83, 70, 22);
		gfx.PutPixel(2 + x, 7 + y, 80, 67, 21);
		gfx.PutPixel(3 + x, 7 + y, 81, 68, 21);
		gfx.PutPixel(4 + x, 7 + y, 81, 68, 21);
		gfx.PutPixel(5 + x, 7 + y, 80, 67, 21);
		gfx.PutPixel(6 + x, 7 + y, 76, 63, 20);
		gfx.PutPixel(7 + x, 7 + y, 74, 61, 18);
		gfx.PutPixel(8 + x, 7 + y, 76, 66, 21);
		gfx.PutPixel(9 + x, 7 + y, 81, 69, 21);
		gfx.PutPixel(10 + x, 7 + y, 79, 66, 20);
		gfx.PutPixel(11 + x, 7 + y, 72, 60, 18);
		gfx.PutPixel(12 + x, 7 + y, 67, 56, 17);
		gfx.PutPixel(13 + x, 7 + y, 65, 54, 16);
		gfx.PutPixel(14 + x, 7 + y, 67, 56, 16);
		gfx.PutPixel(15 + x, 7 + y, 72, 60, 18);
		gfx.PutPixel(16 + x, 7 + y, 77, 64, 21);
		gfx.PutPixel(17 + x, 7 + y, 79, 66, 21);
		gfx.PutPixel(18 + x, 7 + y, 85, 71, 22);
		gfx.PutPixel(19 + x, 7 + y, 88, 74, 23);
		gfx.PutPixel(0 + x, 8 + y, 81, 68, 21);
		gfx.PutPixel(1 + x, 8 + y, 81, 68, 21);
		gfx.PutPixel(2 + x, 8 + y, 81, 68, 21);
		gfx.PutPixel(3 + x, 8 + y, 81, 68, 21);
		gfx.PutPixel(4 + x, 8 + y, 81, 68, 21);
		gfx.PutPixel(5 + x, 8 + y, 81, 68, 21);
		gfx.PutPixel(6 + x, 8 + y, 81, 68, 21);
		gfx.PutPixel(7 + x, 8 + y, 80, 68, 21);
		gfx.PutPixel(8 + x, 8 + y, 81, 68, 21);
		gfx.PutPixel(9 + x, 8 + y, 79, 67, 21);
		gfx.PutPixel(10 + x, 8 + y, 73, 61, 18);
		gfx.PutPixel(11 + x, 8 + y, 63, 53, 15);
		gfx.PutPixel(12 + x, 8 + y, 57, 48, 14);
		gfx.PutPixel(13 + x, 8 + y, 56, 47, 13);
		gfx.PutPixel(14 + x, 8 + y, 57, 48, 14);
		gfx.PutPixel(15 + x, 8 + y, 63, 53, 16);
		gfx.PutPixel(16 + x, 8 + y, 73, 62, 18);
		gfx.PutPixel(17 + x, 8 + y, 80, 67, 21);
		gfx.PutPixel(18 + x, 8 + y, 81, 68, 21);
		gfx.PutPixel(19 + x, 8 + y, 79, 66, 20);
		gfx.PutPixel(0 + x, 9 + y, 81, 68, 21);
		gfx.PutPixel(1 + x, 9 + y, 81, 68, 21);
		gfx.PutPixel(2 + x, 9 + y, 81, 68, 21);
		gfx.PutPixel(3 + x, 9 + y, 81, 68, 21);
		gfx.PutPixel(4 + x, 9 + y, 81, 68, 21);
		gfx.PutPixel(5 + x, 9 + y, 81, 68, 21);
		gfx.PutPixel(6 + x, 9 + y, 81, 68, 21);
		gfx.PutPixel(7 + x, 9 + y, 82, 68, 21);
		gfx.PutPixel(8 + x, 9 + y, 81, 68, 21);
		gfx.PutPixel(9 + x, 9 + y, 78, 65, 20);
		gfx.PutPixel(10 + x, 9 + y, 67, 56, 17);
		gfx.PutPixel(11 + x, 9 + y, 57, 47, 13);
		gfx.PutPixel(12 + x, 9 + y, 54, 45, 13);
		gfx.PutPixel(13 + x, 9 + y, 54, 45, 13);
		gfx.PutPixel(14 + x, 9 + y, 53, 44, 13);
		gfx.PutPixel(15 + x, 9 + y, 57, 47, 14);
		gfx.PutPixel(16 + x, 9 + y, 67, 56, 16);
		gfx.PutPixel(17 + x, 9 + y, 76, 64, 20);
		gfx.PutPixel(18 + x, 9 + y, 80, 67, 21);
		gfx.PutPixel(19 + x, 9 + y, 79, 66, 20);
		gfx.PutPixel(0 + x, 10 + y, 81, 68, 21);
		gfx.PutPixel(1 + x, 10 + y, 81, 68, 21);
		gfx.PutPixel(2 + x, 10 + y, 81, 68, 21);
		gfx.PutPixel(3 + x, 10 + y, 81, 68, 21);
		gfx.PutPixel(4 + x, 10 + y, 81, 68, 21);
		gfx.PutPixel(5 + x, 10 + y, 81, 68, 21);
		gfx.PutPixel(6 + x, 10 + y, 81, 68, 21);
		gfx.PutPixel(7 + x, 10 + y, 81, 68, 21);
		gfx.PutPixel(8 + x, 10 + y, 81, 68, 21);
		gfx.PutPixel(9 + x, 10 + y, 77, 63, 20);
		gfx.PutPixel(10 + x, 10 + y, 65, 54, 17);
		gfx.PutPixel(11 + x, 10 + y, 55, 45, 13);
		gfx.PutPixel(12 + x, 10 + y, 54, 45, 13);
		gfx.PutPixel(13 + x, 10 + y, 54, 45, 13);
		gfx.PutPixel(14 + x, 10 + y, 53, 44, 13);
		gfx.PutPixel(15 + x, 10 + y, 55, 45, 13);
		gfx.PutPixel(16 + x, 10 + y, 63, 53, 16);
		gfx.PutPixel(17 + x, 10 + y, 74, 62, 20);
		gfx.PutPixel(18 + x, 10 + y, 80, 67, 21);
		gfx.PutPixel(19 + x, 10 + y, 80, 67, 20);
		gfx.PutPixel(0 + x, 11 + y, 82, 69, 22);
		gfx.PutPixel(1 + x, 11 + y, 82, 69, 21);
		gfx.PutPixel(2 + x, 11 + y, 81, 68, 21);
		gfx.PutPixel(3 + x, 11 + y, 81, 68, 21);
		gfx.PutPixel(4 + x, 11 + y, 81, 68, 21);
		gfx.PutPixel(5 + x, 11 + y, 81, 68, 21);
		gfx.PutPixel(6 + x, 11 + y, 81, 67, 21);
		gfx.PutPixel(7 + x, 11 + y, 81, 68, 21);
		gfx.PutPixel(8 + x, 11 + y, 81, 68, 21);
		gfx.PutPixel(9 + x, 11 + y, 77, 65, 20);
		gfx.PutPixel(10 + x, 11 + y, 67, 56, 17);
		gfx.PutPixel(11 + x, 11 + y, 57, 47, 13);
		gfx.PutPixel(12 + x, 11 + y, 54, 45, 13);
		gfx.PutPixel(13 + x, 11 + y, 54, 45, 13);
		gfx.PutPixel(14 + x, 11 + y, 53, 44, 13);
		gfx.PutPixel(15 + x, 11 + y, 56, 46, 13);
		gfx.PutPixel(16 + x, 11 + y, 65, 55, 16);
		gfx.PutPixel(17 + x, 11 + y, 75, 62, 20);
		gfx.PutPixel(18 + x, 11 + y, 82, 69, 21);
		gfx.PutPixel(19 + x, 11 + y, 83, 70, 22);
		gfx.PutPixel(0 + x, 12 + y, 84, 70, 22);
		gfx.PutPixel(1 + x, 12 + y, 82, 69, 21);
		gfx.PutPixel(2 + x, 12 + y, 81, 68, 21);
		gfx.PutPixel(3 + x, 12 + y, 81, 68, 21);
		gfx.PutPixel(4 + x, 12 + y, 81, 68, 21);
		gfx.PutPixel(5 + x, 12 + y, 79, 65, 21);
		gfx.PutPixel(6 + x, 12 + y, 77, 64, 21);
		gfx.PutPixel(7 + x, 12 + y, 79, 66, 21);
		gfx.PutPixel(8 + x, 12 + y, 81, 68, 21);
		gfx.PutPixel(9 + x, 12 + y, 79, 67, 21);
		gfx.PutPixel(10 + x, 12 + y, 71, 61, 18);
		gfx.PutPixel(11 + x, 12 + y, 60, 51, 15);
		gfx.PutPixel(12 + x, 12 + y, 56, 46, 13);
		gfx.PutPixel(13 + x, 12 + y, 55, 45, 13);
		gfx.PutPixel(14 + x, 12 + y, 55, 46, 13);
		gfx.PutPixel(15 + x, 12 + y, 59, 50, 15);
		gfx.PutPixel(16 + x, 12 + y, 70, 59, 18);
		gfx.PutPixel(17 + x, 12 + y, 78, 65, 20);
		gfx.PutPixel(18 + x, 12 + y, 82, 69, 21);
		gfx.PutPixel(19 + x, 12 + y, 84, 70, 22);
		gfx.PutPixel(0 + x, 13 + y, 22, 18, 6);
		gfx.PutPixel(1 + x, 13 + y, 60, 50, 16);
		gfx.PutPixel(2 + x, 13 + y, 88, 74, 22);
		gfx.PutPixel(3 + x, 13 + y, 81, 68, 21);
		gfx.PutPixel(4 + x, 13 + y, 79, 66, 21);
		gfx.PutPixel(5 + x, 13 + y, 68, 57, 17);
		gfx.PutPixel(6 + x, 13 + y, 61, 51, 15);
		gfx.PutPixel(7 + x, 13 + y, 67, 55, 17);
		gfx.PutPixel(8 + x, 13 + y, 78, 64, 21);
		gfx.PutPixel(9 + x, 13 + y, 81, 68, 22);
		gfx.PutPixel(10 + x, 13 + y, 78, 66, 19);
		gfx.PutPixel(11 + x, 13 + y, 70, 59, 18);
		gfx.PutPixel(12 + x, 13 + y, 64, 54, 16);
		gfx.PutPixel(13 + x, 13 + y, 62, 51, 15);
		gfx.PutPixel(14 + x, 13 + y, 63, 52, 15);
		gfx.PutPixel(15 + x, 13 + y, 69, 58, 18);
		gfx.PutPixel(16 + x, 13 + y, 76, 63, 20);
		gfx.PutPixel(17 + x, 13 + y, 86, 72, 22);
		gfx.PutPixel(18 + x, 13 + y, 52, 44, 14);
		gfx.PutPixel(19 + x, 13 + y, 22, 18, 6);
		gfx.PutPixel(1 + x, 14 + y, 55, 45, 15);
		gfx.PutPixel(2 + x, 14 + y, 96, 81, 25);
		gfx.PutPixel(3 + x, 14 + y, 80, 67, 21);
		gfx.PutPixel(4 + x, 14 + y, 76, 64, 20);
		gfx.PutPixel(5 + x, 14 + y, 60, 51, 15);
		gfx.PutPixel(6 + x, 14 + y, 51, 44, 12);
		gfx.PutPixel(7 + x, 14 + y, 59, 49, 14);
		gfx.PutPixel(8 + x, 14 + y, 74, 62, 20);
		gfx.PutPixel(9 + x, 14 + y, 81, 68, 22);
		gfx.PutPixel(10 + x, 14 + y, 82, 68, 21);
		gfx.PutPixel(11 + x, 14 + y, 79, 66, 20);
		gfx.PutPixel(12 + x, 14 + y, 75, 64, 20);
		gfx.PutPixel(13 + x, 14 + y, 72, 61, 19);
		gfx.PutPixel(14 + x, 14 + y, 74, 62, 19);
		gfx.PutPixel(15 + x, 14 + y, 77, 65, 20);
		gfx.PutPixel(16 + x, 14 + y, 80, 67, 21);
		gfx.PutPixel(17 + x, 14 + y, 97, 81, 25);
		gfx.PutPixel(18 + x, 14 + y, 41, 35, 11);
		gfx.PutPixel(1 + x, 15 + y, 42, 35, 11);
		gfx.PutPixel(2 + x, 15 + y, 79, 67, 20);
		gfx.PutPixel(3 + x, 15 + y, 84, 71, 22);
		gfx.PutPixel(4 + x, 15 + y, 77, 65, 20);
		gfx.PutPixel(5 + x, 15 + y, 64, 54, 17);
		gfx.PutPixel(6 + x, 15 + y, 57, 49, 14);
		gfx.PutPixel(7 + x, 15 + y, 63, 53, 16);
		gfx.PutPixel(8 + x, 15 + y, 75, 64, 20);
		gfx.PutPixel(9 + x, 15 + y, 80, 68, 21);
		gfx.PutPixel(10 + x, 15 + y, 82, 68, 21);
		gfx.PutPixel(11 + x, 15 + y, 82, 69, 21);
		gfx.PutPixel(12 + x, 15 + y, 81, 69, 21);
		gfx.PutPixel(13 + x, 15 + y, 80, 68, 21);
		gfx.PutPixel(14 + x, 15 + y, 80, 68, 21);
		gfx.PutPixel(15 + x, 15 + y, 82, 69, 22);
		gfx.PutPixel(16 + x, 15 + y, 84, 70, 22);
		gfx.PutPixel(17 + x, 15 + y, 77, 64, 20);
		gfx.PutPixel(18 + x, 15 + y, 33, 28, 9);
		gfx.PutPixel(1 + x, 16 + y, 1, 1, 0);
		gfx.PutPixel(2 + x, 16 + y, 32, 27, 8);
		gfx.PutPixel(3 + x, 16 + y, 89, 75, 23);
		gfx.PutPixel(4 + x, 16 + y, 82, 69, 21);
		gfx.PutPixel(5 + x, 16 + y, 76, 65, 20);
		gfx.PutPixel(6 + x, 16 + y, 73, 62, 20);
		gfx.PutPixel(7 + x, 16 + y, 75, 64, 20);
		gfx.PutPixel(8 + x, 16 + y, 81, 68, 21);
		gfx.PutPixel(9 + x, 16 + y, 81, 68, 21);
		gfx.PutPixel(10 + x, 16 + y, 81, 68, 21);
		gfx.PutPixel(11 + x, 16 + y, 81, 68, 21);
		gfx.PutPixel(12 + x, 16 + y, 81, 68, 21);
		gfx.PutPixel(13 + x, 16 + y, 81, 68, 21);
		gfx.PutPixel(14 + x, 16 + y, 81, 68, 21);
		gfx.PutPixel(15 + x, 16 + y, 83, 70, 22);
		gfx.PutPixel(16 + x, 16 + y, 82, 69, 21);
		gfx.PutPixel(17 + x, 16 + y, 21, 18, 5);
		gfx.PutPixel(2 + x, 17 + y, 5, 4, 1);
		gfx.PutPixel(3 + x, 17 + y, 37, 30, 10);
		gfx.PutPixel(4 + x, 17 + y, 84, 70, 22);
		gfx.PutPixel(5 + x, 17 + y, 92, 78, 24);
		gfx.PutPixel(6 + x, 17 + y, 85, 72, 22);
		gfx.PutPixel(7 + x, 17 + y, 79, 67, 21);
		gfx.PutPixel(8 + x, 17 + y, 81, 68, 21);
		gfx.PutPixel(9 + x, 17 + y, 81, 68, 21);
		gfx.PutPixel(10 + x, 17 + y, 81, 68, 21);
		gfx.PutPixel(11 + x, 17 + y, 81, 68, 21);
		gfx.PutPixel(12 + x, 17 + y, 81, 68, 21);
		gfx.PutPixel(13 + x, 17 + y, 88, 74, 23);
		gfx.PutPixel(14 + x, 17 + y, 92, 77, 24);
		gfx.PutPixel(15 + x, 17 + y, 71, 60, 18);
		gfx.PutPixel(16 + x, 17 + y, 22, 19, 6);
		gfx.PutPixel(17 + x, 17 + y, 2, 2, 1);
		gfx.PutPixel(3 + x, 18 + y, 2, 1, 1);
		gfx.PutPixel(4 + x, 18 + y, 37, 31, 9);
		gfx.PutPixel(5 + x, 18 + y, 44, 37, 11);
		gfx.PutPixel(6 + x, 18 + y, 58, 48, 15);
		gfx.PutPixel(7 + x, 18 + y, 85, 71, 22);
		gfx.PutPixel(8 + x, 18 + y, 81, 68, 21);
		gfx.PutPixel(9 + x, 18 + y, 81, 68, 21);
		gfx.PutPixel(10 + x, 18 + y, 81, 68, 21);
		gfx.PutPixel(11 + x, 18 + y, 82, 69, 21);
		gfx.PutPixel(12 + x, 18 + y, 82, 69, 21);
		gfx.PutPixel(13 + x, 18 + y, 53, 44, 14);
		gfx.PutPixel(14 + x, 18 + y, 43, 36, 11);
		gfx.PutPixel(15 + x, 18 + y, 28, 24, 7);
		gfx.PutPixel(6 + x, 19 + y, 32, 27, 8);
		gfx.PutPixel(7 + x, 19 + y, 87, 73, 23);
		gfx.PutPixel(8 + x, 19 + y, 81, 68, 21);
		gfx.PutPixel(9 + x, 19 + y, 81, 68, 21);
		gfx.PutPixel(10 + x, 19 + y, 81, 68, 21);
		gfx.PutPixel(11 + x, 19 + y, 83, 70, 22);
		gfx.PutPixel(12 + x, 19 + y, 83, 69, 22);
		gfx.PutPixel(13 + x, 19 + y, 22, 18, 6);


	}
}

void Rock::Move()
{
	x-= 2;
}

void Rock::ShipCollision(Ship& ship)
{
	if (
		(x<ship.GetX() + ship.GetWidth() &&
		x + width > ship.GetX() &&
		y + height > ship.GetY() &&
		y < ship.GetY() + ship.GetHeight())||
		x<0
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

int Rock::GetX()
{
	return x;
}

int Rock::GetY()
{
	return y;
}

int Rock::GetWidth()
{
	return width;
}

int Rock::GetHeight()
{
	return height;
}

bool Rock::GetShipColission()
{
	return shipCollision;
}
