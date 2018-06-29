# Grav Webcomponents Plugin

Webcomponents is a [Grav](http://github.com/getgrav/grav) plugin that can be used to get webcomponents integrated into your Grav site with ease. Simply drop your webcomponents into user/webcomponents (unpacked from bower_components if using a framework like Polymer).

# Installation

## GPM Installation (Preferred)

The simplest way to install this plugin is via the [Grav Package Manager (GPM)](http://learn.getgrav.org/advanced/grav-gpm).  From the root of your Grav install type:

    bin/gpm install webcomponents

## Manual Installation

If for some reason you can't use GPM you can manually install this plugin. Download the zip version of this repository and unzip it under `/your/site/grav/user/plugins`. Then, rename the folder to `webcomponents`.

You should now have all the plugin files under:

	/your/site/grav/user/plugins/webcomponents

# Usage

Create your own or download webcomponents from webcomponents.org. While not required, a library like Polymer is a great way to get started with Webcomponent based development. Place all custom webcomponents in the `user/webcomponents` directory and they'll automatically be added as imports to every page! It's that easy!


## Configuration

Webcomponents is **enabled** and **always loaded** by default.  You can change this behavior by setting `always_load: true` in the plugin's configuration.  Simply copy the `user/plugins/webcomponents/webcomponents.yaml` into `user/config/plugins/webcomponents.yaml` and make your modifications.

```
enabled: true                  # Enable / Disable this plugin
always_load: true              # If set to false you'll need to invoke when to use them manually
