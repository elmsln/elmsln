# Grav Comments Plugin

The **Comments Plugin** for [Grav](http://github.com/getgrav/grav) adds the ability to add comments to pages, and moderate them.

# Installation

The Comments plugin is easy to install with GPM.

```
$ bin/gpm install comments
```

Or clone from GitHub and put in the `user/plugins/comments` folder.

# Usage

Add `{% include 'partials/comments.html.twig' with {'page': page} %}` to the template file where you want to add comments.

For example, in Antimatter, in `templates/item.html.twig`:

```twig
{% embed 'partials/base.html.twig' %}

    {% block content %}
        {% if config.plugins.breadcrumbs.enabled %}
            {% include 'partials/breadcrumbs.html.twig' %}
        {% endif %}

        <div class="blog-content-item grid pure-g-r">
            <div id="item" class="block pure-u-2-3">
                {% include 'partials/blog_item.html.twig' with {'blog':page.parent, 'truncate':false} %}
            </div>
            <div id="sidebar" class="block size-1-3 pure-u-1-3">
                {% include 'partials/sidebar.html.twig' with {'blog':page.parent} %}
            </div>
        </div>

        {% include 'partials/comments.html.twig' with {'page': page} %}
    {% endblock %}

{% endembed %}
```

The comment form will appear on the blog post items matching the enabled routes.

To set the enabled routes, create a `user/config/plugins/comments.yaml` file, copy in it the contents of `user/plugins/comments/comments.yaml` and edit the `enable_on_routes` and `disable_on_routes` options according to your needs.

> Make sure you configured the "Email from" and "Email to" email addresses in the Email plugin with your email address!

# Enabling Recaptcha

The plugin comes with Recaptcha integration. To make it work, create a `user/config/plugins/comments.yaml` file, copy in it the contents of `user/plugins/comments/comments.yaml` and uncomment the captcha form field and the captcha validation process.
Make sure you add your own Recaptcha `site` and `secret` keys too.

# Where are the comments stored?

In the `user/data/comments` folder. They're organized by page route, so every page with a comment has a corresponding file. This enables a quick load of all the page comments.

# Visualize comments

When the plugin is installed and enabled, the `Comments` menu will appear in the Admin Plugin. From there you can see all the comments made in the last 7 days.

Further improvements to the comments visualization will be added in the next releases.

# Email notifications

The plugin interacts with the Email plugin to send emails upon receiving a comment. Configure the Email plugin correctly, setting its "Email from" and "Email to" email addresses.

# Things still missing

- Allow to delete comments from the Admin Plugin
- Ability to see all comments of a page in the Admin Plugin
- Ability to reply to a comment from the Admin Plugin
- Auto-fill the comment form when a user is logged in
