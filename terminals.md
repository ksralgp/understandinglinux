# Terminals
## Read this Article Instead
Searching around the interwebs this appears to be the best article on terminals and ttys. You can view this page as this article summarized in my words

http://www.linusakesson.net/programming/tty/index.php

So if you really want to know how things work read this article.

## Roughly What is Meant by "Terminal"
A terminal is a computer interface with text input/output. The name derives from a time when a user of main-frame would use a dedicated device, known as a terminal, for communicating with the  mainframe. The TTY subsystem within Linux manages the interaction between a terminal device, the kernel, and user-space. Today an application that provides a text input/output interface like terminals of the past is known as a terminal emulator. The TTY subsystem changed to provide abstractions for these applications as well. 

## Origins of the TTY Subsystem
One of the first terminals was a piece of hardware known as a TeleTYpewriter. A Teletypewriter can be thought of as a traditional electronic typewriter that communicates with a mainframe. Text input is provided by a keyboard and communicated to the mainframe over a serial wire. Messages from the mainframe are sent to the teletypewriter and printed to a piece of paper at the teletypewriter. As technology evolved this was replaced with a digital terminal that contained a digital keyboard and display which is a called a terminal. Over time an OS abstraction was needed to simplify how user-space applications (IE a shell) interacted with different I/O devices. This is known as the TTY subsystem, a name derived from the TeleTypeWriter.

The following diagram shows the interaction between a classic terminal, the kernel, and user-space:

<pre>
                                 |---------------------- Computer ----------------------------------------|
                                      |---------------- Kernel Space -----------------------|
                                                                                             |--- User Space ---|
Terminal <--> Serial Line <--> UART <--> UART Driver <--> Line Discipline <--> TTY Driver <----> Applications

</pre>

The triplet of (UART Driver, Line Discipline, TTY Driver) forms a notion of TTY device in the kernel. Like other devices, it is exposed to user-space via a device file under /dev.

The line discipline determines how kernel handles special editing commands like backspace. For example a line discipline is provided that will buffer input and apply backspace prior to sending data to user-space. If a user-space application contains its own handling for these characters it can use the raw mode line discipline.

So in summary, a tty was initially an OS abstraction used to represent a text input/output device connected to a computer via serial port. The abstraction is exposed to user-space as a device.

## The Modern Terminal and TTY/PTY
As computing evolved (personal computers, windowed multi-tasking graphical environments, etc) the notion of a terminal evolved. Things no longer communicate over serial so terminal like interactions now happen on a terminal emulator. Let's start with a personal computer with an integrated keyboard and display (via graphics driver). The kernel provides a terminal emulator for interfacing with graphics and the keyboard.

<pre>
          |---------------------- Computer -----------------------------------------------------------------|
          |---------------- Kernel Space -------------------------------------------------------|
                                                                                                 |--- User Space ---| 
Display <--> Graphics Driver <-->  | Terminal Emulator | <--> Line Discipline <--> TTY Driver <----> Applications
Keyboard --> Keyboard Driver --->  |                   |
</pre>

This is how things are running when you boot into login without a window manager. Something I do out of paranoia on arch.

In a graphical environment like XFCE the terminal emulator is an application that runs in user-space that behaves like a terminal (text input/output). Many terminal emulators still rely on on parts of the kernel's TTY subsystem for session management and line discipline. The kernel provides a pty (psuedo terminal) abstraction for this.

<pre>
          |-----Kernel Space ----------------|
                                              |-------- User Space ------------------|
             | TTY Driver (PTY follower) | <-----> User Space Applications (IE Bash)
                        -----
                          |
                          |
                        -----
             |       PTY Primary         | <---> Terminal Emulator
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

## Information Missing a Home
Another important concept is session management. Within a terminal a user is running 1 or more programs simultaneously and interacting with 1 of them, known as the foreground process/program.

## Questions
How does SSH interact with the tty subsystem?

## References
https://en.wikipedia.org/wiki/Computer_terminal#Text_terminals

https://unix.stackexchange.com/questions/4126/what-is-the-exact-difference-between-a-terminal-a-shell-a-tty-and-a-con

https://askubuntu.com/questions/14284/why-is-a-virtual-terminal-virtual-and-what-why-where-is-the-real-terminal

http://www.linusakesson.net/programming/tty/index.php
