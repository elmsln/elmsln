Drush Recipes plugin
=====================
This is a YAML / XML / JSON based format which allows for the definition
of structured drush commands that should be executed.
This is useful in place of puppet / jenkins command engines as well as
in augmenting them, since it's effectively a super-drush command.

It also provides support for conditions and recipe nesting so you could
provide branching paths to other developers, like a script that sets up
a new site (drush si) and then asks what theme to use as the base-theme
(bootstrap vs zurb-foundation vs zen vs omega vs adaptive vs...). This
as a recipe would be one recipe referencing many others (conditionally).

Recipes can be provided local to drush, the drush_recipes plugin, other drush
plugins, modules, themes, install profiles, or custom sites/all/drush_recipes
style directories. This allows for maximal flexibility on the part of module
developers as well as those who want to write scripts to ease deployment and
stash these in private locations.

Recipes are simple text files which can be version controlled instead of
constantly writing drush thing | drush another thing | drush another thing.
It also goes a step beyond simple make files (and can use them too!) for
times when you want to (for example) download bootstrap, and jquery_update
and set jquery_update default version to 1.5 on backend and 1.8 on front-end.
All of this could be done in 1 recipe which a user could run drush cook setup-bootstrap and it would be off and running

For the full list of commands check out the homepage and some of the video tutorials.

==== Target "Diffing" ====
You can also use the target diff'ing engine to have drush recipes calculate
what drush calls would be required to take a site from one state to another. This is then used to generate a recipe which *should* be able to get it
reasonable close to the other system as far as modules, themes, settings,
roles, and permissions go; with support for more matching in the future.

==== Writing Recipes ====
There is also a command for writing recipes via command line (drush dwr)
so you don't need to learn the format, just type the commands you want to
store for later use. The builder supports argument based (drush dl views),
conditional (stuff.drecipe vs thing.drecipe), make (thing.make), and
referencing of other recipes (dr_security.drecipe). There is a more advanced
format that allows for specifying targets and options but the builder doesn't
have support for this yet

==== DVR ====
We can record commands with one simple command, then run a bunch of commands, end recording and play it all back! drush dvr start

==== Future ====
I'm working on (in my spare time) a webservice that could be used to sync
recipes and help teams deploy them / stay on the same page. This would also
serve as a community for sharing recipes similar to dropbucket but for
all of these useful chain automation techniques. The address is awesome even
if the service still isn't finished. http://drush.recipes/

Feedback encouraged, Help much appreciated, enjoy!
