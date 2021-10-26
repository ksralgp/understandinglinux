# Linux Namespaces
## Namespaces And Processes
Namespaces are a feature of Linux related to processes and global system resources. A process in Linux belongs to a set namespaces. This relationship is described by a set of files in <code>/proc/[pid]/ns/[namespacetype]</code>. For example, Firefox is curretly running on my machine as PID 6171. The files in <code>/proc/6171/ns/</code> provide information on the different namespaces this process belongs to:
```
> ls -lh /proc/6171/ns/
total 0
lrwxrwxrwx 1 ksurable ksurable 0 Oct 25 12:53 cgroup -> 'cgroup:[4026531835]'
lrwxrwxrwx 1 ksurable ksurable 0 Oct 25 12:39 ipc -> 'ipc:[4026531839]'
lrwxrwxrwx 1 ksurable ksurable 0 Oct 25 12:53 mnt -> 'mnt:[4026531840]'
lrwxrwxrwx 1 ksurable ksurable 0 Oct 25 12:39 net -> 'net:[4026531992]'
lrwxrwxrwx 1 ksurable ksurable 0 Oct 25 12:39 pid -> 'pid:[4026531836]'
lrwxrwxrwx 1 ksurable ksurable 0 Oct 25 12:53 pid_for_children -> 'pid:[4026531836]'
lrwxrwxrwx 1 ksurable ksurable 0 Oct 25 12:53 time -> 'time:[4026531834]'
lrwxrwxrwx 1 ksurable ksurable 0 Oct 25 12:53 time_for_children -> 'time:[4026531834]'
lrwxrwxrwx 1 ksurable ksurable 0 Oct 25 12:39 user -> 'user:[4026531837]'
lrwxrwxrwx 1 ksurable ksurable 0 Oct 25 12:53 uts -> 'uts:[4026531838]'
```
There are 10 files in this directory that correspond to the 10 different types of namespace supported by my OS. Each namespace type is related to a different type of global system resource.

Namespaces are used to implement process isolation. Processes within the same namespace appear to have their own isolated instance of certain global resources. Changes to the global resources are visibile to other processes that are members of the namespace, but invisible to other processes. 

The namespaces a process belongs to can be controlled during process creation using <code>clone</code> or be adjusted for a process using <code>setns</code> or <code>unshare</code>.

## Namespace Types
Namespace types share a common idea of process membership and isolation. But, each namespace type has unique implementation details. Luckily, there is a manual page for each namespace type. The following table briefly describes each namespace type and provide the man command to learn more. An important detail found in the manual pages is the relationship between a newly created namespace and the namespace of the process creating it. Many namespaces have a concept of nesting where things in a child namespace are visible to its parent.

Namespace | Man page | Brief Description 
--------  | -------  | ----------------
PID | man pid_namespaces | Isolates process ID numbers and correspondigly processes 
User | man user_namespaces | Isolates security-related identifies and attributes like user IDs, group IDs, root directory. This allows for the creation of processes that are privelaged for operations inside a namespace, but is unprivelaged for operations outside the namespace
Mount | man mount_namespaces | Isolates the list of mounts seen by a process
cgroup | man cgroup_namespaces | Virtualizes the view of a process's cgroups
UTS | man uts_namespaces | Isolation of hostname and NIS domain name
Network | man network_namespaces | Isolation of system resources associated with networking. A physical network device can live in exactly one network namespace
Time | man time_namespaces | Virtualizes the values of two system clocks: CLOCK_MONOTONIC and CLOCK_BOOTTIME
IPC | man ipc_namespaces | Isolates certain Linux IPC resources like POSIX message queues

## System APIs related to Namespaces
The following APIs allow for control of the namespaces a process belongs to:
API | Brief Description
--- | ----------------
clone | General API for creating a child process similar to fork. Supports flags related to namespaces
setns | Allows the calling process to join an existing namespace
unshare | Moves the calling process to a new namespace

# References
https://man7.org/linux/man-pages/man7/namespaces.7.html

http://ifeanyi.co/posts/linux-namespaces-part-1/

https://www.redhat.com/sysadmin/7-linux-namespaces
