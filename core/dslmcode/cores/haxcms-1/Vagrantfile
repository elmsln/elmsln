# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "ncaro/php7-debian8-apache-nginx-mysql"
  if Vagrant.has_plugin?("vagrant-cachier")
    config.cache.scope = :box
  end
  # private network port maping, host files point to haxcms domain
  config.vm.network "private_network", ip: "10.0.0.54"
  # forward the vm ports for database and apache to local ones
  config.vm.network "forwarded_port", guest: 80, host: 5454
  config.vm.network "forwarded_port", guest: 3306, host: 5406
  config.vm.hostname = "haxcms.local"
  config.hostsupdater.aliases = ["haxcms.local"]
  config.vm.boot_timeout = 600
  config.ssh.shell = "bash -c 'BASH_ENV=/etc/profile exec bash'"
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
    v.name = "haxcms"
  end
  # https://github.com/hashicorp/vagrant/issues/7508
  # fix for ioctl error
  config.vm.provision "fix-no-tty", type: "shell" do |s|
    s.privileged = true
    s.inline = "sed -i '/tty/!s/mesg n/tty -s \\&\\& mesg n \\|\\| true/' /root/.profile"
  end
  # fix apt lock error
  config.vm.provision "disable-apt-periodic-updates", type: "shell" do |s|
    s.privileged = true
    s.inline = "echo 'APT::Periodic::Enable \"0\";' > /etc/apt/apt.conf.d/02periodic"
  end
  # run script as root
  config.vm.provision "shell-install-haxcms", type: "shell" do |s|
    s.privileged = true
    s.inline = "ln -s /var/www/html ~/haxcms && cd /var/www/ && rm -rf html && git clone https://github.com/elmsln/haxcms.git && mv haxcms html && cd html && bash scripts/haxtheweb.sh admin admin admin@admin.admin admin && bash scripts/github-publishing-ssh.sh && sudo chmod 755 ~/.config"
  end
  # all done! tell them how to login
  config.vm.provision "shell-output-link", type: "shell" do |s|
    s.privileged = false
    s.inline = "ln -s /var/www/html ~/haxcms && echo 'finished! go to http://haxcms.local and login with username admin and password admin.'"
  end
end
