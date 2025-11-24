# Sample Test Scenarios for File Explorer System

## Test 1: Basic Operations
```
1. Start program
2. Press 1 → Create folder "Documents"
3. Press 1 → Create folder "Projects"
4. Press 1 → Create folder "Pictures"
5. Press 2 → Create file "readme.txt"
6. Press 7 → Display tree

Expected output:
📁 root [Current]
├── 📁 Documents
├── 📁 Pictures
├── 📁 Projects
└── 📄 readme.txt
```

## Test 2: Nested Structure
```
1. Press 8 → Change to "Documents"
2. Press 1 → Create folder "Work"
3. Press 2 → Create file "notes.txt"
4. Press 8 → Change to "Work"
5. Press 2 → Create file "report.doc"
6. Press 8 → ".." (go to parent)
7. Press 8 → ".." (go to root)
8. Press 7 → Display tree

Expected output:
📁 root [Current]
├── 📁 Documents
│   ├── 📁 Work
│   │   └── 📄 report.doc
│   └── 📄 notes.txt
├── 📁 Pictures
├── 📁 Projects
└── 📄 readme.txt
```

## Test 3: Search Operations
```
Setup:
- Create folders: dev, dev_backup
- Create files: data.txt, database.csv, readme.md

Search Test:
1. Press 5 → Choose 1 (DFS)
2. Enter "data"

Expected results:
📄 /root/data.txt
📄 /root/database.csv

3. Press 5 → Choose 1 (DFS)
4. Enter "dev"

Expected results:
📁 /root/dev
📁 /root/dev_backup
```

## Test 4: Move Operations
```
Setup:
- Create folder "source"
- Create folder "destination"
- Create file "file1.txt" in root

Move Test:
1. Press 4 → Move operation
2. Enter source: "file1.txt"
3. Enter destination: "destination"
4. Press 7 → Display tree

Expected: file1.txt should be inside destination folder
```

## Test 5: Delete Operations
```
Setup:
- Create folder "temp"
- Inside temp, create files: temp1.txt, temp2.txt
- Create folder "cache" inside temp

Delete Test:
1. Press 3 → Delete
2. Enter "temp"
3. Press 'y' to confirm
4. Press 7 → Display tree

Expected: temp folder and all contents deleted
```

## Test 6: Error Handling
```
1. Duplicate Test:
   - Press 1 → Create folder "test"
   - Press 1 → Try to create folder "test" again
   Expected: ❌ Error message about duplicate

2. Delete Root Test:
   - Navigate to root
   - Try to delete "root"
   Expected: ❌ Cannot delete root

3. Invalid Move Test:
   - Create folder "folder1"
   - Try to move "folder1" into "folder1"
   Expected: ❌ Cannot move into itself

4. File as Parent Test:
   - Create file "doc.txt"
   - Try to change directory to "doc.txt"
   Expected: ❌ Not a directory error
```

## Test 7: Navigation Test
```
1. Create nested structure:
   root/
   ├── level1/
   │   └── level2/
   │       └── level3/

2. Navigate down:
   - cd level1
   - cd level2
   - cd level3
   - Press 9 → Show path
   Expected: /root/level1/level2/level3

3. Navigate up:
   - cd .. (to level2)
   - cd .. (to level1)
   - cd / (to root)
   - Press 9 → Show path
   Expected: /root
```

## Test 8: Complex Real-World Scenario
```
Create a project structure:

1. Create folders:
   - src
   - tests
   - docs
   - config

2. Navigate to src:
   - Create main.c
   - Create utils.c
   - Create folder "headers"
   - Inside headers, create main.h

3. Navigate to tests:
   - Create test_main.c
   - Create test_utils.c

4. Navigate to docs:
   - Create README.md
   - Create API.md

5. Display complete tree
6. Search for ".c" files
7. Move API.md to root
8. Delete config folder

Final structure:
📁 root [Current]
├── 📁 docs
│   └── 📄 README.md
├── 📁 src
│   ├── 📁 headers
│   │   └── 📄 main.h
│   ├── 📄 main.c
│   └── 📄 utils.c
├── 📁 tests
│   ├── 📄 test_main.c
│   └── 📄 test_utils.c
└── 📄 API.md
```

## Test 9: BFS vs DFS Comparison
```
Setup:
Create structure:
root/
├── folder1/
│   ├── data.txt
│   └── subfolder1/
│       └── data.log
├── folder2/
│   └── data.json
└── data.csv

Test:
1. Search "data" using DFS (option 5, type 1)
2. Search "data" using BFS (option 5, type 2)

Compare order of results:
- DFS: Goes deep first (data.txt, data.log, then data.json, data.csv)
- BFS: Goes wide first (data.txt, data.json, data.csv, then data.log)
```

## Test 10: Stress Test
```
1. Create 10 folders: folder1 to folder10
2. In each folder, create 5 files: file1.txt to file5.txt
3. Display tree (should show 10 folders with 5 files each)
4. Search for "file" (should find 50 files)
5. Delete folder5 (should remove 5 files)
6. Display tree again
```

## Performance Test
```
1. Create deep nested structure (10 levels)
2. Navigate to deepest level
3. Show current path
4. Search from root
5. Navigate back to root using multiple ".."
6. Time taken should be reasonable
```

## Memory Test
```
1. Create large structure (many files and folders)
2. Delete everything except root
3. Exit program
4. No memory leaks should be reported (use valgrind if available)
```

## Command Sequence for Quick Test

```
1  Documents
1  Projects
2  readme.txt
7
8  Documents
2  notes.txt
8  ..
7
5  1  doc
4  readme.txt  Documents
7
3  readme.txt
7
0
```

This sequence tests: create folder, create file, display, navigate, search, move, delete, exit.
