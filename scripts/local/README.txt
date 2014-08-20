ELMSLN Local development scripts

=== bash ===
To use the bash script included in the bash directory, create a directory in your home directory called .elmsln and create a file called elmsln-hosts. In here you’ll list all the ssh commands that you want to loop through and perform git pull origin master against.

An example of this would be a list of ssh targets / servers to connect to that you’ve got ssh key binding with and want to execute the elmsln upgrade script against. This is the true power of chain automation at work as it will spider all systems it finds in the elmsln-hosts directory, then spider for all sites it founds on those systems and execute a standard drupal upgrade routine. This eliminates the management of drupal at a code / db level and ensures that if the system worked on 1 instance (even if in vagrant) that this has a reasonable assurance of working without issue against all deploys of the network.

A ton of testing goes into the lead up to run this 1 command but then it can sit and do its magic without overwhelming the operator.

example elmsln-hosts file:
ssh -p 22 name@server.com
ssh -p 22 stuff@10.10.10.1

This would hit both hosts, login, go to the correct directory, and then execute the spider command.

As long as they have all been created based on the installation instructions you will be able to effectively spider through your galaxies and update all of them to the latest package. Similar scripts can be constructed for config directories too.

=== automator ===
Automator scripts that wrap these functions in them for local development have also been included. This can be useful when you are crazy and want to have a standard "wake up and start to take over the world" button that you press every morning which gets everything on version across the internet.

=== powermate ===
This is the set that I use with my PowerMate by Griffin technology.
Start your day the btopro way: press command and your power mate button.
"EVERYTHING IS AWEASOME":
— boots up sublime
- open github client
- vagrant up && vagrant ssh
- open a browser tab to online.elmsln.local
- performs a spidering git pull origin master on all defined elmsln-hosts sites
- and, of course, starts playing the song "Everything is Awesome"

This is mostly for example purposes and is a bit scary unless you know why you are doing it :).
