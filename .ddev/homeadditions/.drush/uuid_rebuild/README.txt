UUID Rebuild

This is a drush plugin to do something dangerous — which is to forcibly rebuild all UUIDs in a site. If you use UUIDs for relational activities, this can be dangerous since you might be using this data to reference other system integrations.

When to use this then?
Usually when building a new site from default content, you get duplicate UUIDs. This causes issues if you really do want the IDs in 1 site to be universally unique and not just mostly unique.

Usage

drush uuid-recreate

Then confirm the yes prompt and it will rebuild all the UUIDs in a site. There is no undo for this, you will lose all previous UUID data.