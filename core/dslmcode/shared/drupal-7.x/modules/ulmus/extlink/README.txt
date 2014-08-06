
The External Links module is a very simple approach to adding icons to links
to external websites or e-mail addresses. It is a purely JavaScript
implementation, so the icons are only shown to users that have JavaScript
enabled.

External Links was written by Nathan Haug.
Built by Robots: http://www.lullabot.com

Install
-------
Simply install External Links like you would any other module.

1) Copy the extlink folder to the modules folder in your installation.

2) Enable the module using Administer -> Modules (/admin/build/modules).

3) No additional configuration is necessary though you may fine-tune settings at
   Administer -> Site configuration -> External Links (/admin/settings/extlink).

A note about the CSS
--------------------
This module adds a CSS file that is only a few lines in length. You may choose
to move this CSS to your theme to prevent the file from needing to be loaded
separately. To do this:

1) Open the .info file for your theme, add this line of code to prevent
   the extlink.css file from loading:
   stylesheets[all][] = extlink.css
2) Open the extlink.css file within the extlink directory and copy all the code
   from the file into your theme's style.css file.
3) Copy the extlink.png and mailto.png files to your theme's directory.

Note that you DO NOT need to make a extlink.css file. Specifying the file in the
info file is enough to tell Drupal not to load the original file.
