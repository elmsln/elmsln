## Summary

The network is made up of several Drupal distributions that use RESTful communications and single sign-on technology. ELMSLN follows a bitcoin style distributed hubs and authorities topology. This allows maximal flexibility to those developing both the course and the technologies powering the course. You can get a sense of some of these by looking in the [diagrams](https://github.com/btopro/elmsln/tree/master/docs/diagrams) section of the included docs.

## What is the CIS?
CIS stands for Course Information System and is located at online.elmsln . It is the data hub and bridge between legacy systems and the rest of the network. CIS keeps track of all the data that makes online courses possible. This includes, courses, offerings, sections, instructors, standard language and everything logistically focused in the delivery of online programs.

By abstracting the logistics from the course itself, we can then use this information to power the tools used by a course. This is a fundamentally different approach from traditional LMS solutions which are logistics centric where the course is the point in time it is happening (and then materials are added into it).

## What is a Course then?
A Course, in general, is the collection of data and services that we as learning designers stitch together to form a story of the topics we want learners to gain insight into. We don't often think of it that way since we typically pull solutions from a mix of internet sources, off the shelf products, textbooks, and custom materials; but we are building all of these; remixing as it were to form a course.

In ELMSLN, the same is true, its just that a lot of the tools you can use are provided (or being developed) together. A Course is first established in CIS. This doesn't create anything other then a place holder to relate information to.  After that, you need to start creating services that are implemented by that course. This can either by done under the services tab on the course in CIS or by using the System setup form.

Almost all courses will use the Course Outline service (courses.elmsln) as this is the course scaffolding system which allows you to create outlines of content to present to students. There are many other services in active development including studio.elmsln, blog.elmsln, discuss.elmsln and interact.elmsln. These services each provide a dedicated capability in your course and can have their data routed back into other services used in the make up of a course.