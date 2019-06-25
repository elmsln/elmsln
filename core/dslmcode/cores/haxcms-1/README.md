# HAXcms
Get all the details you want on [HAXTheWeb.org](https://haxtheweb.org/haxcms-1)!
HAXcms seeks to be the smallest possible back-end CMS to make HAX work and be able to build websites with it. Leveraging JSON Outline Schema, HAX is able to author multiple pages, which it then writes onto the file system. This way a slim server layer is just for basic authentication, knowing how to save files, and placing them in version control.

## Features
- All of HAX without a bloated CMS
- Incredibly simple, readable file structure of flat HTML files and lightning fast, high scale micro-sites
- cdn friendly configuration
- 0 config, 100% offline capable, PWA generation
- clean, simple theme layer abstracted from content
- No database (simple `.json` files help manage the data)
- Files you can reach out and touch, fork, and theme with ease!
- Support for multiple sites
- automatic git repo creation and management (never touch commandline again, but dive in if you really needed)
- Built in gh-pages publishing

# Requirements (PHP)
- PHP 7.1
- Apache 2.4
## Install and win the future, NOW!
### MAMP
- Download [MAMP](https://www.mamp.info/)
- Download this repo https://github.com/elmsln/HAXcms/archive/master.zip
- Place HAXcms files in the htdocs folder of MAMP.
- Turn MAMP on and click "My website"
- Copy the password it gives you, click to access HAX and then HAX YOUR WEB!
### Contaaaiiinnnneeerrrrs
- Clone this repo: `git clone https://github.com/elmsln/haxcms.git`
- Install a server container (recomnended). Here are some options (We support 'em all!):  
  - [docker](https://store.docker.com/search?type=edition&offering=community)
  - [ddev](https://ddev.readthedocs.io/en/latest/#installation)
  - [docksal](https://docksal.io/installation/)
  - [lando](https://docs.devwithlando.io/installation/installing.html)
  - [vagrant](https://www.vagrantup.com/downloads.html)
- Open a terminal window, go to the directory where you downloaded your container app and type `ddev start` (for ddev) or `fin init` (for docksal) or `lando start && lando magic` (for lando) or `vagrant up` (for vagrant).
- Go to the link any of them give you in a browser.
- Username/password is `admin`/`admin` to get building out static sites locally that you can push up anywhere!
- Click the icon in the top-right and you're off and running!
## Requirements (nodejs)
coming soon
## Scope
Generate `.html` files which have only "content" in them. Meaning the contents of the page in question. A simple method of adding new pages and managing the organization of those pages into a simple hierarchy (outline). Support for multiple mini web sites so that you can write a lot about different topics. HAXcms is only intended to be a micro-site generator and play nicely with the rest of the HAX ecosystem without needing a monster CMS in order to utilize it.

## Usage
Go to `yoursite.com` and login with the username and password you entered in the `_config/config.php` by clicking on the login icon

## HAXiam deployment
[HAXiam](https://github.com/elmsln/HAXiam) (HAX, I am) is a SaaS configuration for HAXcms.
It allows for the replication of HAXcms per user account for enterprise deployments. It's 
able to better interface with enterprise login systems while maintaining a clean copy of HAXcms.

HAXcms does not require HAXiam to operate but it is an alternate configuration that we support. 
Therefore if you see anything in the docs or under the hood referencing how to change settings 
when in that type of environment, you know why.
## License
[Apache 2.0](LICENSE.md)
