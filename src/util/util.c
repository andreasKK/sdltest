#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <SDL2/SDL.h>

#include "../util/util.h"
#include "../util/constants.h"
#include "../component/vector.h"
#include "../component/triangle.h"
#include "../component/rectangle.h"


void FreeMem(void *ptr) {
	free(ptr);
	ptr = NULL;
}

void FreeScreen(Screen *screen) {
	SDL_FreeSurface(screen->frontBuffer->surface);
	SDL_DestroyWindow(screen->frontBuffer->window);
	SDL_FreeSurface(screen->backBuffer->surface);
	screen->backBuffer->surface = NULL;
	screen->frontBuffer->surface = NULL;
	screen->frontBuffer->window = NULL;
	FreeMem(screen->backBuffer);
	FreeMem(screen->frontBuffer);
	FreeMem(screen->color);
	FreeMem(screen);
}

void FreeShapeArray(ShapeArray *shapes) {
	if (shapes) {
		if (shapes->lineArray) {
			FreeArray(shapes->lineArray->lines, shapes->lineArray->size, LINE);
			FreeMem(shapes->lineArray);
		}
		if (shapes->triangleArray) {
			FreeArray(shapes->triangleArray->triangles, shapes->triangleArray->size, TRIANGLE);
		}
		if (shapes->rectangleArray) {
			FreeArray(shapes->rectangleArray->rectangles, shapes->rectangleArray->size, RECTANGLE);
		}
		// TODO SHAPE
		FreeMem(shapes);
	}
}

void FreeArray(void **ptr, size_t size, const unsigned int type) {
	if (type == LINE) {
		Line **lines = (Line**)ptr;
		for (size_t i = 0; i < size; i++) {
			if (lines[i]) {
				FreeComponent(lines[i], LINE);
			}
		}
	}
	if (type == TRIANGLE) {
		Triangle **triangles = (Triangle**)ptr;
		for (size_t i = 0; i < size; i++) {
			if (triangles[i]) {
				FreeComponent(triangles[i], TRIANGLE);
			}
		}
	}
	if (type == RECTANGLE) {
		Rectangle **rectangles = (Rectangle**)ptr;
		for (size_t i = 0; i < size; i++) {
			if (rectangles[i]) {
				FreeComponent(rectangles[i], RECTANGLE);
			}
		}
	}
	// TODO SHAPE
}

void FreeComponent(void *ptr, const unsigned int type) {
	if (type == LINE) {
		Line *line = (Line*)ptr;
		FreeMem(line->p0);
		FreeMem(line->p1);
		FreeMem(line);
	}
	if (type == TRIANGLE) {
		Triangle *triangle = (Triangle*)ptr;
		FreeMem(triangle->p0);
		FreeMem(triangle->p1);
		FreeMem(triangle->p2);
		FreeMem(triangle);
	}
	if (type == RECTANGLE) {
		Rectangle *rectangle = (Rectangle*)ptr;
		FreeMem(rectangle->topLeft);
		FreeMem(rectangle->bottomRight);
		FreeMem(rectangle);
	}
	// TODO SHAPE
}

void *AllocMem(size_t size) {
	void * ptr = NULL;
	ptr = malloc(size);
	if (ptr == NULL) {
		printf("\nAllocMemError: Out of Memory, cannot allocate %d bytes", size);
		exit(-1);
	}
	return ptr;
}

void ReAllocMem(void *ptr, size_t newSize) {
	if (realloc(ptr, newSize) == NULL) {
		printf("\nReAllocMemError: Reallocations of %d bytes from pointer %p returned NULL", newSize, ptr);
	}
}

void OutputComponent(void *ptr, const unsigned int type) {
    if (type == LINE) {
        Line *line = (Line*)ptr;
        printf("\np0(%f, %f) | p1(%f, %f)", line->p0->x, line->p0->y, line->p1->x, line->p1->y);
    }
    if (type == TRIANGLE) {
        Triangle *triangle = (Triangle*)ptr;
        printf("\np0(%f, %f) | p1(%f, %f) | p2(%f, %f)", 
            triangle->p0->x, triangle->p0->y, 
            triangle->p1->x, triangle->p1->y,
            triangle->p2->x, triangle->p2->y
        );
    }
    if (type == RECTANGLE) {
        Rectangle *rectangle = (Rectangle*)ptr;
        printf("\ntopLeft(%f, %f) | bottomRight(%f, %f)", 
            rectangle->topLeft->x, rectangle->topLeft->y,
            rectangle->bottomRight->x, rectangle->bottomRight->y
        );
    }
	// TODO
}

size_t GetShapeIndex(ShapeArray *shapes, void *shape, const unsigned int type) {
	if (shapes) {
		if (type == LINE) {
			if (shapes->lineArray) {
				Line *line = (Line*)shape;
				for (size_t i = 0; i < shapes->lineArray->size; i++) {
					if (AreEqualLines(shapes->lineArray->lines[i], line)) {
						return i;
					}
				}
			}
		}
		if (type == TRIANGLE) {
			if (shapes->triangleArray) {
				Triangle *triangle = (Triangle*)shape;
				for (size_t i = 0; i < shapes->triangleArray->size; i++) {
					if (AreEqualTriangles(shapes->triangleArray->triangles[i], triangle)) {
						return i;
					}
				}
			}
		}
		if (type == RECTANGLE) {
			if (shapes->rectangleArray) {
				Rectangle *rectangle = (Rectangle*)shape;
				for (size_t i = 0; i < shapes->rectangleArray->size; i++) {
					if (AreEqualRectangles(shapes->rectangleArray->rectangles[i], rectangle)) {
						return i;
					}
				}
			}
		}
		// TODO SHAPE
	}
	return -1;
}

bool IsEqual(float x, float y) {
	return (fabsf(x - y) < EPSILON);	
}

bool IsGreaterThanOrEqual(float x, float y) {
	return ((x > y) || (IsEqual(x, y)));
}

bool IsLesserThanOrEqual(float x, float y) {
	return ((x < y) || (IsEqual(x, y)));	
}

