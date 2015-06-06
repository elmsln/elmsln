D.A.A.N.A.A.
Pronounced (in a Pittsburgh accent) DAAAAAAAAYYYYYNNNNAAAAAAA
Is short for Drush Assign Author Nodes Another Author

This was created in the even that you bulk delete a user from a bunch of sites (say an employee that no longer works for you). You can run drush ucan which will remove the user from the system and give all their content to annonymous. Well, there's no good way of assigning those nodes to someone else via drush.

That's where DAAAAAAAAYYYYYNNNNAAAAAAA comes in, DAAAAAAAAYYYYYNNNNAAAAAAA allows you to give all of those annonymous nodes over to someone else as author. It takes 1 param, loads all nodes that are currently marked annonymous, loads them, changes author to match the user id of the username/id you passed in and then your done.

This was originally written for ELMSLN / Drush recipes so you could run routines that remove users and then change ownership of their material to another user without manual intervention.