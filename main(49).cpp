#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Node {
    int data;
    vector<Node*> children;
};

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    return newNode;
}

void generateRandomTree(Node* parent, int maxDepth, int maxChildren, int& idCounter) {
    if (maxDepth <= 0) return;

    int numChildren = rand() % (maxChildren + 1);

    for (int i = 0; i < numChildren; ++i) {
        Node* child = createNode(++idCounter);
        parent->children.push_back(child);
        generateRandomTree(child, maxDepth - 1, maxChildren, idCounter);
    }
}

Node* findNode(Node* root, int value) {
    if (root == nullptr) return nullptr;
    if (root->data == value) return root;

    for (Node* child : root->children) {
        Node* found = findNode(child, value);
        if (found != nullptr) return found;
    }
    return nullptr;
}

bool addChildToNode(Node* root, int parentValue, int newValue) {
    Node* parent = findNode(root, parentValue);
    if (parent != nullptr) {
        parent->children.push_back(createNode(newValue));
        return true;
    }
    return false;
}

int countNodes(Node* root) {
    if (root == nullptr) return 0;
    int count = 1;
    for (Node* child : root->children) {
        count += countNodes(child);
    }
    return count;
}

void printTree(Node* root, int depth = 0) {
    if (root == nullptr) return;
    
    for (int i = 0; i < depth; ++i) cout << "  ";
    cout << "|--" << root->data << endl;

    for (Node* child : root->children) {
        printTree(child, depth + 1);
    }
}

void deleteTree(Node* root) {
    if (root == nullptr) return;
    for (Node* child : root->children) {
        deleteTree(child);
    }
    delete root;
}

bool removeNode(Node* parent, int value) {
    if (parent == nullptr) return false;

    for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
        if ((*it)->data == value) {
            deleteTree(*it);
            parent->children.erase(it);
            return true;
        }
        if (removeNode(*it, value)) return true;
    }
    return false;
}

void showMenu() {
    cout << "\n--- MENU KERUVANNYA DEREVOM ---\n";
    cout << "1. Vyvesty derevo\n";
    cout << "2. Dodaty vuzol do obranogo batka\n";
    cout << "3. Vydalyty vuzol (z pidderevom)\n";
    cout << "4. Poshuk vuzla\n";
    cout << "5. Obchyslyty kilkist vuzliv\n";
    cout << "0. Vykhid\n";
    cout << "Vybir: ";
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    
    int idCounter = 1;
    Node* root = createNode(idCounter);
    generateRandomTree(root, 3, 3, idCounter);

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nStruktura dereva:\n";
                printTree(root);
                break;
            case 2: {
                int pVal, nVal;
                cout << "Vvedit ID batka ta nove znachennya: ";
                cin >> pVal >> nVal;
                if (addChildToNode(root, pVal, nVal)) cout << "Dodano uspishno.\n";
                else cout << "Batka ne znaydeno!\n";
                break;
            }
            case 3: {
                int val;
                cout << "Vvedit ID vuzla dlya vydalennya: ";
                cin >> val;
                if (val == root->data) cout << "Nemozhlyvo vydalyty korin cherez tse menu.\n";
                else if (removeNode(root, val)) cout << "Vuzol vydaleno.\n";
                else cout << "Vuzol ne znaydeno.\n";
                break;
            }
            case 4: {
                int val;
                cout << "Yakyy ID shukayemo? ";
                cin >> val;
                Node* found = findNode(root, val);
                if (found) cout << "Vuzol " << val << " znaydeno. Maye ditey: " << found->children.size() << "\n";
                else cout << "Ne znaydeno.\n";
                break;
            }
            case 5:
                cout << "Zagalna kilkist vuzliv: " << countNodes(root) << "\n";
                break;
        }
    } while (choice != 0);

    deleteTree(root);
    return 0;
}
