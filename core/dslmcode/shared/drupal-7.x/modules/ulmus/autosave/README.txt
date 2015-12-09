
DESCRIPTION
===========
The Autosave module automatically saves a node after a period of time. Content types that can be autosaved as well as the
period of time a node is autosaved, is configurable.

Autosaved nodes are are saved as a snap shot of the form.

NOTE: this version of autosave only works for single form (of selected node type) on a page.


DEPENDENCIES
============
None

INSTALLATION
============
1. Place the "autosave" folder in your "modules" directory (i.e. modules/autosave).
2. Enable the Autosave module under Administer >> Site building >> Modules.
3. Under config for a node type select it to use Autosave.
5. Under Admin -> Site Config -> Autosave enter the period of time before each autosave (in milliseconds).

AUTHOR
======
original concept by Edmund Kwok (edmund.kwok [at] insyghtful.com)
Drupal 6 version and current maintainer: Peter Lindstrom sponsored by About.com
Drupal 7 version and current maintainer: Larry Garfield sponsored by American Public Media.

CHANGE LOG
==========
- 6.x-2.0 version is a complete re-write to remove dependencies on TinyMCE.
- this version is now tied to the WYSIWYG module and currently is known to work with FCK, CK and TinyMCE 3.0 editors but requires
the 6.x-2.x-dev version of WYSIWYG with this patch: http://drupal.org/node/614146#comment-2193764; this patch should be commited soon and will
eventually be expanded to include other editors.