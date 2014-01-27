Current state of Rubik for Drupal 7
-----------------------------------
Rubik has undergone a slight visual overhaul and structural refactoring to
accommodate some key changes in D7. In particular:

- Page wrapper and styles have been simplified to work both in page context
  and overlay context.
- New page elements like action links, removed page elements like generic
  footer.
- New icons for the admin path restructuring and nicer button styles for
  indicating actions.

Because these changes represent a departure from the previous visual look of
Rubik, D7 will be using the 4.x version series. There are plans to backport
many of these changes to D6 in a 4.x branch as well.

### @TODO

- Update RTL stylesheets, sprites
- Browser testing


Rubik
-----
Rubik is a clean admin theme designed for use with the admin module. It features
a set of icons for admin pages provided by Drupal core and aggressive styling to
reduce visual noise wherever possible.


Requirements
------------
You must install the [Tao][1] base theme for Rubik to operate properly.


Overview for subthemers
-----------------------
Rubik can be used quite successfully as a base for non-admin themes. Here are
some reasons you might want to use Rubik as a base theme:

- You want to inherit its styling for form and other major page elements.
- You want to inherit its admin-element styling, e.g. you want to use the same
theme for both the frontend and backend.
- You want to inherit form layouts and preprocess routing that Rubik provides.

Before beginning to subtheme based on Rubik, please read the README included
with Tao. As Rubik is a subtheme of Tao, many of the principle and ideas in Tao
apply to subtheming Rubik as well.


### Form theming

To work with form theming in Rubik (and Drupal in general) you should become
familiar with [`drupal_render()`][2]. Form rendering in Rubik is done in the
**template file**, not the preprocess, allowing any additional preprocessors to
alter the form in its structured state.

Rubik pushes many system forms through a series of additional preprocess
functions before templating.

- `rubik_preprocess_form_buttons()` detects any root level submit and button
type elements and groups them together under `$form['buttons']` so they can be
placed in a wrapping element.
- `rubik_preprocess_form_legacy()` handles legacy theme function-based forms
that use a declared theme function. It will first render the form using the
function specified by `#theme` and then generate a form array that can be used
with `drupal_render()` in templates.


### Icon classes

The admin icons in Rubik are displayed using a CSS sprite and corresponding CSS
class. The class that refers to each icon is based on a link path to the admin
page. For a path at `admin/settings/foo`, the classes added to the containing
element of `span.icon` are:

  - `path-admin-settings-foo`
  - `path-admin-settings`
  - `path-admin`

This allows for your element to fallback to a more generic, placeholder icon if
the most specific class cannot be used.


### Object & form template layouts

Rubik groups elements in the tao object template and various forms into two
columns.

- For object templates (`theme('node')`, `theme('comment')`, etc.) you can
switch to a typical 1-column layout in you  preprocess function:

        $vars['layout'] = FALSE;

- For form templates, you should use `hook_theme()` to and declare the form's
template as `form-simple`. If a prior preprocess has moved form elements in
`$vars['sidebar']` for the form, you will need to move them back to the
`$vars['form']` element.

        // Switch comment form back to simple layout.
        function mysubtheme_theme() {
          $items['comment_form'] = array(
            'arguments' => array('form' => array()),
            'path' => drupal_get_path('theme', 'rubik') .'/templates',
            'template' => 'form-simple',
          );
          return $items;
        }


### Stylesheets

- `core.css` provides styles for standard Drupal core markup elements, in
particular form elements, list items, pagers, etc. It does not style any "page
wrapper" or "design elements" like the site logo, navigation, etc.
- `icons.css` provides styles for the admin icons provided by Rubik.
- `style.css` provides styles for the Rubik admin theme page wrapper and other
aesthetic elements. This includes the site title, tabs, navigation, breadcrumb,
etc. **This is the file you will most likely want to override to begin your
subtheme.**


Maintainer
----------
- yhahn (Young Hahn)


[1]: http://drupal.org/project/tao
[2]: http://api.drupal.org/api/function/drupal_render/6
