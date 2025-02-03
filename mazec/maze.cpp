#include "../astar/astar.h"

#include "raylib.h"
#define SCREENWIDTH 600
#define SCREENHEIGHT 600

using namespace std;

const int rows = 25;
const int cols = 25;
const int cellWidth = SCREENWIDTH/cols;
const int cellHeight = SCREENHEIGHT/rows;

class Cell {
public:
    int i;
    int j;
    bool isBlocked;

    Cell(int i, int j) {
        this->i = i;
        this->j = j;
        this->isBlocked = false;
    }
};

vector<vector<Cell*>> grid(rows, vector<Cell*>(cols, NULL));

class maze : public State<pair<int, int>> {
public:
    vector<vector<int>> board = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                                    { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                                    { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                                    { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                                    { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                                    { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                                    { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                                    { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                                    { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };;

    // maze(pair<int, int> data) {
    //     this->data = data;
    // }

    int hn(pair<int, int> current, pair<int, int> dest) {
        return (sqrt(
        (current.first - dest.first) * (current.first - dest.first)
        + (current.second - dest.second) * (current.second - dest.second)));
    }

    vector<pair<pair<int, int>, int>> fn_neighbours(pair<int, int> state) {
        vector<pair<pair<int, int>, int>> nextStates;
        int row = this->board.size();
        int col = this->board[0].size();
        auto [curr_row, curr_col] = state;

        if(curr_row > 0 && this->board[curr_row-1][curr_col] != 0)
            nextStates.push_back({{curr_row-1, curr_col}, 1});
        if(curr_col > 0 && this->board[curr_row][curr_col-1] != 0)
            nextStates.push_back({{curr_row, curr_col-1}, 1});
        if(curr_row < row-1 && this->board[curr_row+1][curr_col] != 0)
            nextStates.push_back({{curr_row+1, curr_col}, 1});
        if(curr_col < col-1 && this->board[curr_row][curr_col+1] != 0)
            nextStates.push_back({{curr_row, curr_col+1}, 1});
        if(curr_row > 0 && curr_col > 0 && this->board[curr_row-1][curr_col-1] != 0)
            nextStates.push_back({{curr_row-1, curr_col-1}, 1});
        if(curr_row > 0 && curr_col < col-1 && this->board[curr_row-1][curr_col+1] != 0)
            nextStates.push_back({{curr_row-1, curr_col+1}, 1});
        if(curr_row < row-1 && curr_col > 0 && this->board[curr_row+1][curr_col-1] != 0)
            nextStates.push_back({{curr_row+1, curr_col-1}, 1});
        if(curr_row < row-1 && curr_col < col-1 && this->board[curr_row+1][curr_col+1] != 0)
            nextStates.push_back({{curr_row+1, curr_col+1}, 1});    

        return nextStates;
    }


    bool operator==(const State& other) {
        return other.data.first == data.first && other.data.second == data.second;
    }

    void print_state(pair<int, int> currentState) {
        cout << currentState.first << ", " << currentState.second << endl;
    }
};

void solve_maze_ui() {
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "example - basic window");
    // SetTargetFPS(60);

    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = new Cell(j*cellWidth, i*cellHeight);
        }
    }
    int result = false;
    Node<pair<int, int>>* res;
    int lastMousePosX = 0;
    int lastMousePosY = 0;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        int mousePosX = GetMouseX();
        int mousePosY = GetMouseY();
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 pos = GetMousePosition();
            int indexJ = pos.x/cellWidth;
            int indexI = pos.y/cellHeight;
            if((lastMousePosX != indexI || lastMousePosY != indexJ) && (indexI >= 0 && indexI < rows && indexJ >= 0 && indexJ < cols)) {
                lastMousePosX = indexI;
                lastMousePosY = indexJ;
                grid[indexI][indexJ]->isBlocked = !grid[indexI][indexJ]->isBlocked;
                result = false;
            }
        } else {
            lastMousePosX = mousePosX;
            lastMousePosY = mousePosY;
        }
        if(IsKeyPressed(KEY_ENTER)) {
            if(!result) {
                maze* maze_class = new maze();
                vector<vector<int>> board(rows, vector<int>(cols, 0));
                for(int i = 0; i < rows; i++) {
                    for(int j = 0; j < cols; j++) {
                        board[i][j] = grid[i][j]->isBlocked ? 0 : 1;
                    }
                }
                maze_class->board = board;
                res = A_star<pair<int, int>>(maze_class, {0, 0}, {rows-1, cols-1});
                // for(int i = 0; i < rows; i++) {
                //     for(int j = 0; j < cols; j++) {
                //         cout << maze_class->board[i][j] << " ";
                //     }
                //     cout << endl;
                // }
                // cout << rows-1 << " " << cols-1;
                if (res == NULL) {
                    cout << "No path found!" << endl;
                }
                result = true;
            }
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    if(grid[i][j]->isBlocked) {
                        DrawRectangle(grid[i][j]->i, grid[i][j]->j, cellWidth, cellHeight, RED);
                    } else {
                        DrawRectangleLines(grid[i][j]->i, grid[i][j]->j, cellWidth, cellHeight, BLACK);
                    }
                }
            }

            // Now draw the path (move this to the end)
            if(result) {
                Node<pair<int, int>>* temp = res;
                while (temp != NULL) {
                    DrawRectangle(grid[temp->data.first][temp->data.second]->i, 
                                grid[temp->data.first][temp->data.second]->j, 
                                cellWidth, cellHeight, BLUE);
                    temp = temp->parent;
                }
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();
}

int main() {
    solve_maze_ui();

    return 0;
}