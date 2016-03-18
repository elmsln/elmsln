ELMSLN 0.2.1, 2016-03-17 - leprechaun
This fixed a critical upgrade path issue that would cause sites to be out of sync with how we intend them to be at a base level. Things like base-line permissions, menu links, and many other issues resolved in 0.2.0 would not be reflected (potentially) for those using ELMSLN before major versions.
Breaking changes (though should only affect patient 0, aka btopro):
- remove all but core themes #706
- Remove piwik from core #746
Major changes:
- DR drup command needs a loop hole closed #523
Additional changes:
- add few forums to master #733
- Disable new-release notification for authorities during install #735
- Make sure discuss_helper is enabled OOTB #738
- Add OG field support to discuss #740
- ELMSLN js api #742
- Review features_builder as part of innovate #745

ELMSLN 0.2.0, 2016-03-10 - Tipping point
------------------------
- SSL Terminator #178
- Content Outline Icons Not Uniform Size on Mobile Device #184
- Active/Sync this Now Button #186
- Link to specific course section. #192
- Icons in ToC appear when they shouldn't #197
- More icons #198
- Missing icons #214
- Outline designer -- Book title override conflict #223
- Figure Label design component #308
- Side by Side critique interface #317
- create a flow chart of system hierarchy #347
- account / role granting needs a recipe #365
- Notifications #367
- Clean up current edit form #378
- Network fly out overrides #407
- MOOC Navigation "block" / callout #408
- rewrites to take someone to the right place if a service doesn't exist #419
- section name displays centered if really long #430
- Vagrant Installation Error - PDOException: SQLSTATE[HY000] #435
- Opening document links in new window (Media Shortcodes) #450
- Support debugging on roster syncs #461
- Re-export cis_sample_content #466
- Course Outline Button not Accessible in Profile Edit Tab #467
- Update Behat bash Script Settings #469
- On updating, instructional significance icons missing in ToC [Courses] #476
- Mobile clean up #483
- Notifications for editing a book not in their section #512
- Innovate tool coming back with Access Denied #518
- Submit shortcode doesn't display pop up properly #521
- language for innovate #535
- Document Setting up ELMSLN in vagrant up to making a course network #541
- Document Innovate #542
- Odd formatting on bulleted lists (in A&A 121) #544
- randomly select student to critique #548
- H5Ps in Media - support for tagging and associating with a course #549
- shift location of admin/config/system/course-settings #551
- Centos7 clean up #556
- Sanitize course name / title #557
- Hide Dont have access to message #559
- Prevent WHITE HEADINGS ON WHITE TEXT #560
- Clipboardjs not enabled by default in media system. #565
- entityCacheLoad warning on MOOC admin pages #566
- Add path to feeds_node_helper_export/% some where #570
- META: Move big picture stuff to roadmap in docs #572
- Support for adding external applications to course network #573
- How to create a new course (breif video) #574
- add support for vagrant-cachier #579
- Image style warning in people distro #583
- imagefield_focus included twice #584
- node_export throws warnings in travis #585
- Kill off passwords printing on drush SI calls #586
- Assessment engine info file clean up #592
- Generate an ELMSLN icon font #593
- AWS handsfree php-fpm #599
- entity iframe codes scraped into shortcode area #603
- ICOR JMOL conflict #604
- Comply / ECD and Inbox need permissions set #605
- Shortcode Collapsed fieldsets #607
- Allow custom groupings in Course network structure #609
- Sync Custom tools across course network #610
- pull-down.sh needs to clean up permissions #615
- tooltip #623
- Review Angular Foundation #624
- ICOR permissions #625
- Media Add menu doesn't show options #627
- Document how to install H5P libraries #628
- Book nav auto labeling settings not working. #635
- Course Outline Renaming Issue - Not all Changes Saving #637
- How to highlight text in WYSIWYG editor #638
- banners that are cross system set don't validate on save #641
- enable outline_child_pages in all mooc sites #646
- Outline Child pages permission #651
- media display tabs notice #653
- Scaling issue for images via shortcodes #655
- Copy to clipboard shortcodes not working #656
- Unable to see image attribution #659
- materialize / adminimal admin menu #660
- support for letsencrypt #661
- convert domains to use individual conf files #662
- CIS status page to report git version #664
- Icon in FA icon alter doesn't reflect til second save #672
- jQuery 1.11 regression in accessibility module #673
- upgrade to drupal core 7.43 #674
- Visability settings for online.elmsln.local type urls #676
- Document how to install H5P #677
- Render 2nd/3rd level Navigation menu hierarchies in Local sub-header #678
- cis_tokens not on by default #679
- PDO #686
- OG admin page complains about LTI consumer not being labeled #687
- CLE feedback #688
- Courses/CIS Sync if Course Section has special characters #689
- Page delivery optimizations #690
- git php integration into CIS #692
- elmsln api missing in studio #696
- document how to install via 1-liners #699
- questions: general infrastructure & deploying contrib modules #700
- If not in same outline the breadcrumb nav still loads #703
- Accessibility test dropdown will cause empty menus on non-node paths #704
- Missing icons #708
- need initial state support for discuss #709
- need initial state for studio #710
- need initial state for blog #711
- add markdown filter support if gitbook method used #712
- when creating new items focus cursor on title field #714
- commit epiceditor integration changes back to wysiwyg API #716
- add shortcut under network flyout #717
- Update cis lmsless permission label #718
- Add ELMSLN core permission for admin area #719
- Studio assignment type should be select or other field #721
- MOOC page type should accept any input format #722
- All new assignments should default to master section #723
- Move Assignment add to Add+ menu #724
- change submit widget (after submission) to provide more links: #725
- scroll / resize window on save in Submit widget #727
- Markdown format selected for everything if git_book_markdown enabled #728
- add support for iframes NOT resizing #729
- Editorial: Automatically associate exercises to master #731
- Editorial form UX clean up #730

