CONTENTS OF THIS FILE
---------------------

* Introduction
* Installation


INTRODUCTION
------------

Current Maintainer: Ryan Kois <ryan.kois@gmail.com>

Bulk Photo Nodes is a module that allows a user to upload or import many images
at once, and have many individual nodes created, one for each image . Where this
module significantly differentiates from other modules like Bulk Media Upload is
that the after uploading/importing the images, the user is given the opportunity
to edit all of the fields for each node in a single form.

Another form to the right acts as a bulk settings form where each field that has
a value is applied to each node's corresponding field, excpept where the user
has overridden the bulk settings form by specifying a value in the field of an
individual node.

The module is pluggable, leaving open the possibility to integrate the
module with various third party services.

INSTALLATION
------------

First, download the module to your site's modules directory, and enable the
module. Next, enable the module, and configure its permissions at 
admin/people/permissions. Bulk Photo Nodes provides a 'Create bulk photo nodes'
permission. Grant it to whoever you want to be able to create bulk photo nodes.

Next, visit a content type at admin/structure/types/manage/YOUR_CONTENT_TYPE.
You'll now see a 'Bulk Photo Node Settings' vertical tab near 'Publishing 
options'. Once in the tab, select an image field that you would like to use to 
establish the 'one image per node' relationship that the module asserts.

Enable the various submodules you'd like to use to upload/import your images.
Now if you go to the node add page for that content type, you should see the 
various forms that the submodules provide. In order to use the regular node add
form, append an ?override=1 to the URL.

Next, upload/import your photos, edit their fields as necessary and start saving
bulk photo nodes!
