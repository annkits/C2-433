# Git Tutorial

## Оценка 3

### 1. Check Current Branch
Use `git status` to check the current branch:

```bash
On branch main
Your branch is up to date with 'origin/main'.
Untracked files:
  (use "git add <file>..." to include in what will be committed)
```

### 2. View Git Log
Run `git log` to view the commit history:

```bash
commit d44bf5b22122169461bd5ae044382fc64dd5ec4a (HEAD -> main, origin/main, origin/HEAD)
Author: annkits <annpodolskaya0965@gmail.com>
Date: Sat Mar 8 08:36:27 2025 +0700
    Update and rename lab2.c to linked_lists.c

commit 4cde8f6e21a8a1cd1e544d18c8624a7ebec6530a
Author: annkits <annpodolskaya0965@gmail.com>
Date: Mon Feb 24 15:41:30 2025 +0700
    Add files via upload

commit 51cd71f6be73505825ff2017bfb58f1b463ec2c8
Author: annkits <annpodolskaya0965@gmail.com>
Date: Sat Feb 22 12:19:28 2025 +0700
    Add files via upload
```

### 3. Create `sort.c` File
Create a file named `sort.c` and insert a sorting function (example: Selection Sort).

### 4. Check `git status` After Creating `sort.c`
```bash
On branch main
Your branch is up to date with 'origin/main'.
Untracked files:
  (use "git add <file>..." to include in what will be committed)
    git_moves/
nothing added to commit but untracked files present (use "git add" to track)
```

### 5. Stage Files
Stage the files using:
```bash
git add .
```

### 6. Check `git status` After Staging
```bash
On branch main
Your branch is up to date with 'origin/main'.
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
    new file: git_moves/chronology.docx
    new file: git_moves/sort.c
```

### 7. Commit Changes
Commit the staged changes:
```bash
git commit -m "Сообщение коммита: что поменялось"
```

Output:
```
2 files changed, 22 insertions(+)
create mode 100644 git_moves/chronology.docx
create mode 100644 git_moves/sort.c
```

### 8. Check `git status` After Commit
```bash
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)
nothing to commit, working tree clean
```

### 9. Add Comment to Commit
Add a comment to the same commit (likely amending the previous commit):
```bash
git commit --amend -m "Updated commit message"
```

### 15. Check `git status` and `git log`
```bash
commit 989e637c6a64e6da821395fbdb5a4bddfa123f6 (HEAD -> main)
Author: annkits <annpodolskaya0965@gmail.com>
Date: Sat Mar 8 09:26:41 2025 +0700
    aаaаaаaаaаa

commit 82214930e20e317f4c3df90398c5b8881ea3d6ad
Author: annkits <annpodolskaya0965@gmail.com>
Date: Sat Mar 8 09:18:09 2025 +0700
    aаaаa

commit e95a8b6d12c3a7454dcebcfdc583bc3858131a5c
Author: annkits <annpodolskaya0965@gmail.com>
Date: Sat Mar 8 09:07:20 2025 +0700
    Сообщение коммита: что поменялось
```

Files:
- `chronology.docx`: aаaаa
- `sort.c`: aаaаaаaаaаa

## Ветки (Branches)

### 1. Create a New Branch
Create a branch named `mybranch`:
```bash
git branch mybranch
# or
git checkout -b mybranch
```

### 2. List Branches
Check the created branch:
```bash
git branch
```
Output:
```
* main
  mybranch
```

### 3. Switch to `mybranch`
Switch to the new branch:
```bash
git switch mybranch
# or
git checkout mybranch
```
Output:
```
Switched to branch 'mybranch'
```

### 4. Check `git status` on Branch Switch
On `mybranch`:
```bash
On branch mybranch
nothing to commit, working tree clean
```

### 6. Create `file1.txt`
Create a file named `file1.txt` with your name (e.g., Ann Korotkova).

