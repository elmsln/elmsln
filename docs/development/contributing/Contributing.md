# Contributing
This describes some of the policies and procedures for contributing back to the ELMS:LN project as well as how we handle things on github as far as branch and issue management go.

## Travis CI
All commits and pull requests get a minimal level of testing against the Travis CI Continuous Integration web service. This is effectively a “will it blend” test at the moment to see if the entire project builds. This doesn’t mean it is correct, it simply asks as a means of detecting MAJOR issues with a pull request prior to acceptance.

## Vagrant
The majority of the core contributors have a Vagrant image that they use to contribute back and test changes. Because we all start from the same VM or “one-line-installer” it increases the likelihood immediately that code working in 1 environment will work in all others in existence. For this reason it is highly recommended to use the fully automated mechanisms for building the project.

## Release management
In order to better manage quality of each release, we have adopted the following release policy: It’s ready when it’s ready. This may not seem like a real policy, but it’s important because it means we won’t just ship a release in order to meet some fictitious deadline. The only time we will push releases beyond just the “when it’s ready” is when there is a critical security update to be had.

## Branch management
- master: all releases are cut off from here; this is the authority branch and we try to keep it as close to 100% upgrade / maintainable as possible.
- develop: prior to cutting a point release, we will branch master off to develop, then merge the currently active release branch off. This provides local testing capability via Vagrant as well as remote via Travis and greater safety in merging over to master upon success. 
- x.x.x: for each major release there is a branch that is developed against to lead up to it. This is cut from master whenever a new release branch starts and all other pull requests and sub-branches should be cut off of this one in order to improve merge-ability.

### Issue branches
If there is a specific tricky issue that needs its own branch, these should be named i{issue number} like `i96` for example. These branches are only to be used for more wicked problem spaces where we’re creating lots of new functionality OR when you plan on tackling something for the day and want to keep it all tidy. The idea isn’t to work in `i` branches endlessly, it’s to keep them tight knit and then get them pushed into their associated working branch as quickly as possible. *This is especially true / a necessary evil for theming*. Theming is notoriously painful to get to rebase / merge happily with upstreams because unlike modules, themes tend to touch a lot of files across parts of the project.

## Pull requests
It is not required but preferred that all commits making their way in have a PR to track. This helps improve with transparency of testing as well as keeps core maintainers all on the same page. All core maintainers have the ability to push against master for project sustainability.
