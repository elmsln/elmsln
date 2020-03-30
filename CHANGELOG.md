## 1.0.0 - 2020-03-30 - March forward
The NARA UX audit on HAX has dramatically improved the initial usability of HAX to new users and now it's enabled by default. We've also got support for cloudfront CDNs thanks to work in HAXcms which have been ported here. This is a nearly 1 million line change between the front end assets and backend removals. HAX is a dramatic improvement (again) and investment in it has improved the accessibility and usability of everything it's involved working on.

This aligns our pipeline for HAXcms and ELMS:LN with the build workflow the core development team utilizes. Meaning that we're able to run 1 build routine and simultaneously support both platforms as well as publishing to npm and other sources to optimize internal workflows. Penn state now has a cloudfront delivered https://cdn.webcomponents.psu.edu/haxcms and /cdn which can serve both audiences.

### Notable
- API, LOR, HUB, comply and other experimental tools have been removed
- HAX enabled by default
- Lots of studio improvements
- Better cross browser compatibility
- All assets should load faster on all browsers, CDN agnostic
- Support for cloudfront
- 100s of issues not from this repo between HAXcms, lrnwebcomponents and EdTechJoker are incorporated here.

To read about the changes in this release see: https://github.com/elmsln/elmsln/milestone/21?closed=1
To read about changes to HAXcms included in this release: https://github.com/elmsln/HAXcms/milestone/3?closed=1
## 0.12.0 - 2019-10-01 - HAX impovements
We'll be able to roll updates faster. This sees HAXcms 0.12.0 release aligning with ELMSLN
as we'll continue to do that from now on as best we can. This includes lots of improvements to HAX and the databinding / interplay with Drupal's input filters as well as bug fixes that were reported as part of development in between. There's improvements in the studio around permissions, minor doc updates from students, PHP version compatibility and support for Ubuntu 18 LTS. HAXcms core has been updated as well though its planned to start tests at Headless Drupal as backend toward the end of the year at the earliest. The outlining tools and UX feedback from HAXcms will feed directly into having course outline options built on top of Drupal as a backend, allowing ELMSLN sites to remain in place, yet progressively be upgraded to leverage the latest and greatest of HAXcms in place. HAXcms scope is on singular site / publishing flows so the theme engine and UX improvements in HAXcms can help inform ELMS:LN without there being a conflict in use-case.

To read about the changes in this release see: https://github.com/elmsln/elmsln/milestone/19?closed=1
To read about changes to HAXcms included in this release: https://github.com/elmsln/HAXcms/milestone/2?closed=1
## ELMS:LN 0.11.0 - 2019-08-02 - Headless by default
Over a year in the making, this moves us onto V1 spec webcomponents and increasingly more headless.
HAXcms is now actually included under the hood and it's build routine powers the ELMS:LN universe.
This allows the team to focus on both projects via the same build routine. HAX has seen an incredible
amount of performance, quality, capability, and accuracy enhancements over the last year and is starting
to find its way outside of the ELMS:LN ecosystem with improvements submitted to the UX of the project
worked back in from both front end and other CMS communities.

To read about the changes in this release see: https://github.com/elmsln/elmsln/milestone/20?closed=1

## ELMS:LN 0.10.0 - 2018-06-29 - #haxtheelms
3 years after the idea was expressed, the team finally has build a truly decoupled, transformative authoring experience. After months of development, testing, and talk, action is materialized. We present you with the HAX authoring system baked into ELMS:LN, out of the box, highly preformance optimized, with tons of great elements and integrations from day 1. For the moment, there are effectively two editing modes while we engage in deeper, production level testing and broader UX testing of HAX. There's traditional edit mode, and HAX editor which unleashes the power of web components for the masses. #haxtheweb is also bringing together people across multiple platforms to unite on front-end based UX patterns and design assets.

This is a game changer for quality of what can be produced and is the beginning of realization of the web component promise and buy-in from all team members. This release closes 118 issues with HAX being it's own repo that has 131 issues of its own closed towards this release. There is also a massive performance gain over 0.9.0 on page to page and perception of performance as well as resource optimization. Meaning ELMS:LN sends less data, sends it faster, uses what it has more wisely, and lazy loads all dynamic content that's been previously created.

This also positions the team for doing more iterative releases w/ more features as we've adopted an enhanced build routine that is more accountable then previous methods of releasing components. The next push is towards much deserved vacations for the team, gathering UX feedback, and working on a next generation content presentation engine leveraging the skills we've all learned to this point.

To read about the changes in this release see: https://github.com/elmsln/elmsln/milestone/12?closed=1

## ELMS:LN 0.9.0, 2017-09-20 - Birth
This is the biggest design release of the platform to date. It takes a bold new step into the web components world and the world of one page apps through the creation of our first production Polymer application in the Open Studio. It realizes the paradygm shift away from traditional page transactions to AJAX and web component based application development.

The new studio is in production usage already and is seeing incredibly promising early results from students and faculty using it (over 100 using it currently). This release closes 157 issues, many related to studio and UX bug fixes. The changes pushed in 0.8.1 are also reflected, meaning that we now have a concept of near infinite scale as far as section size during roster synchronization.

This means that no matter how big ELMSLN gets, no matter how many tools it has, no matter how many user accounts you push at it, it will process them all. User page transaction scale is then up to the resources you through behind it. On the topic of scale, this also includes enhancements to the web component page delivery which show 200% gains over previous page delivery (back end gain, front end coming).

There is also support built in for Canvas roster API integration which can pull names and avatars throughout ELMS:LN as well; meaning that student experience is that much more seemless when interfacing with that LMS.

This release is published on September 10th, 2017; marking our first 10 year anniversary. We celebrate our "birthday" as a movement on the date stamp of the first file we created coining "ELMS" and what it was to do. You can read this historical document here: https://psu.box.com/s/g477s7ippa8e9yxjp5jz98n2ot9w64gd

We celebrate today for tomorrow marks the dawn of a new era.

To read about the changes in this release see: https://github.com/elmsln/elmsln/milestone/11?closed=1

## ELMS:LN 0.8.1, 2017-09-19 - Snake it
Only #1945 added so that older builds can complete without our design enhancements yet. This was asked for by the community and is not the issue finished but gets this contributed functionality into production systems running 0.8.0 previously.

## ELMS:LN 0.8.0, 2017-05-26 - Kunitz
This release fixes 53 issues since the last release, with 99 since 0.7.0. This is a the beginning of a paradigm shift for the project with regard to design. The system is starting to take on the UX patterns of Material more directly through the core adoption of Web Component architecture across the entire platform. The theme hasn't been completely replaced but it has had major design overhauls since 0.7.x and is drastically easier to navigate / learn.