### 7. Stage and Commit `file1.txt`
```bash
git add file1.txt
git commit -m "txt file"
```
Output:
```
[mybranch be7d3b] txt file
1 file changed, 1 insertion(+)
create mode 100644 git_moves/file1.txt
```

### 8. View Branch History
```bash
git log --oneline --graph
```
Output:
```
* be7d3b (HEAD -> mybranch) txt file
* 989e637 (origin/main, origin/HEAD, main) aаaаaаaаaаa
* 8221493 aаaаa
* e95a8b6 Сообщение коммита: что поменялось
* d44bf5b Update and rename lab2.c to linked_lists.c
* 4cde8f6 Add files via upload
* 51cd71f Add files via upload
```

### 9. Switch Back to `main`
```bash
git switch main
# or
git checkout main
```
Output:
```
Switched to branch 'main'
Your branch is up to date with 'origin/main'.
```

### 10. View Log on `main`
```bash
git log --oneline --graph
```
Output:
```
* 989e637 (HEAD -> main, origin/main, origin/HEAD) aаaаaаaаaаa
* 8221493 aаaаa
* e95a8b6 Сообщение коммита: что поменялось
* d44bf5b Update and rename lab2.c to linked_lists.c
* 4cde8f6 Add files via upload
* 51cd71f Add files via upload
```

### 11. Create and Commit `file2.txt`
Create `file2.txt` and commit:
```bash
git add file2.txt
git commit -m "file2.txt"
```
Output:
```
[main 2b47d27] file2.txt
1 file changed, 1 insertion(+)
create mode 100644 file2.txt
```

### 12. View All Branches
```bash
git log --oneline --graph --all
```
Output:
```
* 2b47d27 (HEAD -> main) file2.txt
* be7d3b (mybranch) txt file
* 989e637 (origin/main, origin/HEAD) aаaаaаaаaаa
* 8221493 aаaаa
* e95a8b6 Сообщение коммита: что поменялось
* d44bf5b Update and rename lab2.c to linked_lists.c
* 4cde8f6 Add files via upload
* 51cd71f Add files via upload
```

### 13. Switch to `mybranch`
```bash
git switch mybranch
```

### 14. Check for `file2.txt`
`file2.txt` is not present in `mybranch` (created in `main`).

### 15. Compare Branches
```bash
git diff mybranch main
```
Output:
```
diff --git a/file2.txt b/file2.txt
new file mode 100644
index 0000000..4a03c87
--- /dev/null
+++ b/file2.txt
@@ -0,0 +1 @@
+Second file
\ No newline at end of file
diff --git a/git_moves/file1.txt b/git_moves/file1.txt
deleted file mode 100644
index e9aaa42..0000000
--- a/git_moves/file1.txt
+++ /dev/null
@@ -1 +0,0 @@
-Ann Korotkova
```

### 16. Add and Push `chronology.txt`
Add a text document with screenshots to `mybranch`, commit, and push:
```bash
git add git_moves/chronology.txt
git commit -m "Add chronology.txt with screenshots"
git push -u origin mybranch
```

### 17. Verify Branches on GitHub
Ensure both `main` and `mybranch` exist on GitHub. Push `main` changes:
```bash
git push origin main
```

## Оценка 4

### 1. Switch to `mybranch`
```bash
git switch mybranch
```

### 2. Update `sort.c`
Add a `main` function to `sort.c` with an array (e.g., `int a[] = {4, 2, 0};`) and call the sorting function.

### 3. Check `git diff`
Shows changes in `sort.c` (added `main` function and array).

### 4. Check `git diff --staged`
Empty, as no changes are staged.

### 5. Stage `sort.c`
```bash
git add sort.c
```

### 6. Check `git diff`
No output (changes are staged).

### 7. Check `git diff --staged`
Shows staged changes in `sort.c`.

### 8. Modify `sort.c`
Remove a number from the array in `sort.c`.

### 9. Check `git diff`
Shows the removed number.

