# Environment Variables
The [environ](https://man7.org/linux/man-pages/man7/environ.7.html) man page does an excellent job explaining Environment and Environment Variables. See that page first.

## Process Environment
A process in Linux has an associated Environment accessible in the external variable 'environ'
```
extern char **environ
```
This variable points to an array of NULL terminated strings. Each element of the array defines an Environment variable using the syntax `name=value`. A set of APIs are provided for interacting with 'environ`:
API | Description 
--- | -----------
getenv | Get the value of an Environment Variable
setenv | Set the value of an Environment Variable. An existing variable is only modified based on an overwrite argument
unsetenv | Deletes a variable from the Environment
putenv | Set the value of an Environment Variable. Always overwrites an existing variable.

### Environment Inheritance
The Environment a process starts with is dependent on the process creation API and its arguments:
API | Created Process Environment
--- | ---------------------------
fork | The child process has a copy of the parent process Environment
execl, execlp, execv, execvp | The Environment of the new process image is inherited from the process calling the exec* API
execle, execvpe | The Environment of the new process image is specified as an input argument

## Shell Environment
Most shell languages support scoped Environment variables:
* Locally Scoped - Locally managed by the shell. A child process launched by the shell does not inherit this variable
* Exported - Placed in the Environment of the shell process. A child process launched by the shell will inherit this variable in its environment

Different shells use different syntax to signify local versus exported
Shell | Local Syntax | Exported Syntax
----- | ------------ | ---------------
Bash | name=value | export name=value
Fish | set name value | set -x name value


## Common Environment Variables
Name | Common Usage
---- | ------------
PATH | A sequence of directories many programs search to resolve an executable specified by filename only. Directory names are separated by a ':' character. Note the APIs execlp and execvp try to resolve names using PATH
USER | The name of the logged-in user

# Links 
https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap08.html<br>
https://man7.org/linux/man-pages/man7/environ.7.html<br>
https://man7.org/linux/man-pages/man3/exec.3.html<br>
https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html<br>
https://fishshell.com/docs/current/cmds/set.html#cmd-set
