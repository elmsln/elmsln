FontFolio Drupal Theme
----------------------

FontFolio is responsive portfolio type theme. It is clean, grid based, 2 column theme.

Original Wordpress Theme created by Marios Lublinski from http://www.dessign.net
WP description says: FontFolio Theme for WordPress is stylish, customizable,
simple, and readable. Perfect for any illustrator or graphic designer.

Drupal version by: Israel Shmueli. http://ish.co.il 
Drupal theme demonstration website:  http://fontfolio.ish.co.il

I would like the Drupal version to be used also for artists and craftpersons
portfolios. 

Documantation:
----------------------
http://drupal.org/node/1653300



Multilingual support
----------------------
Easier setup for Multilingual portfolio website.
By default, links to frontpages in all enabled languages will attached to
main menu far end. You can disable this feature via the theme setting page.


Full RTL support
----------------------
As demonstrated in http://fontfolio.ish.co.il 
Every FontFolio css file has an RTL version that drupal will atomaticly include 
for Right to Left languages like Arabic, Hebrew, Persian and Urdu.

Installation
------------
 1. Download FontFolio from http://drupal.org/project/fontfolio

 2. Place the fontfolio folder in proper themes folder inside your installatin sites
    folder. Ussually in sites/all/themes folder.

Configuration
------------
 1. Search Box:
    Enable the "Search" module.
    Go to block administration page: admin/structure/block and make sure that "Search form" block is placed in the "Search" region.
    Make sure that "Search form" is the only block positioned within the in "Search" region, remove other blocks if any.
    Make sure to set permissions to use Search for anonymous and authenticated users.

 2. Number of posts on FrontPage:
    Go to admin/config/system/site-information and set to 9 the "Number of posts on front page". This number is also valid for Taxonomy term teaser lists

 3. Image styles:
    FontFolio use CSS image "width" rule to make sure images will displayed in the "right" dimensions for each part and will not break the layout.
    For efficiency and better performance you should pre set proper dimensions using Drupal's image styles.
    You should go to admin/config/media/image-styles and create new styles or override existing image styles to contain the needed effects.
    In the Demo website 'medium' image style was overridden to have single effect of "Scale and crop" with dimensions of 562x464 .
    For full node displays 'Large' Image style was overridden to contain only 'Scale': width 700 (upscaling allowed).

 4. Content type Teaser display:
    Go to admin/structure/types choose your content types and click the Manage display tab. Then click the "teaser" display link.
    For the default "Article" node type you can go to /admin/structure/types/manage/article/display/teaser .
    Now configure the teaser display to hide all fields but the image field.
    For "Default" displays you usually want the the body field to be visible.
 
 5. Secondary menu
    The links below main menu are the Secondary menu links.
    You should go to admin/structure/menu/settings and make sure that you are satisfied with the "Source for the Secondary links" settings. In FontFolio Demo the source for both, main links and secondary links is "Main menu". This way the main menu display only the first level menu links and secondary links really function as secondary menu while displaying the relevant sub menu (second level) items.
 
 6. Views
    To get basic fontfolio style grid with views you can:
      A. Create new view with page display.
      B. Set its format to "Unformatted list".
      C. Click the format settings and insert "post-box" in "Row class" field.
      D. Set the nomber of items to number that is divisible by 4 (e.g 8).
      
    In case you want the first item to displayed bigger like the default fontfolio frontpage:
      E. Add to your view new attachment display and keep its "Unformatted list" format.
      F. Click the format settings and override (only for this display) the "Row class" to "big-post-box".
      G. Set 1 for Items to display and "no" for "render pager".
      H. Now click on "Page" display to set its pager "offset" field to 1.
      I. Add "fontfolio" as your view tag. You can assign tag via the "edit view name/descriptionthe" button.
         adding the tag will make any view to use the template views-view--fontfolio.tpl.php .
         This template keeps the big box attachment on first view page and remove it from any 
         other pages of paged view.
         