### 10. Check `git diff --staged`
No output (modification not staged).

### 11. Explanation
- `git diff`: Compares working directory to staged changes.
- `git diff --staged`: Compares staged changes to the last commit.

### 12. Check `git status`
```bash
On branch mybranch
Your branch is up to date with 'origin/mybranch'.
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
    modified: sort.c
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
    modified: sort.c
```

### 13. Unstage `sort.c`
```bash
git restore --staged sort.c
```

### 14. Check `git status`
```bash
On branch mybranch
Your branch is up to date with 'origin/mybranch'.
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
    modified: sort.c
no changes added to commit (use "git add" and/or "git commit -a")
```

### 15. Stage and Commit
```bash
git add sort.c
git commit -m "15 commit"
```

### 16. View Log
```bash
commit b262ce9b3d09d8b3a456dd9480aba1d6a7e3c17c (HEAD -> mybranch)
Author: annkits <annpodolskaya0965@gmail.com>
Date: Sun Mar 9 11:16:02 2025 +0700
    15 commit
```

### 17. Add `printf` to `sort.c`
Add `printf("hello git\n");` to `main` in `sort.c`.

### 18. Contents of `sort.c`
```c
int main() {
    int a[] = {4, 2};
    int b = SelectionSort(a);
    printf("hello git\n");
}
```

### 20. Revert Changes
```bash
git restore sort.c
```

### 21. Contents of `sort.c` After Revert
```c
int main() {
    int a[] = {4, 2};
    int b = SelectionSort(a);
}
```

### 22. Check `git status`
```bash
On branch mybranch
Your branch is ahead of 'origin/mybranch' by 1 commit.
  (use "git push" to publish your local commits)
nothing to commit, working tree clean
```

### 23. Push `mybranch`
```bash
git push origin mybranch
```

## Ветки и Fast-Forward Merge

### 1. Create and Commit `greeting.txt`
```bash
echo "hello" > git_moves/greeting.txt
git add git_moves/greeting.txt
git commit -m "Add file greeting.txt"
```
Output:
```
[mybranch 22733f1] Add file greeting.txt
1 file changed, 1 insertion(+)
create mode 100644 git_moves/greeting.txt
```

### 2. Update `greeting.txt`
Add "hello" to `greeting.txt`, stage, and commit:
```bash
git add git_moves/greeting.txt
git commit -m "Add content to greeting.txt"
```

### 3. Create `feature/uppercase` Branch
```bash
git branch feature/uppercase
```

### 4. Switch to `feature/uppercase`
```bash
git switch feature/uppercase
```

### 5. Check `git status`
```bash
On branch feature/uppercase
nothing to commit, working tree clean
```

### 6. Update `greeting.txt`
Change content to `HELLO`.

### 7. Stage `greeting.txt`
```bash
git add git_moves/greeting.txt
```

### 8-9. Check Branches
```bash
git branch
```
Output:
```
  main
  mybranch
* feature/uppercase
```

### 10. Switch to `main`
```bash
git switch main
```

### 11. View `greeting.txt`
```bash
cat git_moves/greeting.txt
```
Output:
```
hello
```

### 12. Compare Branches
```bash
git diff feature/uppercase main
```
Output:
```
diff --git a/file2.txt b/file2.txt
deleted file mode 100644
index 4a03c87..0000000
--- a/file2.txt
+++ /dev/null
@@ -1 +0,0 @@
-Second file
\ No newline at end of file
diff --git a/git_moves/chronology.docx b/git_moves/chronology.docx
deleted file mode 100644
index e60de29..0000000
diff --git a/git_moves/chronology.txt b/git_moves/chronology.txt
new file mode 100644
index 0000000..d828477
--- /dev/null
+++ b/git_moves/chronology.txt
@@ -0,0 +1 @@
+допустим, здесь должны быть скриншоты...
\ No newline at end of file
diff --git a/git_moves/file1.txt b/git_moves/file1.txt
new file mode 100644
index 0000000..e9aaa42
--- /dev/null
+++ b/git_moves/file1.txt
@@ -0,0 +1 @@
+Ann Korotkova
```

