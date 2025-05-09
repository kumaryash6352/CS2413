bool isSymmetricP(struct TreeNode* a, struct TreeNode* b) {
    if(a && b) {
        if(a->val != b->val) return false;
        return isSymmetricP(a->left, b->right) && isSymmetricP(a->right, b->left);
    } else {
        return a == NULL && b == NULL;
    }
}
bool isSymmetric(struct TreeNode* root) {
    return isSymmetricP(root->left, root->right);
}
