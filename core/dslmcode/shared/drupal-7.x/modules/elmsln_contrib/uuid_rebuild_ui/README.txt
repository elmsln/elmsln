UUID Rebuild UI

This is a add on for UUID to do something dangerous — which is to forcibly rebuild all UUIDs in a site. If you use UUIDs for relational activities, this can be dangerous since you might be using this data to reference other system integrations.

When to use this then?
Usually when building a new site from default content, you get duplicate UUIDs. This causes issues if you really do want the IDs in 1 site to be universally unique and not just mostly unique.


Check out the uuid_rebuild project if you want to do this without having GUI integration.