ELMSLN 0.1.0, 2016-02-18 - Birthday present
------------------------
- Package Poll support into ICOR #540
- Odd formatting on bulleted lists (in A&A 121) #544
- H5Ps in Media - support for tagging and associating with a course #549
- shift location of admin/config/system/course-settings #551
- drop user progress from icor #555
- Centos7 clean up #556
- Sanitize course name / title #557
- some browsers block document.domain setting in iframes #558
- Hide Dont have access to message #559
- Our VM min spec is 2 gigs #563
- field_cis_active WD exception #564
- entityCacheLoad warning on MOOC admin pages #566
- Support for adding external applications to course network #573
- Cent7 #577
- add support for vagrant-cachier #579
- travis mad at hub #580
- Image style warning in people distro #583
- imagefield_focus included twice #584
- node_export throws warnings in travis #585
- Kill off passwords printing on drush SI calls #586
- upgrade drupal core to 7.42 #590
- Assessment engine info file clean up #592
- Document steps after one-line installers #594
- ICOR JMOL conflict #604
- Comply / ECD and Inbox need permissions set #605
- pull-down.sh needs to clean up permissions #615
- Review and enhance Roadmap in docs #618
- ICOR permissions #625
- Media Add menu doesn't show options #627
- Default permissions for Blog / Journal #630
- Auto generated aliases need to verify directories exist #633
- Theme breaks if not course outline is present #634
- Book nav auto labeling settings not working. #635
- Course Outline Renaming Issue - Not all Changes Saving #637
- banners that are cross system set don't validate on save #641
- Enable image upload from settings page #642
- MOOC extra options UX tweaking #645
- enable outline_child_pages in all mooc sites #646
- Discussion Board Text Entry #647

ELMSLN 0.0.10, 2016-01-31 - DCNJ Sprint Weekend
------------------------
- elmsln api theme settings #538
- System sync opt out #537
- Innovate/Idea Success Label #534
- Service Instance Auto-Reload #533
- Idea vs Innovate Labeling #532
- make sure httprl is installed prior to nonblocking bootstrap #531
- When cis_devel is in place disable non-blocking calls #530
- allow for httprl non-blocking elmsln api calls #528
- Let's look at icon solutions #525
- Instructor View #121
- Need clipboard icon #509
- Tool Selection and Strategy #514
- Clean up menus across network #404
- rewrites to take someone to the right place if a service doesn't exist #419
- Editing course names after creation? #501

