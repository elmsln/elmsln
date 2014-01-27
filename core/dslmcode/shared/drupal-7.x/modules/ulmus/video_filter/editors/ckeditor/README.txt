
##############################################
## ONLY if you use ckeditor WITHOUT wysiwyg ##
##############################################

Installation:

Do the following steps to add video_filter button to the CKEditor toolbar:

   1. Open ckeditor.config.js (in the ckeditor module root)

   2. Scroll down to the end of the file, right before "};" insert:

      // Video_filter plugin.
      config.extraPlugins += (config.extraPlugins ? ',video_filter' : 'video_filter' );
      CKEDITOR.plugins.addExternal('video_filter', Drupal.settings.basePath + Drupal.settings.video_filter.modulepath + '/editors/ckeditor/');

   3. Add button to the toolbar.

      3.1 Go to Configuration -> CKEditor (admin/config/content/ckeditor)
          Click "Edit" on the profile you what to use with Linkit.

      3.2 Expand "Editor appearance" and go to "Toolbar".

          The button name is: video_filter
          For example if you have a toolbar with an array of buttons defined as
          follows:

          ['Bold','Italic']

          simply add the button somewhere in the array:

          ['Bold','Italic','video_filter']

          (remember the single quotes).
