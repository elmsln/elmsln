# HAXCMS
HAX CMS seeks to be the smallest possible back-end CMS to make HAX work and be able to build websites with it. Leveraging JSON Outline Schema, HAX is able to author multiple pages, which it then writes onto the file system.

## Scope
Generate `.html` files which have only "content" in them. Meaning the contents of the page in question. A simple method of adding new pages and managing the organization of those pages into a simple hierarchy (outline). Support for multiple mini web sites so that you can write a lot about different topics. HAXCMS is only intended to be a micro-site generator and play nicely with the rest of the HAX ecosystem without needing a monster CMS in order to utilize it.

## Features
- All the HAX without much of a CMS to power it
- Incredibly simple, readable file structure of flat HTML files
- No database (simple `.json` files help manage the data)
- Support for multiple sites

## Install
Download, checkout and get this package on a server (this is a PHP based implementation so your server should have PHP and Apache or Nginx at minimum). Go to `config.php` and fill in the information requested.

## Usage
Go to `{{yoursite.com}}` and login with the username and password you entered in the `config.php` by clicking on the login icon

## License
[Apache 2.0](LICENSE.md)