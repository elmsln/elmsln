Description:
------------
This module adds a system similar to publish / unpublished 
status of nodes. The reason that this is needed is so that 
you can tell certain roles they can't view nodes while others 
can. The issue with publishing status is that there is no grey.
Menu systems automatically hide unpublished nodes while also 
checking for the node_access.

This blocks situations where admins and sub-admins need to work on content 
in the context that it will be presented left in a position where they are 
unable to do so. This will help create the same level of security that publish
status does but without the limitations on admin-esk users to actively work
with content the way it will eventually render (menu wise).

Use this module if you want to be able to limit what some users see in
books and menus but still want others to have full visibility of those posts.

This module is based heavily on View Unpublished, it just builds on the ideas
to make them more flexible in the menu system while still providing the same
end result functionality.  It has to do this because of the core limitation
provided by using unpublish status.

The access grants of this module are very high and as a result this 
SHOULD work with other access control methods.  Note that "work with" 
means that hidden nodes always takes priority because of the 
implication of the project.  It is trying to effectively unpublish 
the node without the weight of unpublish (have I said this enough).

Usage:
------
hidden_nodes looks for the "view all hidden content" permission when a user tries to
view a node that is marked hidden.

After installing the module, navigate to your user access page and assign the
appropriate permissions to the roles you wish to be able to view hidden nodes.
