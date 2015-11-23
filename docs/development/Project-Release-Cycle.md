Following the direction of Drupal 8 and the Drupal 7 fork Backdop, ELMSLN will use a Semantic versioning style. This gives releases 3 numbers associated with them of the form 1.2.3 which can be seen as follows:

### first digit
Major version release, potentially incompatible / breaking API changes. This might be something like ELMSLN upgrading all under the hood components to use Drupal 8. Capabilities may be added or removed based on what ever the designation for this being a major version release is.
### second digit
Backwards-compatible release, potentially adds new capabilities like new services or authorities but is expected to be compatible within the major version branch. In here we add, never remove capabilities but there is a functional change / addition to the system.
### third digit
Backwards-compatible release, fixes bugs. An example of this could be cleaning up usability, accessibility, or workflow issues. Notices and error messages would likely be resolved in these minor version numbers. It is reasonable to assume that unless you have modified ELMSLN in some fundamental way that you can upgrade to this version without issue.

All version upgrades of any kind should be tested either in vagrant or on development / staging servers of some kind before being pushed to live.

## 0.x.x releases
The only exception to the semantic versioning rule of "major version" is that all 0.x.x releases are implied pre-releases in pursuit of 1.0.0. We will be attempting to work through the upgrade and versioning process through the 0.x.x release cycle. There have been only a few exceptions where `master` is non-functional in the last year and we've largely been accounting for configuration changes via the rolling upgrade systems currently in place. 0.x.x will give us a chance to also have snapshots to have conversations with others around while we build toward creation of all (initial) tools in the network for a 1.0.0.

## first release on this cycle
0.1.0 will have a stable 'courses' (mooc 1.x) and 'online' (cis 2.x) included as part of the release. As we make small improvements (improve usability, etc) 0.1.1 will be released. As we release a more stabilized version of the studio (cle 1.x) however, would increase the release version to a 0.2.0 to reflect the new application being deemed stable enough for use.

## Service / Authority versioning
ELMSLN is made up of other tools, all with their own versions. For example, CIS 7.x-1.x and CIS 7.x-2.x refer to the versions specific to this tool / application in the larger system. These are Drupal specific version / identifiers and may change independent of ELMSLN versioning. This is by design. 0.6.5 of ELMSLN might actually have MOOC 1.2, CLE 1.4, and CIS 2.0. While 0.7.0 might have MOOC 1.3, CLE 1.5, CIS 2.1, and ICOR 1.0. The new tool inclusion being what makes this a 0.n+1.0 release, while all the versions of the included tools have increased, not impacting the overall version number.

## Additional sources
* https://www.drupal.org/node/586146
* https://backdropcms.org/releases