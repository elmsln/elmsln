These are some systems and functionalities on the long term roadmap with the Core development team. These have come out of community conversations as well as whiteboard sessions with the team. It is subject to change but can help inform the scope of each tool and why something lives where it does. They are also loosely in order based on how much work has been put into them and what we'd consider each at this time.

The Core Architecture: ELMSLN is a package deployment intended to run on its own server. There are also future plans for running "fractal networks" which span servers. The core architecture has been running relatively unmodified since Fall 2013 and is considered very stable.Status: **Production**

##Versions
These are not hard version releases but are a general idea of what's to be expected when. 0.1.x is the biggest deal for us as a development team because it means the product is something approachable that people can ask questions / issues against. There's enough capability for people to start to envision the rest of what is to come. Our timelines are largely dictated by the amount of developer hours that contributors can lend to different parts of the project while accomplishing their day to day job. This is a platform built in the trenches every day based on real needs from real faculty, students and instructional designers. As a result, we focus on things in an order that may not always make sense to someone passing through.

0.1.x - infrastructure in place that is upgradable and will start to formally support upgrade paths (though we have informally since 2014). This means..
- [x] things work, courses can be produced with the idea that they will be sustainable and there is an upgrade procedure going forward for under the hood changes (we need a bash based upgrade hook).
- [x] Fractal installs (multiple elmsln deployments supporting one overall structure) are possible from a web-services perspective but we still havent automated the process yet.
- [x] All authorities and services that are initially planned at least have place-holders.
- [x] Need to support hands-free installers including Ubuntu/Debian and CentOS/RedHat 6/7.
- [x] Have a functioning, self-rebuilding demo
- [x] Bakery / Single Sign-on built in

0.2.x - usability improvements, especially around CIS / system wide management. Improved documentation / tutorials via a demo site showcasing the capabilities of the system. Any and all improvements to all tools in the network. Focus on accessibility, usability and template-ability of remixables (anything being embedded in anything) as well as a lot of work towards HAX (our new authoring system). Usability and stability improvements as well. Major advancements in comply, studio , icor and media distributions.

0.3.x - Outline Designer 3.x enhancements; more rapid course creation with a viable end product from a single screen. User experience and additional overall network enhancements throughout. Increased test coverage both in Simpletest and Behat. Gradebook and next generation conversation around the feedback recieved is added.

0.4.x - Anything that is lower priotity then 0.3.x currently gets pushed off to 0.4.x.

...

1.0.0 - The system has all the capabilities that people think of in an LMS but without being one by any means due to the architectural superiority of the platform.

**Course content outline (mooc / courses)** - Instructional outline, pacing of the course and textbook replacement type of material.
**Status**: Has been in Production for years, minor UX tweaks to get it to the goal line. **Production** phase.

**Course Information System (cis / online)** - Hub to route all data through to power the learning experience. This has a lot of data that a traditional LMS structures everything around but CIS uses this to influence the course experience, not determine it. CIS has a 1.x (legacy) version that was for public / front facing sites. This scope has shifted as 2.x of CIS is a data / internal engine. Those that want a front facing site can utilize Publicize as it was built out of that hull.
**Status**: 2.x has been in production for awhile. The UX of this needs refined for sure but it's functional.**.

**Innovate (ulmus / innovate)** - We all have great ideas, but we don't all have the skillsets nessecary to bring them to life. Innovate seeks to change that by empowering users to build whatever they want in Drupal as a site builder. Innovate is built on something we call "ulmus" which is a meta-distribution / system, it's the base-line that ALL of our tools share in common. We use this as the branching point to make any new tool in the network, and so we didn't want to be the only ones able to do it. Anyone who can request a course space, can request an innovate space which will create a blank slate ELMSLN tool which has sections, will sync w/ the CIS like anything else, does all the crazy webservices, enables all the modules, makes the roles, etc. We've automated the boring so you can rapid prototype on top. Surprise us, surprise yourself, build the future. **Production**

