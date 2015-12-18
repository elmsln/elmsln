## Sections
Sections live across ELMSLN's many systems in a distributed fashion. They are seamlessly layered into the experience instead of front and center. Because of this, it can be confuing at times for administration / staff / faculty who have multiple sections within the same course. This will explain what a section is and how it operates both technically as well as how to tell what section you are in.

### What is a section (less technical)
A section is a group of students who get the same experience when traveling through ELMSLN. This allows you to associate users to a faculty member to the content outline they should recieve (in MOOC / content outline for example). Studio and other systems allow you to associate their key types per section as well so you could have different assignments in one section vs another.

### What is a "master" section?
There's a section created in all systems that have sections called Master (key is master). This allows you to start setting up a course before the logistics to run it have been established. A master implies the default configuration utilized to run a course when new sections are noticed. Whatever the configuration of the master section in a system, it will give it's settings to anything new created.

This *DOES NOT* replicate content / materials in any way, it's a reference. For example, there's 1 content outline for Art 200 and the master utilizes it. Now a new section is created cause we are teaching this course and it's told to point to the same content outline. Updating the content outline in "master" or the "new section" *will update the content everywhere*. If you want a new / branched / different content outline per section / offering of a course, you'll have to create one (or automate the approach).

By only utilizing one copy at the time of delivery, it simplifies how many editions (and wasted space keeping those editions) exist across all systems.

### What is a section (technically)
A Section is an organic group in the majority of systems in ELMSLN, the key exception being CIS which utilizes a series of field_collections to accomplish this task. Sections are produced based on data entered in CIS. A section in CIS is part of an offering, which is part of a course. This allows multiple sections to be added to the same offering (like Fall 2015). Sections are produced downstream based on a unique key value entered into CIS. Sections in CIS support multiple Key values, which allows for grouping the logistics of an experience together.

For example, sections abc-123 and abc-567 are two groups of students but have the same instructor. In CIS, these values are associated with an offering of the course to indicate they have the same syllabus, welcome letter, and use the same resources. When this is synced over to MOOC / Studio / other systems, it will create two organic groups, one per unique item. This keeps the students separated as far as working groups, but allows them to have the same materials from a logistical stand point. You could also create a section / offering combo per unique key, there's nothing wrong with that either. We just allow for flexibility in this area because of the complexities of delivering courses at a large institution with multiple campuses / faculty.

Some systems will use this OG for permissions purposes and others just to gain and revoke access to content. This is the flexibility of the design, allowing parts of course experiences to be heavily permissions moderated while others can be much more open.