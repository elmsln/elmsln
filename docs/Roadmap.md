These are some systems and functionalities on the long term roadmap with the Core development team. These have come out of community conversations as well as whiteboard sessions with the team. It is subject to change but can help inform the scope of each tool and why something lives where it does. They are also loosely in order based on how much work has been put into them and what we'd consider each at this time.

The Core Architecture: ELMSLN is a package deployment intended to run on its own server. There are also future plans for running "fractal networks" which span servers. The core architecture has been running relatively unmodified since Fall 2013 and is considered very stable. Status: **Production**

0.1.x - infrastructure in place that is upgradable and will start to formally support upgrade paths (though we have informally since 2014). This means things work, courses can be produced with the idea that they will be sustainable and there is an upgrade procedure going forward for under the hood changes (we need a bash based upgrade hook). Also need to support fractal installs (multiple elmsln deployments supporting one overall structure). All authorities and services that are initially planned at least have place-holders. Need to support a hands-free, automated self-upgrading deployment mode. This effectively means you aren't modifying from what's provided.

0.2.x - usability improvements, especially around CIS / system wide management. Improved documentation / tutorials via a demo site showcasing the capabilities of the system. Any and all improvements to all tools in the network. Focus on accessibility, usability and template-ability of remixables (anything being embedded in anything) as well as a lot of work towards HAX (our new authoring system). Usability and stability improvements as well. Major advancements in comply, studio and media distributions.

0.3.x - Outline Designer 3.x enhancements; more rapid course creation with a viable end product from a single screen. User experience and additional overall network enhancements throughout.

**Course content outline (mooc / courses)** - Instructional outline, pacing of the course and textbook replacement type of material.
**Status**: Has been in Production for years, minor UX tweaks to get it to the goal line. **Release Candidate** phase.

**Course Information System (cis / online)** - Hub to route all data through to power the learning experience. This has a lot of data that a traditional LMS structures everything around but CIS uses this to influence the course experience, not determine it. CIS has a 1.x (legacy) version that was for public / front facing sites. This scope has shifted as 2.x of CIS is a data / internal engine. Those that want a front facing site can utilize Publicize as it was built out of that hull.
**Status**: 1.x has been in production for some time, UX is currently in a full overhaul though data model underneath is largely the same as 1.x. **Late phase Beta**.

**Media / Asset management (elmsmedia / media)** - An asset management system to allow for the easy uploading, cateloging, and embedding of assets in course content. This is built on an award winning methodology for keeping media separate and tightly integrated from content / the rest of the setup.
Status: This is still gaining functionality and Usability improvements as well as integrations currently only available in the 6.x version (3playmedia specifically). This is in production at 2 groups though and will be coming into production usage at a 3rd in the Fall 2015. **Mid phase Beta**.

**Studio (cle / studio)** - Place for students to submit images, media, links and be able to get feedback / critique / community. The studio is based on an award winning concept of open critique.
**Status**: This has a lot of functionality built out but needs a ton of usability work and testing. **Alpha**

**Editorial / Journal / Blog (editorial / blog)** - A journaling / blog system. This could serve as a blog for the course for the student (or instructor) to make postings throughout the course, or as a way for the student to keep things in a more private journal area to reference / learn from for later.
**Status**: Gaining functionality actively as it will be alpha in Fall 2015. **Alpha**

**Discussions (discuss / discuss)** - traditional forum conversations as well as embeddable conversations in the context of other systems. For example you could embed a discussion at the bottom of a page of content in the content system but it's actually taking place in the Discussion engine.
**Status**: Built on top of Harmony Core, this has a lot of raw capability and is stability but needs a usability audit. **Alpha**

**Gradebook / Assessments / Rubrics** - The ability to assess work from anywhere (both in and out of network). In network this would make it easier to pull in the information to display but by detaching it from the rest of the systems we can not only throttle permissions / access controls, we can allow for association to things NOT in the system (like participation external to the system, new forms of interaction not currently supported, etc).
**Status**: Needs flushed out fully. There are assessment, rubric and gradebook work that's been undertaken but it hasn't graduated to a full distribution / tool in the network yet. **Dev**

**Compliance (ecd / comply)** - Compliance is important for legal matters but shouldn't be hitting you in the face throughout the entire authoring experience. Compliance is a system dedicated to the process of quality, accessibility, authorizations and copyright. This helps provide a paper trail for the rationale behind giving a non-student access to a course (for example a staff member).
**Status**: This has been planned out and discussed as to what it will do. It does currently spin up when ELMSLN is deployed but doesn't do anything at the moment (blank slate). **Dev**

**Inbox (inbox / home)** - Learner hub. Inbox, Calendar, course overview / dashboard, badges, XAPI learning paths (not statements), progression, analytics (displays, not data) all this is currently envisioned here in some capacity.
**Status**: Whiteboarded and written down, lots of conversations but no movement yet. Some of these capabilities DO live in a vendor deployment though the code still needs vetted for primary project inclusion. **Dev**

**Labs** - more information coming.
**Status**: Whiteboarding and conversations only at this time.** Pre Dev**