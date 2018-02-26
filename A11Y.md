# Accessibility
Accessibility (A11y) is very important to the ELMS:LN community. Because the project was founded at Pennsylvania State University, we try and stick to the accessibility requirements the university has aligned with. At the time of this writing, the university requires we work toward the [WCAG 2.0 AA](https://www.w3.org/TR/WCAG20/) standard established by the W3C.

## Methods
If you have issues with any aspect of ELMS:LN associated with accessibility please report it in our [issue queue](https://github.com/elmsln/elmsln/issues). We use various tools and techniques to ensure compliance including (but not limited to):
- Automated testing for build quality
- Aligning with Polymer / Google produced web components (heavily vetted for accessibility)
- Using the WAVE browser plugin to check accessibility while building
- QUAL API, a javascript library, is built into our text editor to help authors spot check their material
- Colorblindness simulations baked into the platform for people to check image contrast visually
- Alt text requirements for media submission and highly accessible tables
- Voice and keyboard based control systems baked into the platform
