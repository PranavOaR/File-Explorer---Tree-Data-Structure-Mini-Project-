# 📚 File Explorer - Complete Code Documentation

## Table of Contents
1. [Project Overview](#project-overview)
2. [Data Structures](#data-structures)
3. [Core Functions](#core-functions)
4. [File Operations](#file-operations)
5. [Search & Display Operations](#search--display-operations)
6. [Navigation Functions](#navigation-functions)
7. [Utility Functions](#utility-functions)
8. [Menu Functions](#menu-functions)
9. [Main Program Flow](#main-program-flow)
10. [Complexity Analysis](#complexity-analysis)

---

## Project Overview

### What is this project?
This is a **menu-driven file system simulator** written in C that demonstrates the use of a **tree data structure** with parent-child-sibling relationships. It allows users to:
- Create folders and files
- Navigate through directories
- Search for files/folders
- Delete files and folders
- Display the entire directory tree structure

### Why a Tree Data Structure?
A tree structure naturally represents a hierarchical file system where:
- **Root** = Main directory (`/`)
- **Nodes** = Folders or files
- **Parent pointers** = Link to parent directory (for navigation)
- **Child pointers** = Link to first child
- **Sibling pointers** = Link to next item in same directory

---

## Data Structures

### Node Structure
```c
typedef struct Node {
    char name[MAX_NAME_LENGTH];        // Name of file/folder (max 50 chars)
    int isFile;                        // 0 = folder, 1 = file
    struct Node *parent;               // Pointer to parent node
    struct Node *firstChild;           // Pointer to first child
    struct Node *nextSibling;          // Pointer to next sibling
} Node;
```

**Visual Example:**
```
        root (folder)
       /    |    \
   Docs  Images  Downloads
    /|     |        |
   A B     C        D
```

In this structure:
- `root` has `firstChild = Docs` and children linked via `nextSibling`
- `Docs` has `firstChild = A`, and B is in its `nextSibling`
- Each node has a `parent` pointer back to its parent

### Global Variables
```c
Node *root = NULL;          // Points to root directory
Node *currentDir = NULL;    // Points to current working directory
```

---

## Core Functions

### 1. `Node* createNode(const char *name, int isFile)`

**Purpose:** Creates a new node for a file or folder

**Parameters:**
- `name`: Name of the file/folder (string)
- `isFile`: 1 if it's a file, 0 if it's a folder (boolean)

**Returns:** Pointer to the newly created node

**What it does:**
1. Allocates memory for a new Node structure
2. Copies the name into the node
3. Sets the `isFile` flag
4. Initializes all pointers to NULL
5. Returns the node pointer

**Example:**
```c
Node *myFolder = createNode("Documents", 0);  // Create folder
Node *myFile = createNode("notes.txt", 1);    // Create file
```

**Time Complexity:** O(1) - Constant time (just allocation and assignment)
**Space Complexity:** O(1) - Fixed size node allocation

---

### 2. `void addChild(Node *parent, Node *child)`

**Purpose:** Adds a child node to a parent with sorted ordering

**Parameters:**
- `parent`: Parent node to add child to
- `child`: Child node to be added

**What it does:**
1. Validates parent and child are not NULL
2. Sets the child's parent pointer to the parent
3. Finds the correct position to insert the child (maintains sorting):
   - **Folders come before files** (folders alphabetically sorted, files alphabetically sorted)
   - This creates a natural file browser order
4. Inserts the child at the correct position

**Sorting Example:**
```
Before:
parent → [Photos] → [Settings] → [readme.txt] → [notes.txt]

After adding "Documents" (folder):
parent → [Documents] → [Photos] → [Settings] → [readme.txt] → [notes.txt]

After adding "index.html" (file):
parent → [Documents] → [Photos] → [Settings] → [index.html] → [notes.txt] → [readme.txt]
```

**Time Complexity:** O(n) - where n is number of siblings (must traverse to find insertion point)
**Space Complexity:** O(1) - No extra space needed

---

### 3. `Node* findChild(Node *parent, const char *name)`

**Purpose:** Searches for a child with a specific name

**Parameters:**
- `parent`: Parent node to search in
- `name`: Name to search for (string)

**Returns:** Pointer to the found child, or NULL if not found

**What it does:**
1. Starts from the first child of parent
2. Traverses sibling list comparing names
3. Returns the node if found
4. Returns NULL if not found

**Example:**
```c
Node *found = findChild(currentDir, "Documents");
if (found != NULL) {
    printf("Found!\n");
} else {
    printf("Not found!\n");
}
```

**Time Complexity:** O(n) - where n is number of siblings
**Space Complexity:** O(1) - No extra space needed

---

### 4. `int countChildren(Node *parent)`

**Purpose:** Counts the number of children a node has

**Parameters:**
- `parent`: Node to count children for

**Returns:** Number of children (0 if parent is NULL or has no children)

**What it does:**
1. Traverses the sibling list starting from firstChild
2. Increments counter for each sibling found
3. Returns the total count

**Time Complexity:** O(n) - where n is number of children
**Space Complexity:** O(1) - Only uses a counter variable

---

## File Operations

### 5. `void createFolder(Node *parent, const char *name)`

**Purpose:** Creates a new folder in a parent directory

**Parameters:**
- `parent`: Parent directory where folder will be created
- `name`: Name of the new folder

**What it does:**
1. Validates parent is not NULL and is a directory (not a file)
2. Checks if a child with the same name already exists
3. Creates a new node with `isFile = 0`
4. Adds it to parent using `addChild()`
5. Prints success or error message

**Error Handling:**
- ❌ Cannot create in a file
- ❌ Cannot create duplicate names
- ❌ Invalid parent directory

**Example:**
```c
createFolder(currentDir, "My Documents");
// Output: ✅ Folder 'My Documents' created successfully!
```

**Time Complexity:** O(n) - where n is number of siblings (due to addChild sorting)
**Space Complexity:** O(1) - One new node allocated

---

### 6. `void createFile(Node *parent, const char *name)`

**Purpose:** Creates a new file in a parent directory

**Parameters:**
- `parent`: Parent directory where file will be created
- `name`: Name of the new file

**What it does:**
1. Validates parent is not NULL and is a directory
2. Checks if a child with the same name already exists
3. Creates a new node with `isFile = 1`
4. Adds it to parent using `addChild()`
5. Prints success or error message

**Error Handling:**
- ❌ Cannot create in a file
- ❌ Cannot create duplicate names
- ❌ Invalid parent directory

**Example:**
```c
createFile(currentDir, "document.txt");
// Output: ✅ File 'document.txt' created successfully!
```

**Time Complexity:** O(n) - where n is number of siblings
**Space Complexity:** O(1) - One new node allocated

---

### 7. `void removeFromParent(Node *node)`

**Purpose:** Removes a node from its parent's child list (internal function)

**Parameters:**
- `node`: Node to remove from its parent

**What it does:**
1. Gets the parent of the node
2. If node is the first child, updates parent's firstChild pointer
3. Otherwise, traverses sibling list to find the previous node
4. Updates the previous node's nextSibling to skip the removed node

**Visual Example:**
```
Before: A → B → C → D
Remove C: A → B → D
```

**Time Complexity:** O(n) - where n is number of siblings
**Space Complexity:** O(1) - No extra space

---

### 8. `void deleteNodeRecursive(Node *node)`

**Purpose:** Recursively frees all memory of a node and its descendants

**Parameters:**
- `node`: Node to delete and its entire subtree

**What it does:**
1. Returns if node is NULL (base case)
2. Recursively calls itself on all children
3. Frees the node's memory

**Example Tree Deletion:**
```
       root
      /    \
   Folder1  Folder2
    /  \      /
   A    B    C

deleteNodeRecursive(Folder1) will delete: Folder1, A, B (all memory freed)
```

**Time Complexity:** O(m) - where m is number of nodes in subtree (visits each once)
**Space Complexity:** O(h) - where h is height (recursion call stack)

---

### 9. `void deleteNode(Node *node)`

**Purpose:** Deletes a file or folder with validation

**Parameters:**
- `node`: Node to delete

**What it does:**
1. Validates node exists
2. Prevents deletion of:
   - Root directory
   - Current directory
   - Ancestors of current directory
3. Removes node from parent's child list
4. Recursively deletes the node and all its contents
5. Prints success or error message

**Error Handling:**
- ❌ Cannot delete root directory
- ❌ Cannot delete current directory
- ❌ Cannot delete directory ancestors

**Example:**
```c
Node *toDelete = findChild(currentDir, "OldFolder");
deleteNode(toDelete);
// Output: ✅ Folder 'OldFolder' and all its contents deleted successfully!
```

**Time Complexity:** O(m) - where m is size of subtree
**Space Complexity:** O(h) - recursion depth

---

## Search & Display Operations

### 10. `void searchDFS(Node *node, const char *name, const char *currentPath)`

**Purpose:** Recursively searches the entire tree for files/folders matching a search term

**Parameters:**
- `node`: Current node being searched (start with root)
- `name`: Search term (substring matching)
- `currentPath`: Current path being built (for display)

**What it does:**
1. Base case: Returns if node is NULL
2. Builds the full path to current node
3. Checks if node's name contains the search term (substring match)
4. If match found, prints with icon (📄 for file, 📁 for folder)
5. If current node is a folder, recursively searches all children
6. Continues until entire tree is explored

**Traversal Order:** Pre-order DFS (processes node before children)

**Example Search:**
```
Search term: "doc"

Tree:
  root
   ├─ Documents
   │  └─ notes.doc
   └─ Downloads
      └─ old.doc

Output:
  📁 /root/Documents
  📄 /root/Documents/notes.doc
  📄 /root/Downloads/old.doc
```

**Time Complexity:** O(n) - where n is total number of nodes (visits each once)
**Space Complexity:** O(h) - recursion call stack depth

---

### 11. `void displayTree(Node *node, int depth, int isLast)`

**Purpose:** Recursively displays the entire tree with beautiful ASCII formatting

**Parameters:**
- `node`: Current node to display
- `depth`: Current depth in tree (for indentation)
- `isLast`: Is this the last sibling? (for correct connector characters)

**What it does:**
1. Prints indentation based on depth (using `│` and spaces)
2. Prints connector (├── for non-last, └── for last)
3. Prints icon: 📄 for files, 📁 for folders
4. Marks current directory with [Current]
5. Recursively displays all children

**ASCII Tree Example:**
```
📁 root [Current]
├── 📁 Documents
│   ├── 📄 notes.txt
│   └── 📄 resume.pdf
├── 📁 Pictures
│   ├── 📄 photo1.jpg
│   └── 📄 photo2.jpg
└── 📁 Downloads
    └── 📄 installer.exe
```

**Time Complexity:** O(n) - where n is total nodes (prints each once)
**Space Complexity:** O(h) - recursion depth for indentation

---

### 12. `char* getFullPath(Node *node)`

**Purpose:** Builds and returns the complete absolute path of a node

**Parameters:**
- `node`: Node to get path for

**Returns:** Dynamically allocated string with full path (must be freed by caller)

**What it does:**
1. Allocates memory for path string
2. Starts from the given node
3. Traverses up to root using parent pointers
4. Builds path string in reverse
5. Returns the complete path

**Path Building Example:**
```
Current node: "notes.txt" in "Documents" in "root"

Traversal: notes.txt → Documents → root
Result path: "/root/Documents/notes.txt"
```

**Time Complexity:** O(h) - where h is height of tree (height is path length)
**Space Complexity:** O(h) - allocates string of path length

---

### 13. `void printCurrentPath(Node *node)`

**Purpose:** Prints the current path to console (wrapper for getFullPath)

**Parameters:**
- `node`: Node to print path for

**What it does:**
1. Calls getFullPath to get the path
2. Prints the path
3. Frees the allocated memory
4. Handles NULL cases

**Example:**
```c
printCurrentPath(currentDir);
// Output: /root/Documents/Photos
```

**Time Complexity:** O(h) - delegates to getFullPath
**Space Complexity:** O(h) - delegates to getFullPath

---

## Navigation Functions

### 14. `void changeDirectory(Node **current, const char *name)`

**Purpose:** Changes the current working directory

**Parameters:**
- `current`: Pointer to current directory pointer (changed by reference)
- `name`: Directory name to navigate to (".." for parent, "/" for root)

**What it does:**
1. Validates current directory pointer
2. Handles special cases:
   - ".." → Navigate to parent directory
   - "/" → Navigate to root directory
3. Finds the child directory with given name
4. Validates it's a directory (not a file)
5. Updates current directory
6. Prints the new path

**Error Handling:**
- ❌ Directory not found
- ❌ Cannot navigate to file
- ❌ Already at root (for "..")

**Example:**
```c
changeDirectory(&currentDir, "Documents");
// Output: ✅ Changed to directory: /root/Documents

changeDirectory(&currentDir, "..");
// Output: ✅ Changed to parent directory: /root

changeDirectory(&currentDir, "/");
// Output: ✅ Changed to root directory: /root
```

**Time Complexity:** O(n) - where n is siblings in current directory (findChild)
**Space Complexity:** O(h) - for getFullPath string

---

## Utility Functions

### 15. `void clearInputBuffer()`

**Purpose:** Clears leftover input from the input buffer

**What it does:**
1. Reads characters from input one by one
2. Stops when newline or EOF is reached
3. Prevents input overflow in next scanf

**Why needed:**
- If user enters invalid input, leftover characters stay in buffer
- Without clearing, next scanf reads these leftover characters
- Causes unexpected behavior

**Example:**
```
User types: "abc" when number expected
scanf("%d") fails, "abc\n" stays in buffer
clearInputBuffer() removes "abc\n"
```

**Time Complexity:** O(k) - where k is number of leftover characters
**Space Complexity:** O(1) - No extra space

---

### 16. `void freeTree(Node *node)`

**Purpose:** Recursively frees all memory allocated for the entire tree

**Parameters:**
- `node`: Root node of tree to free

**What it does:**
1. Base case: Returns if node is NULL
2. Recursively calls freeTree on all children
3. Frees the node's memory
4. Prevents memory leaks

**Example:**
```c
freeTree(root);  // Frees entire file system tree
```

**Memory Cleanup Example:**
```
Tree:  root
      /    \
   Folder1  Folder2
    /
   File1

freeTree(root):
  - Recursively free Folder1
    - Recursively free File1 (freed)
    - Free Folder1 (freed)
  - Recursively free Folder2 (freed)
  - Free root (freed)

Result: All 5 nodes freed, no memory leaks
```

**Time Complexity:** O(n) - where n is total nodes (visits each once)
**Space Complexity:** O(h) - recursion call stack depth

---

## Menu Functions

### 17. `void printMenu()`

**Purpose:** Displays the main menu with current directory information

**What it does:**
1. Prints a formatted menu box
2. Shows current working directory path
3. Lists all 8 menu options (1-7 and 0 to exit)
4. Asks user for input

**Output:**
```
========================================
       FILE EXPLORER SYSTEM
========================================
Current Directory: /root/Documents
========================================
1. Create Folder
2. Create File
3. Delete
4. Search (DFS)
5. Display Tree
6. Change Directory
7. Show Current Path
0. Exit
========================================
```

**Time Complexity:** O(h) - for printing current path
**Space Complexity:** O(1) - Just printing

---

### 18. `void handleCreateFolder()`

**Purpose:** Menu handler for creating a folder

**What it does:**
1. Prompts user for folder name
2. Validates input
3. Calls createFolder with user's input
4. Handles errors

**User Interaction:**
```
📁 CREATE FOLDER
Enter folder name: MyFolder
✅ Folder 'MyFolder' created successfully!
```

**Time Complexity:** O(n) - delegates to createFolder
**Space Complexity:** O(1) - stores one name string

---

### 19. `void handleCreateFile()`

**Purpose:** Menu handler for creating a file

**What it does:**
1. Prompts user for file name
2. Validates input
3. Calls createFile with user's input
4. Handles errors

**User Interaction:**
```
📄 CREATE FILE
Enter file name: document.txt
✅ File 'document.txt' created successfully!
```

**Time Complexity:** O(n) - delegates to createFile
**Space Complexity:** O(1) - stores one name string

---

### 20. `void handleDelete()`

**Purpose:** Menu handler for deleting files/folders

**What it does:**
1. Prompts user for name to delete
2. Finds the node to delete
3. If it's a folder, asks for confirmation (prevents accidents)
4. Calls deleteNode
5. Handles errors

**User Interaction:**
```
🗑️  DELETE
Enter name of file/folder to delete: OldFolder
⚠️  This will delete the folder and all its contents. Continue? (y/n): y
✅ Folder 'OldFolder' and all its contents deleted successfully!
```

**Time Complexity:** O(n) - delegates to deleteNode
**Space Complexity:** O(h) - for recursive deletion

---

### 21. `void handleSearch()`

**Purpose:** Menu handler for searching files/folders

**What it does:**
1. Prompts user for search term
2. Calls searchDFS from root node
3. Displays all matches

**User Interaction:**
```
🔍 DFS SEARCH
Enter search term: doc

🔍 Searching for 'doc'...
  📁 /root/Documents
  📄 /root/Documents/notes.doc
  📄 /root/Downloads/old.doc
```

**Time Complexity:** O(n) - delegates to searchDFS
**Space Complexity:** O(h) - recursion depth

---

### 22. `void handleDisplayTree()`

**Purpose:** Menu handler for displaying entire tree

**What it does:**
1. Calls displayTree on root node
2. Shows entire file system structure

**User Interaction:**
```
🌳 DIRECTORY TREE
========================================
📁 root [Current]
├── 📁 Documents
│   ├── 📄 notes.txt
│   └── 📄 resume.pdf
├── 📁 Pictures
│   └── 📄 photo.jpg
└── 📁 Downloads
========================================
```

**Time Complexity:** O(n) - delegates to displayTree
**Space Complexity:** O(h) - recursion depth

---

### 23. `void handleChangeDirectory()`

**Purpose:** Menu handler for directory navigation

**What it does:**
1. Prompts user for directory name (supports ".." and "/")
2. Calls changeDirectory
3. Displays new path or error

**User Interaction:**
```
📂 CHANGE DIRECTORY
Enter directory name (or '..' for parent, '/' for root): Documents
✅ Changed to directory: /root/Documents
```

**Time Complexity:** O(n) - delegates to changeDirectory
**Space Complexity:** O(h) - for path string

---

### 24. `void handleShowPath()`

**Purpose:** Menu handler for displaying current path

**What it does:**
1. Prints the current working directory path
2. Uses printCurrentPath

**User Interaction:**
```
📍 CURRENT PATH
Full path: /root/Documents/Photos
```

**Time Complexity:** O(h) - for path building
**Space Complexity:** O(h) - for path string

---

## Main Program Flow

### `int main()`

**Purpose:** Entry point and main event loop

**What it does:**

1. **Initialization:**
   - Creates root directory node
   - Sets currentDir to root
   - Displays welcome message

2. **Main Loop:**
   - Displays menu
   - Gets user input
   - Validates input
   - Routes to appropriate handler using switch statement

3. **Menu Options:**
   ```
   1 → handleCreateFolder()
   2 → handleCreateFile()
   3 → handleDelete()
   4 → handleSearch()
   5 → handleDisplayTree()
   6 → handleChangeDirectory()
   7 → handleShowPath()
   0 → Exit program
   ```

4. **Exit:**
   - Frees entire tree
   - Prints goodbye message
   - Returns 0

**Program Flow Diagram:**
```
START
  ↓
Initialize root
  ↓
Display welcome
  ↓
LOOP:
  ├─ Print menu
  ├─ Get choice
  ├─ Route to handler
  ├─ Execute operation
  ├─ Press Enter
  └─ Back to LOOP
  
If choice = 0:
  ├─ Free tree
  ├─ Exit
  ↓
END
```

**Time Complexity:** O(1) per iteration (delegates to handlers)
**Space Complexity:** O(n) - entire tree structure in memory

---

## Complexity Analysis

### Time Complexity Summary

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| createNode | O(1) | Simple allocation and assignment |
| addChild | O(n) | n = siblings (must find insertion point) |
| findChild | O(n) | n = siblings (linear search) |
| createFolder | O(n) | n = siblings (calls addChild) |
| createFile | O(n) | n = siblings (calls addChild) |
| deleteNode | O(m) | m = subtree size (recursive deletion) |
| searchDFS | O(n) | n = total nodes (visits all) |
| displayTree | O(n) | n = total nodes (prints all) |
| getFullPath | O(h) | h = tree height (up to root) |
| changeDirectory | O(n) | n = siblings (findChild) |

### Space Complexity Summary

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Tree structure | O(n) | n = total nodes in tree |
| searchDFS | O(h) | h = recursion depth |
| displayTree | O(h) | h = recursion depth |
| getFullPath | O(h) | h = path length to root |
| deleteNode | O(h) | h = recursion depth |

---

## Key Concepts

### 1. Tree Data Structure
- **Hierarchical representation** of file system
- **3-pointer node** model (parent, firstChild, nextSibling)
- **Efficient** for navigating and searching

### 2. Recursion
- **DFS Search:** Recursively explores tree
- **Display Tree:** Recursively prints tree
- **Delete:** Recursively frees memory

### 3. Linked List Traversal
- Children are linked via sibling pointers
- Traversing siblings is like traversing a linked list
- Sorting implemented in addChild

### 4. Memory Management
- **Dynamic allocation** with malloc
- **Proper cleanup** with free
- **No memory leaks** with freeTree

### 5. Input Validation
- **Buffer clearing** to prevent input overflow
- **Error handling** for invalid operations
- **User confirmations** for destructive operations

---

## Example Usage Walkthrough

```c
// 1. CREATE STRUCTURE
root (created automatically)
  └─ Documents (created by user)
       └─ notes.txt (created by user)

// 2. CREATE FOLDER
User input: Create Folder → "Documents"
Result: Node created, added to root's children

// 3. NAVIGATE
User input: Change Directory → "Documents"
Result: currentDir now points to Documents node

// 4. CREATE FILE
User input: Create File → "notes.txt"
Result: Node created, added to Documents's children

// 5. DISPLAY TREE
User input: Display Tree
Result:
  📁 root
  └── 📁 Documents [Current]
      └── 📄 notes.txt

// 6. SEARCH
User input: Search → "notes"
Result:
  📄 /root/Documents/notes.txt

// 7. DELETE
User input: Delete → "notes.txt"
Result: File deleted, tree updated

// 8. EXIT
User input: Exit → 0
Result: Tree freed, program exits
```

---

## Common Pitfalls Avoided

1. **Memory Leaks:** Proper freeTree implementation
2. **Circular References:** Parent pointers checked before navigation
3. **Duplicate Names:** findChild prevents duplicates
4. **Invalid Operations:** Validation before each operation
5. **Buffer Overflow:** Input buffer clearing and size limits

---

## Conclusion

This implementation provides a complete, working file system simulator that demonstrates:
- ✅ Tree data structure usage
- ✅ Recursive algorithms
- ✅ Memory management
- ✅ User interface design
- ✅ Error handling
- ✅ Sorting and searching

The code is modular, well-commented, and efficient for an educational mini-project!
