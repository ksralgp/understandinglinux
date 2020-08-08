== Read this Article Instead ==
Searching around the interwebs this appears to be the best article on terminals and ttys. You can view this page as this article summarized in my words

http://www.linusakesson.net/programming/tty/index.php

So if you really want to know how things work read this article.

== Background ==
In Linux a tty is an abstraction for a text input/output device. But the story and full implementation is more complicated.

The name tty refers to hardware known as a TeleTYpewriter. A Teletypewriter can be thought of as a traditional electronic typewriter that communicates with a mainframe. Text input is provided by a keyboard and communicated to the mainframe over a serial wire. Messages from the mainframe are sent to the teletypewriter and printed to a piece of paper at the teletypewriter. As technology evolved this was replaced with a digital terminal that contained a digital keyboard and display which is a called a terminal. Over time an OS abstraction was needed to simplify how user-space applications (IE a shell) interacted with different I/O devices. So in summary, a tty was initially an OS abstraction used to represent a text input/output device connected to a computer via serial port.

<pre>
                                 |---------------------- Computer ----------------------------------------|
                                       |---------------- Kernel Space ----------------------|
Terminal <--> Serial Line <--> UART <--> UART Driver <--> Line Discipline <--> TTY Driver <--> User-Space

</pre>

An important Kernel concept associated with tty is line discipline. The line discipline determines how kernel handles special editing commands like backspace. For example a line discipline is provided that will buffer input and apply backspace prior to sending data to user-space. If a user-space application contains it own handling for these characters it can use the raw mode line discipline.

Another important concept is session management. Within a terminal a user is running 1 or more programs simultaneously and interacting with 1 of them, known as the foreground process/program. 

The triplet of (UART Driver, Line Discipline, TTY Driver) forms a notion of TTY device in the kernel. Like other devices, it is exposed to user-space via a device file under /dev.

== The Modern Terminal and TTY/PTY ==
As computing evolved (personal computers, windowed multi-tasking graphical environments, etc) the notion of a terminal evolved. Things no longer communicate over serial so terminal like interactions now happen on a terminal emulator. Let's start with a personal computer with an integrated keyboard and display (via graphics driver). The kernel provides a terminal emulator for interfacing with graphics and the keyboard.

<pre>
          |---------------------- Computer -----------------------------------------------------------------|
          |---------------- Kernel Space -----------------------------------------------------|
Display <--> Graphics Driver <-->  |Terminal Emulator | <--> Line Discipline <--> TTY Driver <--> User-Space Applications
Keyboard --> Keyboard Driver --->  |                  |
</pre>

This is how things are running when you boot into login without a window manager. Something I do out of paranoia on arch.

In a graphical environment like XFCE the terminal emulator is an application that runs in user-space that behaves like a terminal (text input/output). Many terminal emulators still rely on on parts of the kernel's TTY subsystem for session management and line discipline. The kernel provides a pty (psuedo terminal) abstraction for this.

<pre>
          |-----Kernel Space ---------------|
             | TTY Driver (PTY follower) | <---> User Space Applications (IE Bash)
                 |
		 |
             | PTY Primary               | <---> Terminal Emulator
</pre>

== How It Is Implemented ==





















. An abstraction for the interaction between mainframe an I/O device helps standardize:
* How an application sends and receives data
* How an endpoint I/O device sends and receives data



session manager

ps l <-- TTY column




	

/dev/pts/


infocmp
terminfo
curses
tty <-- tells you the tty associated with stdinput
stty <-- prints 

== Questions ==
How does SSH work?

== References ==
https://en.wikipedia.org/wiki/Computer_terminal#Text_terminals
https://unix.stackexchange.com/questions/4126/what-is-the-exact-difference-between-a-terminal-a-shell-a-tty-and-a-con
https://askubuntu.com/questions/14284/why-is-a-virtual-terminal-virtual-and-what-why-where-is-the-real-terminal
http://www.linusakesson.net/programming/tty/index.php
