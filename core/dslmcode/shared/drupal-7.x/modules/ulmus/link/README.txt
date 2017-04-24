Module description
------------------
The link module can be count to the top 50 modules in Drupal installations and provides a standard custom content field for links. With this module links can be added easily to any content types and profiles and include advanced validating and different ways of storing internal or external links and URLs. It also supports additional link text title, site wide tokens for titles and title attributes, target attributes, css class attribution, static repeating values, input conversion, and many more.

Requirements / Dependencies
---------------------------
1. Drupal 6: Custom content module (CCK)
2. Drupal 7: Fields API is provided already by core [no dependencies].
3. Drupal 8: Link module is in core now. No module installation needed. Yay! Don't forget to activate it. It's deactivated by default.

INFO Since some misleading user reports we need to clarify here - Link module is NOT about to add links to any menus or the navigation nor primary/secondary menu. This can be done with default menu module (part of Drupal core). The Link module provides an additional custom field for storing and validating links to be added with any content type, which means another input block additional to your text-body, title, image and any other input you can make on new content creation.

Installation
------------
1. Drop the entire link module directory into your 'sites/all/modules' folder
2. Enable the module from the Administration area modules page (admin/build/modules)
3. Create or Edit a content-type and add a new field of type link (admin/content/types in D6, admin/structure/types in D7)

Configuration
-------------
Configuration is only slightly more complicated than a text field. Link text titles for URLs can be made required, set as instead of URL, optional (default), or left out entirely. If no link text title is provided, the trimmed version of the complete URL will be displayed. The target attribute should be set to "_blank", "top", or left out completely (checkboxes provide info). The rel=nofollow attribute prevents the link from being followed by certain search engines. More info at Wikipedia (http://en.wikipedia.org/wiki/Spam_in_blogs#rel.3D.22nofollow.22).

Example
-------
If you were to create a field named 'My New Link', the default display of the link would be:  <em><div class="field_my_new_link" target="[target_value]"><a href="[URL]">[Title]</a></div></em> where items between [] characters would be customized based on the user input.

The link module supports both, internal and external URLs. URLs are validated on input. Here are some examples of data input and the default view of a link:  http://drupal.org results in http://drupal.org, but drupal.org results in http://drupal.org, while <front> will convert into http://drupal.org and node/74971 into http://drupal.org/project/link

Anchors and query strings may also be used in any of these cases, including:  node/74971/edit?destination=node/74972<front>#pager

Theming and Output
------------------
Since link module is mainly a data storage field in a modular framework, the theming and output is up to the site builder and other additional modules. There are many modules in the Drupal repository, which control the output of fields perfectly and can handle rules, user actions, markup dependencies, and can vary the output under many different conditions, with much more efficience and flexibility for different scenarios. Please check out modules like views, display suite, panels, etc for such needs.