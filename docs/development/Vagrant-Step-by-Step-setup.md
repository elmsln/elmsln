ELMSLN Vagrant Instructions
==============
[Watch how to use this!](https://www.youtube.com/watch?v=ZeuDKzs6sj0&list=PLJQupiji7J5fygec37Wd-gAbpMj8c5A_C)
### What is this
This is a Vagrant profile for installing a fully functioning [ELMS Learning Network](https://github.com/elmsln/elmsln) in a single command!  This instance is for development purposes but you can follow the [installation instructions](https://elmsln.readthedocs.io/en/latest/INSTALL) to install this on any real server!

### How to use this to bring up ELMSLN
1. Install [VirtualBox](https://www.virtualbox.org/wiki/Downloads) (5.1.14+)
2. Install [Vagrant](http://www.vagrantup.com/downloads.html) (1.9.1+)
3. Install [git](http://git-scm.com/downloads)
4. Open Terminal(OSX/Linux) or PowerShell (Windows) and navigate to the folder you want elmsln in. Now clone the repository using the command (`git clone https://github.com/elmsln/elmsln.git`)
![clone elmsln](https://cloud.githubusercontent.com/assets/16597608/13260179/60875b1e-da28-11e5-865f-89e6586f370a.PNG)

### Spin up the development instance (OSX / Linux)
```
cd elmsln
sh developer
```

### Spin up the development instance (Windows)
Find Powershell, right click, select run as Administrator. Navigate to elmsln directory
```
cd elmsln
vagrant plugin install vagrant-vbguest
vagrant plugin install vagrant-hostsupdater
vagrant plugin install vagrant-cachier
vagrant up
```
If you have issues downloading the box try running `vagrant box add --insecure -c elmsln/ubuntu16 --force` ahead of time which will download just the box in question.
This will take a long time the first time you do it as it has to download a server image. After the first build, future builds from scratch should take about 10-12 minutes.

### After installation completes
Now you'll be able to jump into any of the domains that ELMSLN starts to establish for use! Go to http://online.elmsln.local/ after installation completes.  If it all worked you should see a new Drupal site running the Course Information System (CIS) distribution.
*If this address doesn't resolve, you may need to do this extra step at the bottom in Legacy - host file management*

You can log into this with `user: admin | password: admin`

![log in](https://cloud.githubusercontent.com/assets/329735/22887464/ca97877e-f1c7-11e6-98df-2207a421204d.png)

To connect to the console of your instance: `vagrant ssh`
Here you'll have access to command line elms called `leafy`. Type `leafy` to see developer options for selection. This also comes installed with a fully primed copy of `drush` so you can type `drush sa` to see a list of possible drupal sites to run commands against. `drush @elmsln` is a target that will run the command against every site it finds in the elmsln instance.

### Create a new course
1. Click Add, then select New Course
2. Create the name of the course. Ex: Art100
3. Choose which services to access under course network
4. Finish by clicking Create course
5. Wait while the services are installed
6. Once it says service is available, you can click Access service

### Why use this
It has been optimized and heavily tested for use with ELMS:LN and it is what we use in daily testing and development and is the easiest way to get up and running. The alternative is to deploy the system on a live server environment and hook up real IPs to DNS entries. This is great / realistic but a lot of times people just want to play with things before jumping in fully. Vagrant provides this and does so with minimal barriers to entry.

### Legacy - host file management
This step is now only required if you don't follow the above directions about how to get our development environment up and running. Add this code to your /etc/hosts (or [windows equivalent](http://www.howtogeek.com/howto/27350/beginner-geek-how-to-edit-your-hosts-file/)) so you can access it "over the web".
```
###ELMSLN development
# front facing addresses
10.0.18.55      courses.elmsln.local
10.0.18.55      media.elmsln.local
10.0.18.55      online.elmsln.local
10.0.18.55      analytics.elmsln.local
10.0.18.55      studio.elmsln.local
10.0.18.55      interact.elmsln.local
10.0.18.55      blog.elmsln.local
10.0.18.55      comply.elmsln.local
10.0.18.55      discuss.elmsln.local
10.0.18.55      inbox.elmsln.local
10.0.18.55      people.elmsln.local
10.0.18.55      innovate.elmsln.local
10.0.18.55      grades.elmsln.local
10.0.18.55      hub.elmsln.local
10.0.18.55      lq.elmsln.local
10.0.18.55      cdn1.elmsln.local
10.0.18.55      cdn2.elmsln.local
10.0.18.55      cdn3.elmsln.local

# backend webservices addresses
10.0.18.55      data-courses.elmsln.local
10.0.18.55      data-media.elmsln.local
10.0.18.55      data-online.elmsln.local
10.0.18.55      data-studio.elmsln.local
10.0.18.55      data-interact.elmsln.local
10.0.18.55      data-blog.elmsln.local
10.0.18.55      data-comply.elmsln.local
10.0.18.55      data-discuss.elmsln.local
10.0.18.55      data-inbox.elmsln.local
10.0.18.55      data-people.elmsln.local
10.0.18.55      data-innovate.elmsln.local
10.0.18.55      data-grades.elmsln.local
10.0.18.55      data-hub.elmsln.local
10.0.18.55      data-lq.elmsln.local
```

### Spin up the vagrant instance**
```
cd elmsln
sh developer
```

Now you'll be able to jump into any of the domains that ELMSLN starts to establish for use!  Go to http://online.elmsln.local/ after installation completes (grab a coffee, it takes awhile the first time to finish).  If it all worked you should see a new Drupal site running the Course Information System (CIS) distribution.

You can log into this with `user: admin | password: admin`

![log in](https://cloud.githubusercontent.com/assets/16597608/13260446/767d8ae6-da29-11e5-8346-393a09c54cf6.PNG)

To connect to the console of your instance: `vagrant ssh`

### Create a new course
1. Click Add, then select New Course
2. Create the name of the course. Ex: Art100
3. Choose which services to access under course network
4. Finish by clicking Create course
5. Wait while the services are installed
6. Once it says service is available, you can click Access service

### Why use this
It has been optimized and heavily tested for use with ELMS:LN and it is what we use in daily testing and development and is the easiest way to get up and running. The alternative is to deploy the system on a live server environment and hook up real IPs to DNS entries. This is great / realistic but a lot of times people just want to play with things before jumping in fully. Vagrant provides this and does so with minimal barriers to entry.

**Note: If you are experiencing an APDQC Error (https://github.com/elmsln/elmsln/issues/1843) when running `sh developer` after the first time please run the following commands to fix:

- `vagrant ssh (within the elmsln folder where you usually do sh developer)`
- `sudo service mysql restart`
- `logout`

This should fix your install and allow you to continue developing smoothly :)
