#include <bits/stdc++.h>
#include "raylib.h"

#define SCREENWIDTH 450
#define SCREENHEIGHT 525
#define GRIDWIDTH 450
#define GRIDHEIGHT 450

using namespace std;

const int rows = 9;
const int cols = 9;
const int cellWidth = GRIDWIDTH/cols;
const int cellHeight = GRIDHEIGHT/rows;

class Cell {
public:
    int i, j, value;
    bool fixed;

    Cell(int i = 0, int j = 0, int value = 0, bool fixed = false) {
        this->i = i;
        this->j = j;
        this->value = value;
        this->fixed = fixed;
    }
};

vector<vector<Cell*>> grid(rows, vector<Cell*>(cols, NULL));

int main() {
    vector<vector<int>> unSolved = {
        {2, 0, 0, 0, 3, 0, 0, 4, 0},
        {0, 3, 0, 6, 0, 0, 0, 0, 7},
        {0, 0, 9, 0, 0, 7, 1, 0, 8},
        {0, 0, 4, 0, 7, 2, 0, 0, 0},
        {0, 2, 5, 0, 8, 1, 9, 0, 0},
        {1, 0, 3, 0, 0, 6, 0, 0, 5},
        {0, 0, 0, 0, 2, 0, 4, 0, 0},
        {4, 0, 6, 8, 0, 0, 0, 7, 0},
        {5, 0, 0, 9, 0, 0, 3, 0, 0}
    };

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Sudoku Generator");
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++) {
            if(unSolved[i][j] != 0) {
                grid[i][j] = new Cell(j*cellWidth, i*cellHeight, unSolved[i][j], true);
            } else {
                grid[i][j] = new Cell(j*cellWidth, i*cellHeight);
            }
        }
    }
    Cell* selected = grid[0][0];
    Rectangle rect1 = { cellWidth*3, 0, cellWidth*3, GRIDHEIGHT };
    Rectangle rect2 = { 0, cellHeight*3, GRIDWIDTH, cellHeight*3 };
    Rectangle rect3 = { 0, 0, GRIDWIDTH, GRIDHEIGHT };
    float thickness = 3.0;
    Color color = DARKBLUE;

    while(!WindowShouldClose()) {

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 pos = GetMousePosition();
            int indexJ = pos.x/cellWidth;
            int indexI = pos.y/cellHeight;
            if(indexI >= 0 && indexI < rows && indexJ >= 0 && indexJ < cols) {
                selected = grid[indexI][indexJ];
            }
        }

        int key = GetCharPressed();

        // NOTE: Only allow keys in range [32..125]
        if ((key >= 48) && (key <= 57))
        {
            if(!selected->fixed) {
                selected->value = key-48;
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    Cell* currCell = grid[i][j];

                    if(currCell->fixed) {
                        DrawText(to_string(currCell->value).c_str(), currCell->i + (2*cellWidth)/5, currCell->j + (2*cellHeight)/5, 20, BLACK);
                    } else {
                        if(currCell->value != 0) {
                            DrawText(to_string(currCell->value).c_str(), currCell->i + (2*cellWidth)/5, currCell->j + (2*cellHeight)/5, 20, RED);
                        }
                    }
                    DrawRectangleLines(currCell->i, currCell->j, cellWidth, cellHeight, BLACK);
                }
            }

            DrawRectangle(selected->i, selected->j, cellWidth, cellHeight, LIGHTGRAY);
            if(selected->fixed) {
                DrawText(to_string(selected->value).c_str(), selected->i + (2*cellWidth)/5, selected->j + (2*cellHeight)/5, 20, BLACK);
            } else {
                if(selected->value != 0) {
                    DrawText(to_string(selected->value).c_str(), selected->i + (2*cellWidth)/5, selected->j + (2*cellHeight)/5, 20, RED);
                }
            }

            DrawRectangleLinesEx(rect1, thickness, color);
            DrawRectangleLinesEx(rect2, thickness, color);
            DrawRectangleLinesEx(rect3, thickness, color);

        EndDrawing();
    }

    CloseWindow();
 
    return 0;
}
