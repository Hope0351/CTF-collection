# :game_die: Parrotos And Hack The Box Buildout Part 1 9Ced497169C9

---

A lot of this series is general tools and settings that will benefit most anyone using [HTB](https://www.hackthebox.eu). The finer details of which shell to use or how to set up an editor are very subjective, and therefore I keep those topics to a minimum in a later post. I will merely offer some useful aliases and other notes that I have found helpful.

## Prep

Download the [iso](https://www.parrotsec.org/download/) of your choice. I tend to go with the security mate version and will be using version 4.10, the latest stable release, for this walkthrough.

My virtual host is VMWare Fusion 12 on macOS Big Sur, and I use BIOS as my firmware of choice. I gave it a 60GB disk and 8GB of ram. Those resources are probably overkill, but I have them to spare, so why not.

While you certainly can install ParrtOS on bare metal, you should use a virtual machine if you are doing exercises like this. Not saying you are at risk, but these are hostile networks you are playing in.

## Virtual Machine Setup

Create a new virtual machine using the ISO you chose.

Click finish or customize the settings and available resources. One thing to keep in mind is that the network settings should stay NAT and autoselect. Selecting a bridged network may open the host up to malicious traffic.

## Installation

Boot into the Live installation, which is the first item in the boot menu and the default choice. From here on out, the choices are the same regardless of where you are installing the OS.

Click on Install Parrot and then click through the menu till you get to Partitions. I recommend you choose to erase the disk and let it partition automatically. It’s your choice to encrypt or not, I never bother encrypting VM’s as my host is always full-disk encrypted, and I turn it off when not using it.

Add your login details. I personally never set my machines to log me in automatically, but feel free if you want to for ease of use.

Review all the settings and make sure everything is as it should be.

Go ahead and install. This will take a while, so if you haven’t already, go [sign up](https://www.hackthebox.eu/invite) for HTB. When this finishes, restart the machine and select the first item on the boot screen which again, is the default.

## Sharing

Let's set up the sharing as that will make things a whole lot easier. This will also enable cut and past between the host and the virtual machine if it does not already work. At this point, I would create a snapshot so you have a functional clean image in case something breaks.

## Get matty jones’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I put the folder I want to share at my root, but really the location does not matter as long as you have the proper permissions.

Now we set it up in the VMware settings. Don’t worry about the warning message at the bottom. It is shown regardless.

We now configure it in Parrot. After you update */etc/fstab* bounce the box just to make sure all is light and bright. If you get an error message saying root is locked and you end up in a loop, the restore the snapshot you created and double check your fstab line. If you are following this, it is all but certain you mistyped something in there.

## Next Steps

At this point, you have a very capable foundation for working on HTB and various types of CTF’s. A few tweaks, though, can go a long way towards making your life a little easier and the OS a little more comfortable.

If you are more inclined towards the Offensive Security side of the fence, adding some additional tools and updating others would be a good idea.

If working on bug bounties, malware analysis, and exploit development, there are some additional tweaks that make development and debugging tasks easier.

Continuing with Part 2, we will dig into OS updates, an upgraded environment, additional tooling, and fixing some bugs in Parrot that are also present in other security-related distributions.

Further additions to the series will include methodologies, specific techniques, write-ups, and live hunts through the deep and dark web, using this specific box.

---
