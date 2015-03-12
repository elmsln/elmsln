handsfree-install.sh

This provides an installation routine that does everything without need for
interaction. This is great when installing in a completely automated manner where
you don’t need to go back in after the fact. Use this for a deployment being
completely setup to run ELMSLN from the onset.

This doesn’t require a root password, it assumes that root needs to be established
and setup on mysql at run time. Because of this, it will create an unknown mysql
root password and then use this to generate an elmslndbo account with a random password.

This information is then passed into the preinstall function along with other force fed
values (which can be piped into this script if needed as arguments) to setup a ELMSLN
deployment automatically and without much if any real input.

Because of this, wide sweeping assumptions are made about configuration so this is great
for running against something like digital ocean / amazon EC2 where you’re doing it
for other people inputting said information elsewhere or requesting a box from you.

If you are managing a deployment / network as a stand alone then you probably want to
run through the typical install routine until you’ve done it a few times.