# Containers
## Containers, Isolation, and Packaging
In Linux, it is common to run a set of related processes within a container. When running within a container, processes only have visibility to system resources associated with the container. The processes running in the container have access to the Linux Kernel, but little to zero visibility into the host OS. Multiple containers can run simultaneously on a single host OS.


To support running in isolation, containers need to have little to zero outside dependencies. This is achieved through the use of a Container Image. This image contains the instructions and files needed to setup the container environment and start the entry process. Note, a container can only rely on access to the Linux kernel (via system calls) running within the Host OS. It cannot rely on libraries and packages installed on the Host OS because it is isolated from these files. Therefore, a Container Image contains data and instructions used to create a filesystem within the container with all of the dependent files. This filesystem often resembles a Linux distribution.

To summarize, a Container allows a set of processes to run in an isolated and self-contained environment on a Host OS. Multiple containers can run simultaneously on a Host OS. 

## Key Components of Containers

Component | Description
--------- | ----------
Container Image | A file that describes how to setup the environment within a running container. Any data/files needed to setup the environment should be part of this file. For example, this file describes how to setup the file system used in the container along with the files that belong to this filesystem.
Container Runtime | An application responsible for translating a container image into a running a container. The runtime is also responsible for managing the lifetime of the container.

## Userful Features of Containers

 Feature | Description
-------- | -----------
No manual dependency management | Running an application on Linux often requires installing the right dependent packages. A containerized application has all of its dependencies within its image 
Dependency isolation | Two applications with conflicting dependencies (IE different versions of the same library) are isolated from one another when run within containers
Consistent envrionment | A container fully defines its environment and reduces the chances of hitting "it worked on my machine"
Kernel managed isolation | Isolation of processes in different containers is achieved through Linux kernel features. A process running within a container does not have awareness of processes running in other containers or the host OS
Portability | A container can be deployed to a different machine
Horizontal Scaling | Multiple instances of an application can be started by running multiple containers from the same image
Lower Overhead Virtualization | Containers tend to have lower overhead than traditional virtual machines

## References
https://en.wikipedia.org/wiki/List_of_Linux_containers

https://en.wikipedia.org/wiki/OS-level_virtualization

https://www.redhat.com/en/topics/containers/whats-a-linux-container

https://www.redhat.com/en/topics/containers

https://github.com/opencontainers/image-spec/blob/main/spec.md

https://github.com/opencontainers/runtime-spec/blob/master/spec.md
