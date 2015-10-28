Items created for the courses / mooc toolset prior to platform versioning varied based on what the output would look like. This is how you standardize things to bring these courses more inline with the user experience currently available in courses that are created as part of the system.
ssh to the server and run

`drush @courses.COURSEHERE drup d7_optional_mooc /var/www/elmsln/scripts/upgrade/drush_recipes/d7/optional/mooc`

This will ask you if you'd like to run a command that it found, say yes and it will start to untangle the old user experience and enable the new user experience. You'll want to test this before applying to anything though as customizations you applied might be lost or at least the UX modification could make it difficult to locate. If you use Context, Views and Features this most likely won't be an issue.