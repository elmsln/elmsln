# Contributing to this project

Please take a moment to review this document in order to make the contribution
process easy and effective for everyone involved.

Following these guidelines will help us get back to you more quickly, and will
show that you care about making ELMSLN better just like we do. In return, we'll
do our best to respond to your issue or pull request as soon as possible with
the same respect.

_**Please Note:** These guidelines are adapted from [Chosen](https://github.com/harvesthq/chosen)'s
[issue-guidelines](https://github.com/harvesthq/chosen/blob/master/contributing.md) and serve as
an excellent starting point for contributing to any open source project._

## Apereo process
When making a significant contribution to ELMS:LN we ask that you fill out a [ICLA](https://www.apereo.org/licensing/agreements/icla). The Individual Contributor License Agreement from Apereo (who helps foster ELMS:LN and educational technology projects more generally) helps us maintain good legal standing through due diligence that everyone involved in contribution has aknowledged that they are allowed to contribute the work they have performed.

## Copyright / Licensing
The ELMS:LN main repo is GPLv3 which may be seen as very aggressive but effectively it's to ensure validity of the entire project's pieces working together from a license compatibility perspective. All sub-repos defer to their respective licensing (always defer to local LICENSE.md / LICENSE.txt when in question).

## Quality controls
The following methodologies are how we help ensure quality of tagged ELMS:LN releases. While core developers often roll their own systems against whatever the latest test branch is, this is not recommended beyond core developers. Part of this methodology on the part of the core team forces the integrity and quality of even our development branches to be exceedingly high.

Other ways we ensure quality:
- Travis CI tests all commits and pull requests
- We use local git precommit hooks to ensure JS/PHP code is tested to ensure it doesn't break (see the [developer](developer) script in the main repo for how we work on the project in core)
- Web components help scope and encapsulate work, minimizing issues that could possibly occur visually
- We are working on a google lighthouse / accessibility / visual diff quality control system (based on our web component library)
- Only core team members have the ability to commit code and the majority of development happens in pull requests with all commits needing to be tied to an issue in the issue queue

No new library is added to core without at least two core memebers understanding how it works and all code is checked for license compatibility prior to inclusion to ensure legal compliance.

## Coding standards
While we use Travis CI to improve build quality, there are some other steps you can take to help ensure you meet our code quality standards:
- When developing code, use git at all times. This is the only VC system we support
- When using git to develop and push changes, utilize this pre-commit script to help stop broken code from bleeding into commits: `https://github.com/elmsln/elmsln/blob/master/scripts/git/pre-commit.sh`
- PHP code seeks to pass [Drupal coding standards](https://www.drupal.org/docs/develop/standards) while not all parts of this project are Drupal, these serve as a useful baseline
- Javascript code we attempt to stick to [Google's style guide](https://google.github.io/styleguide/jsguide.html) though this can get tricky. As the majority of our JS development is in Webcomponents it's important to follow the conventions of modularity in that methodology of development.
- Webcomponents have a "Gold standard checklist" which we attempt to follow when developing our elements regardless of how we produce them. [The Gold Standard Checklist for Web Components](https://github.com/webcomponents/gold-standard/wiki)

## Documentation
All documentation for ELMS:LN can be found and pull requested from the following repo: [ELMS:LN Documentation](https://github.com/elmsln/documentation)

We use HAX Desktop App to manage our documentation which if you'd like to speed up contributions and testing to our docs then check out: [Hax Desktop App](https://github.com/LRNWebComponents/hax-desktop-app)

## Using the issue tracker

The [issue tracker](https://github.com/elmsln/elmsln/issues) is the
preferred channel for [bug reports](#bugs), [features requests](#features)
and [submitting pull requests](#pull-requests), but please respect the
following restrictions:

* Please **do not** derail or troll issues. Keep the discussion on topic and
  respect the opinions of others.


<a name="bugs"></a>
## Bug reports

A bug is a _demonstrable problem_ that is caused by the code in the repository.
Good bug reports are extremely helpful &mdash; thank you!

Guidelines for bug reports:

1. **Use the [GitHub issue search](https://github.com/elmsln/elmsln/search?type=Issues)** &mdash; check if the issue has already been
   reported.

2. **Check if the bug has already been fixed** &mdash; try to reproduce it using the
   repository's latest `master` changes.

3. **Isolate the problem** &mdash; ideally reproducing this issue in our [vagrant environment](https://github.com/elmsln/elmsln-vagrant)

A good bug report shouldn't leave others needing to contact you for more
information. Please try to be as detailed as possible in your report. What is
your environment? What steps will reproduce the issue? What browser(s) and OS
experience the problem? What outcome did you expect, and how did it differ from
what you actually saw? All these details will help people to fix any potential
bugs.

Example:

> Short and descriptive example bug report title
>
> A summary of the issue and the browser/OS environment in which it occurs. If
> suitable, include the steps required to reproduce the bug.
>
> 1. This is the first step
> 2. This is the second step
> 3. Further steps, etc.
>
> `<url>` - a link to the reduced test case
>
> Any other information you want to share that is relevant to the issue being
> reported. This might include the lines of code that you have identified as
> causing the bug, and potential solutions (and your opinions on their
> merits).

**Note:** In an effort to keep open issues to a manageable number, we will close any issues
that do not provide enough information for us to be able to work on a solution.
You will be encouraged to provide the necessary details, after which we will reopen the issue.

<a name="features"></a>
## Feature requests

Feature requests are welcome. But take a moment to find out whether your idea
fits with the scope and aims of the project. It's up to *you* to make a strong
case to convince the project's developers of the merits of this feature. Please
provide as much detail and context as possible.

Building something great means choosing features carefully especially because it
is much, much easier to add features than it is to take them away. Additions
to ELMSLN will be evaluated on a combination of scope (how well it fits into the
project), maintenance burden and general usefulness.

Creating something great often means saying no to seemingly good ideas. Don't
dispair if your feature request isn't accepted, take action! Fork the
repository, build your idea and share it with others. Open source works best when smart and dedicated people riff off of each others' ideas to make even greater things.

<a name="pull-requests"></a>
## Pull requests

Good pull requests &mdash; patches, improvements, new features &mdash; are a fantastic help.
They should remain focused in scope and avoid containing unrelated commits.

**Please ask first** before embarking on any significant pull request (e.g.
implementing features, refactoring code, porting to a different language),
otherwise you risk spending a lot of time working on something that the
project's developers might not want to merge into the project. You can solicit
feedback and opinions in an open feature request thread or create a new one.

Please use the [git flow for pull requests](#git-flow) and follow Drupal's
[code conventions](#code-conventions) before submitting your work. Adhering to
these guidelines is the best way to get your work included in ELMSLN.

<a name="git-flow"></a>
#### Git Flow for pull requests

1. [Fork](http://help.github.com/fork-a-repo/) the project, clone your fork,
   and configure the remotes:

   ```bash
   # Clone your fork of the repo into the current directory
   git clone git@github.com:<YOUR_USERNAME>/elmsln.git
   # Navigate to the newly cloned directory
   cd elmsln
   # Assign the original repo to a remote called "upstream"
   git remote add upstream https://github.com/elmsln/elmsln
   ```

2. If you cloned a while ago, get the latest changes from upstream:

   ```bash
   git checkout master
   git pull upstream master
   ```

3. Create a new topic branch (off the main project development branch) to
   contain your feature, change, or fix:

   ```bash
   git checkout -b <topic-branch-name>
   ```

4. Commit your changes in logical chunks. Please adhere to these [git commit
   message guidelines](http://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html)
   or your code is unlikely be merged into the main project. Use Git's
   [interactive rebase](https://help.github.com/articles/interactive-rebase)
   feature to tidy up your commits before making them public.

5. Locally merge (or rebase) the upstream development branch into your topic branch:

   ```bash
   git pull [--rebase] upstream master
   ```

6. Push your topic branch up to your fork:

   ```bash
   git push origin <topic-branch-name>
   ```

7. [Open a Pull Request](https://help.github.com/articles/using-pull-requests/)
    with a clear title and description.

**IMPORTANT**: By submitting a patch, you agree to allow the project owner to
license your work under the [GPL License](http://en.wikipedia.org/wiki/GNU_General_Public_License).

### Change is deemed unsuitable
If a change suggested via the PR workflow above ultimately is deemed not to be valid by the core team, the following will occur:
- Reason for why it was rejected / has not been accepted will be given
- Ways of cleaning it up or suggestions of how to accomplish the given change via another repo / patch will be recommended
- Contributor will be told to keep being awesome. We reject work, not people.

Any change that falls outside the goals of the project or meeting the project's goals will be rejected or redirected elsewhere. ELMS:LN's project goals can be found in our [governance document](GOVERNANCE.md).