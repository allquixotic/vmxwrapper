# vmxwrapper

[vmxwrapper](http://github.com/allquixotic/vmxwrapper) is a program designed to start VMWare Workstation or VMWare Player's `vmware-vmx` with the [Bumblebee]() project's `optirun` wrapper. 

### Why Is It Necessary?

`vmxwrapper` is necessary because `vmware-vmx` uses command line arguments that inhibit its being wrapped in a Bash script, and it also refuses to run if it is `fork()`'ed from a child process that is not `vmware`. I have not yet found another way to use the Nvidia GPU to render the VMware guest aside from running `vmxwrapper`.

### What Are The Dependencies?

1. You need a working Bumblebee installation. Verify that it works by comparing the output of `optirun glxinfo` and `glxinfo`.

2. You need a C compiler and a reasonably similar C library to GLIBC. `apt-get install gcc` or `yum install gcc` should take care of this on most distros.

3. You need to know your way around the console a little, although the instructions below are fairly explicit in telling you everything you need to know.

### How Do I Install It?

1. Download the source code and install your C compiler, first. Then run `make` in the source directory.

2. You should now become root, with `sudo bash` on Debian/Ubuntu, or `su` on Fedora/SUSE. This will give you a *root shell* (denoted by `#`), which means that every command executed in the shell from now on runs as root, until you type `exit` or otherwise close that shell.

3. Does the directory `/usr/lib/vmware` exist, and is it where you installed VMware? If **not**, then you **must** edit the source code of `vmxwrapper.c` to replace the path of `/usr/lib/vmware` to the path where the VMware binaries are installed. The remainder of this tutorial assumes you did that, and I also assume you will change the path `/usr/lib/vmware` in my instructions to the path where your VMware is installed. (Hint: On Fedora, it's **probably** in `/usr/lib64/vmware`.)

4. As root, run `chmod a+x vmxwrapper`

5. As root, run `chmod +s vmxwrapper`

6. As root, run `chown root:root vmxwrapper`

7. As root, run `cp vmxwrapper /usr/lib/vmware/bin/`

8. As root, run `mv /usr/lib/vmware/bin/vmware-vmx /usr/lib/vmware/bin/vmware-vmx.real`

9.  As root, run `mv /usr/lib/vmware/bin/vmxwrapper /usr/lib/vmware/bin/vmware-vmx`

10. Find the location of `librrfaker.so`, `libgefaker.so`, and `libdlfaker.so`. On Ubuntu, they are in a subdirectory of /usr/lib. On Fedora, they're probably in /usr/lib itself or /usr/lib64.
  You can use a tool such as `find /usr -name librrfaker.so` to find the path.

11. For each of the three libraries listed above, run: `chmod +s <path>`, where <path> is the path to the library.

That should be it! Now `vmware-vmx` will be wrapped in `optirun`.

### Tell Me More!

The gist of this program/procedure is the following:

 - The way `optirun` works is, it uses the `LD_PRELOAD` environment variable to tell the dynamic linker to load the three libraries listed above into an executable at the highest level of precedence. This means that when the program tries to resolve symbols that are available both in the system libraries and in the LD_PRELOADed libraries, it will choose the symbols implemented in the LD_PRELOADed library.

 - The `vmware-vmx` binary tries very hard not to be "wrapped" in anything. It will fail if you try to wrap it in a shell script.

 - The dynamic linker on Linux prevents libraries from being LD_PRELOADed into a process that is setuid root (that `+s` flag I kept giving to `chmod` in the instructions) -- **UNLESS** the preloaded libraries are also setuid root.

 - We solve these problems by forcing the dynamic linker to load our libraries by making them setuid root, then we use some hacks to fool vmware-vmx into thinking it isn't being wrapped in optirun by replacing the vmxwrapper process directly with the executable image of vmware-vmx.

Contact email address, in case this does not work for you:

smcnam AT gmail DOT com
