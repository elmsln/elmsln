# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  # centos 6.5 - 32 bit, uncomment below if you have a 32 bit OS
  #config.vm.box = "chef/centos-6.5-i386"

  # centos 6.5 - 64 bit
  config.vm.box = "puphpet/centos65-x64"
  # private network port maping, host files point to elmsln domains
  config.vm.network "private_network", ip: "10.0.18.55"
  # forward the vm ports for database and apache to local ones
  config.vm.network "forwarded_port", guest: 80, host: 80
  config.vm.network "forwarded_port", guest: 3306, host: 3306


  # run script as root
  config.vm.provision "shell",
    path: "scripts/vagrant/handsfree-vagrant.sh"

  # run as the vagrant user
  config.vm.provision "shell",
    path: "scripts/vagrant/cleanup.sh",
    privileged: FALSE

  # all done! tell them how to login
  config.vm.provision "shell",
    inline: "echo 'finished! go to http://online.elmsln.local and login with username admin and password admin. To edit files on the box point an sftp client to /var/www/elmsln on 0.0.0.0 u/p vagrant/vagrant port 2222.'"
end
