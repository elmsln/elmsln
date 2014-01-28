This drush plugin is a complement to the Entity Cache module (http://drupal.org/project/entitycache) 
by running through and loading any/all entity content (it started off as a
patch at #1212488: Drush command to cache entities but I've been able to use
it on a number of my own sites and makes more sense as a separate plugin - part
of the rewriting will involve loading content for any entity type without
entitycache). Once entity content is loaded, it can get cached. With the entity
cache module, the content with get cached to entitycache bins thus making the
latter content loads much faster. By providing an argument, you can also cache
all entities of a certain type.

	drush ecl will get a list of all entity types that are supported by
		Entity Cache and will cache their content
	drush ecl <entity_type> will cache all content from the entity_type
		(provided it can get cached via entity cache)

On sites with large amounts of content, it may take a while for the content to
get cached. And on sites with frequently updated content, this plugin may be
unnecessary (though the cache loading will end up going much more quickly) :)