**Media / Asset management (elmsmedia / media)** - An asset management system to allow for the easy uploading, cateloging, and embedding of assets in course content. This is built on an award winning methodology for keeping media separate and tightly integrated from content / the rest of the setup.
Status: This is still gaining functionality and Usability improvements as well as integrations currently only available in the 6.x version (3playmedia specifically). **Beta**.

**Interactive Course Object Repository (icor / interact)** - This is similar to an asset management system but think of a separate system for more complex, sticky types of assets. For example, a timeline. Not a flash / file that you upload to have embedded but that you actually assemble the timeline in ICOR by stitching together dates (content you create) and then are given an embed code you can put anywhere. Similar to ELMSMedia on the surface, but once you start making things in it it's clear that this is different. Some other things this does: Polls, a zip file that's unpacked for embedding for complex things that are interactions of their own. Anything that's overly specific and complex but still *sorta* media, goes here. **Beta**

**Studio (cle / studio)** - Place for students to submit images, media, links and be able to get feedback / critique / community. The studio is based on an award winning concept of open critique.
**Status**: This has a lot of functionality built out but needs a ton of usability work and testing. **Beta**

**Editorial / Journal / Blog (editorial / blog)** - A journaling / blog system. This could serve as a blog for the course for the student (or instructor) to make postings throughout the course, or as a way for the student to keep things in a more private journal area to reference / learn from for later.
**Status**: Gaining functionality actively as it will be alpha in Fall 2015. **Beta**

**Compliance (ecd / comply)** - Compliance is important for legal matters but shouldn't be hitting you in the face throughout the entire authoring experience. Compliance is a system dedicated to the process of quality, accessibility, authorizations and copyright. This helps provide a paper trail for the rationale behind giving a non-student access to a course (for example a staff member).
**Status**: Needs additional integrations / nightly routines and some streamlining of capabilities but the core functionality is in place. It can automatically issue access overrides to users at a system and course network level. **Alpha**

**Discussions (discuss / discuss)** - traditional forum conversations as well as embeddable conversations in the context of other systems. For example you could embed a discussion at the bottom of a page of content in the content system but it's actually taking place in the Discussion engine.
**Status**: Built on top of Harmony Core, this has a lot of raw capability and is stability but needs a usability audit. **Alpha**

**Inbox (inbox / home)** - Learner hub. Inbox, Calendar, course overview / dashboard, badges, XAPI learning paths (not statements), progression, analytics (displays, not data) all this is currently envisioned here in some capacity.
**Status**: Whiteboarded and written down, lots of conversations but no movement yet. Some of these capabilities DO live in a vendor deployment though the code still needs vetted for primary project inclusion. **Dev**

**Assessment (grades / assessment)** - The ability to assess work from anywhere (both in and out of network). In network this would make it easier to pull in the information to display but by detaching it from the rest of the systems we can not only throttle permissions / access controls, we can allow for association to things NOT in the system (like participation external to the system, new forms of interaction not currently supported, etc).
**Status**: Needs flushed out fully. There are assessment, rubric and gradebook work that's been undertaken (a lot of it actually) but it hasn't all come together yet.  **Placeholder only**

**Program Hub (hub / eph)** - This system allows you to produce complex program hubs to either market or unify courses in a program area. This is heavily influx but being developed for an online degree in which we'll want alumni of the program (in the future) to be able to login and talk to current students. It's the cross-section of communications, resources, course lists, advisors, faculty, student interest groups, alumni, everything related to a specific program. These program hubs will be able to be created from CIS when a program is produced (future functionality).
**Status** There is currently thought and design work going into this but not functionality is there **Placeholder only**

**Live Questions (lq / lq)** -- Live questions is a tool that can be used for synchronous classroom settings. Think of it as a backchannel that you'd project on a screen next to a teacher, or something TAs can use to more easily field questions. It's intended for classroom augmentation and making conversations easier to have in person by leveraging online without asking students to use social media platforms (which they hate being asked to do).
**Status** A pilot has run of this in a classroom with success though it has not yet been ported over to the LQ system that's found here. **Placeholder only**