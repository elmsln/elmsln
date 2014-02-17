INSTALLATION
============

1. Download & Enable Libraries API module.
http://drupal.org/project/libraries

2. Download Timeline JS libraries from Github:
https://github.com/VeriteCo/TimelineJS

3. Place Timeline JS libraries into sites/all/libraries/timeline

USAGE
=====

1. Create a content type with the right fields.

To create a TimelineJS view, you will need to use a content type that has
fields which correspond to display elements on the timeline.

When creating a TimelineJS view, you will need to map the following display
elements:

 * Headline (required) - Plain text; a high level summary.
 * Body text - Plain text; a paragraph or two of optional details.
 * Start and End Date - Required start and optional end of an event; can be a
   date field or timestamp.
 * Media URL - Drupal core image fields and link fields are supported; must
   contain a raw URL to an image or video.
 * Media Credit - Byline naming the author or attributing the source.
 * Media Caption - Brief explanation of the media content.
 * Tag - Content tagging; maximum of 6 tags.

Once a content type has the necessary fields, you can create your TimelineJS
view using the Views interface.

2. Create your new view

Using the "Add new view" form, create your new TimelineJS view and choose the
content type that has the required TimelineJS fields. Change the display format
to "TimelineJS". Click "Continue and edit" to finish setting up the new view.

3. Configuring the view

Click "Add" in the fields section of the Views interface to add all the required
fields from your content type. Once all your fields have been added to the view,
they will be available for field mappings.

Click the TimelineJS "settings" in format section. Edit the general
configuration of the timeline display and then edit the field mappings and
make sure each timeline element has a corresponding content field selected.
If you do not select a field mapping for all the required elements, you will
get errors on your view.

Click "Save" for your view to complete the configuration. The preview display
on the Views edit interface shows the data used by TimelineJS.
To see the TimelineJS display, access the block or page you just created.


MAINTAINERS
===========
* Juha Niemi (juhaniemi)
* Olli Erinko (operinko)
* Jon Peck (fluxsauce)
