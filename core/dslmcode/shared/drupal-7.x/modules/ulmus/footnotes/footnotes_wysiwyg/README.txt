Footnotes Wysiwyg
--------------------
Installation Instructions:
1. Make sure you have enabled wither the WYSIWYG or CKEditor module. Otherwise
nothing will happen.
2. Enable the module in /admin/modules
3. Enable the "Add Footnote" button in the WYSIWYG or CKEditor module settings.

Note: If you are using the CKEditor module, in addition to adding the button
you must also check the 'Add Footnotes' checkbox for the 'Plugins' setting.


TinyMCE
----------------------
The TinyMCE plugin provides a simple dialog to enter footnote text that will be 
inserted as a [fn]square bracket[/fn] footnote into the text. (Ie the tags and
text are visible as is in your text.)

This is all the plugin currently does. Existing footnotes must be edited in
text, you cannot reopen them in the dialog. The value= attribute is not supported,
again, you must write it manually into the tag.

The plugin reuses the tiny_mce_popup.js - you can also point this at the 
tiny_mce_popup.js that resides in the tinymce/jscripts/tiny_mce directory of your 
Wysiwyg install by changing the file footnote.htm's <script> tag where the 
tiny_mce_popup.js is added.


CKEditor
------------------------
Note: The recommended CKEditor version that this plugin is known to work 
correctly with is CKEditor 3.3.1. Some newer versions (in particular 3.5.2 has
been tested) only partially work. See known issues.

This is a rather sophisticated plugin to show a dialog to insert
<fn> footnotes or edit existing ones. It produces and understands
the <fn>angle bracket</fn> variant and uses the fakeObjects API to
show a nice icon to the user, while producing proper <fn> tags when 
the text is saved or View Source is pressed. 

If a text contains footnotes of the [fn]square bracket[/fn] variant, 
they will be visible in the text and this plugin will not react to them.

This plugin uses Drupal.t() to translate strings and will not as such
work outside of Drupal. (But removing those function calls would be the only
change needed.) While being part of a Wysiwyg compatible module, it could 
also be used together with the CKEditor module. 


Credits
---------------------

Original author (TinyMCE): elgreg
Port to Drupal 6.x: hingo
CKEditor support: Owen Barton

Known issues
----------------------

Translation is currently not implemented. See http://drupal.org/node/672034
The few strings that would need translation are found in tinymce_plugin/footnote.(htm|js)

The Footnotes CKEditor plugin has been verified to work on CKEditor 3.3.1. On
newer versions, in particular 3.5.2 there is a bug that when right clicking on
an existing footnote, the "Edit footnote" entry is missing from the context
menu. Also, if one then clicks on the "Add footnote" toolbar button, the values
of the existing footnote are not shown in the dialog box, rather a new, empty
footnote dialog is shown. If "Ok" is clicked, the old footnote is lost and
replaced with the empty or new values.

