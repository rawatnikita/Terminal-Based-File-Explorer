**TERMINAL BASED FILE EXPLORER**

This repo contains the implementation of a file explorer application,similar to the Linux file explorer ,but with limited features.

The application works in two modes : NORMAL MODE and COMMAND MODE. 

1. NORMAL MODE: The user can navigate through the directories in this mode, open files in vi editor and view the file information.

 Traversal:

 Go back - Left arrow key takes the user to the previously visited directory.

 Go forward - Right arrow key takes the user to the next directory.

 Up one level - Backspace key takes the user up one level.

 Home - ​ h ​ key takes the user to the home folder (the folder where the application was started).The root of the application is the directory where the    application was started.

 On pressing the enter key a file opens in vi editor.
 
2. COMMAND MODE: The user can enter shell commands to move, copy, delete or create new files/directories. The application enters the Command mode whenever “:” (colon) key is pressed. On pressing ​ ESC ​ key, the application goes back to Normal Mode.



All commands have been implemented using system calls.
