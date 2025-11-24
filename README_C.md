# 🗂️ File Explorer System - C Implementation

A **menu-driven file system simulator** implemented in C using a **Tree Data Structure** to represent hierarchical folders and files.

---

## 📋 Overview

This project simulates a hierarchical file system with interactive menu-driven operations:
- Create and manage files and folders
- Navigate through directories
- Search using DFS and BFS algorithms
- Move and delete files/folders
- Display tree structure with ASCII art

---

## 🏗️ Architecture

### Data Structure

The system uses a **Tree** with parent-child-sibling relationships:

```c
typedef struct Node {
    char name[50];            // Name of file or folder
    int isFile;               // 1 = file, 0 = folder
    struct Node *parent;      // Pointer to parent node
    struct Node *firstChild;  // First child (for folders)
    struct Node *nextSibling; // Next sibling in same directory
} Node;
```

**Tree Structure Example:**
```
        root
       /  |  \
   docs  pics  music
    |     |
  file1  img1
```

Each folder can have multiple children (files and folders), and siblings are linked together.

---

## ⚙️ Features

### Core Operations

| Feature | Description | Implementation |
|---------|-------------|----------------|
| **Create Folder** | Create new folder in current directory | Prevents duplicates |
| **Create File** | Create new file in current directory | Validates parent is folder |
| **Delete** | Delete file/folder recursively | Confirms before folder deletion |
| **Move** | Move file/folder to another location | Prevents circular references |
| **Search (DFS)** | Depth-First Search for files/folders | Recursive traversal |
| **Search (BFS)** | Breadth-First Search for files/folders | Queue-based traversal |
| **Display Tree** | Show directory structure | ASCII art with icons |
| **Change Directory** | Navigate to child/parent/root | Supports `.` and `..` |
| **Show Path** | Display current absolute path | Builds path from root |
| **List Directory** | Show contents of current folder | Sorted display |

### Advanced Features

✅ **Memory Management**: Proper malloc/free with no memory leaks  
✅ **Input Validation**: Error checking for all user inputs  
✅ **Error Handling**: Informative error messages  
✅ **Sorted Display**: Folders first, then alphabetically  
✅ **Path Operations**: Absolute and relative path support  
✅ **Recursive Operations**: Folder deletion, tree display  

---

## 🚀 Compilation and Execution

### Prerequisites
- GCC compiler (or any C compiler)
- Terminal/Command line

### Compilation

```bash
# Navigate to project directory
cd "DS Project - File Explorer"

# Compile with GCC
gcc -o file_explorer file_explorer.c -Wall -Wextra

# Or with optimization
gcc -O2 -o file_explorer file_explorer.c -Wall -Wextra
```

### Running the Program

```bash
# Execute the program
./file_explorer
```

---

## 📖 Usage Guide

### Menu Interface

When you run the program, you'll see:

```
========================================
       FILE EXPLORER SYSTEM
========================================
Current Directory: /root
========================================
1. Create Folder
2. Create File
3. Delete
4. Move
5. Search (DFS)
6. Search (BFS)
7. Display Tree
8. Change Directory
9. Show Current Path
10. List Current Directory
0. Exit
========================================
Enter your choice:
```

### Example Workflow

#### 1. Creating Folders and Files

```
Enter your choice: 1
📁 CREATE FOLDER
Enter folder name: Documents
✅ Folder 'Documents' created successfully!

Enter your choice: 2
📄 CREATE FILE
Enter file name: readme.txt
✅ File 'readme.txt' created successfully!
```

#### 2. Navigating Directories

```
Enter your choice: 8
📂 CHANGE DIRECTORY
Enter directory name: Documents
✅ Changed to directory: /root/Documents

# Go back to parent
Enter directory name: ..
✅ Changed to parent directory: /root
```

#### 3. Displaying Tree Structure

```
Enter your choice: 7
🌳 DIRECTORY TREE
========================================
📁 root [Current]
├── 📁 Documents
└── 📄 readme.txt
========================================
```

#### 4. Searching for Files

```
Enter your choice: 5
🔍 SEARCH
1. DFS (Depth-First Search)
2. BFS (Breadth-First Search)
Choose search type: 1
Enter search term: doc

🔍 Searching for 'doc'...
Using DFS:
  📁 /root/Documents
  📄 /root/Documents/doc1.txt
```

#### 5. Moving Files

```
Enter your choice: 4
🚚 MOVE
Enter name of file/folder to move: readme.txt
Enter destination folder name: Documents
✅ 'readme.txt' moved successfully!
```

#### 6. Deleting Items

