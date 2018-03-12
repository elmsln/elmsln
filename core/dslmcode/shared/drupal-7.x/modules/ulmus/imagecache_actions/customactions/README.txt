README
------
README for the custom actions effect module.


Dependencies
------------
Hard dependencies:
- Imagecache actions.
- Image (Drupal core).

Soft dependencies/recommended modules:
- Imagemagick (preferred toolkit).
- PHP filter (Drupal core).


Which toolkit?
--------------
Personally, I prefer the imagemagick toolkit:
- It is better in anti-aliasing, try to rotate an image using both toolkits and
  you will see what I mean.
- It does not execute in the PHP memory space, so is not restricted by the
  memory_limit PHP setting.
- The GD toolkit will, at least on my Windows configuration, keep font files
  open after a text operation, so you cannot delete, move or rename it anymore.


Installing
----------
As usual. After enabling the module you can add custom actions to images.


Custom action PHP snippets
--------------------------
Given the correct permission, the custom action effect allows you to write your
own PHP snippet that does the requested processing on the image. How it can do
so, depends on the toolkit.

For all toolkits, the snippet should return true to indicate success and false
to indicate failure.

GD
--
The GD image resource is available in $image->resource. You can call the GD
functions on this resource. This effect will query the width and height after
your processing, so you don't have to change that yourself.

Imagemagick
-----------
All real image processing is done at the end, if all effects have added their
command line arguments to the $image->ops array. So your custom action should
add the imagemagick commands and its parameters by adding new string entries to
the end of that array.

If your commands change the width or height of the resulting image, you should
record so by changing $image->info['width'] and/or $image->info['height'].

General
-------
To ease your task, this effect makes some information regarding the image being
processed available in a number of variables: $image, $image_context,
$image_style, and $image_effect_id. These variables are readily available in
your snippet.

$image is an object containing the following properties:
- source: string, the source of the image, e.g. public://photo.jpg
- info: array, example data:
   - width (int) 180
   - height  (int) 180
   - extension (string) png
   - mime_type (string) image/png
   - file_size (int) 4417
- toolkit: string, imagemagick or GD
- resource: resource. The GD image resource.
- ops: array. An array of strings with the ImageMagick commands.

$image_context is an associative array containing:
- effect_data: array, the data of this image effect, example data for the custom
  action effect:
   - php  (string)
- managed_file: object|null. A managed file object containing these properties:
   - fid (string) 2
   - uid (string) 1
   - filename  (string) photo.jpg
   - uri (string) public://photo.jpg
   - filemime  (string) image/jpeg
   - filesize  (string) 445751
   - status  (string) 1
   - timestamp (string) 1327525851
   - metatags  Array [0]
   - rdf_mapping Array [0]
- referring_entities: array|null. A nested array with (fully loaded) entities
  referring to the current image. The 1st level of entries is keyed by the field
  name, the 2nd by entity type, and the 3rd by entity id. Example data:
   - field_photo Array [1]
      - node  Array [1]
         - 12  Object of: stdClass
            - nid (string) 12
            - vid (string) 12
            - type  (string) page
            - author ...
            - timestamp ...
            - ...
- entity: object|null, the 1st entity in referring_entities. This is for easy
  access to the referring entity if it may be assumed that only 1 entity is
  referring to the current image.
- image_field: array|null, the 1st image field in entity that is referring to
  the current image. This is for easy access to the image field data if it may
  be assumed that only 1 image field is referring to the current image. Example
  data:
   - fid (int) 2
   - alt (string) ...
   - title (string) ...
   - ...

$image_style is an associative array containing the current image style being
processed. It ocntians a.o.:
- isid: the unique image style id
- name: machine name.
- label: Human readable name.
- effects: An array with the effects of this image style, ordered in the way
  they should be applied.

$image_effect_id is an int containng the unique id of the current image effect
being applied. This can be used to look the current image effect up in the
$image_style array.

Of course there are many other possible useful globals. Think of:
- base_url
- base_path
- base_root
- is_https
- user
- language
and of course $_SERVER and $_GET.

Using these information you can access entity data as follows:

Specific case (1 entity, of known entity_type, referring to the image):
<?php
$entity_type = 'node';
$field_name = 'my_field';
$entity = $image_context['entity'];
$field = field_get_items($entity_type, $entity, $field_name);
?>

Or the more general case (not knowing the referring type, or multiple entities
that may be referring to the image):
<?php
$referring_entities = $image_context['referring_entities'];
foreach ($referring_entities as $field_name => $field_referring_entities) {
  foreach ($field_referring_entities as $entity_type => $entities) {
    foreach ($entities as $entity_id => $entity) {
      $field = field_get_items($entity_type, $entity, $field_name);
    }
  }
}
?>

"Dynamic" parameters
--------------------
Thee are many requests for adding token support or allowing for dynamic
parameters in another way. However, the current image style processing does not
easily allow for this. But for these cases we have the custom action to our
rescue. It is quite easy to:
- Create you own array of parameters.
- Call the effect callback yourself

Exanple, calling the watermark/canvas overlay effect:
<?php
$data = array(
  'xpos' => 'center',
  'ypos' => 'center',
  'alpha' => '100',
  'scale' => '',
  'path' => 'module://imagecache_actions/tests/black-ribbon.gif',
);
return canvasactions_file2canvas_effect($image, $data);
?>

Or, to be on the safe side with effect info altering:
<?php
$definition = image_effect_definition_load('canvasactions_file2canvas');
$callback = $definition['effect callback'];
if (function_exists($callback)) {
  $data = array(
    'xpos' => 'center',
    'ypos' => 'center',
    'alpha' => '100',
    'scale' => '',
    'path' => 'module://imagecache_actions/tests/black-ribbon.gif',
  );
  return $callback($image, $data);
}
return FALSE;
?>