We've also started to get the build process down for Polymer / Webcomponent architecture and now have 100s of web components available for usage, many of which have experimental support for HAX. There have been a lot of minor bugs fixed associated with the studio, network wide communications edge cases, and performance improvements related to syncing. Git book based workflows for markdown ingestion have also been drastically improved and are now being utilized in production deploys (at PSU).

There is also experimental support for one-page-apps which will start the process of rapidly improving the UX patterns within different parts of the system both in terms of user experience as well as performance and responsiveness. ELMS:LN will start to feel more like an app unlocking the power of an ecosystem rather then a complex architecture full of "lots of stuff".

A community note attached to this release cycle: ELMS:LN has also been formally accepted into the Apereo Incubation program which is a huge next step for our community!

To read about the changes in this release see: https://github.com/elmsln/elmsln/milestone/18?closed=1

## ELMS:LN 0.7.1, 2017-02-22 - MileHigh

This release fixes 46 issues since the last release. Major improvements in stability to Studio which is starting to gain critique capabilities. We're also seeing improved ability to maintain and establish course / section context when jumping domains. We're starting to improve data visualization on dashboards for xAPI data which now can be visible everywhere.

Minor and Medium bug fixes in edge cases in CIS, Assessment, Discuss, and Media systems which would cause Course nodes not to save correctly. We've got some minor CSS tweaks to the lmsless bar and a better default banner to make the system more visually appealing out of the box and setting us up for our UX improvement thread. There is also experimental support for Polymer elements (which will change everything in the coming year) and Bookmarking in MOOC.

To read about the changes in this release see: https://github.com/elmsln/elmsln/milestone/17?closed=1

## ELMS:LN 0.7.0, 2017-01-30 - Redux
This release fixes over 100 issues since the last release (200ish since 0.6.0). Major improvements in stability to Studio which has graduated as the 1st angular2 based system in the network, as well as lots of UX improvements in all levels of the system. Media, Online, and Courses see major improvements in usability as well. All other systems are a lot easier to access and system context is being maintained between systems much better. Multiple demonstrations of this release are starting to make believers of the approach.

To read about the changes in this release see: https://github.com/elmsln/elmsln/milestone/13?closed=1

## ELMS:LN 0.6.3, 2016-12-18 - Evergreen
This release now adds support for CAS, cleans up multiple minor installation issues with Ubuntu 16, fixes some minor UX issues and enhances the internal ELMSLNJS API for building Angular apps against ELMSLN.

To read about the changes in this release see: https://github.com/elmsln/elmsln/milestone/16?closed=1

## ELMS:LN 0.6.2, 2016-12-02 - Dominant

This release includes lots of edge-case performance, edge-case stability, usability and minor bug fixes noticed after deployment of 0.6.1.

To read about the changes present in this release see: https://github.com/elmsln/elmsln/milestone/15?closed=1

## ELMS:LN 0.6.1, 2016-11-22 - Gravy

This release includes minor fixes noticed after deploying 0.6.0 in the wild on multiple servers. This is a minor release based on scope of the issues and upgrading from 0.6.0 should be minimally invasive. There is a server level upgrade to apply at this version marker but it is not critical. This also includes additional work towards the Angular version of the studio which is close to working.

Thanks to these reporters & contributors to this release:
@djfusco @rickhumphries @Deb-G @mmilutinovic1313 @btopro @bradallenfisher @heyMP

## ELMSLN 0.6.0, 2016-11-20 - Turkey

This release has major improvements to infrastructure deployment, migration and QA workflows. It also drops previously produced keychain requirements which had username and passwords and replaces them with a hash based methodology which can be updated and random at will. These are specific to each service account running commands on user's behalf so it was never a serious security issue but always good to do house cleaning. Also includes many bug fixes, vastly improved developer UX in vagrant via the `sh developer` command and other PHP7 compatibility improvements.

* User profile borked in firefox bug style guide / theme #1446
* Support continuous operation for Voicecommander in A11y module accessibility AWESOME! #1492
* Add keyboard key shortcuts for voice / other options accessibility #1491
* WD advagg: Reading from the file system failed. This can sometimes happen during a deployment. accessibility minor #1485
* PHP Deprecated: Methods with the same name as their class will not be constructors in a future version of PHP; ctools_context has a deprecated constructor infrastructure #1484
* Unable to change banner for CIS and Courses bug minor online / CIS #1481
* Error notices on Course Outline bug minor #1479
* remove trigger delay notices minor #1478
* notice if CPR didn't respond w/ profile bug minor #1483
* Add/Edit Network Option Removed bug User Experience #1480
* Create RestWS meta controller for render-as ELMSLN core infrastructure medium security related #812
* Update Vagrant documentation #1477
* Make elmsln{type}:// a real stream wrapper Developer Experience development ELMSLN core minor #1378
* Fork base-box for vagrant to improve spin up time Developer Experience vagrant #1470
* Extract cfg password file to new location infrastructure security related #1471
* Track page views by default in MOOC courses / mooc #1472
* First login experience community documentation question #1308
* Install screen during spin up at root ip Developer Experience infrastructure User Experience #1361
* Possible to replace keychain? infrastructure #1465
* account for email and username is job scripts bug infrastructure #1421
* System topology Developer Experience hard infrastructure scale / performance #866
* make tmp directory for older installs bug infrastructure minor #1469
* Support for environment specific alias files development drush related infrastructure #1457
* Disable aggregation for better performance scale / performance #1468
* Add all domains to sites.php infrastructure #1463
* Promote 0.5.0 release a bit community #1467
* h5p question feedback text has silly max height bug media / elmsmedia style guide / theme #1466
* Document contextual hierarchy of concepts action plan community documentation #1382
* Add better banner style guide / theme #1451
* elmsln api callback for 'what content types can this user create' infrastructure #1461
* Make upgrade hook in elmsln_core for temporary directory setting infrastructure #1459

## ELMSLN 0.5.0, 2016-11-08 - Pumpkin

