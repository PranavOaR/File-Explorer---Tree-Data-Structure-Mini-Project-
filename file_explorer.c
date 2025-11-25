// File Explorer System - C Implementation with Tree Data Structure
// Author: REVA University - October 2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Maximum name length for files and folders
#define MAX_NAME_LENGTH 50
#define MAX_PATH_LENGTH 500

/*
================================================================================
                            STRUCTURE DEFINITIONS
================================================================================
*/

// Node structure for file system tree
typedef struct Node {
    char name[MAX_NAME_LENGTH];
    int isFile;
    struct Node *parent;
    struct Node *firstChild;
    struct Node *nextSibling;
} Node;

// Global pointer to root and current directory
Node *root = NULL;
Node *currentDir = NULL;

/*
================================================================================
                            HELPER FUNCTION PROTOTYPES
================================================================================
*/

// Node creation and management
Node* createNode(const char *name, int isFile);
void addChild(Node *parent, Node *child);
Node* findChild(Node *parent, const char *name);

// File operations
void createFolder(Node *parent, const char *name);
void createFile(Node *parent, const char *name);
void deleteNode(Node *node);
void deleteNodeRecursive(Node *node);

// Search operations
void searchDFS(Node *node, const char *name, const char *currentPath);

// Display operations
void displayTree(Node *node, int depth, int isLast);
void printCurrentPath(Node *node);
char* getFullPath(Node *node);

// Navigation
void changeDirectory(Node **current, const char *name);

// Utility functions
void clearInputBuffer();
void freeTree(Node *node);
int countChildren(Node *parent);

// Menu functions
void printMenu();
void handleCreateFolder();
void handleCreateFile();
void handleDelete();
void handleSearch();
void handleDisplayTree();
void handleChangeDirectory();
void handleShowPath();

/*
================================================================================
                        NODE CREATION AND MANAGEMENT
================================================================================
*/

// Create a new node
Node* createNode(const char *name, int isFile) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    
    if (newNode == NULL) {
        printf("❌ Error: Memory allocation failed!\n");
        return NULL;
    }
    
    strncpy(newNode->name, name, MAX_NAME_LENGTH - 1);
    newNode->name[MAX_NAME_LENGTH - 1] = '\0';
    newNode->isFile = isFile;
    newNode->parent = NULL;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    
    return newNode;
}

// Add child to parent with sorted order
void addChild(Node *parent, Node *child) {
    if (parent == NULL || child == NULL) {
        printf("❌ Error: Invalid parent or child node!\n");
        return;
    }
    
    child->parent = parent;
    
    if (parent->firstChild == NULL) {
        parent->firstChild = child;
        return;
    }
    
    Node *current = parent->firstChild;
    Node *previous = NULL;
    
    while (current != NULL) {
        if (!child->isFile && current->isFile) {
            if (previous == NULL) {
                child->nextSibling = parent->firstChild;
                parent->firstChild = child;
            } else {
                previous->nextSibling = child;
                child->nextSibling = current;
            }
            return;
        }
        
        if (child->isFile == current->isFile && strcmp(child->name, current->name) < 0) {
            if (previous == NULL) {
                child->nextSibling = parent->firstChild;
                parent->firstChild = child;
            } else {
                previous->nextSibling = child;
                child->nextSibling = current;
            }
            return;
        }
        
        previous = current;
        current = current->nextSibling;
    }
    
    previous->nextSibling = child;
}

// Find child by name
Node* findChild(Node *parent, const char *name) {
    if (parent == NULL || name == NULL) {
        return NULL;
    }
    
    Node *current = parent->firstChild;
    
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->nextSibling;
    }
    
    return NULL;
}

// Count children
int countChildren(Node *parent) {
    if (parent == NULL) return 0;
    
    int count = 0;
    Node *current = parent->firstChild;
    
    while (current != NULL) {
        count++;
        current = current->nextSibling;
    }
    
    return count;
}

/*
================================================================================
                            FILE OPERATIONS
================================================================================
*/

// Create a new folder
void createFolder(Node *parent, const char *name) {
    if (parent == NULL) {
        printf("❌ Error: Invalid parent directory!\n");
        return;
    }
    
    if (parent->isFile) {
        printf("❌ Error: Cannot create folder inside a file!\n");
        return;
    }
    
    if (findChild(parent, name) != NULL) {
        printf("❌ Error: A file or folder with name '%s' already exists!\n", name);
        return;
    }
    
    Node *newFolder = createNode(name, 0);
    if (newFolder == NULL) {
        return;
    }
    
    addChild(parent, newFolder);
    
    printf("✅ Folder '%s' created successfully!\n", name);
}

