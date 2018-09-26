# OSAssignment_TBFE
#Name: Suraj Garg
#Roll: 2018202003

Guideline To Use FileExplorer  (FE)
------------------------------------------------------------------------
Git Hub Repository :  
Git Lab Repository : http://10.3.1.184/gargsuraj12/OSAssignment_TBFE.git
------------------------------------------------------------------------
File Name : makefile 
------------------------------
a) Dependencies are displayed in makeFile.
b) Program can be ./tbfeDriver
------------------------------------------------------------------------
Functionalities Implemented : (Index are Provided based on Indexes present in assignment document) 
----------------------------------------
Normal Mode : 

1. a) List Of Files and Directories is being Displayed as per details shared in assignment. 
	b) Scrolling is not implemented.  		
	c) File Explorer (FE) show the entries for "." and ".." .
	
2. a) i) Next Directory Content is displayed on press of "Enter" key if it is directory.
		ii) Files are getting displayed using xdg-open on press of "Enter" or "Right Arrow" key. 

3. a) User will be able to Go Back on "Left Arrow" or "Backspace" key if he has navigated before in forward directories.
		In case user is at application's root directory itself. On first left key press , he will not be able to move in backward direction.
	b) User will be able to Go Forward on Right arrow key on all directories.
		In case user is at opened directory itself for first time he will be not able to go to Current "." and Back ".." directories. 
		In case user is at intermediate directories , then he will not be able to go to anywhere on Current "." directory with right arrow key.
		In case user is at intermediate directories , then he will be able to go to anywhere on Back ".." directory with right arrow key. But maximum back he can go till application's root directory.	 
	c) On pressing BackSpace he can go to Up One Level. 
	d) On Pressing 'h' user will be navigated directly to the application's root directory.
		
Command Mode : 
On press of ":" user will be able to navigate from Normal Mode to Command Mode. 
Currently on press of "Esc+Enter" user will be able to navigate from Command Mode to Normal Mode. 
1. a) copy will work for single as well as multiple files but not for directories.
		 Note: Absolute destination path is required to copy files.
		Ex : copy qw.txt logs.txt /home/abcd						( /home/abcd will be full qualified path)
	b) move will work for single file and for directories and its subdirectories.
		 Note: Absolute source and destination path is required.
		Ex : move /home/user/Desktop/dir1/qw.txt  /home/user/Desktop/qw.txt						( /home/abcd will be full qualified path)			
	c) rename will work for single file as well as directory.
		Ex : rename old_name new_name 						(assuming the file or directory exist in current folder).
2. a) create_file will create file ; provided directory has rights in the folder where is it creating.
	Ex.  create_file newFile.txt  .								( inside the current directory )
			create_file newFile.txt  /home/abcd						( /home/abcd will be full qualified path)
	b) create_dir will create single directory ; provided directory has rights in the folder where is it creating.
	Ex.  create_dir sampleDir .  											(inside the current directory )
			create_dir sampleDir /home/abcd						( /home/abcd will be full qualified path)
3. a) delete_file will delete single file ; provided directory has rights in the folder where is it executing.
	Ex.  delete_file newFile.txt   .																( newFile.txt will be deleted if present in current folder )
			delete_file newFile.txt   /																	( newFile.txt will be deleted if present in application root directory )
			delete_file /home/abcd/newFile.txt										( /home/abcd/newFile.txt will be full qualified path of the file which need to be deleted )
	b) delete_dir will delete single directory ; provided directory has rights in the folder where is it executing.
	Ex.  delete_dir newDir  . 																	( newDir directory will be deleted if present in current folder )
			delete_file newDir   /																	( newDir will be deleted if present in application root directory )
			delete_dir /home/abcd/newDir								( /home/abcd/newDir will be deleted if present in current folder  with all its internal file recursively )
4. Goto Implemented
	 a) goto /																				(Will move the control of the application to the application's root directory and dispays all the files)
	 b) goto /home/abcd/														( where /home/abcd/ is the absolute path, willmove the control and list the files of that directory)	
5. Search Not Implemented.
6. SnapShot Not Implemented.
7. On press of "Esc+Enter" , user will be able to navigate to Normal Mode.	

------------------------------------------------------------------------
Assumptions : 

a) Please open the terminal in full screen mode before launching application to give proper layout.
b) Max File Entries displayed will be terminal row size-3 items.
c) For Command Mode , all the command will be written at last 2nd row from bottom.
d) Any Error or informative message while accessing the application will be displayed at bottom left of  the screen.
e) By Default the Focus of the cursor will be set on first entry of the directory.
g) Commands only accepts proper inputs with alphabets  and certain special character like Period (".") , Underscore("_") , backslash ("/"). 
h) File Name max will be 25 character. 

------------------------------------------------------------------------
Others :

a) On press of "q" or "Q" , if user is in Normal Mode , application will stop and set focus to terminal.
b) If any informative message is displayed on screen then it will get vanish on next directory change.
c) As an when a command execution is completed , old command will vanish out and focus will be set on for typing next new command.
