#include <iostream>
#include <limits>

struct Node {
    int data;
    int count;
    Node* left;
    Node* right;
};

int isInteger(const std::string& message);

Node* createTree(Node* root, int data) {
    if (root == nullptr) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->count = 1;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    if (data < root->data) {
        root->left = createTree(root->left, data);
    } 
    else if (data > root->data) {
        root->right = createTree(root->right, data);
    }
    else {
        root->count++;
    }
    return root;
}

void printTree(Node* node, int level = 0) {
    if (node == nullptr) return;

    printTree(node->right, level + 1);
    for (int i = 0; i < level; i++) std::cout << "   ";
    std::cout << node->data << "(" << node->count << ")" << std::endl;
    printTree(node->left, level + 1);
}

bool searchTree(Node* root, int value) {
    if (root == nullptr) return false;
    if (root->data == value) return true;
    if (value < root->data)
        return searchTree(root->left, value);
    else
        return searchTree(root->right, value);
}

int countOccurrences(Node* root, int value) {
    if (root == nullptr) return 0;
    
    if (root->data == value) {
        return root->count;
    }
    
    if (value < root->data)
        return countOccurrences(root->left, value);
    else
        return countOccurrences(root->right, value);
}

void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;
    int value;
    std::cout << "-1 — окончание построения дерева\n";

    while (true) {
        value = inputInteger("Введите число: ");
        if (value == -1) {
            std::cout << "Построение дерева окончено\n\n";
            break;
        }
        root = createTree(root, value);
    }

    std::cout << "Дерево (число в скобках - количество вхождений):\n";
    printTree(root);

    std::cout << "\n--- Поиск значений в дереве ---\n";
    while (true) {
        value = isInteger("Введите значение для поиска (-1 для окончания): ");
        if (value == -1) {
            std::cout << "Поиск значений окончен\n";
            break;
        }
        if (searchTree(root, value))
            std::cout << "Значение " << value << " найдено в дереве.\n";
        else
            std::cout << "Значение " << value << " отсутствует в дереве.\n";
    }

    while (true) {
        value = isInteger("Введите значение для подсчёта вхождений (-1 для окончания): ");
        if (value == -1) {
            std::cout << "Подсчет вхождений окончен\n";
            break;
        }
        std::cout << "Количество вхождений элемента " << value << ": " 
                  << countOccurrences(root, value) << std::endl;
    }

    deleteTree(root);
    return 0;
}

int isInteger(const std::string& message) {
    int value;
    while (true) {
        std::cout << message;
        if (!(std::cin >> value)) {
            std::cout << "Ошибка: введено не число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (std::cin.peek() != '\n') {
            std::cout << "Ошибка: введено не целое число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        return value;
    }
}