// Create a new file
void createFile(Node *parent, const char *name) {
    if (parent == NULL) {
        printf("❌ Error: Invalid parent directory!\n");
        return;
    }
    
    if (parent->isFile) {
        printf("❌ Error: Cannot create file inside a file!\n");
        return;
    }
    
    if (findChild(parent, name) != NULL) {
        printf("❌ Error: A file or folder with name '%s' already exists!\n", name);
        return;
    }
    
    Node *newFile = createNode(name, 1);
    if (newFile == NULL) {
        return;
    }
    
    addChild(parent, newFile);
    
    printf("✅ File '%s' created successfully!\n", name);
}

// Remove node from parent's child list
void removeFromParent(Node *node) {
    if (node == NULL || node->parent == NULL) {
        return;
    }
    
    Node *parent = node->parent;
    
    if (parent->firstChild == node) {
        parent->firstChild = node->nextSibling;
        return;
    }
    
    Node *current = parent->firstChild;
    while (current != NULL && current->nextSibling != node) {
        current = current->nextSibling;
    }
    
    if (current != NULL) {
        current->nextSibling = node->nextSibling;
    }
}

// Delete node recursively
void deleteNodeRecursive(Node *node) {
    if (node == NULL) {
        return;
    }
    
    Node *child = node->firstChild;
    while (child != NULL) {
        Node *nextChild = child->nextSibling;
        deleteNodeRecursive(child);
        child = nextChild;
    }
    
    free(node);
}

// Delete a file or folder
void deleteNode(Node *node) {
    if (node == NULL) {
        printf("❌ Error: Node not found!\n");
        return;
    }
    
    if (node == root) {
        printf("❌ Error: Cannot delete root directory!\n");
        return;
    }
    
    if (node == currentDir) {
        printf("❌ Error: Cannot delete current directory! Navigate to parent first.\n");
        return;
    }
    
    Node *temp = currentDir;
    while (temp != NULL) {
        if (temp == node) {
            printf("❌ Error: Cannot delete an ancestor of current directory!\n");
            return;
        }
        temp = temp->parent;
    }
    
    removeFromParent(node);
    
    char nodeName[MAX_NAME_LENGTH];
    strcpy(nodeName, node->name);
    int wasFile = node->isFile;
    
    deleteNodeRecursive(node);
    
    if (wasFile) {
        printf("✅ File '%s' deleted successfully!\n", nodeName);
    } else {
        printf("✅ Folder '%s' and all its contents deleted successfully!\n", nodeName);
    }
}

/**
 * Move a node from one location to another
 * 
 * @param src - Source node to move
 * @param dest - Destination folder
 */
void moveNode(Node *src, Node *dest) {
    if (src == NULL || dest == NULL) {
        printf("❌ Error: Invalid source or destination!\n");
        return;
    }
    
    // Cannot move root
    if (src == root) {
        printf("❌ Error: Cannot move root directory!\n");
        return;
    }
    
    // Destination must be a folder
    if (dest->isFile) {
        printf("❌ Error: Destination must be a folder!\n");
        return;
    }
    
    // Cannot move into itself or its descendants
    if (!src->isFile) {
        Node *temp = dest;
        while (temp != NULL) {
            if (temp == src) {
                printf("❌ Error: Cannot move a folder into itself or its descendants!\n");
                return;
            }
            temp = temp->parent;
        }
    }
    
    // Check if name already exists in destination
    if (findChild(dest, src->name) != NULL) {
        printf("❌ Error: A file or folder with name '%s' already exists in destination!\n", src->name);
        return;
    }
    
    // Remove from current parent
    removeFromParent(src);
    
    // Reset sibling pointer
    src->nextSibling = NULL;
    
    // Add to new parent
    addChild(dest, src);
    
    printf("✅ '%s' moved successfully!\n", src->name);
}
void searchDFS(Node *node, const char *name, const char *currentPath) {
    if (node == NULL) {
        return;
    }
    
    // Build current full path
    char fullPath[MAX_PATH_LENGTH];
    snprintf(fullPath, MAX_PATH_LENGTH, "%s/%s", currentPath, node->name);
    
    // Check if current node matches search term
    if (strstr(node->name, name) != NULL) {
        if (node->isFile) {
            printf("  📄 %s\n", fullPath);
        } else {
            printf("  📁 %s\n", fullPath);
        }
    }
    
    // Recursively search children
    if (!node->isFile) {
        Node *child = node->firstChild;
        while (child != NULL) {
            searchDFS(child, name, fullPath);
            child = child->nextSibling;
        }
    }
}

