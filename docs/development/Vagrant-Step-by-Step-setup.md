ELMSLN Vagrant Instructions
==============
[Watch how to use this!](https://www.youtube.com/watch?v=ZeuDKzs6sj0&list=PLJQupiji7J5fygec37Wd-gAbpMj8c5A_C)
###What is this
This is a Vagrant profile for installing a fully functioning [ELMS Learning Network](https://github.com/elmsln/elmsln) in a single command!  This instance is for development purposes but you can follow the [installation instructions](https://elmsln.readthedocs.io/en/latest/INSTALL) to install this on any real server!

###How to use this to bring up ELMSLN
1. Install [VirtualBox](https://www.virtualbox.org/wiki/Downloads) (ensure you are on the version 5.0.26)
2. Install [Vagrant](http://www.vagrantup.com/downloads.html) (you'll need Vagrant 1.8.4)
3. Install [git](http://git-scm.com/downloads)
4. Navigate to the folder you want elmsln in, and clone the repository using the command (`git clone https://github.com/elmsln/elmsln.git`)
![clone elmsln](https://cloud.githubusercontent.com/assets/16597608/13260179/60875b1e-da28-11e5-865f-89e6586f370a.PNG)
5. Add this code to your /etc/hosts (or [windows equivalent](http://www.howtogeek.com/howto/27350/beginner-geek-how-to-edit-your-hosts-file/)) so you can access it "over the web":
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

###Spin up the vagrant instance
```
cd elmsln
sh developer
```

Now you'll be able to jump into any of the domains that ELMSLN starts to establish for use!  Go to http://online.elmsln.local/ after installation completes (grab a coffee, it takes awhile the first time to finish).  If it all worked you should see a new Drupal site running the Course Information System (CIS) distribution.

You can log into this with `user: admin | password: admin`

![log in](https://cloud.githubusercontent.com/assets/16597608/13260446/767d8ae6-da29-11e5-8346-393a09c54cf6.PNG)

To connect to the console of your instance: `vagrant ssh`

###Create a new course
1. Click Add, then select New Course
2. Create the name of the course. Ex: Art100
3. Choose which services to access under course network
4. Finish by clicking Create course
5. Wait while the services are installed
6. Once it says service is available, you can click Access service

###Why use this
It has been optimized and heavily tested for use with ELMS:LN and it is what we use in daily testing and development and is the easiest way to get up and running. The alternative is to deploy the system on a live server environment and hook up real IPs to DNS entries. This is great / realistic but a lot of times people just want to play with things before jumping in fully. Vagrant provides this and does so with minimal barriers to entry.