Another release, another big release. This update has massive performance, accessibility and usability enhancements. There's also built in support for mapping, xAPI visualization and tracking, read time statistical generation is now stable, PDF / Print mode printing, more refined media and testing work. The usability improvements associated with color and design now give greater context of where people are and what they are doing. MaterializeCSS has also been fully implemented, replacing our 2 year long run with Zurb Foundation / hacky / some materialize code. Materialize nets us a larger design community and really clean visualization / design patterns to start from. There's also a lot of work under the hood in stability and improvements people won't notice but that put us on better footing going forward, including Ubuntu 16 with PHP 7, MariaDB, and HTTP2 support for the fastest page delivery currently possible by web-stacks. There's also some experimental work for Angular 2.0 apps in the 2.x version of the Studio. The next release will focus more on getting this and other Angular experiments graduated to full usage. This release has the most issues stomped and functionality added since the project initially got a 0.0.0 release marker.

* Cut a 0.5.0 release after 1 last build #1453
* Add quiz_result_export to assessment system assessment / grades assessment / quiz #1449
* Make a pie chart off of H5P results big data Tincan / XAPI #1450
* enable elmsln LRS configuration defaults in media / mooc Tincan / XAPI #1448
* Add oh mai zsh icon AWESOME! Developer Experience #1434
* Document patch in Bakery Developer Experience drupal related #1442
* Dropdowns don't work in Firefox style guide / theme #1445
* Change Accessibility menu to Preferences accessibility #1447
* Bakery gives us too much of a developer-esk message when it does profile updating User Experience #1441
* Function to do an entity injection at the paragraph level, between systems User Experience #1440
* Upgrade materialize to latest style guide / theme #1439
* Allow for off-canvas / modal shortcodes discuss / discuss style guide / theme #1264
* Bring back "ELMS Places" concept enhancement interact / icor #479
* Suggestion: Marking or Notification System for when to run leafy Developer Experience #1427
* Zurb Foundation in v0.5.0 change notice community style guide / theme #1419
* Move print buttons to accessibility menu accessibility enhancement Learner Experience #1431
* Apply CSS to print view accessibility enhancement Learner Experience #1432
* PDF Libraries community courses / mooc documentation enhancement infrastructure #280
* Add "check for updates" to leafy AWESOME! Developer Experience infrastructure #1148
* Gitbook import titles are doubled courses / mooc enhancement #1400
* user profile / dashboard inspiration people / cpr style guide / theme User Experience #1426
* Page tpl configurable wrapper to support full width enhancement style guide / theme #1428
* People next steps people / cpr User Experience #1307
* Apply LTI patch to support Canvas launches enhancement LTI #1356
* Fix RestWS create permission for non admin roles bug hard #1347
* Fix PHP 7 bombs in contrib Developer Experience easy enhancement infrastructure scale / performance #998
* apdqc recommendations scale / performance #1350
* Implement views_content_cache in media / interact scale / performance #1374
* Support Ubuntu16 (as best we can) AWESOME! Developer Experience infrastructure scale / performance vagrant #1416
* Notice: Array to string conversion bug minor #1423
* fonts style guide / theme #1415
* Latest UX not showing as responsive on mobile style guide / theme #1417
* add support for vibrate jquery plugin enhancement User Experience #1152
* upgrade hook to deal w/ authority require_once issue bug major change #1413
* Allow for breaking false content locks enhancement #1398
* Upgrade core and contrib where needed drupal related #1411
* update imageinfo_cache #1412
* Support multiple versions of the same distro name space in same version development infrastructure #1408
* set APDQC defaults for lock and session tables scale / performance #1349
* Make a CLE 2.x studio / cle #1406
* Allow admins/staff to still be able to edit user objects locally easy enhancement studio / cle #1392
* Accessibility: Create an animated gif player style accessibility easy media / elmsmedia style guide / theme #1315
* switch cis_helper_sync_network_roster to use internal mechanism for sync development easy enhancement online / CIS #944
* Add read time data to mooc/book-toc path courses / mooc enhancement #1389
* drop "media preference" field in favor of CDN auto detect fail enhancement Learner Experience media / elmsmedia people / cpr #1369
* Drop "sync" vs "non-sync" connotation for settings pages in services bug ELMSLN core Staff Experience #643
* Make ckeditor templates selection ...well... less terrible enhancement User Experience #1387
* mooc: Make left hand nav just be there courses / mooc enhancement Instructor Experience medium Staff Experience #1366
* ckeditor link needs to default to internal bug minor #1386
* export Read time pemission courses / mooc easy minor #1385
* Make Read time a button / part of page to calculate bug courses / mooc hard ready #1196
* Offering page needs to default services all selected enhancement infrastructure medium online / CIS #1164
* don't ask CIS for sections if we don't have one bug enhancement online / CIS scale / performance #1384
* CIS filefield paths needs to clear banner image on upload easy online / CIS #1383
* Try to apply materialize stuff to better filters / views filters ELMSLN core enhancement medium style guide / theme #1367
* Display mode for documents bug easy #1372
* Do update hook for tincanapi function replacement easy minor Tincan / XAPI #1379
* Add dinosaur with sunglasses icon AWESOME! #1381
* Change Icon / Banner image to be delivered from CIS enhancement online / CIS #1368
* Make a elmsln:// file schema module Developer Experience ELMSLN core enhancement infrastructure #1311
* add support for tincanapi to use non-blocking calls scale / performance #1375
* add support for prefetch to populate caches before arriving at targets AWESOME! #1376
* Implement views_content_cache across CIS / MOOC enhancement scale / performance #1256
* Make submit widget into horizontal card studio / cle #1285
* allow querying results to return rendered output enhancement infrastructure #1365
* Make an icon font of elmsln icons style guide / theme #1364
* vagrant add php-fpm reboot for dev ux Developer Experience vagrant #1362
* xapi Data path enhancements big data Instructor Experience Staff Experience Tincan / XAPI #1358
* implement domain prefetching scale / performance #1352
* Add Read time stats onto the /data page courses / mooc #1343
* Break drupal's core "conflict" connotation with node forms bug community #1245
* Make callback to return form as JSON Developer Experience medium #870
* xAPI metadata testing and applying it to all statements calls bug Tincan / XAPI #1191
* Add in the news area to elmsln.org community #1335
* Front end stack install steps documentation #1342
* add colorblindness simulation accessibility AWESOME! ELMSLN core #13463
* don't set a php-fpm specific memory limit in installers infrastructure #13377
* Wire up entity/type/data AWESOME! big data Tincan / XAPI #13402
* Add support for blob fields in field UI development enhancement #1329
* Pathcache needs enabled bug scale / performance #1325
* Devel developer experience improvement Developer Experience #1326
* Lay out vision for each distribution and future ones not started yet community documentation #1064
* su claims access denied on ubuntu 14 even when root bug easy infrastructure #492
* Ubuntu / Deb complains about not being able to email bug easy infrastructure minor #568
* During Amazon spin up. PHP Warning: Error while sending QUERY packet bug Developer Experience infrastructure medium minor testing #697
* additional testing for read time AFTER initial install big data courses / mooc enhancement media / elmsmedia #1155
* review authcache and the submit widget token bug courses / mooc #522
* Add banner picture to user profile fields list people / cpr style guide / theme #1265
* Implement W3 spec on low vision accessibility documentation easy enhancement non-coder #778
* Host a git version / mirror on elmsln.org community #1305
* Add h5p accessibility to our documentation accessibility community documentation #1299
* Produce new video for the homepage‏ community documentation enhancement #1026
* symlink in the parsedown library added for gitbook #1303
* Accessible fallback for media types accessibility enhancement media / elmsmedia #1302
* Gitbook.com Plugin for ELMS:LN enhancement #1006
* Masquerade logical flaw w/ staff accounts ELMSLN core #1295
* Users should be able to view profiles ELMSLN core #1294
* upgrade h5p drupal related #1291
* Service Unavailable infrastructure #1289
* Icon Libraries for CIS LMS-less Links documentation easy non-coder student design project #779
* Support for Image galleries enhancement media / elmsmedia #1112
* Support for Flyouts / off-screen / related concepts discuss / discuss enhancement interact / icor Learner Experience media / elmsmedia student design project style guide / theme User Experience #480
* Hidden nodes enhancement courses / mooc drupal related easy enhancement #1017
* Remove Extra drupal_set_message Messages in mooc_helper_book_nav enhancement #1283
* do we still need open.fndtn.reveal for scroll-disable being applied? enhancement minor style guide / theme #1280
* Only show ulmus to those w. CIS admin permission‏ enhancement medium online / CIS Staff Experience #1025
* media feedback from usage User Experience #1258
* Side nav current tool highlight style guide / theme #1281
* materialize all the things hacktoberfest style guide / theme #1273
* Hexagon css AWESOME! #1278
* Tooltipped dropdown hacktoberfest style guide / theme #1275
* Heading color hacktoberfest style guide / theme #1277
* Escape key in Lightbox style applied to materialize style guide / theme #1238
* Clipboard.js namespace collision bug Instructor Experience media / elmsmedia Staff Experience #1085
* On duplicate check for internal links and rewrite them courses / mooc enhancement medium #849
* Convert Foundation grid classes to MaterializeCSS Developer Experience style guide / theme #1268
* Switch sticky footer to materialize version style guide / theme #1266
* H5P icons in Media system enhancement Instructor Experience media / elmsmedia Staff Experience #1252
* Studio: Convert submission cards to use material card style studio / cle #1250
* My Journal Labeling in Blogs blog / Editorial bug easy User Experience #1015
* Edit Section List - Options not appearing in display after save. scale / performance #1215
* capture admin/structure/types/manage/elmsmedia_image settings media / elmsmedia #1255
* Review pathcache scale / performance #1172
* Look into using views_content_cache to replace most views caching methods scale / performance #1216
* ELMSMedia enhancements media / elmsmedia #1248
* Refactor display mode tabs setting storage Developer Experience enhancement media / elmsmedia #1231
* admin pages w/ lmsless applied bug minor #1205
* Image Gifs don't animate when rendered through image viewmode bug #1220
* Include an internal shared settings file Developer Experience ELMSLN core enhancement infrastructure #1230
* Bulk upload for Images enhancement media / elmsmedia #1240
* hide accessibility button on front page bug minor #1170
* Ubuntu /tmp / temp files directory location bug infrastructure #1180
* ELMS editor // "templates" pulldown pops open new window instead bug Instructor Experience Staff Experience #1236
* Image circle style enhancement media / elmsmedia #1235
* Support parallax image style in media enhancement media / elmsmedia medium style guide / theme #1122
* Modifications to Cent7 setup routine infrastructure #1226
* Visually offset h5p questions / activities courses / mooc enhancement media / elmsmedia style guide / theme #1168
* Add exif / getid3 to media enhancement media / elmsmedia #1140
* Support for TED videos in media big data enhancement #1212
* a11y module feedback accessibility bug #1184
* Materialize CSS Components Available in 0.4.0 documentation #1187
* add Card display mode to media enhancement media / elmsmedia #1224
* Style top bar on mobile platforms style guide / theme #1213
* Make mistakes, learn from them. community #1229
* resize event clean up on safari / firefox bug ELMSLN core #1228
* drupal 7.50 upgrade drupal related easy #1010
* materialize actions needs message encoding bug minor #1223
* content not being added OOTB bug #1217
* Tincan module and .live function error bug Tincan / XAPI #1190
* rewrite tincan_xapi_bridge alter hook bug Tincan / XAPI #1207
* Course outliner script error bug courses / mooc #1195
* Nav order reversed in sidebar vs. breadcrumbs? bug courses / mooc #1206
* xAPI: Track vimeo / youtube / local videos enhancement Tincan / XAPI #1193
* EasyCDN Module Update (multiple versioning supported) #1203
* Verify offering updates are using pinprick API enhancement infrastructure online / CIS #1165
* Replace Outline Designer autosave with form save button discussion Instructor Experience Staff Experience User Experience #294
* Better pagination buttons on mobile courses / mooc style guide / theme #1201
* fix submit widget spacing after submission ELMSLN core style guide / theme #1169
* Set IMCE to be considered an admin path bug #1200
* read time stuff bug #1189

