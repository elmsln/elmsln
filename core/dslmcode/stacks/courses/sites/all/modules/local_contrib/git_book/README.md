# Git Book

Git Book creates a content type that forms a new kind of book node which pulls its content from a git repository. It
utilizes the Git.php library to make this easy to do. Git book is currently made up of two modules:

Git Book - Provides the Feature / Content type / some simple helper functions needed to manage the git_book type.
Git Book Read The Docs -Provides support for repos that utilize the Read the Docs (readthedocs.org) style YAML file +
documentation structure. This allows you to manage outlines of content in github and suck it into a drupal site to do
whatever you want with.

Currently when the git_book type is created, it will pull the content in and when it's deleted it will delete the repo
from your server.

## Requirements
 - YAML support (yum install php-pecl-yaml or equivalent)
 - git
 - Private files directory

## Installation

First you need to read through the requirements (above) and make sure your server has YAML, git, and private directory
support. Next, you need to download the gitphp library from the following url:

https://github.com/kbjr/Git.php/zipball/master

Take that zip file, and put it's contents into a folder called "gitphp" in your /sites/all/libraries directory.

Also, you need to make sure your Drupal site has write access to your private directory. This is where it will store the
git repository.

## Roadmap
Future plans are for synchronization as well as ability to push changes back to git repo (though this assumes the server
is authorized to do so).

## Resources
[Drupal planet article](https://drupal.psu.edu/blog/post/pulling-git-repo-content-drupal)
[Video showing this working](https://www.youtube.com/watch?v=UYrR53XG3f4) in [ELMSLN](https://www.drupal.org/project/elmsln.org)