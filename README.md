![ELMSLN](https://raw.githubusercontent.com/elmsln/elmsln/master/docs/assets/snowflake-with-text.png "ELMS Learning Network")

ELMSLN
==============
ELMS Learning Network (ELMSLN) is an open source educational technology platform for building and sustaining innovation in course technologies. It accomplishes this by taking a Suite of Tools approach to learning design, allowing several systems to make up the different aspects of a course learning environment.  Each course effectively forms a network of technologies (hence the name) which can then be better tailored to each individual course's needs.

Learn more about ELMSLN @ [elmsln.org](https://www.elmsln.org/)


| Version | PHP | Includes | Status |
| ------- | --- | -------- | ------ |
[1.0.4](https://github.com/elmsln/elmsln/archive/1.0.4.zip)  | 7.2+ | LitElement 2.x.x, Drupal 7.x, HAXcms 1.x.x | [![Build Status](https://travis-ci.org/elmsln/elmsln.svg?branch=master)](https://travis-ci.org/elmsln/elmsln)

Contributing
==============
You can learn more about contributing to ELMS:LN in our [CONTRIBUTING.md](CONTRIBUTING.md) guide. Vagrant is the fastest way to get up and running quickly. See the [Vagrant installation documentation](https://btopro.gitbooks.io/elmsln-documentation/content/developer-guide/vagrant-setup.html) on how to get up and running now! elmsln.org also has some sponsored demos of the technology but the real deal is always best!

### Ubuntu notice
Until update channels are updated to 2.2.4 please use this to get Vagrant working in Ubuntu 18+
```
wget -c https://releases.hashicorp.com/vagrant/2.2.4/vagrant_2.2.4_x86_64.deb
sudo dpkg -i vagrant_2.2.4_x86_64.deb
```

Issues
==============
If you notice an issue or have a question please file it in our [issue queue](https://github.com/elmsln/elmsln/issues).

Documentation
==============
See the Docs for questions and documentation either on our [docs site](https://btopro.gitbooks.io/elmsln-documentation/content/) or [API site](http://api.elmsln.org).

Vision and Governance
==============
See https://github.com/elmsln/elmsln/blob/master/GOVERNANCE.md for our ELMS:LN Vision and Governance statement.

Code of Conduct
==============
See https://github.com/elmsln/elmsln/blob/master/CONFLICT_RESOLUTION.md for our Conflict Resolution guide.
See https://github.com/elmsln/elmsln/blob/master/CODE_OF_CONDUCT.md for our ELMS:LN code of conduct.

How can I get more involved?
==============
There are many ways you can get involved in helping build ELMSLN; not all of which are technical in nature. The easiest way is to click the issues button in this repository. Submit feedback, help, questions, pedagogy, ideas, fan-art anything that helps us further our mission! All help and outreach is welcome and responded to.

Test, ask, jump in on the issue queues on github, drupal.org, twitter, email, phone, meet ups, drupalcamps, edtech events, our offices, coffee shops, or anywhere else that you can find pieces that will help build upon this work. We are here to make the future awesome together.

LICENSE
==============
ELMSLN is a collection of many, many projects, all individually licensed, all open source. The myriad of License files is why this section is added to avoid confusion. If you have a licensing question or concern please raise it in the issue queue.

- The ELMS:LN top level repository is GPLv3, though most of the underlying code pulled in is not GPLv3. V3 enabled the greatest level of compatibility with our downstream repositories
- Drupal core and contributed modules / themes are GPLv2 due to licensing requirements of the drupal.org community.
- GravCMS is MIT licensed
- Polymer core is BSD 3 clause
- The majority of included Webcomponents (especially those from the [LRNWebComponents](https://github.com/LRNWebComponents) repos) are Apache 2.0
- For other included libraries see their respective LICENSE.txt / LICENSE.md file included local to those projects and libraries.