## ELMSLN 0.4.0, 2016-08-18 - Jarvis
This is our biggest enhancement yet. With massive improvements in stability, usability, accessibility and sets us on good ground going forward with futuristic capabilities. There are too manu feature additions to list but among them include automatic media / course time analytics generation, background http snaking call structures, ableplayer for the most accessible video experience anywhere, early work on quizing/testing, greater xAPI coverage with custom metadata and in-browser voice and keyboard command support.

* poster image should override what youtube delivers for poster #1177 an hour agolink missing on ckeditor link page #1179
* Add ability to see what child tags exist in Tag Scanner #1175
* increase default php upload size to 2gigs infrastructure #1174
* Add global advagg incremented via system upgrade bug minor style guide / theme #1171
* Media Player Accessibility / assessment accessibility hard media / elmsmedia medium student design project style guide / theme #96
* Snake enhancements ELMSLN core enhancement hard infrastructure online / CIS #914
* stop axing pathauto in services enhancement service #1161
* Better describe why we enable elmsln_core every time we run upgrades Developer Experience #1159
* Support Chosen AND materializeCSS select enhancement style guide / theme #1158
* Improve accessibility of MaterializeCSS select list accessibility #1138
* Students should not be able to critique their own submissions. studio / cle #1154
* Make section sync create inactive sections instantly (but marked inactive) online / CIS Staff Experience #1145
* Estimate time to take in material courses / mooc enhancement Learner Experience media / elmsmedia medium Tincan / XAPI #847
* Group assignments and critiques together on dashboard studio / cle #1127
* Critique individual submission incorrectly using random generated submission critique bug studio / cle #1153
* Page edit grouping courses / mooc Instructor Experience Staff Experience style guide / theme #1072
* Wrap iframe in div for intrinsic height rendering trick ELMSLN core enhancement medium style guide / theme #782
* Add Media Button To Media Site bug media / elmsmedia #1084
* Update Vagrant to use Rhel 7 Based OS and php-fpm easy future infrastructure scale / performance vagrant #736
* Switch install scripts to use php-fpm / FCGI Developer Experience development future infrastructure medium scale / performance vagrant #472
* Critique submission error bug studio / cle #1143
* Critiques not showing in dashboard. bug studio / cle #1116
* Create critique button studio / cle #1128
* Instructors aren't able to critique assignments that are marked "no-critique" Instructor Experience studio / cle #1115
* Method of creating link to non-randomized critique studio / cle #1137
* Look into modernizr cache clear issue accessibility bug media / elmsmedia #1108
* running updb via UI can cause a 500 error bug Developer Experience #1097
* Keep display mode settings w/ types in media bug minor #1129
* Clicking the peer review as student throws error. bug studio / cle #1114
* Test and reroll this patch against a11y module development minor #1123
* Students should not be allowed to submit assignments passed their due dates. bug enhancement Pedagogy studio / cle #1113
* Add EasyCDN module enhancement #1118
* Parallax Scrolling enhancement media / elmsmedia #1104
* enable modernizr out of the box for elmsmedia bug easy media / elmsmedia #1103
* Audit content accessibility / usability accessibility courses / mooc #1073
* Support for Carousel enhancement style guide / theme #1111
* Materialize Authoring UX enhacnements courses / mooc enhancement #1107
* CIS offering submit validation error bug online / CIS #1106
* mooc_helper_book_nav Error in MOOC bug courses / mooc minor #1099
* EIM minor notice on form ajax submit bug #1105 10 CORE CONTRIBUTOR NOTICE: Branch management policy Developer Experience #1102
* Idea: Time-based hiding of nodes courses / mooc enhancement Pedagogy #1034
* update h5p to latest release media / elmsmedia Tincan / XAPI #1096
* xAPI tag for hypothesis for questions enhancement Pedagogy Tincan / XAPI #1056
* Interactive Breadcrumb runs off page with many menu items courses / mooc enhancement medium student design project #715
* Firefox/H5P Display adds extra whitespace bug media / elmsmedia minor style guide / theme #1079
* Video Viewmodes not autoplaying for Vimeo bug media / elmsmedia #1078
* Quick User View ELMSLN core enhancement #1081
* Make container to float full display items in media Developer Experience Instructor Experience media / elmsmedia Staff Experience #1091
* Card design component media / elmsmedia student design project style guide / theme User Experience #519
* Provide option for san-serif class application in wysiwyg courses / mooc easy enhancement #591
* Prevent FigureLabel title from wrapping text bug easy style guide / theme #441
* Quiz Builder/Tool - Adding Questions after a Preview assessment / quiz easy #1029
* Quiz Builder/Tool - Adding Images assessment / quiz easy enhancement #1027
* Session Expiration bug User Experience #920
* Bulleted Lists - New System bug style guide / theme #1092
* Image Attribution courses / mooc enhancement Instructor Experience medium question Staff Experience #639
* Clean up MOOC Navigation block bug courses / mooc enhancement medium student design project #526
* Implement puzzler once bug fixed courses / mooc enhancement #1053
* confusion when adding user groups manually bug studio / cle #1093
* view modes isn't displaying anything bug media / elmsmedia #1080
* entity iframe / rendered iframes don't allow full screen bug User Experience #1090
* icor_defaults bricks bug infrastructure major change #1087
* clean up the current view til we get our nice ones in place in CIS online / CIS #1050
* Control who can view CIS settings menu easy ELMSLN core Staff Experience #990
* review cachability of all views ELMSLN core scale / performance #1036
* Lots of white space til resize bug media / elmsmedia style guide / theme #1083
* warning from achievements module bug easy minor studio / cle #1022
* drop visual listing in CIS online / CIS #1049
* Materialize library not loading in Libraries API (master) bug minor #1075
* Officially implement MaterializeCSS enhancement style guide / theme User Experience #1065
* Drop Magellan for scrollspy.html style guide / theme #1068
* Fix FERPA protection checkbox bug style guide / theme #1067
* Directions for getting learning locker integrated documentation ready Tincan / XAPI #1008
* Create simple web-app that generates install command community enhancement #1037
* Document Crouton installer singularity / crazy stuff #839
* Optimize for Reader mode across platform enhancement #1058
* Fix phone home screen icons from elms to be the logo‏ enhancement minor style guide / theme #1057
* Add background to lightbox image to account for png's bug easy student design project style guide / theme #465
* Responsive tables courses / mooc easy enhancement style guide / theme #545
* Run automated upgrade routine and check development drupal related easy infrastructure #1032
* Low vision user needs additional contrast on forms accessibility enhancement #1045
* drupal 7.44 #1044
* CLE needs path for cle bug studio / cle #1042
* Failed to decode downloaded font bug style guide / theme #1039
* voicecommander error if JS loaded out of order bug #1043
* review entity_iframe_consumer / provider for consolidation Developer Experience ELMSLN core #1040
* replace entity_iframe drilldown with postMessage Developer Experience enhancement #975
* spacing after videos bug easy media / elmsmedia style guide / theme #170
* block robot crawlers by default infrastructure #1038
* Ubuntu 14 Install doesn't seem to work. bug drush related infrastructure #987
* Quiz Builder/Tool - Editing Questions assessment / quiz #1030
* Standard round of security updates drupal related major change security related #1024
* Quiz Builder/Tool - Marking Questions as Correct assessment / quiz bug #1028
* Figure Out Why Angular won't load in CDN Module bug development #991
* jquery added twice at least for admins bug scale / performance style guide / theme #1023
* CIS 2.x UX overhaul medium online / CIS Staff Experience student design project style guide / theme User Experience #405
* Materialize community Developer Experience style guide / theme #669
* drupal material themes to review easy style guide / theme #1014
* Add placeholder js library and see what it does? development #1018
* Do a video showing LRS + ELMSLN + xAPI community documentation easy #1013
* review hook_set_cis_service_data development easy ELMSLN core infrastructure #999
* Angular Local Integration Developer Experience easy minor #978
* quiz_ddlines patch was accepted, update drupal related easy #1012
* section list page bombs when there's a metric ton of sections to display stats about authority bug #1011
* Service "Almost there" in CIS bug documentation minor online / CIS #955
* voice in forms accessibility enhancement #983
* Robot to test upgrades to elmsln across the distros Developer Experience enhancement singularity / crazy stuff testing #60
* Grades planning assessment / rubrics authority #754
* Submit for Apereo Incubation AWESOME! community easy non-coder #917
* Field focus on all node edit forms bug minor #1005
* Voice close button issue bug minor #984
* Revisit XAPI statement structure enhancement Tincan / XAPI #946
* Possible Image Rendering Glitch bug courses / mooc minor style guide / theme #1001
* minor bugs to track down bug Developer Experience easy minor #931
* Vagrantfile install unsuccessful bug Developer Experience infrastructure #989
* Patch FastClick module to support versioning action plan bug Developer Experience minor #982
* Document patch made to h5p_tincan_bridge module Developer Experience documentation #974
* enhance jwerty library to provide api accessibility enhancement #981
* Keyboard command interface accessibility enhancement #980
* Voice command option interface accessibility enhancement #979
* Update Libraries Module enhancement #972
* Pages showing hidden in course outline bug medium minor #908
* use Window.postMessage to support for streamlined data operations enhancement hard infrastructure #954
* tweaks to install documentation documentation #973
* Debug h5p xapi ajax calls when loaded in iframe mode. bug #964
* Performance delivery enhancements ELMSLN core infrastructure medium scale / performance #680
* better class structure on interface buttons accessibility ELMSLN core enhancement style guide / theme #969
* shift keyboard shortcuts to not interfere with forms bug #970
* Disable VC in entity iframe mode bug #963
* Review render boost module easy hard infrastructure medium scale / performance #707
* Youtube Uploader libraries media / elmsmedia #928
* Voice performance enhancement #953
* Switch Sections Option Isn't Appearing bug courses / mooc minor #811