### 13. Merge `feature/uppercase` into `main`
```bash
git merge feature/uppercase
```

### 14. View `greeting.txt` After Merge
```bash
cat git_moves/greeting.txt
```
Output:
```
HELLO
```

### 15. Delete `feature/uppercase`
```bash
git branch -d feature/uppercase
```

### 16. Merge `mybranch` into `main`
```bash
git merge mybranch
```

### 17. View Log
```bash
git log --oneline --graph --all
```

## Оценка 5

### 1. Create `branch1`
```bash
git branch branch1
git switch branch1
```

### 2. Create `file.txt`
```bash
echo "This is a relevant fact" > file.txt
```

### 3. Commit `file.txt`
```bash
git add file.txt
git commit -m "fact"
```

### 4. Switch to `main` and Update `file.txt`
```bash
git switch main
echo "This is an indispensable truth!" > file.txt
```

### 5. Commit `file.txt` in `main`
```bash
git add file.txt
git commit -m "truth"
```

### 6. View Log
```bash
git log --oneline --graph --all
```
Output:
```
* 15cfa49 (HEAD -> main) truth
* 15cfa47e (branch1) fact
```

### 7. Merge `branch1` into `main`
```bash
git merge branch1
```
This results in a merge conflict.

### 8. Check `git status` During Conflict
```bash
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)
You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)
Unmerged paths:
  (use "git add <file>..." to mark resolution)
    both added: file.txt
no changes added to commit (use "git add" and/or "git commit -a")
```

### 9. Resolve Conflict
Edit `file.txt` to resolve the conflict, then:
```bash
git add file.txt
git commit
```

### 10. View Log After Merge
```bash
git log --oneline --graph
```
Output:
```
* fecf16b (HEAD -> main) 1try
* 15cfa47e (branch1) fact
* 15cfa49 truth
```

### 11. Push Changes
```bash
git push origin main
```

## Merge Conflicts with MergeSort in Python

### 1. Create `mergesort.py` in `main`
Copy content from `base.py` into `mergesort.py`.

### 2. Stage and Commit
```bash
git add git_moves/mergesort.py
git commit -m "mergesort"
```
Output:
```
[main 1b5a811] mergesort
1 file changed, 5 insertions(+)
create mode 100644 git_moves/mergesort.py
```

### 3. Create `Mergesort-Impl` Branch
```bash
git branch Mergesort-Impl
git switch Mergesort-Impl
```

### 4. Update `mergesort.py`
Replace content with code from `righty.py`.

### 5. Commit Changes
```bash
git add git_moves/mergesort.py
git commit -m "righty"
```
Output:
```
[Mergesort-Impl cf6d810] righty
1 file changed, 89 insertions(+), 5 deletions(-)
rewrite git_moves/mergesort.py (98%)
```

### 6. Switch to `main` and Update `mergesort.py`
Replace content with code from `lefty.py`.

### 7. Commit Changes
```bash
git add git_moves/mergesort.py
git commit -m "lefty"
```
Output:
```
[main b39462e] lefty
1 file changed, 89 insertions(+), 5 deletions(-)
rewrite git_moves/mergesort.py (98%)
```

### 8. View Log
```bash
git log --oneline --graph
```
Output:
```
* b39462e (HEAD -> main) lefty
* 1b5a811 mergesort
```

### 9. List Branches
```bash
git branch
```
Output:
```
* main
  Mergesort-Impl
  mybranch
  branch1
```

### 10. Merge `Mergesort-Impl` into `main`
```bash
git merge Mergesort-Impl
```

### 11. Resolve Conflicts and Push
Resolve merge conflicts in `mergesort.py`, then:
```bash
git add git_moves/mergesort.py
git commit
git push origin main
```

### 12. Push Documentation
Push the document with results.