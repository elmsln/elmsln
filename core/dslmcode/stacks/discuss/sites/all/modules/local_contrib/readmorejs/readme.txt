Hey! There are a few things you need to get this module running but it's pretty easy.

First download the Readmore.js library to your libraries directory and rename it to "readmore.js" so that we've got a structure like:
sites/*/libraries/readmore.js/readmore.min.js

https://github.com/jedfoster/Readmore.js (Download zip, as of now there aren't any tagged releases)

Next up make sure that you're running jQuery version 1.7 or greater as this is a requirement of the plugin, this module won't check you've set this up properly.

Final step is to configure the module which you can do at /admin/config/user-interface/readmorejs. You will need to enter "Selectors" else this module won't do anything. These should be the elements you want to effect with the plugin.

There's also more things that you can configure, values will be check_plain'ed and have left out the callbacks options for now, if there's a demand will look at including.

Todo:
Make a few bits translatable.