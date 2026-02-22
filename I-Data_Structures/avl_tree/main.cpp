#include <iostream>
#include <climits>
using namespace std;

class AVLTree {
    int value;
    AVLTree* left;
    AVLTree* right;
    int height;

    void compute_height() {
        int leftH=this->left ? this->left->height : -1, rightH=this->right ? this->right->height: -1;
        this->height = max(leftH, rightH) + 1;
    }

public:
    AVLTree() {
        height = -1;
        left = right = nullptr;
        value=INT_MIN;
    }

    AVLTree* insert(int val) {
        if (this->height == -1) {
            this->value=val;
            this->left=nullptr;
            this->right=nullptr;
            this->height=0;
            return this->balance();
        }

        if (val<this->value) {
            if (!this->left) this->left=new AVLTree;
            this->left=this->left->insert(val);
        }else{
            if (!this->right) this->right=new AVLTree;
            this->right=this->right->insert(val);
        }

        return this->balance();
    }

    void print_preorder_DFT() const {
        if (this->height==-1) {
            cout << "Empty tree" << '\n';
            return;
        }

        cout << this->value << " ";
        if (this->left) this->left->print_preorder_DFT();
        if (this->right) this->right->print_preorder_DFT();
    }

    AVLTree* right_rotation() {
        AVLTree* newRoot=this->left;

        this->left=newRoot->right;
        newRoot->right=this;

        this->compute_height();
        newRoot->compute_height();

        return newRoot;
    }

    AVLTree* left_rotation() {
        AVLTree* newRoot=this->right;

        this->right=newRoot->left;
        newRoot->left=this;

        this->compute_height();
        newRoot->compute_height();

        return newRoot;
    }

    AVLTree* left_right_rotation() {
        this->left=this->left->left_rotation();
        return this->right_rotation();
    }

    AVLTree* right_left_rotation() {
        this->right=this->right->right_rotation();
        return this->left_rotation();
    }

    AVLTree* balance() {
        if (this) {
            this->compute_height();

            int leftH=this->left ? this->left->height : -1, rightH=this->right ? this->right->height : -1;

            //left subtree is taller
            if (leftH > rightH+1) {
                int leftLeftH=this->left->left ? this->left->left->height : -1, leftRightH=this->left->right ? this->left->right->height : -1;

                if (leftLeftH >= leftRightH) return this->right_rotation();
                return this->left_right_rotation();
            }

            //right subtree is taller
            if (rightH > leftH+1) {
                int rightLeftH=this->right->left ? this->right->left->height : -1, rightRightH=this->right->right ? this->right->right->height : -1;

                if (rightRightH >= rightLeftH) return this->left_rotation();
                return this->right_left_rotation();
            }
        }

        return this;//no rotation, root exists but is balanced
    }

    ~AVLTree() {
        if (left) delete left;
        if (right) delete right;
    }
};


int main() {
    //AVL e balansirano BST, znachi insert raboti kako kaj BST
    //max height difference megu nivoata (height) na dve deca od eden ist node treba da e 1
    AVLTree* root = new AVLTree;
    int input;

    cout << "Enter values for AVL tree nodes: " << '\n';
    while (cin >> input) {
        root=root->insert(input);
    }

    cin.clear();
    cin.ignore(INT_MAX, '\n');

    root->print_preorder_DFT();

    delete root;

    return 0;
}