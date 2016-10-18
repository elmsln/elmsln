# Front-end Dev
My front-end stack that changes day to day :)

Here is a demo of the installation and a rundown of features. https://www.youtube.com/watch?v=nNmILmypXyU

## Installation

### Install the necessary package managers

``$ npm install -g bower``

``$ npm install -g gulp``

``$ npm install -g gulp-hologram``

``$ gem install bundler``

### Clone the repo

``$ git clone git@github.com:heyMP/frontend-dev.git``

``$ cd frontend-dev``

### Install the dependencies

``$ npm install``

``$ bower install``

``$ bundle install``

#### Segmentation Fault
If you receive any Drush errors that contain `Segmentation fault` run `npm install`, WITHOUT sudo. There are occasions where the npm cleanup script doesn't run when using sudo.

### Run Gulp Server
``$ gulp server``

If you are using this stack on a server rendered website then run gulp without its built in server:

``$ gulp``

## Bower Dependencies

Bower makes it extremely easy to add new third-party libraries to your project.  Front-end dev makes that process even easier by automatically pulling those javascript and css files from bower into your project via gulp.

### Example: Adding Bootstrap through Bower

The first step is to run:

```$ bower install bootstrap --save```

Notice the ``--save`` flag.  Not only does this add Bootstrap to the list of your
project dependencies, it also lets Front-end Dev know to automatically pull any
javascript or css resources into our existing project.

Now run:

```$ gulp build```

This will allow gulp to parse through the list of bower dependencies and create
third-party.js and third-party.css files.

### Overriding Bower Imports

Sometimes there will be lots of javascript and css files that will be packaged
with a library.  You'll want to use Bower's 'override' option specify which files
you want to be pulled into your project.

Edit the 'bower.json' file. You will see an option in the json array for 'overrides'.
here is where you have a few options.

#### Specify a file

```
  "overrides": {
    "bootstrap": {
      "main": js/tooltip.js"
    }
  }
```

#### Specify multiple files

```
  "overrides": {
    "bootstrap": {
      "main": ["js/tooltip.js", "js/modal.js"]
    }
  }
```

#### Ignore library all together

```
  "overrides": {
    "bootstrap": {
      "ignore": "true"
    }
  }
```

To see all of the available options, visit the [main-bower-files website](https://github.com/ck86/main-bower-files#overrides-options).
