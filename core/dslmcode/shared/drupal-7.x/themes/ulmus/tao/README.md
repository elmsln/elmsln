Current state of Tao for Drupal 7
---------------------------------
Many of the concepts in Tao for Drupal 6.x have been addressed by the theme
layer of Drupal 7 in one way or another. As a result, various parts of Tao have
been refactored and other parts are up in the air conceptually.

### Key changes

- $vars['attr'] is deprecated in templating and preprocessors. Use the D7 core
  handling through $attributes_array and $classes_array instead.
- Custom js for fieldset collapsibility is deprecated. Tao now uses the default
  D7 js for fieldset collapsing.
- theme_form_element() in D7 properly marks form elements with their types.

### @TODO / still concepting

- Future of tao-based print-friendly stack.
- Fully update README once all major changes are stabilized.


Tao
---
Tao is a base theme for Drupal that is all about going with the flow. It is not
meant for general-purpose use, but instead takes care of several tasks so that
sub-themes can get on with their job:

- Aggressive resets of not only browser default styles but Drupal core defaults
- Unification of several template families into a single consistent format (e.g.
node.tpl.php, block.tpl.php, etc.)
- Theme overrides of several core annoyances (fieldsets, pagers)
- On-screen print stylesheet display and framework for further customized print
styling

Tao makes several assumptions about how you, the themer, would like to work with
Drupal and the theme system:

- Minimize template overrides and leverage preprocessors as much as possible
- Preference for generalized styling over exceptions and particular design of
one-off elements
- High degree of control over CSS, particularly selector specificity


Overview for subthemers
-----------------------
The following is a comprehensive list of things to know about Tao as a
subthemer.


### Alterations to core markup

Tao leaves most core element markup alone. When things don't make sense,
however, it makes changes and aggressive ones at that. Here's a list of things
to expect:

- `theme('fieldset')`

  The `fieldset` element in core has been retained but with additional markup
for simpler theming. The `legend` element contains a sub-element `span` that
can be positioned properly across browsers and the main contents of the
fieldset follow other object templates with a `.fieldset-content` div.

- `theme('form_element')`

  To distinguish between different instances of the `.form-item` wrapper, Tao
adds a `.form-item-labeled` class to labeled items and `.form-item-option` to
checkboxes and radios.

- `theme('pager')`

  All numeric page links are grouped together into a `ul.pager-list` set.
Next/previous links are grouped together under `ul.pager-links`.

- `theme('username')`

  All username instances are wrapped in an `a.username` or `span.username`.


### Attributes and the `$attr` variable

  The `$vars['attr']` variable is the standard way for adding any HTML attribute
to the major containing element of the corresponding template. The
`drupal_attributes($attr)` is used in each template to render attributes. For
example, to add a class to a node, you would add the following to your
subtheme's node preprocessor:

    $vars['attr']['class'] .= ' myclass';


### CSS resets & removal

Tao implements an aggressive `reset.css` but also strips out the inclusion of
many of the CSS files included in core with the exception of `colors.css` and
`locale.css` (see `tao.info` for the specifics). Tao reimplements and
consolidates Drupal core CSS styles in a way that will not affect a
typographical or other strict grid in `drupal.css` that can be overridden by
sub themes for even greater control.

Tao does not remove any contrib CSS added from other module directories, e.g.
`sites/all/modules` or `profiles/myprofile/modules`.

**Note:** The main reason for the stripping of core CSS is to achieve consistent
typography and grid layout. Many styles in Drupal core add inconsistent
`padding`, `line-height`, and `font-size` adjustments to elements, making it
extremely costly to hunt down individual instances and correct them.


### Print preview

Tao allows a site's print stylesheets to be previewed by checking whether
`$_GET['print']` is set. For example, to preview a node's print stylesheets, you
would go to `http://example.com/node/5?print`. Other niceties related to print,
like support for full expansion of a book tree on print, has been added.


### Say no to `media='all'`

Tao does not use the `all` key for any of its stylesheets and expects that you
will not either. Be specific - if the stylesheet is for the screen, or for
print, say so. Any stylesheet overrides your subtheme provides should use the
same media key as the one in `tao.info` for the stylesheet that is being
overridden.


### Stylesheets

- `reset.css` provides browser CSS style resets and core styling resets.
Override this in your subtheme only if you need to add or omit certain reset
styles.
- drupal.css` reimplements core CSS styles that are functionally important
without allowing any modifications to a typographical or layout grid.
- `base.css` provides very basic structural, non-aesthetic styling for many
elements. See inline comments for more information.
- `print.css` is a default print stylesheet. Override this in your subtheme to
alter print styling entirely.


### Template unification

All of the following theme functions go through the exact same template in Tao
(with the exception of `node` and `fieldset` which go through slightly modified
versions for better usability and compatibility with contrib modules):

- `theme('block')`
- `theme('box')`
- `theme('comment')`
- `theme('fieldset')`
- `theme('node')`

The template is designed to follow a strict pattern. Each element is classed as
such:

    [theme_hook]-[element_type]

with the name of its hook and then the type of wrapping element within the
template. For example, for a node, the following elements are provided:
`.node-title`, `.node-content`, `.node-links` etc. For comments, the
corresponding classes would be `.comment-title`, `.comment-content`,
`.comment-links` and so on.


Maintainer
----------
- yhahn (Young Hahn)