## ELMSLN 0.3.1, 2016-06-08 - Pittsburgh

This sees a lot of improvements around deployments that have lots of courses by implementing a new network call methodology known as snake. This positions us to be able to propagate data across the network and keep it in sync without fear of the system crippling itself while doing so. Users, Courses, Sections (and their associations) will all be kept in sync across authorities and services.

* Voice command support #684
* enhanced keyboard and voice support for scroll / other operations #951
* Fix weird tincan api h5p bridge module developer hook call #948
* course context across systems on forms #941
* document patch to quiz_ddlines #939
* Using 'Course Title' field across systems #934
* update to latest version of advagg #924
* Roll patches for pwa #923
* Support ubuntu 12 #911
* Auto grant roles / sync roster on addition of an offering in CIS #907
* Test php 7 #901
* Where to put the Quiz module #899
* Visuals for #500 #897
* Section sync in authorities #894
* Batch API / make sure cron doesn't time out when syncing course and section lists #893
* Ensure @stack.group calls work #891
* API call directional changes #886
* Uploading Template Image Throws `Undefined variable:` error in WYSIWYG Templates #885
* Auto grant roles to instructors and admins on authorities #837
* increase the number of advagg bundles in elmsln_advagg #836
* Add simplify #826
* Test patch from Replicate UI #823
* Add more tables / clean up templates available #785
* Method for adding new icon libraries #783
* Idea - Referencing/Remixing Book Outlines #763
* Link to Material Design Iconic fonts in #608
* Allow adding people in CPR that show up everywhere #617
* People dashboard #550
* Do the options below the WYSIWYG when editing content actually affect the content? #500
* Feature request - non time-based section control #234

