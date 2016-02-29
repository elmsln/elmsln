## System
The information architecture of ELMSLN is unique to most systems that exist (at the time of this writing). We treat the application as more of an operating system, a system of systems. There are sub-systems and many many dedicated functionality systems. We have systems that can produce other systems, systems that manage compliance of some systems, systems to manage people, systems to manage courses.

We provide all these systems so that the network as a whole is more flexible and scalable then anything else. While it can operate as a whole in one location, elmsln never assumes that it is physically located on the same server. When a system needs data, it issues a web server based call (either RESTful or back-end API) to the location data exists. Even if it's on the same server, it still uses the remote call methodology. This ensures that you can scale in traditional methods (throw memory, processors, storage at it) as well as via more advanced methods (load balancer, reverse proxy).

Because of the nature of the system, these techniques could be applied to any aspect of the system. Courses and Studio could run on separate load balanced setups from CIS and compliance which could be separate from media and interact which do asset delivery. This lets you mix and remix to your needs whether they be scale, privacy, or policy in nature.

## Visualizing the network
This image depicts the network as a series of connected systems with lines for data flow and what can get information from what. Everything in the end is RESTful and has a backend low-bootstrap API to allow for faster "job" style command execution that may not be object centric.

![ELMSLN](https://raw.githubusercontent.com/elmsln/elmsln/master/docs/diagrams/ELMSLN-system-connections.jpg "ELMS Learning Network visual")