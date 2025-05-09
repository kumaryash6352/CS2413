bool filled(int x, int y, char** grid, int gridSize, int gridColSize) {
    return x >= 0
        && y >= 0
        && x < gridSize
        && y < gridColSize
        && grid[x][y] == '1';
}

void clear(int x, int y, char** grid, int gridSize, int gridColSize) {
    if(!filled(x, y, grid, gridSize, gridColSize)) return;
    grid[x][y] = '0';
    int dxs[] = {-1, 1, 0, 0};
    int dys[] = {0, 0, 1, -1};
    for(int i = 0; i < 4; i++)
        clear(x + dxs[i], y + dys[i], grid, gridSize, gridColSize);
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    int count = 0;
    for(int x = 0; x < gridSize; x++) {
        for(int y = 0; y < *gridColSize; y++) {
            if(filled(x, y, grid, gridSize, *gridColSize)) {
                count++;
                clear(x, y, grid, gridSize, *gridColSize);
            }
        }
    }
    return count;
}
