Entity iframe
What it does
Expose a path for viewing entities in an iframe display format.  This creates a path of the 
following pattern: /entity_iframe/%type/%id.  The most common use for this is nodes so node 2 
would be /entity_iframe/node/2.  There's a link automatically added to all entities for this 
iframe link as a shortcut.

Installation
Turn the module on.  Then go to any fieldable entity
(node, user, term, etc), click the link or see the embed code.

Configuration
Go to the permissions page and make sure roles can view the iframe page output as well 
as set if they can view the embed code on the site.  In order to view the embed code the
given role will need to be able to both see the embed code as well as the iframe mode 
(meaning they'll need both permissions).  A common setup for this could be giving site
editors both permissions to embed in other areas where anonymous users don't see the embed
but can access iframe mode.

Go to admin/config/system/entity_iframe and select the theme you want to use 
(stark is used by default). You can also chose to disable the iframe link on certain 
entity types and bundles from this page.  This most common use of this would be to
activate this for the node entity and then only show it on certain content types as
these are the "bundles" for node.

There's also the ability to show a link to the embed mode, the embed code or tweak
the default embed properties.

Views integration should work with all entity types that are enabled for the entity types and
bundles selected in the admin interface. For example, if you add an iframe link to a view of nodes
and only 2 types are allowed to be displayed in an iframe the other type's rows will be blank.

Recommended other modules
http://drupal.org/project/entitycache
Entitycache module is recommended when using this mode because of the bundle and type
comparisons that have to load entity definitions for visibility of iframe mode.  This
additional check is rather minor in cached environments but should be noted that
entity cache can mitigate any effects once the cache is primed.

Advanced
You can customize the field output for the entity via the field display management UI.
For example, you could choose not to display certain fields when a node is viewed via an iframe

There is an a developer hook that allows for custom modification of the iframe properties
used for output of the embed code.  They have sensible defaults for easy targeting when
used in remote systems but can be changed or added to via hook_entity_iframe_properties_alter

To activate the entity_iframe theme you can add ?entity_iframe
(&entity_iframe for non-clean-url sites) to the URL to switch the theme.  This only changes 
the theme and does not actually use the entity_iframe field display settings / mode.

"iframe mode" sub-module
This attempts to make all links to items in an iframe, stay in that theme.
See hook_url_outbound_alter for how this is being accomplished.  This is 
core functionality but as hook_url_outbound_alter can cause conflicts with other modules
it is being silo'ed as a sub-module.