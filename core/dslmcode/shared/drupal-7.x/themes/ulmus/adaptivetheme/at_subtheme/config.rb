#
# This file is only needed for Compass/Sass integration. If you are not using
# Compass, you may safely ignore or delete this file.
#
# If you'd like to learn more about Sass and Compass, see the sass/_README.txt
# file for more information.
#
# This config file is borrowed from Zen, so thanks JohnAlbin for your hard work
# in bringing such fine tools to Drupal so us mere mortals may benefit.


# Set the Environment Variable
# Using :development enables the use of FireSass but will bloat the stylesheets
# with debug code, be sure to change to :production when moving from development
# to production servers.
environment = :development
#environment = :production


# Location of the theme's resources.
# Compass will overwrite the CSS files in the css_dir when set to watch.
css_dir = "css"
sass_dir = "sass"
images_dir = "css/images"


# Assuming this theme is in sites/*/themes/THEMENAME, you can add the partials
# included with a module by uncommenting and modifying one of the lines below:
#add_import_path "../../../default/modules/FOO"
#add_import_path "../../../all/modules/FOO"
#add_import_path "../../../../modules/FOO"


################################################################################
# You probably don't need to edit anything below this.


# You can select your preferred output style here (can be overridden via the
# command line)
#output_style = :expanded or :nested or :compact or :compressed
output_style = (environment == :development) ? :expanded : :compact


# To enable relative paths to assets via compass helper functions. Since Drupal
# themes can be installed in multiple locations, we don't need to worry about
# the absolute path to the theme from server root.
relative_assets = true

# To disable debugging comments that display the original location of your
# selectors. Uncomment:
# line_comments = false

# Pass options to sass.
# - For development, we turn on the FireSass-compatible debug_info.
# - For production, we force the CSS to be regenerated even though the source
#   scss may not have changed, since we want the CSS to be compressed and have
#   the debug info removed.
sass_options = (environment == :development) ? {:debug_info => true} : {:always_update => true}