## ELMSLN 0.3.0, 2016-05-11 - OV

This sees lots of documentation, bug, accessibility, performance and usability enhancements as well as improved functionality in all tools in the network. Notably Piwik, CIS 1.x and all legacy theme components have been removed (lots of cruft).

* ELMSLN tool Builder #26
* .ferpa-protect class for hiding protected work and properties in plain sight #286
* CIS Section Authority #298
* look into http://www.jsdelivr.com/ #329
* Refactor "elmsmedia_feature" #353
* Accessibility: high contrast mode #360
* Mode to help people w/ dyslexia #412
* LocalStorage bin across domain #413
* expand community list on elmsln.org #423
* Add keyboard shortcuts for navigating the course content outline #431
* Document shortcodes #503
* elmsln api call for updating a course name network wide #527
* stomp out admin theme mode for non-admin users #552
* on new course creation need to use elmsln api to spider authorities #553
* localstorage bin for rememberng input in fields #598
* Add unison plugin to vagrant documentation #602
* Difficult to get from "Media" to "Course" #658
* app.css change for "warnings" #702
* H5P/Learning Locker Bridge #705
* Submit patch related to fix in #687 back to lti_tool_provider #734
* add section syncing to authorities #744
* Play with Features Builder #749
* Remove piwik references from example config #750
* git book patch #752
* Authority data model #755
* Core 0.0.5 to 0.2 update - CIS 1.x homepage view/letter tabs #756
* Core 0.0.5 to 0.2 update - saving course settings #757
* Core 0.0.5 to 0.2 update - editing links in network list #758
* Core 0.0.5 to 0.2 update - search and replace #759
* Core 0.0.5 to 0.2 update - edit/share/more icons #760
* support drush concurrency in elmsln-upgrade-sites #762
* Images for Applying-shortcodes #765
* Adding Students to Offerings/Classes #766
* hovering token replacements show for non-admins #774
* test and enable a11y module #775
* FERPA Privacy mode not totally working in critique pages #776
* A11y simulation mode #781
* Guidelines For Reverse Committing #787
* Users other than admin unable to login #789
* Document drush usage in elmsln #790
* Compliance on assets #794
* Media: views for different roles #795
* Course List Sync from CIS to authorities #799
* A11y suggestions #800
* apply patch to httprl spider #804
* original domain #809
* Switch Sections Option Isn't Appearing #811
* Breadcrumb showing in iframe #813
* Redirect loop in mooc/book-homepage callback #814
* Fatal error when adding H5P nodes #815
* investigate studio / comply build issues #817
* Support user role in \_cis_connector_assemble_entity_list #821
* Create OG permissions / roles structure #824
* Auto refresh drush plugins for all user accounts we control on version upgrade #825
* Flexibility in vagrant script #831
* Make authority spider elmsln_api command #833
* Enable collapse.js available everywhere #834
* masquerade block rewriting needs to check for sections #841
* CIS 1.x - The farewell tour #843
* Look into ghostinspector #844
* Try out the mapfield innovation #845
* leafy should have shortcuts for restarting apache / mysql / php-fpm #852
* Authority section / course sync clean up #853
* notice message link text is same as message #854
* Fix blink of admin_menu on every page #855
* static cache course context #859
* Document course data model across the network #860
* make network'ed entity sync function #861
* Add variable to service instances that has UUID of course #862
* Both prevent and support recursive network calls #863
* upgrade.php notices #864
* Learn how to spell in elmsln_core.install #865
* imagine other calls as snake recursion #867
* More refined snake example #869
* clean up CIS forms #875
* Document distributed course data model #877
* CIS making new courses won't set machine name #879
* elmsmedia url alias default is off #880
* interact support sections #881
* Rebuild permissions on upgrades #882
* add pull-down.sh to developer mode in leafy #883
* pin prick caches on service creation #887
* account for compliance not having section connotation #888
* outline designer page icon breaks #889

