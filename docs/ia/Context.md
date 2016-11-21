## Conceptual context

### Learner Context
- I am a _student_, I have _courses_ I am taking via enrollment in _sections_
- I login by accessing _online_, because this is my online experience at organization
- I am shown a dashboard of all the _courses_ I am taking
- I am shown relevant messages (inbox) and data (from LRS) that are pervasive across _courses_
- I can select a course, which shows me a more course specific dashboard / progression
- I can select to continue where I left off, dropping me into the course experience

### Assuming the top is an organization hosting the technology; Organization Context
- 1 organization is powered by 1 application suite (which bc its a fractal could be any number of deploys but we'll express as 1 here)
- An organization uses elmsln for courses and operational management of their organization scope:
  - Courses can be grouped into programs (reference only, not required)
  - Courses can belong to departments (reference only, not required)
  - Departments can have related programs (reference only, not required)
- An organization powers their processes from the Course information system (CIS). This is their online world, hence is accessed at the "online" domain. It is the starting point for everything and controls their universe of elms.
- Courses are created in the CIS
  - CIS is in charge of ensuring the course and applications required for powering it know about this new course as well as create spaces for the course to exist
- A course is a network of solutions to form a cohesive experience for all members of the system
- Course access is managed through the CIS via creation of sections and offerings
  - Offerings help to group the point in time a course is going to run (ex: Fall next year)
    - Offerings are mostly a placeholder / organizational element to help with sorting / filtering later
  - Sections are part of offerings. A section is a unique running of the course, potentially when there is a different audience, instructor, delivery location, etc. where it makes sense to make new sections
  - Sections are required for setting up access to courses.
- The bulk of the course user experience pattern take place on service systems, meaning they are a service of the course _and can be uniquely configured without impacting other course services or other courses_. This functionality is unique to elms in that everything is basically a play space / sandbox if it wants to be (though 95% of the time they will remain uniform)
- Faculty and staff will create and manage courses primarily through the use of Authorities. Authorities are things like CIS, Media, and Assessment which are not afforded the same flexibility as course services. This is because once a rubric tool exists, it is the primary rubric tool for all. Experimentation from there happens in a new space or in a _rubric+1_ name scenario.

### Me
- Profile / dashboard
- Quick links to important items (help, etc)
- courses I have access to (allowing me to switch)

### Course Network
- Profile / dashboard (in this course)
- Quick links to important items (syllabus, help, etc)
- Other applications in this course (potentially)

### Administrative systems (staff / faculty)
- Other applications that help power this ecosystem

Visually building out from the user (instead of the network) then implies that the learner is the center of the universe and everything is affixed to them.