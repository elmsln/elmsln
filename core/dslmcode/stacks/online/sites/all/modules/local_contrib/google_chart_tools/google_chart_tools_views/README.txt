Google Chart Tools - Views Integration

Google Chart Tools Views is provide a designated views format plugin named "Google Chart Tools".
After selecting this, the very first thing to do is turn on the views3 built in aggregation mode. 
Under Advanced column there a "Use aggregation" row, its should say YES.
For learning how to deal with the views3 built in aggregation, try a great screencast by Johan Falk:
http://nodeone.se/en/the-aggregation-setting-the-emmajane-episode

Now it time to add our data (fields).
The first field is representing the x-Axis (header).
Remember its have to be the first one. 
And usually it need to be set to Aggregation type: Group results together.
Many times you want to use this field by date 
(node post date or user registration date) to achieve that,
use this excellent module: drupal.org/project/views_date_format_sql

Next, lets add the numbers. this field/s will draws the graph (line points, bars, etc').
This field will mostly using one of the other "Aggregation type" functions which will returns numbers.
These numbers are points on the y-Axis (row) for each of the x-Axis points.
If the first field is a node post date with "Aggregation type" set to Group results together,
We can add node NID field with "Aggregation type" set to "Count". 

This setting will generate a chart which demonstrate the numbers of node created each day.

*Organizational Chart*
For generating an *Organizational Chart* using view it's a different story:
First we need to set the type in the views format settings (Google Chart Tools) to "OrgChart".
We will NOT gonna' use the aggregation mode, there no need for it.
Now we need to add fields in very specific order to make this to work.
the order is like this:
Name, Display Name, Parent, Tooltip, Style, Selected Style.

*The first three are required.

The 1st field is the *Name*, its can be the taxonomy term name or a node title or user name, etc'...

The 2nd field is the *Display Name*, its can be equal to the Name field (we must have it though), 
but can also have some extra or different data. This is the field which will be actually display. 

The 3rd field is the *Parent*. its can be the parent term in the taxonomy vocabulary,
or the parent node or user using entity reference or by book hierarchy.
No matter what is the hierarchy we using in the site we must specified the parent of the item.

The 4th field is the *Tooltip*, which is the short description of the item. Any text field can be fit here.

The 5th field is *Style*, it's a text field (can use the Global: Custom text) which can specified a style like: border-color:green.

The 6th field is *Selected Style*, which is similar to the Style field' but for selected item. For instance: border-color:red.

#Sorry, but the views preview is not presenting the chart.#