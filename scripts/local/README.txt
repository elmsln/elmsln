ELMSLN Local development scripts

=== bash ===
To use the bash script included in the bash directory, create a directory in your home directory called .elmsln and create a file called elmsln-hosts. In here you’ll list all the ssh commands that you want to loop through and perform git pull origin master against.

As long as they have all been created based on the installation instructions you will be able to effectively spider through your galaxies and update all of them to the latest package. Similar scripts can be constructed for config directories too.

=== automator ===
Automator scripts that wrap these functions in them for local development have also been included. This can be useful when you are crazy and want to have a standard “wake up and start to take over the world” button that you press every morning which gets everything on version across the internet.

=== powermate ===
This is the set that I use with my PowerMate by Griffin technology.
Start your day the btopro way: press command and your power mate button.
“EVERYTHING IS AWEASOME”:
— boots up sublime
- open github client
- vagrant up && vagrant ssh
- open a browser tab to online.elmsln.local
- performs a spidering git pull origin master on all defined elmsln-hosts sites
- and, of course, starts playing the song “Everything is Awesome”

This is mostly for example purposes and is a bit scary unless you know why you are doing it :).