ELMSLN 0.0.9, 2016-01-29 - DCNJ Sprint Weekend
------------------------
- Rerun 0.0.7 / 0.0.8 correctly this time

ELMSLN 0.0.8, 2016-01-29 - DCNJ Sprint Weekend
------------------------
- "Share" button not appearing on shareable content #524
- Core permissions #471
- No ability to create new blogs, journal entry, etc. #516
- Remove drupal_hash_base64 in drupal_static function #515
- Instructors should be able to hide content in outline designer #487
- Comply should auto add people to master #494
- No text editor in discussion threads/replies #517
- Auto add certain roles to master section #513
- Innovate tool coming back with Access Denied #518
- Document how H5P works / is installed #520
- Different Colors for H1 and H2 titles #488
- Auto add certain roles to master section #513

ELMSLN 0.0.7, 2016-01-29 - DCNJ Sprint Weekend
------------------------
- Drop multi-core option on Vagrant install #493
- elmsln.php #506
- Drupal book-specific search and replace #507
- Add a course #505
- document leafy commandline processor #504
- AJAX CORS Issue #499
- Outline Designer: increase readability of 'hidden' items text #498
- CIS links from cleaned up UX not what they should be #497

ELMSLN 0.0.6, 2016-01-20
------------------------
- new systems build inconsistently after 0.0.4 cron switch #491
- foundation access iframe throws notices #490
- roster not pulling on cron sync #489
- Simple Canvas frame embed support #486
- refactor cis_service_connection mooc elements into mooc_helper #452
- Refactor view lmsless cis link permission #473
- Course/MOOC - creating custom pages for top menus #481
- "Locked" permissions / ELMSLN Core features to build / export #229

ELMSLN 0.0.5, 2016-01-11
------------------------
- CLE redirects webservice calls against it if sections et to master to NO_SECTION #455
- Support debugging on roster syncs #461
- Section hidden on profile page unless they have section switch access #463
- Only cache responses when told to do so #462
- Section switcher needs to remove groups instructor/tas aren't in #448
- cis service connection transactional pages handling on master #445
- Additional performance changes to test #213
- add webservice role grouping #453
- CLE profile require applies to webservices, and shouldn't #454
- Issue Importing Book Outline (XML) #451

ELMSLN 0.0.4, 2016-01-07
------------------------
- Drush aliases for -all don't work on authorities #447
- EC2 installer doesn't need to pull from RHEL repo #432
- Ensure resource icon doesn't show up on authority systems #433
- Steps to Install php-fpm #436
- breadcrumb levels need to do a menu tree check #434
- "Vagrant" should be Varnish in performance docs #438
- course-help CIS generated page is empty #443
- Test Coverage Discussion #289
- ECD keeps adding cis_system types #439
- Breadcrumb items not sorted correctly #442
- Vagrant Installation Error - PDOException: SQLSTATE[HY000] #435

ELMSLN 0.0.3, 2016-01-04
------------------------
- fix bulleted list #422
- Add support for Resources button across top #424
- Permissions exported don't match in CIS #425
- Help and resource pages throw notices when nothing there #426
- page nav scroll on large screens #427
- Don't disable scroll for remixables #428
- Hide chevron, keep Outline text on mobile #429
- Added CHANGELOG.md (this file)
- Added MAINTAINERS.md

ELMSLN 0.0.2, 2015-12-22
------------------------
- notice; we are on minor versions! #417

ELMSLN 0.0.1, 2015-12-22
------------------------
- Years of hardwork, sleepless nights, and driving desire to change the world. This isn't the end, it's the begining of something new. https://github.com/elmsln/elmsln/issues?q=is%3Aissue+is%3Aclosed