## ELMSLN 0.2.1, 2016-03-17 - leprechaun

This fixed a critical upgrade path issue that would cause sites to be out of sync with how we intend them to be at a base level. Things like base-line permissions, menu links, and many other issues resolved in 0.2.0 would not be reflected (potentially) for those using ELMSLN before major versions.
Breaking changes (though should only affect patient 0, aka btopro):

* remove all but core themes #706
* Remove piwik from core #746
  Major changes:
* DR drup command needs a loop hole closed #523

Additional changes:

* add few forums to master #733
* Disable new-release notification for authorities during install #735
* Make sure discuss_helper is enabled OOTB #738
* Add OG field support to discuss #740
* ELMSLN js api #742
* Review features_builder as part of innovate #745

## ELMSLN 0.2.0, 2016-03-10 - Tipping point

* SSL Terminator #178
* Content Outline Icons Not Uniform Size on Mobile Device #184
* Active/Sync this Now Button #186
* Link to specific course section. #192
* Icons in ToC appear when they shouldn't #197
* More icons #198
* Missing icons #214
* Outline designer -- Book title override conflict #223
* Figure Label design component #308
* Side by Side critique interface #317
* create a flow chart of system hierarchy #347
* account / role granting needs a recipe #365
* Notifications #367
* Clean up current edit form #378
* Network fly out overrides #407
* MOOC Navigation "block" / callout #408
* rewrites to take someone to the right place if a service doesn't exist #419
* section name displays centered if really long #430
* Vagrant Installation Error - PDOException: SQLSTATE[HY000] #435
* Opening document links in new window (Media Shortcodes) #450
* Support debugging on roster syncs #461
* Re-export cis_sample_content #466
* Course Outline Button not Accessible in Profile Edit Tab #467
* Update Behat bash Script Settings #469
* On updating, instructional significance icons missing in ToC [Courses] #476
* Mobile clean up #483
* Notifications for editing a book not in their section #512
* Innovate tool coming back with Access Denied #518
* Submit shortcode doesn't display pop up properly #521
* language for innovate #535
* Document Setting up ELMSLN in vagrant up to making a course network #541
* Document Innovate #542
* Odd formatting on bulleted lists (in A&A 121) #544
* randomly select student to critique #548
* H5Ps in Media - support for tagging and associating with a course #549
* shift location of admin/config/system/course-settings #551
* Centos7 clean up #556
* Sanitize course name / title #557
* Hide Dont have access to message #559
* Prevent WHITE HEADINGS ON WHITE TEXT #560
* Clipboardjs not enabled by default in media system. #565
* entityCacheLoad warning on MOOC admin pages #566
* Add path to feeds_node_helper_export/% some where #570
* META: Move big picture stuff to roadmap in docs #572
* Support for adding external applications to course network #573
* How to create a new course (breif video) #574
* add support for vagrant-cachier #579
* Image style warning in people distro #583
* imagefield_focus included twice #584
* node_export throws warnings in travis #585
* Kill off passwords printing on drush SI calls #586
* Assessment engine info file clean up #592
* Generate an ELMSLN icon font #593
* AWS handsfree php-fpm #599
* entity iframe codes scraped into shortcode area #603
* ICOR JMOL conflict #604
* Comply / ECD and Inbox need permissions set #605
* Shortcode Collapsed fieldsets #607
* Allow custom groupings in Course network structure #609
* Sync Custom tools across course network #610
* pull-down.sh needs to clean up permissions #615
* tooltip #623
* Review Angular Foundation #624
* ICOR permissions #625
* Media Add menu doesn't show options #627
* Document how to install H5P libraries #628
* Book nav auto labeling settings not working. #635
* Course Outline Renaming Issue - Not all Changes Saving #637
* How to highlight text in WYSIWYG editor #638
* banners that are cross system set don't validate on save #641
* enable outline_child_pages in all mooc sites #646
* Outline Child pages permission #651
* media display tabs notice #653
* Scaling issue for images via shortcodes #655
* Copy to clipboard shortcodes not working #656
* Unable to see image attribution #659
* materialize / adminimal admin menu #660
* support for letsencrypt #661
* convert domains to use individual conf files #662
* CIS status page to report git version #664
* Icon in FA icon alter doesn't reflect til second save #672
* jQuery 1.11 regression in accessibility module #673
* upgrade to drupal core 7.43 #674
* Visability settings for online.elmsln.local type urls #676
* Document how to install H5P #677
* Render 2nd/3rd level Navigation menu hierarchies in Local sub-header #678
* cis_tokens not on by default #679
* PDO #686
* OG admin page complains about LTI consumer not being labeled #687
* CLE feedback #688
* Courses/CIS Sync if Course Section has special characters #689
* Page delivery optimizations #690
* git php integration into CIS #692
* elmsln api missing in studio #696
* document how to install via 1-liners #699
* questions: general infrastructure & deploying contrib modules #700
* If not in same outline the breadcrumb nav still loads #703
* Accessibility test dropdown will cause empty menus on non-node paths #704
* Missing icons #708
* need initial state support for discuss #709
* need initial state for studio #710
* need initial state for blog #711
* add markdown filter support if gitbook method used #712
* when creating new items focus cursor on title field #714
* commit epiceditor integration changes back to wysiwyg API #716
* add shortcut under network flyout #717
* Update cis lmsless permission label #718
* Add ELMSLN core permission for admin area #719
* Studio assignment type should be select or other field #721
* MOOC page type should accept any input format #722
* All new assignments should default to master section #723
* Move Assignment add to Add+ menu #724
* change submit widget (after submission) to provide more links: #725
* scroll / resize window on save in Submit widget #727
* Markdown format selected for everything if git_book_markdown enabled #728
* add support for iframes NOT resizing #729
* Editorial: Automatically associate exercises to master #731
* Editorial form UX clean up #730

