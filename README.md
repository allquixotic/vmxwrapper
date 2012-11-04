# vmxwrapper

[vmxwrapper](http://github.com/allquixotic/vmxwrapper) is a program designed to start VMWare Workstation or VMWare Player's `vmware-vmx` with the [Bumblebee]() project's `optirun` wrapper. 

### Why Is It Necessary?

`vmxwrapper` is necessary because `vmware-vmx` uses command line arguments that inhibit its being wrapped in a Bash script, and it also refuses to run if it is `fork()`'ed from a child process that is not `vmware`. I have not yet found another way to use the Nvidia GPU to render the VMware guest aside from running `vmxwrapper`.

### How Do I Compile It?

1. Download the source code first. Then run `make` in the source directory.

2. You should now become root, with `sudo bash` on Debian/Ubuntu, or `su` on Fedora/SUSE. This will give you a *root shell* (denoted by `#`), which means that every command executed in the shell from now on runs as root, until you type `exit` or otherwise close that shell.

3. Does the directory `/usr/lib/vmware` exist, and is it where you installed VMware? If **not**, then you **must** edit the source code of `vmxwrapper.c` to replace the path of `/usr/lib/vmware` to the path where the VMware binaries are installed. The remainder of this tutorial assumes you did that, and I also assume you will change the path `/usr/lib/vmware` in my instructions to the path where your VMware is installed. (Hint: On Fedora, it's **probably** in `/usr/lib64/vmware`.)

4. As root, run `chmod a+x vmxwrapper`

5. As root, run `chmod +s vmxwrapper`

6. As root, run `chown root:root vmxwrapper`

7. As root, run `cp vmxwrapper /usr/lib/vmware/bin/`

8. As root, run `mv /usr/lib/vmware/bin/vmware-vmx /usr/lib/vmware/bin/vmware-vmx.real`

9.  As root, run `mv /usr/lib/vmware/bin/vmxwrapper /usr/lib/vmware/bin/vmware-vmx`

That should be it! Now `vmware-vmx` will be wrapped in `optirun`.

Contact email address, in case this does not work for you:

smcnam AT gmail DOT com
