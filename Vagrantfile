# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|

  # centos 6.5 - 32 bit, uncomment below if you have a 32 bit OS
  #config.vm.box = "chef/centos-6.5-i386"
  # centos 7.x - 64 bit
  #config.vm.box = "geerlingguy/centos7"
  # centos 6.7 - 64 bit
  config.vm.box = "bradallenfisher/centos7"
  if Vagrant.has_plugin?("vagrant-cachier")
    config.cache.scope = :box
  end
  # private network port maping, host files point to elmsln domains
  config.vm.network "private_network", ip: "10.0.18.55"
  # forward the vm ports for database and apache to local ones
  config.vm.network "forwarded_port", guest: 80, host: 80
  config.vm.network "forwarded_port", guest: 3306, host: 3306

  # automatically carve out 1/4 of RAM for this VM
  config.vm.provider "virtualbox" do |v|
    host = RbConfig::CONFIG['host_os']

    # Give VM 1/4 system memory or minimum 2 gigs
    if host =~ /darwin/
      # sysctl returns Bytes and we need to convert to MB
      mem = `sysctl -n hw.memsize`.to_i / 1024 / 1024 / 4
    elsif host =~ /linux/
      # meminfo shows KB and we need to convert to MB
      mem = `grep 'MemTotal' /proc/meminfo | sed -e 's/MemTotal://' -e 's/ kB//'`.to_i / 1024 / 4
    elsif host =~ /mingw32/
      mem = `wmic os get TotalVisibleMemorySize | grep '^[0-9]'`.to_i / 1024 / 4
      if mem < 2048
        mem = 2048
      end
    else # sorry weird Windows folks, I can't help you
      mem = 2048
    end
    # you can modify these manually if you want specific specs
    v.customize ["modifyvm", :id, "--memory", mem]
    v.customize ["modifyvm", :id, "--cpus", 1]
  end

  # run script as root
  config.vm.provision "shell",
    args: "https://github.com/elmsln/elmsln.git master https://github.com/elmsln/elmsln-config-vagrant.git",
    path: "scripts/vagrant/handsfree-vagrant.sh"

  # run as the vagrant user
  config.vm.provision "shell",
    path: "scripts/vagrant/cleanup.sh",
    privileged: FALSE

  # all done! tell them how to login
  config.vm.provision "shell",
    inline: "echo 'finished! go to http://online.elmsln.local and login with username admin and password admin. To edit files on the box point an sftp client to /var/www/elmsln on 0.0.0.0 u/p vagrant/vagrant port 2222.'"
end
