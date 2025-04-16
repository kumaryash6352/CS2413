void push_value(int v, int** buf, int* cursor, int* size) {
    if(cursor == size) {
        // realloc
        *buf = realloc(*buf, *size * 2);
        *size *= 2;
    }
    *(*buf + *cursor) = v;
    *cursor += 1;
}
void preorder(struct TreeNode* cursor, int** buf, int* buf_cursor, int* size) {
    if(cursor) {
        push_value(cursor->val, buf, buf_cursor, size);
        preorder(cursor->left, buf, buf_cursor, size);
        preorder(cursor->right, buf, buf_cursor, size);
    }
}
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int* buffer = malloc(256 * sizeof(int));
    int buf_cursor = 0;
    int buf_size = 256;
    preorder(root, &buffer, &buf_cursor, &buf_size);
    buffer = realloc(buffer, buf_size * sizeof(int));
    *returnSize = buf_cursor;
    return buffer;
