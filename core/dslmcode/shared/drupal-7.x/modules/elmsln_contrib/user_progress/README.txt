User Progress API
=================

This module was created to help us simply ingest data from external applications that needed a database backend. Think of it as a extremely simple web service api.
Everything is either a get or a set to records in the database and those records
are affiliated both with the user submitting the data (interacting with an application) as well as the application which has been registered in the database.

This comes with a few examples / ideas for usage but Smart Builder is the primary
driver for why this project was created.  Smart Builder is a flash-app builder of
sorts and so is popular in education but provides no data storage mechanism of its own. It does however have a robust interface for less technical users to read data in from a remote source and send it off based on things that happen in the application.

Because of it's flexibility it's hard to say "this is how to integrate with this application" other then listing examples. If you look through the module trans how things work in _user_progress_set and _user_progress_get functions.


EXAMPLE USAGE
=================

Here's an example transaction from our integration.  All conversations start by calling for a transaction ID so your app needs to call something like:
user_progress/get/guid

This will return a unique value that helps ensure the transaction is secure between drupal and the app.  We place the app on the same server as the drupal site; this way when someone logs into the drupal site to get to the app they are effectively "logging into the app".  This way we can assume their user ID as the currently logged in drupal user on the database side.

All transactions MUST pass the guid to ensure security and relate the data to 1 transaction w/ the application.  If you want data to be stored in different fields you'll need to get new guid's for each of those transactions.

The smart builder application then has to provide what's called a upregid (user progress registry ID).  This is entered by the drupal site admin into the drupal side to basically say "hey, I expect an application to be using user progress for tracking and it has this unique ID".  For now that's just a number that you associate w/ the app in case you have multiple applications (we have 26 of these I believe between our usage for example).

After that you can start to have a conversation with drupal through user_progress/get and user_progress/set (which you can see some supported operations in the _user_progress_set and _user_progress_get functions).

Here's an example call from smart builder to drupal to get the number of times someone has attempted application 13.  We also generate a random number and throw it on the end of calls to ensure that data isn't cached (rare instances this occurred in the past where client side it would cache the call to a destination).

user_progress/get/numtries?upregid=13&guid=19580dd7a6d9c203673d3aa53552eeed&rand=1397155128848

Here's an example call that sets a bunch of data for an idea of what that looks like.  User progress can handle up to 16 data points in 1 transaction.  This is rather arbitrary and was selected as a result of the type of data sets we are storing so it wouldn't be difficult to modify things to handle more.  As 1 chunk though, we have yet to need more then 16 data points stored.

user_progress/set/value?data16=12&data15=12&data14=16&data13=16&data12=2&data11=2&data10=9&data9=9&data8=7&data7=7&data6=7&data5=7&data4=7&data3=7&data2=5&data1=30&upregid=13&guid=19580dd7a6d9c203673d3aa53552eeed&rand=1397155126161

These are then validated by the data handler for type matching, or, if none is defined then a generic scrubber is used.
