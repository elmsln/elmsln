# Aurora

Aurora is an HTML5, [Sass](http://sass-lang.com/) and [Compass](http://compass-style.org/) powered minimalist base theme. It is optimized for both responsive and mobile first web design. Built to encourage best modern front end practices, Aurora comes with, [LiveReload](http://livereload.com/), [Google Chrome Frame](https://developers.google.com/chrome/chrome-frame/), and [Typekit](https://typekit.com/) integrations, with advanced integrations with [Bower](http://bower.io/) for package management and [Grunt](http://gruntjs.com/) for task management (Sass compiling, JS Hinting, Image Optimization, and app-free Live Reloading out of the box) available. It also suggests and recommends Drupal modules to get the most out of both Aurora and out of Drupal. All of the optimizations and integrations in Aurora are designed to be there only when you need them and get out of your way when you don't.

## Documentation

All of [Aurora's Documentation has been moved online](http://snugug.github.io/Aurora/). The most up to date versions of all docs can be found there.

## Upgrading to Aurora 3.x

Aurora 3.x has had a major internal overhaul to put it inline with current best practices. The first two things you'll be likely to see are that both of the previous Sidebar regions have been removed, and all of the site information that would normally be inside your `page.tpl.php` are gone as well. While getting the sidebars back will require you to write a custom `page.tpl.php` file (we encourage you instead to use the HTML5 Sections layout with [Panels](http://drupal.org/project/panels)), the site information was removed with the express intent of moving to a Blocks Everywhere approach to these pieces of information. With that in mind, to use these, we encourage you to use the [Blockify](http://drupal.org/project/blockify) module; it has full Aurora support. We even have a full section in your theme's settings page of recommended modules to use with Aurora to get the best experience out of Drupal.

Additionally, many of the advanced theme settings that made Aurora great have been moved out of Aurora and into [Magic](http://drupal.org/project/magic). This isn't because we don't love Aurora, but it's because we love the idea of having all of frontend be able to share in on this awesomeness. Because of this, some of your settings are going to need to be migrated.

### Changes in Aurora 3.2

In Aurora 3.2, the HTML5 Flexible Panels has been removed completely. Although this is due to a number of reasons the two bigs ones are that 1) it never worked exactly as we intended and 2) it is more robust to just create your own panels layout. To help with this, a sample layout has been added to Aurora to reference. This will give you far more control over the layout, and much cleaner and faster markup.

Please convert any existing layouts to this method BEFORE upgrading.

Links on the how to:
https://drupal.org/node/495654
http://drupalize.me/videos/custom-panels-layouts

## Testing Upcoming Releases

If you plan on testing upcoming releases, you're going to need the prerelease Compass Aurora gem as well as the prerelease code from here or things just may break. Installing the prerelease Compass Aurora gem is easy, but it _may_ break Aurora installs requiring the previous gem. If you need to use multiple versions of a gem, look into [Bundler](http://gembundler.com/). To install the prerelease gem, type the following into your command line:

`gem install compass-aurora --pre`

Aurora will be moving fast, and any breaking changes will be signified with a new full release (1.x to 2.x, 2.x to 3.x, etc…). This is the nature of of a frontend project attempting to stay on top of best practices as they evolve. I will try my best to have as few breaking changes as possible, and do not foresee any in the current product roadmap, so chances are 2.x will be around for a while, but bare it in mind that things may change.

## Using Bundler

Bundler is standard Ruby of managing gem dependencies, and it is highly encouraged you use it to ensure that your project is using the correct version of required gems. As stated above, this stuff moves fast, and if you are updating your gems without understanding what they break, it's likely you're going to get yourself into trouble. Bundler helps to ensure you can use the cutting edge gems on new projects while not breaking old projects.

Installing Bundler is easy, type the following into your command line:

`gem install bundler`

Once you've installed Bundler, in your theme's directory, where your `config.rb` file is, create a file called `Gemfile`. The Gemfile that comes with new Aurora 7.x-3.x subthemes looks like this:

`# Pull gems from RubyGems
source 'https://rubygems.org'

# ~> Refers to all versions of the given gem on the current full version number, so it will be able to use any version of Compass Aurora until Compass Aurora 4.x.x. For a specific version of a gem, remove the ~>
gem 'compass-aurora', '~>3.0.0'
gem 'toolkit', '~>1.0.0'
gem 'singularitygs', '~>1.0.7'
gem 'breakpoint', '~>2.0.2'
gem 'sassy-buttons', '~>0.1.4'
gem 'compass-normalize', '~>1.4.3'

# Now that you're using Bundler, you need to run `bundle exec compass watch` instead of simply `compass watch`.`

Once you've set up your Gemfile, in your command line, run the following:

`bundle install`

This will install the relevant gems and ensure your theme stays at those versions. Then, to compile, instead of using `compass watch`, use the following:

`bundle exec compass watch`

**Aurora 2.x Gemfile**

If you have Aurora projects at 2.x and 3.x, you need to use Bundler with your 2.x projects. A sample Gemfile for a 2.x project would look like the following:

`source 'https://rubygems.org'
gem 'breakpoint', '1.3'
gem 'susy', '1.0.8'
gem 'singularitygs', '0.0.17'
gem 'respond-to', '2.6'
gem 'toolkit', '0.2.6'
gem 'compass-aurora', '~>1.1.1'`

### Maintenance

The Aurora theme is maintained by [Sam Richard](http://drupal.org/user/820332) ([@snugug](http://twitter.com/snugug)) and [Ian Carrico](http://drupal.org/user/1300542) ([@iamcarrico](http://twitter.com/iamcarrico))

Any updates or changes to the Aurora Compass Extension can be made on it's [GitHub page](https://github.com/Snugug/Aurora). Please either submit an issue or a pull request with the desired changes.