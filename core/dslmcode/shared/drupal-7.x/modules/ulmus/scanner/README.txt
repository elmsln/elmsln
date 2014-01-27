Scanner Search and Replace
--------------------------

I. DESCRIPTION:

The Search and Replace Scanner can do plain text search-and-replace, or 
regular expression search-and-replace, against the title, body and CCK text 
content fields on all nodes in your system.  This is useful for finding html 
strings that Drupal's normal search will ignore. The module is very handy if you 
are fixing typos in a lot of content, changing the name of your company, or 
are changing the URL of a link included multiple times in multiple nodes, 
among other things.


II. LIMITATIONS:

1. A user can only have one instance of Search and Replace Scanner running at a time.  Attempting to open Scanner in two separate windows to perform replacements at the same time can lead to unknown errors if you encoutner a timeout.

2. Only works on sites using a MySQL database.

3. Large search and replace actions may not be completed on sites that are 
hosted in environments where PHP's max_execution_time variable can't be 
dynamically expanded. The module automatically attempts to expand the 
maximum execution time of a script to 10 minutes. (It's often set at 2 minutes.)  
If your Web host doesn't let you adjust this variable dynamically, you may be 
able to ask your hosting provider to make the change for your account.


III. WARNING:

This is a very powerful tool, and as such is very dangerous.  You can easily
destroy your entire site with it.  Be sure to backup your database before using 
it.  No, really.


IV. FEATURES:

1. Plain text search and replace.

2. Regular expression search and replace.

3. Case sensitive search option.

4. Plain text search allows 'whole word' matching option.  For example, 
searching for "run" with the whole word option selected will filter out 
"running" and "runs", but will match "run!".

5. You can specify text that should precede or follow the search text in order for a match to be valid.

6. Can limit search and replace to published nodes only.

7. Can search and replace on CCK text fields, in addition to the node title.

8. Searches can be limited to specific fields in specific node types.

9. Searches can be further limited by nodes containing specific taxonomy terms.

10. Will save a new node revision when a replacement is made, in case you want 
to revert a change.

11. Provides an Undo option that lets you revert all nodes that were udpated in 
a specific replacement action.

12. Can dynamically update teasers after replacements in other fields, or can 
by updated manually, or not at all. (Not yet working in D7)

13. Will dynamically expand PHP's maximum execution time for scripts up to 
10 minutes on servers that support it. This allows complex queries on large 
bodies of content.

14. Search results for searches and replacements can be themed.


V. TODO / KNOWN BUGS:

1. Provide better highlighting for search results. Right now there's a known 
bug where multiple search terms on the same line aren't all highlighted. (The 
hit count is correct, though, and all items are replaced correctly.)

2. Perform more thorough testing of the "custom field" feature. (Functionality not yet provided in D7)


VI. INSTALLATION AND ADMINISTRATION:

See INSTALL.txt for installation and administration instructions.


VII. CREDITS:

Version 7.x-dev by:
   - Michael Rossetti
     Drupal username: MikeyR
     rossetti [at] mit.edu

Version 6.x-dev by:
   - Amit Asaravala
     Drupal username: aasarava
     http://www.returncontrol.com
     amit [at] returncontrol.com

Version 5.x-2.0 by:
   - Amit Asaravala
     Drupal username: aasarava
     http://www.returncontrol.com
     amit [at] returncontrol.com
   - Jason Salter
     Drupal username: jpsalter
     http://www.fivepaths.com
     jason [at] fivepaths.com
   - Sponsored by Five Paths Consulting
     http://www.fivepaths.com

Version 5.x-1.0 by:
   -  Tao Starbow
     Drupal username: starbow
     http://www.starbowconsulting.com
     tao [at] starbowconsulting.com


