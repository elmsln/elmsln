ACKNOWLEDGEMENTS

This is the next generation of Corresponding Node References. So, thanks are due
to everyone who ever worked on CNR!

DESCRIPTION

CER keeps reference fields in sync. If entity Alice references entity Bob, CER will make Bob back-reference Alice automatically, and it will continue to keep the two in sync if either one is changed or deleted. CER does this by way of “presets”, which are relationships you set up between reference-type fields.

By “reference-type fields”, I mean any kind of field that references an entity. Out of the box, CER can integrate with the following field types:

- Entity Reference
- Node Reference
- User Reference
- Taxonomy Term Reference
- Profile2 (using the cer_profile2 add-on module)
- Commerce Product Reference (using the cer_commerce add-on module)

CER has an object-oriented API you can use to integrate other kinds of fields, if you need to. For more information, see cer.api.php.

DEPENDENCIES

- Entity API
- CTools
- Table Element

CREATING PRESETS

CER won’t do anything until you create at least one preset. To create a preset, visit admin/config/content/cer and click “Add a preset”. You will need Hierarchical Select installed to continue.

Select the field you want to use for the left side of the preset, then click Continue. Another select field will appear; use it to choose the field to use for the right side of the preset. Click Save, and you’re all set!

THINGS YOU SHOULD KNOW

* If you’re updating from CER 1.x or 2.x, you MUST clear all your caches *before* running update.php so that new classes can be registered with the autoloader! If you don’t do this, you are likely to receive fatal errors during the update.

* If you have Corresponding Node References installed, CER will disable it and take over its field relationships.

* Everything CER does, it does in a normal security context. This can lead to unexpected behavior if you’re not aware of it. In other words, if you don’t have the permission to view a specific node, don’t expect CER to be able to reference it when logged in as you. Be mindful of your entity/field permissions!
  
* devel_generate does not play nicely with CER, especially where field collections are concerned. The results are utterly unpredictable.

ROAD MAP

If any of this stuff interests you, I wholeheartedly encourage you to submit patches or contribute in any way you can!

- Moar automated test coverage
- Performance enhancement
- Documentation

MAINTAINER

Questions, comments, etc. should be directed to phenaproxima (djphenaproxima@gmail.com).