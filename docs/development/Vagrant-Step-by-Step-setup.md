ELMSLN Vagrant Instructions
==============
[Watch how to use this!](https://www.youtube.com/watch?v=ZeuDKzs6sj0&list=PLJQupiji7J5fygec37Wd-gAbpMj8c5A_C)
###What is this
This is a Vagrant profile for installing a fully functioning [ELMS Learning Network](https://github.com/elmsln/elmsln) in a single command!  This instance is for development purposes but you can follow the [installation instructions](http://docs.elmsln.org/en/latest/INSTALL/) to install this on any real server!

###How to use this to bring up ELMSLN
1. Install [VirtualBox](https://www.virtualbox.org/wiki/Downloads) (ensure you are on the latest version 5.0.14+)
2. Install [Vagrant](http://www.vagrantup.com/downloads.html) (you'll need Vagrant 1.7+)
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
vagrant up
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
This project is based on the [Vagrant Project](http://drupal.org/project/vagrant) on Drupal.org, but includes a number of tweaks.  It has been optimized and heavily tested for use with ELMS Learning Network.  It's what we use in daily testing and development and the drop dead easiest way to get up and running with such a complex system.

###Helpful Vagrant Plugins
* **VBGuest**  
   When handling a system through virtualization (a guest on a host), there are tools to simplify the process by allowing for things such as clipboard handoffs and file sharing. Within Virtualbox these tools are called VirtualBox Guest Tools. For them to work properly, they must match to the version of the Linux kernel that is installed in the guest operating system. If you upgrade/update your vagrant instance you're likely to have updated your Linux kernel. This is one of the most common reasons that sharing files into your VM is not working properly. You could manually update the VirtualBox Guest Tools, or you could have a robot do it for you. VBGuest is a script to automatically update your VirtualBox Guest Tools. To install vagrant vbguest, use `vagrant plugin install vagrant-vbguest` There is _not_ an activator in the elmsln Vagrantfile. More information about usage can be found in the [Vagrant Vagrant VBGuest Documentation](https://github.com/dotless-de/vagrant-vbguest)
* **Vagrant Cachier**  
   Vagrant Cachier is great if you are regularly rebuilding your virtual machine. The plugin identifies calls to code repositories and caches a local copy of the files that are downloaded. Then, on subsequent calls to the repository, the plugin checks the local cache before requesting the file from the remote repository. This reduces the data downloaded and, therefore, the time it takes to complete a VM setup. To install vagrant cachier, use `vagrant plugin install vagrant-cachier` There is a cache bucket activator in the [elmsln Vagrantfile](https://github.com/elmsln/elmsln/blob/master/Vagrantfile#L13). More information about usage can be found in the [Vagrant Cachier Documentation](http://fgrehm.viewdocs.io/vagrant-cachier/)
* **Vagrant unison**  
`vagrant plugin install vagrant-unison` can be used to enable a powerful rsync style method between your local machine and the virtual machine.
* Unisoned folder support via `unison` over `ssh` -> will work with any vagrant provider, eg Virtualbox or AWS.

###Usage

1. You must already have [Unison](http://www.cis.upenn.edu/~bcpierce/unison/) installed and in your path.
     * On Mac you can install this with Homebrew:  `brew install unison`
     * On Unix (Ubuntu) install using `sudo apt-get install unison`
     * On Windows, download [2.40.102](http://alan.petitepomme.net/unison/assets/Unison-2.40.102.zip), unzip, rename `Unison-2.40.102 Text.exe` to `unison.exe` and copy to somewhere in your path.
1. Install using standard Vagrant 1.1+ plugin installation methods. 
```
$ vagrant plugin install vagrant-unison
```
1. After installing, edit your Vagrantfile and add a configuration directive similar to the below:
```
Vagrant.configure("2") do |config|
  config.vm.box = "dummy"

  config.sync.host_folder = "src/"  #relative to the folder your Vagrantfile is in
  config.sync.guest_folder = "src/" #relative to the vagrant home folder -> /home/vagrant

end
```
1. Start up your starting your vagrant box as normal (eg: `vagrant up`)

###Start syncing Folders

Run `vagrant sync` to start watching the local_folder for changes, and syncing these to your vagrang VM.

Under the covers this uses your system installation of [Unison](http://www.cis.upenn.edu/~bcpierce/unison/), 
which must be installed in your path.

###Development

To work on the `vagrant-unison` plugin, clone this repository out, and use
[Bundler](http://gembundler.com) to get the dependencies:

```
$ bundle
```

Once you have the dependencies, verify the unit tests pass with `rake`:

```
$ bundle exec rake
```

If those pass, you're ready to start developing the plugin. You can test
the plugin without installing it into your Vagrant environment by just
creating a `Vagrantfile` in the top level of this directory (it is gitignored)
that uses it, and uses bundler to execute Vagrant:

```
$ bundle exec vagrant up 
$ bundle exec vagrant sync
```

###Other projects of interest
(some that have provided inspiration for the work here)
*  [https://github.com/msonnabaum/drupalcon-training-chef-repo](https://github.com/msonnabaum/drupalcon-training-chef-repo)
*  [http://drupal.org/sandbox/mbutcher/1356522](http://drupal.org/sandbox/mbutcher/1356522)
*  [http://drupal.org/project/drush-vagrant](http://drupal.org/project/drush-vagrant)
