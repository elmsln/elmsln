DESCRIPTION
-----------

This module uses the FitVids.js library for fluid width video embeds (e.g. flash video in <iframe>s). You don't need it for pure HTML5 videos.

It supports YouTube, Vimeo, Blip.tv and Kickstarter by default, and you should be able to use it with other video providers.

It's useful if you are using a responsive theme (such as Omega), and want the videos to scale.


CONFIGURATION
-------------

# jQuery selectors

You can usually use the defaults. It assumes that you'll want to apply it to all videos on the page. 

If your theme uses a different class or id, or you only want to target certain videos, you can specify that class/id in the video containers field. You can use any valid jQuery selector, e.g.,

~~~
#my-video-container
.content
body
~~~

You can specify as many containers as you want.


# Video providers

Not all players will work with FitVids, but you can try it out by adding the domain (in the Custom iframe URLs field).


REQUIREMENTS & INSTALLATION
---------------------------

Uses the Libraries API. 

You'll also need to download the jQuery plugin from https://raw.github.com/davatron5000/FitVids.js/master/jquery.fitvids.js before you can enable the module. 

Place it in the /sites/all/libraries/fitvids folder. 

Works best with jQuery 1.7 or above (use jquery_update or add a newer version to your theme manually), but you should be OK with the version that ships with Drupal.