## ELMSLN 0.1.0, 2016-02-18 - Birthday present

* Package Poll support into ICOR #540
* Odd formatting on bulleted lists (in A&A 121) #544
* H5Ps in Media - support for tagging and associating with a course #549
* shift location of admin/config/system/course-settings #551
* drop user progress from icor #555
* Centos7 clean up #556
* Sanitize course name / title #557
* some browsers block document.domain setting in iframes #558
* Hide Dont have access to message #559
* Our VM min spec is 2 gigs #563
* field_cis_active WD exception #564
* entityCacheLoad warning on MOOC admin pages #566
* Support for adding external applications to course network #573
* Cent7 #577
* add support for vagrant-cachier #579
* travis mad at hub #580
* Image style warning in people distro #583
* imagefield_focus included twice #584
* node_export throws warnings in travis #585
* Kill off passwords printing on drush SI calls #586
* upgrade drupal core to 7.42 #590
* Assessment engine info file clean up #592
* Document steps after one-line installers #594
* ICOR JMOL conflict #604
* Comply / ECD and Inbox need permissions set #605
* pull-down.sh needs to clean up permissions #615
* Review and enhance Roadmap in docs #618
* ICOR permissions #625
* Media Add menu doesn't show options #627
* Default permissions for Blog / Journal #630
* Auto generated aliases need to verify directories exist #633
* Theme breaks if not course outline is present #634
* Book nav auto labeling settings not working. #635
* Course Outline Renaming Issue - Not all Changes Saving #637
* banners that are cross system set don't validate on save #641
* Enable image upload from settings page #642
* MOOC extra options UX tweaking #645
* enable outline_child_pages in all mooc sites #646
* Discussion Board Text Entry #647

## ELMSLN 0.0.10, 2016-01-31 - DCNJ Sprint Weekend

* elmsln api theme settings #538
* System sync opt out #537
* Innovate/Idea Success Label #534
* Service Instance Auto-Reload #533
* Idea vs Innovate Labeling #532
* make sure httprl is installed prior to nonblocking bootstrap #531
* When cis_devel is in place disable non-blocking calls #530
* allow for httprl non-blocking elmsln api calls #528
* Let's look at icon solutions #525
* Instructor View #121
* Need clipboard icon #509
* Tool Selection and Strategy #514
* Clean up menus across network #404
* rewrites to take someone to the right place if a service doesn't exist #419
* Editing course names after creation? #501

## ELMSLN 0.0.9, 2016-01-29 - DCNJ Sprint Weekend

* Rerun 0.0.7 / 0.0.8 correctly this time

## ELMSLN 0.0.8, 2016-01-29 - DCNJ Sprint Weekend

* "Share" button not appearing on shareable content #524
* Core permissions #471
* No ability to create new blogs, journal entry, etc. #516
* Remove drupal_hash_base64 in drupal_static function #515
* Instructors should be able to hide content in outline designer #487
* Comply should auto add people to master #494
* No text editor in discussion threads/replies #517
* Auto add certain roles to master section #513
* Innovate tool coming back with Access Denied #518
* Document how H5P works / is installed #520
* Different Colors for H1 and H2 titles #488
* Auto add certain roles to master section #513

## ELMSLN 0.0.7, 2016-01-29 - DCNJ Sprint Weekend

* Drop multi-core option on Vagrant install #493
* elmsln.php #506
* Drupal book-specific search and replace #507
* Add a course #505
* document leafy commandline processor #504
* AJAX CORS Issue #499
* Outline Designer: increase readability of 'hidden' items text #498
* CIS links from cleaned up UX not what they should be #497

## ELMSLN 0.0.6, 2016-01-20

* new systems build inconsistently after 0.0.4 cron switch #491
* foundation access iframe throws notices #490
* roster not pulling on cron sync #489
* Simple Canvas frame embed support #486
* refactor cis_service_connection mooc elements into mooc_helper #452
* Refactor view lmsless cis link permission #473
* Course/MOOC - creating custom pages for top menus #481
* "Locked" permissions / ELMSLN Core features to build / export #229

## ELMSLN 0.0.5, 2016-01-11

* CLE redirects webservice calls against it if sections et to master to NO_SECTION #455
* Support debugging on roster syncs #461
* Section hidden on profile page unless they have section switch access #463
* Only cache responses when told to do so #462
* Section switcher needs to remove groups instructor/tas aren't in #448
* cis service connection transactional pages handling on master #445
* Additional performance changes to test #213
* add webservice role grouping #453
* CLE profile require applies to webservices, and shouldn't #454
* Issue Importing Book Outline (XML) #451

## ELMSLN 0.0.4, 2016-01-07

* Drush aliases for -all don't work on authorities #447
* EC2 installer doesn't need to pull from RHEL repo #432
* Ensure resource icon doesn't show up on authority systems #433
* Steps to Install php-fpm #436
* breadcrumb levels need to do a menu tree check #434
* "Vagrant" should be Varnish in performance docs #438
* course-help CIS generated page is empty #443
* Test Coverage Discussion #289
* ECD keeps adding cis_system types #439
* Breadcrumb items not sorted correctly #442
* Vagrant Installation Error - PDOException: SQLSTATE[HY000] #435

## ELMSLN 0.0.3, 2016-01-04

* fix bulleted list #422
* Add support for Resources button across top #424
* Permissions exported don't match in CIS #425
* Help and resource pages throw notices when nothing there #426
* page nav scroll on large screens #427
* Don't disable scroll for remixables #428
* Hide chevron, keep Outline text on mobile #429
* Added CHANGELOG.md (this file)
* Added MAINTAINERS.md

## ELMSLN 0.0.2, 2015-12-22

* notice; we are on minor versions! #417

## ELMSLN 0.0.1, 2015-12-22

* Years of hardwork, sleepless nights, and driving desire to change the world. This isn't the end, it's the beginning of something new. https://github.com/elmsln/elmsln/issues?q=is%3Aissue+is%3Aclosed
