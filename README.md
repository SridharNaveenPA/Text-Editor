# Text-Editor
A basic command-line text editor written in C that supports writing text, undo/redo actions, reading content, and saving to a file. This project demonstrates linked list usage and file I/O in C.

## Features

- **Write text**: Add sentences to your document.
- **Undo/Redo**: Revert or reapply your last actions.
- **Read content**: Display current document content.
- **Save to file**: Save your work to a text file.
- **Simple menu**: Easy-to-use command-line interface.



## Getting Started

### Prerequisites

- GCC or any standard C compiler

### Compilation

```bash
gcc text_editor.c -o text_editor
```


## Usage

When you run the program, you’ll see a menu:

```
Welcome to the Text Editor!

-------- TEXT EDITOR MENU --------
1. Write text
2. Undo last action
3. Redo last action
4. Read content
5. Save to file
6. Exit
----------------------------------
Enter your choice:
```

**Example Session:**

```
Enter your choice: 1
Enter text to write: Hello World!
Text "Hello World!" written successfully!

Enter your choice: 1
Enter text to write: This is a simple C editor.
Text "This is a simple C editor." written successfully!

Enter your choice: 4
Current content:
Hello World! This is a simple C editor.

Enter your choice: 2
Undo completed.

Enter your choice: 4
Current content:
Hello World!

Enter your choice: 3
Redo completed.

Enter your choice: 4
Current content:
Hello World! This is a simple C editor.

Enter your choice: 5
Enter filename to save content: output.txt
Content saved to file 'output.txt'.

Enter your choice: 6
Exiting the text editor. Goodbye!
```



## File Structure

- `text_editor.c` — Main source code



## How It Works

- Each sentence is stored as a node in a singly linked list.
- Undo/Redo are managed using two separate linked lists.
- Content can be saved to a file line by line.



## Sample Output File (`output.txt`)

```
Hello World!
This is a simple C editor.
```


## License

This project is open-source and free to use for educational purposes.


## Author

*Sridhar Naveen P A*  
*GitHub: [SridharNaveenPA](https://github.com/SridharNaveenPA)*
