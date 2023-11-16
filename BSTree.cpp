#include <iostream>
using namespace std;
template <class E>
struct Node{
    E element;
    Node<E> * left;
    Node<E> * right;
    Node( E e = E(),Node<E> *l = 0, Node<E> *r = 0):
    element(e),left(l),right(r){}
    bool isLeaf() const { 
        return (!left&&!right);
    }// kiem tra nut la
    bool isInternal() const {
        return(left|| right);
    }//kiem tra nut noi
};
template <class E>
class BTree{
    protected:
        Node<E> * root;// Nut goc
    private:
        Node<E> *& searchRec(Node<E> *& r, const E &e){
        if(!r){
            cout << "Khong tim thay \n";
            return r;
        }
        if(r -> element == e){
            return r;
        }
        if(e<r -> element)  {
            return searchRec(r-> left, e);
        }
        else {
            return searchRec(r -> right,e);
        }
        }
        int countRec(Node<E> *& r){
            if(!r) return 0;
            return 1+ countRec(r-> left) + countRec(r->right);
        }        
        int countLeaf(Node<E> *& r){
            if(!r) return 0;
            if(r->idLeaf()) return 1;
            return countRec(r-> left) + ( countRec(r->right));
        }
        int countInternal(Node<E> *& r) {
            if (!r) return 0;
            if (r->isInternal()) return 1 + countInternal(r->left) + countInternal(r->right);
        return 0;
        }

        int height(Node<E> *& r){
            if(!r) return -1;
            if(r->isLeaf()) return 0;
            int h = max(height(r->left),height(r->right));
            return 1+h;
        }
    
        void searchremoveRec( Node<E> *& r, const E & e){
            if(!r) {
                cout <<"Khogn tim thay,khong the xoa\n";
                return;
            }
            if(e < r -> element) searchremoveRec(r -> left, e);
            else if( e > r -> element) searchremoveRec(r -> right, e);
            else{
                Node<E> * cur = r;
                if( !r -> left) r =r -> right;
                else if (!r -> right)  r = r -> left;
                else{
                    // TH 3 co 2 con
                    cur = r -> left;
                    Node<E> * parent = r;
                    for(; cur -> right;){
                        parent = cur;
                        cur = cur -> right;
                    }
                    r -> element = cur -> element;
                    if(cur == r -> left)
                    parent -> left = cur -> left;
                    else
                    parent -> right  = cur -> left;
                }
                delete cur;
                cur =0;
            }
        }
        void preOrder(Node <E> *r){//duyet tien to
        if(r){
            cout <<  r -> element << " ";
            preOrder(r -> left);
            preOrder(r -> right);
        }
        }
        void postOrder(Node<E> * r){// duyet hau to
            if(r){
                postOrder( r-> left);
                postOrder(r -> right);
                cout<< r -> element << " ";
            }
        }
        void inOrder(Node<E> * r){//duyet trung to
            if(r){
                inOrder( r-> left);
                cout<< r -> element << " ";
                inOrder(r -> right);
            }
        }

        void addRec(Node<E> *& r, const E &e) {
            if (!r) {
                r = new Node<E>(e);
            } else {
                if (e < r->element) {
                    addRec(r->left, e);
                } else {
                    addRec(r->right, e);
                }
            }
        }
        Node<E>* copyTree(const Node<E>* otherRoot) {
            if (!otherRoot)
                return nullptr;

            Node<E>* newNode = new Node<E>(otherRoot->element);
            newNode->left = copyTree(otherRoot->left);
            newNode->right = copyTree(otherRoot->right);
            return newNode;
        }
        public:
        BTree(const BTree &other) {
        root = copyTree(other.root);
        }
        void callPostOrder(){
            postOrder(root);
        }
        void callPreOrder(){
            preOrder(root);
        }
        int depthtree() {
            return height(root); // Assuming you renamed the 'height' function to 'depth'
        }

        bool searchKey(const E & e){
            if(!searchRec(root,e)) return false;
            return true;
        }
        BTree(): root(0){}
        void add(const E & e){
            addRec(root,e);
        }
        void clear(Node<E>* &root) {
            if (root == nullptr)
                return;
            clear(root->left);
            clear(root->right);
            delete root;
            root = nullptr; // Set the root to nullptr after deleting it.
        }
        // Destructor (as you already have)
        virtual ~BTree() {
            clear(root);
        }
};
int main(){
    BTree <int> a;
    a.add(13);
    a.add(9);
    a.add(7);
    a.add(10);
    a.add(15);  
    a.callPostOrder();
    int depth = a.depthtree();
    cout << "Depth of the tree: " << depth << endl;
    
    return 0;
};