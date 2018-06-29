# Grav Pagination Plugin


`Pagination` is a [Grav][grav] Plugin that allows to divide articles into discrete pages.


# Installation

To install this plugin, just download the zip version of this repository and unzip it under `/your/site/grav/user/plugins`. Then, rename the folder to `pagination`.

You should now have all the plugin files under

	/your/site/grav/user/plugins/pagination

>> NOTE: This plugin is a modular component for Grav which requires [Grav](http://github.com/getgrav/grav), the [Error](https://github.com/getgrav/grav-plugin-error) and [Problems](https://github.com/getgrav/grav-plugin-problems) plugins, and a theme to be installed in order to operate.

# Config Defaults

```
enabled: true
built_in_css: true
delta: 0
```

The 'delta' value controls how many pages left and right of the current page are visible. If set to 0 all pages will be shown.

If you need to change any value, then the best process is to copy the [pagination.yaml](pagination.yaml) file into your `users/config/plugins/` folder (create it if it doesn't exist), and then modify there.  This will override the default settings.

# Usage for content authors

To use this plugin:

- the `pagination` plugin must be installed and enabled
- the active theme must have pagination support (most Grav themes support pagination; if you’re building your own theme, see the next section for adding pagination support)

On the content side, you should have a blog-like structure, for example:

```
blog/
    blog.md
    my-cool-blog-post/
        item.md
    another-post/
        item.md
```

Then in your `blog.md`, set up the page’s collection using YAML front-matter:

```yaml
---
title: My Gravtastic Blog
content:
  items: '@self.children'
  order:
    by: header.date
    dir: desc
  pagination: true
  limit: 10
---

# My Gravtastic Blog
## A tale of **awesomazing** adventures
```

Your `/blog` page should now list the 10 most recent blog posts, and show pagination links.


# Usage for theme developers

### Including the default pagination template

If you are developing your own theme and want to support pagination, you need to include the pagination template in the relevant pages. For instance in `blog.html.twig`:

```twig
{# /your/site/grav/user/themes/custom-theme/templates/blog.html.twig #}

{% set collection = page.collection() %}

{# Render the list of blog posts (automatically filtered when using pagination) #}
{% for child in collection %}
   ...
{% endfor %}

{# Render the pagination list #}
{% if config.plugins.pagination.enabled and collection.params.pagination %}
    {% include 'partials/pagination.html.twig' with {'base_url':page.url, 'pagination':collection.params.pagination} %}
{% endif %}
```

### Overriding the pagination HTML

If you want to override the look and feel of the pagination, copy the template file [pagination.html.twig][pagination] into the templates folder of your custom theme:

```
/your/site/grav/user/themes/custom-theme/templates/partials/pagination.html.twig
```

You can now edit the override and tweak it to meet your needs.

[pagination]: templates/partials/pagination.html.twig
[grav]: http://github.com/getgrav/grav

# Twig pagination function

It is now possible to create paginated collections on demand in your twig file. You only need to:

* activate the pagination plugin
* pick or create the collection you want
* paginate it
* render the paginated collection

## Creating a paginated collection

### Basic usage

```twig
{# some collection #}
{% set collection = page.collection() %}
{# number of items per page #}
{% set limit = 5 %}
{% do paginate( collection, limit ) %}
```

This creates a paginated collection with `limit` items per page. As usual, any url parameters - except the page parameter, which is recreated - are passed on to the pagination bar's links.

### Extended usage

```twig
{% set collection = page.find( '/other/_events' ).children %}
{% set limit = 5 %}
{% set ignore_url_param_array = [ 'event' ] %}
{% do paginate( collection, limit, ignore_url_param_array ) %}
```

The above example is taken from http://ami-web.nl/events. This code creates a paginated collection with 5 items per page (the event summary list) which is presented together with an active event. The active event appears in only one of the summary pages. Consequently, the url parameter 'event' should be filtered out so it does not show up in the pagination bar's links, preventing inconsistencies with different page parameters. Any non listed url parameters (except the page parameter) are passed through unaffected. The requested page contains logic to pick a sensible default event.

### Rendering the paginated collection

The rest is identical to the standard procedure.

```twig
{% set collection = page.find('/other/_events').children %}
{% set limit = 5 %}
{% set ignore_url_param_array = ['event'] %}
{% do paginate(collection, limit, ignore_url_param_array) %}
```

The above example is taken from http://ami-web.nl/events. This code creates a paginated collection with 5 items per page (the event summary list) which is presented together with an active event. The active event appears in only one of the summary pages. Consequently, the url parameter `event` should be filtered out so it does not show up in the pagination bar's links, preventing inconsistencies with different page parameters. Any non listed url parameters (except the page parameter) are passed through unaffected. The requested page contains logic to pick a sensible default event.

## Rendering the paginated collection

The rest is identical to the standard procedure:

```twig
{# create list of items #}
{% for item in collection %}
   ...
{% endfor %}

{# include the pagination bar #}
{% if config.plugins.pagination.enabled and collection.params.pagination %}
    {% include 'partials/pagination.html.twig' with {'base_url':page.url, 'pagination':collection.params.pagination} %}
{% endif %}
```