```
Enter your choice: 3
🗑️  DELETE
Enter name of file/folder to delete: readme.txt
✅ File 'readme.txt' deleted successfully!

# For folders:
Enter name of file/folder to delete: Documents
⚠️  This will delete the folder and all its contents. Continue? (y/n): y
✅ Folder 'Documents' and all its contents deleted successfully!
```

---

## 🧪 Test Scenarios

### Test 1: Basic File Operations

```bash
1. Create folder "Projects"
2. Create folder "Documents"
3. Create file "notes.txt" in root
4. Create file "code.c" in Projects
5. Display tree
```

**Expected Output:**
```
📁 root [Current]
├── 📁 Documents
├── 📁 Projects
│   └── 📄 code.c
└── 📄 notes.txt
```

### Test 2: Navigation and Path Operations

```bash
1. Change directory to "Projects"
2. Show current path → /root/Projects
3. Create file "main.c"
4. Change to parent (..)
5. Show current path → /root
```

### Test 3: Search Operations

```bash
1. Create structure:
   - root
     - folder1
       - data.txt
     - folder2
       - database.csv
       - data.json
2. Search for "data" using DFS
```

**Expected Results:**
```
📄 /root/folder1/data.txt
📁 /root/folder2
📄 /root/folder2/database.csv
📄 /root/folder2/data.json
```

### Test 4: Move Operations

```bash
1. Create folder "src"
2. Create folder "backup"
3. Create file "main.c" in root
4. Move "main.c" to "src"
5. Display tree
```

**Expected:**
```
📁 root
├── 📁 backup
└── 📁 src
    └── 📄 main.c
```

### Test 5: Error Handling

```bash
# Test duplicate names
1. Create folder "test"
2. Try to create folder "test" again
   → ❌ Error: A file or folder with name 'test' already exists!

# Test invalid parent
1. Create file "doc.txt"
2. Try to create file inside "doc.txt"
   → ❌ Error: Cannot create file inside a file!

# Test move into self
1. Create folder "folder1"
2. Try to move "folder1" into "folder1"
   → ❌ Error: Cannot move a folder into itself or its descendants!
```

### Test 6: Recursive Deletion

```bash
1. Create folder "project"
2. Inside "project", create:
   - folder "src"
   - folder "tests"
   - file "README.md"
3. Inside "src", create files "main.c", "utils.c"
4. Delete "project" folder
```

**Result:**
- All nested files and folders deleted recursively
- Confirmation prompt appears before deletion

---

## 🔧 Implementation Details

### Key Algorithms

#### 1. Depth-First Search (DFS)
```c
void searchDFS(Node *node, const char *name, const char *currentPath) {
    if (node == NULL) return;
    
    // Check current node
    if (strstr(node->name, name) != NULL) {
        // Found match - print path
    }
    
    // Recursively search children
    Node *child = node->firstChild;
    while (child != NULL) {
        searchDFS(child, name, newPath);
        child = child->nextSibling;
    }
}
```

**Time Complexity**: O(n) where n = total nodes

#### 2. Breadth-First Search (BFS)
```c
void searchBFS(Node *root, const char *name) {
    Node *queue[1000];
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        Node *current = queue[front++];
        
        // Check current node
        if (match found) {
            // Print result
        }
        
        // Enqueue all children
        Node *child = current->firstChild;
        while (child != NULL) {
            queue[rear++] = child;
            child = child->nextSibling;
        }
    }
}
```

**Time Complexity**: O(n) where n = total nodes

#### 3. Recursive Tree Display
```c
void displayTree(Node *node, int depth, int isLast) {
    // Print indentation and connectors
    for (int i = 0; i < depth - 1; i++) {
        printf("│   ");
    }
    
    if (depth > 0) {
        printf(isLast ? "└── " : "├── ");
    }
    
    // Print node name
    printf("%s %s\n", icon, node->name);
    
    // Recursively display children
    if (!node->isFile) {
        Node *child = node->firstChild;
        while (child != NULL) {
            displayTree(child, depth + 1, isLastChild);
            child = child->nextSibling;
        }
    }
}
```

#### 4. Path Building
```c
char* getFullPath(Node *node) {
    char *path = malloc(MAX_PATH_LENGTH);
    char temp[MAX_PATH_LENGTH] = "";
    Node *current = node;
    
    // Build path by traversing up to root
    while (current != NULL) {
        // Prepend current node name
        sprintf(temp, "/%s%s", current->name, temp);
        current = current->parent;
    }
    
    strcpy(path, temp);
    return path;
}
```

**Time Complexity**: O(h) where h = height of tree

---

## 📊 Complexity Analysis

| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Create | O(n) | O(1) |
| Delete | O(m) | O(1) |
| Move | O(n + m) | O(1) |
| Search (DFS) | O(n) | O(h) |
| Search (BFS) | O(n) | O(w) |
| Display | O(n) | O(h) |
| Change Directory | O(k) | O(1) |
| Get Path | O(h) | O(h) |

Where:
- n = number of siblings to check
- m = number of nodes in subtree
- h = height of tree
- w = maximum width of tree
- k = number of children to search

---

## 🎯 Design Decisions

### Why Parent-Child-Sibling Structure?

1. **Memory Efficient**: Each node only stores 3 pointers
2. **Easy Traversal**: Can easily navigate up (parent) and down (children)
3. **Flexible**: Supports unlimited children per node
4. **Sorted Insertion**: Can maintain order during insertion

### Why Sorted Display?

- **User Experience**: Folders shown before files
- **Readability**: Alphabetical order makes finding items easier
- **Consistency**: Matches behavior of real file explorers

### Memory Management

- **Dynamic Allocation**: malloc for each node
- **Recursive Cleanup**: freeTree function recursively frees all nodes
- **No Leaks**: All allocated memory properly freed on exit

---

## 🐛 Error Handling

The system handles various error conditions:

| Error | Handling |
|-------|----------|
| Duplicate names | Check before creation |
| Invalid parent | Validate parent is folder |
| Delete root | Prevent with check |
| Delete current dir | Check and prevent |
| Move into self | Check ancestry |
| Non-existent paths | Return helpful error |
| Memory allocation failure | Check malloc return |
| Invalid input | scanf validation |

---

## 🔄 Possible Extensions

### 1. Undo/Redo Feature
```c
// Add operation stack
typedef struct Operation {
    enum OpType { CREATE, DELETE, MOVE } type;
    Node *node;
    Node *oldParent;
    struct Operation *next;
} Operation;

Operation *undoStack = NULL;
```

### 2. File Size Tracking
```c
typedef struct Node {
    // ... existing fields ...
    long size;  // File size in bytes
} Node;
```

### 3. Timestamps
```c
typedef struct Node {
    // ... existing fields ...
    time_t createdAt;
    time_t modifiedAt;
} Node;
```

### 4. Permissions
```c
typedef struct Node {
    // ... existing fields ...
    int permissions; // rwx format
} Node;
```

### 5. Save/Load to File
```c
void saveTree(Node *root, FILE *file);
Node* loadTree(FILE *file);
```

---

## 📝 Code Structure

```
file_explorer.c
├── Structure Definitions
│   └── Node struct
├── Helper Functions
│   ├── createNode()
│   ├── addChild()
│   └── findChild()
├── File Operations
│   ├── createFolder()
│   ├── createFile()
│   ├── deleteNode()
│   └── moveNode()
├── Search Operations
│   ├── searchDFS()
│   └── searchBFS()
├── Display Operations
│   ├── displayTree()
│   ├── getFullPath()
│   └── printCurrentPath()
├── Navigation
│   └── changeDirectory()
├── Menu Functions
│   ├── printMenu()
│   └── handle...() functions
└── Main Function
    └── Menu loop
```

---

## 🎓 Learning Outcomes

This project demonstrates:

✅ **Tree Data Structure**: Parent-child-sibling representation  
✅ **Recursive Algorithms**: DFS, tree display, deletion  
✅ **Iterative Algorithms**: BFS using queue  
✅ **Dynamic Memory Management**: malloc/free  
✅ **Pointer Manipulation**: Complex pointer relationships  
✅ **String Operations**: Path building, searching  
✅ **Menu-Driven Programming**: User interface design  
✅ **Error Handling**: Input validation and edge cases  

---

## 👥 Author

Created for **REVA University** - 3rd Semester Data Structures Project  
Date: October 2025

---

## 📚 References

- Data Structures textbook - Tree implementations
- C Programming - Dynamic memory management
- File system design principles

---

## 🙏 Acknowledgments

- Data Structures course instructor
- C programming resources
- Tree algorithms documentation

---

## Quick Reference Card

```
NAVIGATION:
  /    → Go to root
  ..   → Go to parent
  name → Go to child folder

OPERATIONS:
  Create Folder    → Option 1
  Create File      → Option 2
  Delete           → Option 3
  Move             → Option 4
  Search           → Option 5/6
  Display Tree     → Option 7
  Change Directory → Option 8
  Show Path        → Option 9
  List Contents    → Option 10
  Exit             → Option 0

TIPS:
  - Folders shown with 📁
  - Files shown with 📄
  - Current dir marked [Current]
  - Deletion asks for confirmation
  - Duplicate names not allowed
```

---

**Happy Exploring! 🚀**
