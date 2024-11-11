
#include <iostream>
#include <algorithm> 

class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree() : root{ nullptr } {}
    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } {
        rhs.root = nullptr;
    }
    ~BinarySearchTree() {
        makeEmpty();
    }

    const Comparable &findMin() const {
        if(isEmpty())
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    const Comparable &findMax() const {
        if(isEmpty())
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const Comparable &x) {
        insert(x, root);
    }

    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    void remove(const Comparable &x) {
        remove(x, root);
    }

    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
        if (this != &rhs) {
            BinarySearchTree temp(rhs);
            std::swap(root, temp.root);
        }
        return *this;
    }

    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

protected:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        int height;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt, int h = 0)
            : element{ theElement }, left{ lt }, right{ rt }, height{ h } {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt, int h = 0)
            : element{ std::move(theElement) }, left{ lt }, right{ rt }, height{ h } {}
    };

    BinaryNode *root;

    void insert(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr) {
            t = new BinaryNode{x, nullptr, nullptr,1};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        }
        balance(t);
    }

    void insert(Comparable &&x, BinaryNode *&t) {
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr,1};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        }
        balance(t);
    }

    void remove(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr) {
            return;
        }
        if (x < t->element) {
            remove(x, t->left);
        } else if (t->element < x) {
            remove(x, t->right);
        } else if (t->left != nullptr && t->right != nullptr) {
            BinaryNode *tmp = detachMin(t->right);
            tmp->right = t->right;
            tmp->left = t->left;
            delete t;
            t = tmp;
        } else {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
        balance(t);
    }

    BinaryNode *detachMin(BinaryNode *&t) {
        if (t==nullptr){
            return nullptr;
        }
        if (t->left != nullptr) {
            return detachMin(t->left);
        } else {
            BinaryNode *minNode = t;
            t = t->right;
            return minNode;
        }
    }


    void balance(BinaryNode *&t) {
        if (t == nullptr) return;

        if (height(t->left) - height(t->right) > 1) {
            if (height(t->left->left) >= height(t->left->right)) {
                rotateWithLeftChild(t);
            } else {
                doubleWithLeftChild(t);
            }
        } else if (height(t->right) - height(t->left) > 1) {
            if (height(t->right->right) >= height(t->right->left)) {
                rotateWithRightChild(t);
            } else {
                doubleWithRightChild(t);
            }
        }

        t->height = std::max(height(t->left), height(t->right)) + 1;
    }

    int height(BinaryNode *t) const {
        return t == nullptr ? -1 : t->height;
    }

    void rotateWithLeftChild(BinaryNode *&k2) {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(height(k2->left), height(k2->right)) + 1;
        k1->height = std::max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(BinaryNode *&k1) {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = std::max(height(k1->left), height(k1->right)) + 1;
        k2->height = std::max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild(BinaryNode *&k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(BinaryNode *&k1) {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

    BinaryNode *findMin(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        } else if (t->left == nullptr) {
            return t;
        } else {
            return findMin(t->left);
        }
    }

    BinaryNode *findMax(BinaryNode *t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    bool contains(const Comparable &x, BinaryNode *t) const {
        if (t == nullptr) {
            return false;
        } else if (x < t->element) {
            return contains(x, t->left);
        } else if (x > t->element) {
            return contains(x, t->right);
        } else {
            return true;  // Match found
        }
    }

    void printTree(BinaryNode *t, std::ostream &out) const {
        if (t != nullptr) {
            printTree(t->left, out);
            out << t->element << std::endl;
            printTree(t->right, out);
        }
    }

    void makeEmpty(BinaryNode *&t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        } else {
            return new BinaryNode{t->element, clone(t->left), clone(t->right), t->height};
        }
    }
};
