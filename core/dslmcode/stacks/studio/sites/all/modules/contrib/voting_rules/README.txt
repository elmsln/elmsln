The Voting Rules module provides Rules integration for VotingAPI.

Because Rules requires that content types acted upon be defined ahead of time, you must select the type of content which is being voted on.  Currently, Voting Rules only supports rules based on nodes, users, and comments.

Installation
==========
To install, follow the general directions available at: 
http://drupal.org/node/70151

Events
==========
Voting Rules supports three events for each supported content type:

* User votes on content

  This rule should be used when you want to act on an individual vote, NOT when you want to act on the results of a vote. For example, if you want to promote content to the front page when any user gives a post a 100% rating, then you should use this event. If you want to act on the aggregate data (e.g. average vote is 80% or higher) use the event below.


* Votes are calculated for content

  Used to act on the results of a vote in aggregate. This event is invoked everytime the vote is recalculated, which may happen more than once in one page load, depending on your VotingAPI configuration.   


* User deletes a vote on content

  This is the counterpart to 'User votes on content' and functions in the same way. 

Conditions
==========
* Check the value of a vote

  This condition is used in conjunction with 'User votes on content' and 'User deletes a vote on content.' It allows you to check the value of an individual vote. Note that depending on the module generating the vote the value type may be different. For instance, Fivestar evaluates votes as a percentage (by default 20, 40, 60, 80, or 100) - so you could trigger an action on a 100% vote with the rule: Value is *equal to* 100.

* Evaluate the results of a vote
 
  To be used in conjunction with 'Votes are calculated for content,' this condition allows you to check the total number of votes on the content, the average value of votes on the content, and the sum total of all votes on the content.