/**
 * Search for files/folders using Breadth-First Search
 * 
 * @param root - Root node to start search from
 * @param name - Name to search for (substring match)
 */
void searchBFS(Node *rootNode, const char *name) {
    if (rootNode == NULL) {
        return;
    }
    
    // Simple queue implementation using array
    Node *queue[1000];
    int front = 0, rear = 0;
    
    // Enqueue root
    queue[rear++] = rootNode;
    
    while (front < rear) {
        Node *current = queue[front++];
        
        // Check if current node matches
        if (strstr(current->name, name) != NULL) {
            char *fullPath = getFullPath(current);
            if (current->isFile) {
                printf("  📄 %s\n", fullPath);
            } else {
                printf("  📁 %s\n", fullPath);
            }
            free(fullPath);
        }
        
        // Enqueue children
        if (!current->isFile) {
            Node *child = current->firstChild;
            while (child != NULL) {
                queue[rear++] = child;
                child = child->nextSibling;
            }
        }
    }
}
void displayTree(Node *node, int depth, int isLast) {
    if (node == NULL) {
        return;
    }
    
    // Print indentation and tree characters
    for (int i = 0; i < depth - 1; i++) {
        printf("│   ");
    }
    
    if (depth > 0) {
        if (isLast) {
            printf("└── ");
        } else {
            printf("├── ");
        }
    }
    
    // Print node name with icon
    if (node->isFile) {
        printf("📄 %s\n", node->name);
    } else {
        printf("📁 %s", node->name);
        
        // Mark current directory
        if (node == currentDir) {
            printf(" [Current]");
        }
        printf("\n");
        
        // Display children
        Node *child = node->firstChild;
        while (child != NULL) {
            int isLastChild = (child->nextSibling == NULL);
            displayTree(child, depth + 1, isLastChild);
            child = child->nextSibling;
        }
    }
}

/**
 * Get the full path of a node
 * 
 * @param node - Node to get path for
 * @return Dynamically allocated string with full path (must be freed by caller)
 */
char* getFullPath(Node *node) {
    if (node == NULL) {
        return NULL;
    }
    
    // Build path by traversing up to root
    char *path = (char*)malloc(MAX_PATH_LENGTH);
    if (path == NULL) {
        return NULL;
    }
    
    char temp[MAX_PATH_LENGTH] = "";
    Node *current = node;
    
    // Build path in reverse
    while (current != NULL) {
        char newTemp[MAX_PATH_LENGTH];
        snprintf(newTemp, MAX_PATH_LENGTH, "/%s%s", current->name, temp);
        strcpy(temp, newTemp);
        current = current->parent;
    }
    
    strcpy(path, temp);
    return path;
}

void printCurrentPath(Node *node) {
    char *path = getFullPath(node);
    if (path != NULL) {
        printf("%s", path);
        free(path);
    }
}

/*
================================================================================
                            NAVIGATION
================================================================================
*/

// Change directory
void changeDirectory(Node **current, const char *name) {
    if (current == NULL || *current == NULL) {
        printf("❌ Error: Invalid current directory!\n");
        return;
    }
    
    if (strcmp(name, "..") == 0) {
        if ((*current)->parent != NULL) {
            *current = (*current)->parent;
            printf("✅ Changed to parent directory: ");
            printCurrentPath(*current);
            printf("\n");
        } else {
            printf("❌ Already at root directory!\n");
        }
        return;
    }
    
    if (strcmp(name, "/") == 0) {
        *current = root;
        printf("✅ Changed to root directory: ");
        printCurrentPath(*current);
        printf("\n");
        return;
    }
    
    Node *child = findChild(*current, name);
    
    if (child == NULL) {
        printf("❌ Error: Directory '%s' not found!\n", name);
        return;
    }
    
    if (child->isFile) {
        printf("❌ Error: '%s' is a file, not a directory!\n", name);
        return;
    }
    
    *current = child;
    printf("✅ Changed to directory: ");
    printCurrentPath(*current);
    printf("\n");
}

/*
================================================================================
                            UTILITY FUNCTIONS
================================================================================
*/

// Clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Free tree recursively
void freeTree(Node *node) {
    if (node == NULL) {
        return;
    }
    
    Node *child = node->firstChild;
    while (child != NULL) {
        Node *nextChild = child->nextSibling;
        freeTree(child);
        child = nextChild;
    }
    
    free(node);
}

/*
================================================================================
                            MENU FUNCTIONS
================================================================================
*/

/**
 * Print the main menu
 */
