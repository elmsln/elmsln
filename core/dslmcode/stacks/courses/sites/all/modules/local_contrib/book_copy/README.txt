Book Copy 2.x - Copy a book or part of a book outline with ease

This module is similar to the 1.x version but is a complete rewrite which
now requires the replicate module to function. Replicate was chosen over
node_clone due to simplicity, though it does require downloading the entity module.

If you want to use the API functions that were previously in the 1.x version,
replicate has this capability built into its api for doing custom alters
to nodes replicated.

While replicate supports entity operations, books do not so this project still
is only able to replicate book items that are nodes. Copy history has also been
removed for simplicity.

USE

- Enable the module
- grant permission to copy books to people on the permissions page
- go to the book admin area where you will see a "copy book" link


This has optional support for the Outline Designer Book module which allows for
rapid outline creation, using this module to handle the replication of child items.