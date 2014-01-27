The Node Queue module allows an administrator to arbitrarily put nodes in a
group for some purpose; examples of this might be to highlight one particular
node, as in a typical news site's Lead Article. Another use might be to create
a block listing teasers for 5 forum posts that the admin thinks are important.
Another use might be to create a group of nodes, and then have a block or the
front page offer one of these randomly.

Queues can be set to allow only certain types of nodes to be added to the
queue. Queue can be a fixed size or of infinite length. And the admin can
select which roles have permission to add nodes to a given queue.

Once a queue is set up, a new tab will appear on eligible nodes for eligible
users. This tab will allow the user--regardless of edit permissions--to add or
remove that node from the queue. Queue admins can view the nodes in the queue,
and can modify the order of items already in the queue. Items may also appear
in a nodes links area to add/remove them from the queue.

When a node is added to the queue, it is added to the back of the queue. If a
queue is full when a node is added, the front of the queue is removed. 

Nodequeue has support for nodes with i18n Internationalizations.

It is highly recommended that you use the Views module to display your queues.
However, if you choose not to, here is an alternative: Writing a PHP snippet.

To Create a Block to Display Node Titles of a Queue
===================================================

You'll need the Queue ID, which is easily extracted from the URL on the
queue administration page.

Create a new block, and insert the following PHP snippet into the block:

   <?php print nodequeue_node_titles(QUEUEID); ?>

If you want this queue to be printed in the reverse order, you can tell it
to print backward:

   <?php print nodequeue_node_titles(QUEUEID, '', true); ?>

The '' in the line above is an optional title field. Feel free to put
something here, but it's not terribly necessary in a block.

Programatically displaying nodes from a Queue
===================================================
The following funcitons can be used to display nodes from a subqueue, based on their position.
For more customized displays of content from a queue, please use the Views module (http://drupal.org/project/views).
For the most up to date Nodequeue API information, see http://drupal.org/node/293117.
Programmatic Ways of Displaying Content from a Queue

Nodequeue provides several functions which simplify getting a loaded node object from the front, back or a random position in a queue. For more selecting or displaying content in a more specific or complicated way, the Views module is probably your best bet.

Please note that there are some differences between the functions available in the 5.x-2.x and 6.x.-2.x versions of Nodequeue.
To Create a Block to Display Node Titles of a Queue

You'll need the Queue ID, which is easily extracted from the URL on the queue administration page.

Create a new block, and insert the following PHP snippet into the block:

<?php
print nodequeue_node_titles($subqueue_id);
?>

If you want this queue to be printed in the reverse order, you can tell it to print backward:

<?php
print nodequeue_node_titles($subqueue_id, '', TRUE);
?>

The '' in the line above is an optional title field. Feel free to put something here, but it's not terribly necessary in a block.
To Display a list of teasers from a queue:

Like above, you'll need the Queue ID.

Create a new page (or a new dashboard!) or any node type you like, really, and set the input filter to PHP. Insert the following PHP snippet:

With Nodequeue 6.x-2.x:

<?php
print nodequeue_view_nodes($subqueue_id);
?>

With Nodequeue 5.x-2.x

<?php
print nodequeue_nodes($subqueue_id);
?>

There are a few more options available here; changing the order of the nodes, whether or not to use teasers or full nodes, whether or not to display the links, and how much of the queue to display. See below.
To render the first or last node from a queue

With Nodequeue 6.x-2.x:
<?php
$node = nodequeue_load_front($subqueue_id);
$rendered_node = node_view($node);
 
?>

With Nodequeue 5.x-2.x:
<?php
$rendered_node = nodequeue_fetch_front($subqueue_id);
?>

Or

With Nodequeue 6.x-2.x:

<?php
$node = nodequeue_load_back($subqueue_id);
$rendered_node = node_view($node);
?>

With Nodequeue 5.x-2.x:
<?php
$rendered_node = nodequeue_fetch_back($subqueue_id);
?>
To render a random node from a queue

With Nodequeue 6.x-2.x:

<?php
$node = nodequeue_load_random_node($subqueue_id);
$rendered_node = node_view($node);
?>

With Nodequeue 5.x-2.x:

<?php
$rendered_node = nodequeue_fetch_random($subqueue_id);
?>

Remember that the front of the queue will have the least recently added nodes (unless it was rearranged manually), and the back will have the most recently added.

Actions Module Integration
==========================

The node queue module provides two actions, so that workflow can add and
remove items from queues.