void printMenu() {
    printf("\n");
    printf("========================================\n");
    printf("       FILE EXPLORER SYSTEM\n");
    printf("========================================\n");
    printf("Current Directory: ");
    printCurrentPath(currentDir);
    printf("\n");
    printf("========================================\n");
    printf("1. Create Folder\n");
    printf("2. Create File\n");
    printf("3. Delete\n");
    printf("4. Search (DFS)\n");
    printf("5. Display Tree\n");
    printf("6. Change Directory\n");
    printf("7. Show Current Path\n");
    printf("0. Exit\n");
    printf("========================================\n");
}

/**
 * Handle folder creation
 */
void handleCreateFolder() {
    char name[MAX_NAME_LENGTH];
    
    printf("\n📁 CREATE FOLDER\n");
    printf("Enter folder name: ");
    
    if (scanf("%49s", name) != 1) {
        printf("❌ Error: Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    createFolder(currentDir, name);
}

/**
 * Handle file creation
 */
void handleCreateFile() {
    char name[MAX_NAME_LENGTH];
    
    printf("\n📄 CREATE FILE\n");
    printf("Enter file name: ");
    
    if (scanf("%49s", name) != 1) {
        printf("❌ Error: Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    createFile(currentDir, name);
}

/**
 * Handle deletion
 */
void handleDelete() {
    char name[MAX_NAME_LENGTH];
    
    printf("\n🗑️  DELETE\n");
    printf("Enter name of file/folder to delete: ");
    
    if (scanf("%49s", name) != 1) {
        printf("❌ Error: Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    Node *nodeToDelete = findChild(currentDir, name);
    
    if (nodeToDelete == NULL) {
        printf("❌ Error: '%s' not found in current directory!\n", name);
        return;
    }
    
    // Confirm deletion if folder
    if (!nodeToDelete->isFile) {
        char confirm;
        printf("⚠️  This will delete the folder and all its contents. Continue? (y/n): ");
        scanf(" %c", &confirm);
        clearInputBuffer();
        
        if (confirm != 'y' && confirm != 'Y') {
            printf("❌ Deletion cancelled.\n");
            return;
        }
    }
    
    deleteNode(nodeToDelete);
}

/**
 * Handle search
 */
void handleSearch() {
    char name[MAX_NAME_LENGTH];
    
    printf("\n🔍 DFS SEARCH\n");
    printf("Enter search term: ");
    
    if (scanf("%49s", name) != 1) {
        printf("❌ Error: Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    printf("\n🔍 Searching for '%s'...\n", name);
    searchDFS(root, name, "");
}

/**
 * Handle tree display
 */
void handleDisplayTree() {
    printf("\n🌳 DIRECTORY TREE\n");
    printf("========================================\n");
    displayTree(root, 0, true);
    printf("========================================\n");
}

/**
 * Handle directory change
 */
void handleChangeDirectory() {
    char name[MAX_NAME_LENGTH];
    
    printf("\n📂 CHANGE DIRECTORY\n");
    printf("Enter directory name (or '..' for parent, '/' for root): ");
    
    if (scanf("%49s", name) != 1) {
        printf("❌ Error: Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    changeDirectory(&currentDir, name);
}

/**
 * Handle show current path
 */
void handleShowPath() {
    printf("\n📍 CURRENT PATH\n");
    printf("Full path: ");
    printCurrentPath(currentDir);
    printf("\n");
}

/*
================================================================================
                            MAIN FUNCTION
================================================================================
*/

int main() {
    int choice;
    
    // Initialize file system with root directory
    root = createNode("root", 0);
    if (root == NULL) {
        printf("❌ Fatal Error: Could not create root directory!\n");
        return 1;
    }
    currentDir = root;
    
    // Welcome message
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║                                        ║\n");
    printf("║    FILE EXPLORER SYSTEM IN C           ║\n");
    printf("║    Using Tree Data Structure           ║\n");
    printf("║                                        ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\nWelcome! Your file system is ready.\n");
    
    // Main menu loop
    while (1) {
        printMenu();
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("❌ Error: Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                handleCreateFolder();
                break;
            
            case 2:
                handleCreateFile();
                break;
            
            case 3:
                handleDelete();
                break;
            
            case 4:
                handleSearch();
                break;
            
            case 5:
                handleDisplayTree();
                break;
            
            case 6:
                handleChangeDirectory();
                break;
            
            case 7:
                handleShowPath();
                break;
            
            case 0:
                printf("\n👋 Exiting File Explorer...\n");
                printf("🧹 Cleaning up memory...\n");
                freeTree(root);
                printf("✅ Goodbye!\n\n");
                return 0;
            
            default:
                printf("❌ Invalid choice! Please enter a number between 0 and 7.\n");
        }
        
        // Pause before showing menu again
        printf("\nPress Enter to continue...");
        getchar();
    }
    
    return 0;
}
