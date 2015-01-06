Installation:

This module depends on harmony_core and search_api.

1. Create a search server where your index data will be stored, navigate to: Admin > Configuration > Search and metadata > Search API > Add server (/admin/config/search/search_api/add_server).
There's a long list of options at the below link. An easy example would be local database using the "Database Search" module.
https://drupal.org/node/1999262#service-classes
https://drupal.org/project/search_api_db

2. Next create an Index for the Forum content, navigate to: Admin > Configuration > Search and metadata > Search API > Add index (/admin/config/search/search_api/add_index). When completing the form ensure to select "Thread" for the "Item type" field.

3. With your server and index in place, now we need to select the data to search. Edit your index, in the "Fields" tab you will want to "Add related fields".
3.1 From the related fields drop down select and add "Posts", this creates a link to the posts within the thread.
3.2 Repeat the previous step, but now add "Posts >> Text" as we want to search the posts within a threads' text.
3.3 That's enough related fields added, from the list of fields tick the index column for "Title" and "Posts » Text » Text".

4. Optionally you can now add some filters to the index, these augment the result set that a user will get. This module provides two, "Exclude unpublished threads" and "Thread access". The first is fairly self explanitory. The second will only appear if you have enabled "harmony_access", when it is and you enable this filter users will only see results which they have access to.

At this point you can also restrict which Thread types (bundles) are included in the index.

5. With all the setup for the index complete return to the "View" tab and click the "Index now" button, this may take a while.

6. Your new index is setup and populated, from here the excellent Search API documentation can show the way. You can use multiple methods to provide an interface to the index, lots of modules here to choose from:
https://drupal.org/node/1999262

Here's the documentation for creating a View:
https://drupal.org/node/1597930
