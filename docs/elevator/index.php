<!DOCTYPE html>
<html>

	<head>


<link rel="stylesheet" href="css/master.css" />
<link href='http://fonts.googleapis.com/css?family=Prociono' rel='stylesheet' type='text/css'>
<noscript>
<link rel="stylesheet" href="css/mobile.min.css" />
</noscript>
<script>

//logic:
//if changing to a larger layout (){
//remove current animation classes from container div and grids divs
//add the animation-now class to the container div
//add the .animation-now class to the grids
//}
//if changing to a smaller lauout (){
//remove current animation classes from container div and grids divs
//add the animation-now class to the container div
//add the .animation-now class to the grids
//}
// Called by Adapt.js
function myCallback(i, width) {
  // Alias HTML tag.
  var html = document.documentElement;

  // Find all instances of range_NUMBER and kill 'em.
  html.className = html.className.replace(/(\s+)?range_\d/g, '');

  // Check for valid range.
  if (i > -1) {
    // Add class="range_NUMBER"
    html.className += ' range_' + i;
  }

  // Note: Not making use of width here, but I'm sure
  // you could think of an interesting way to use it.
}
// Edit to suit your needs.
var ADAPT_CONFIG = {
  // Where is your CSS?
  path: 'css/',

  // false = Only run once, when page first loads.
  // true = Change on window resize and page tilt.
  dynamic: true,

  // First range entry is the minimum.
  // Last range entry is the maximum.
  // Separate ranges by "to" keyword.
  range: [
    '0px    to 480px  = mobile.css',
	'481px  to 760px  = 460.css',
    '761px  to 980px  = 720.css',
    '981px  to 1280px = 960.css',
    '1281px = 1200.css',/*
    '1601px to 1940px = 1560.css',
    '1941px to 2540px = 1920.css',
    '2540px           = 2520.css'*/
  ]
};
</script>
<script src="js/adapt.min.js"></script>
	</head>

<body>
<img src="images/elms_logo_03.png" class='preload'/>

<div class="container container_12 animate">

<!-- content set 460 -->
 <div class='grid_5 logo visibility_460 animate'><p><img src="images/elms_logo_02.png" alt="ELMS Logo"/></p></div>
  <div class='grid_7 visibility_460 text_block animate'>
    <h2 class='title'>ELMS</h2></div>
    <div class='grid_6 nav_link animate align_center visibility_460'><p class='highlight'><a class='highlight' href="http://drupal.org/project/cis">Download</a></p></div>
    <div class='grid_7 visibility_460 text_block animate'><p>The E-Learning Management System (ELMS) is a package built in Drupal that allows you to create and manage an online courses from a simple user interface.</p>
    </div>

    <div class='clear'>&nbsp;</div>
    <div class='grid_3 nav_link animate align_center visibility_460'><p><a href="#about">About</a></p></div>
    <div class='grid_3 nav_link animate align_center visibility_460'><p><a href="#features">Features</a></p></div>
    <div class='grid_3 nav_link animate align_center visibility_460'><p><a href="#community">Community</a></p></div>
    <div class='grid_3 nav_link animate align_center visibility_460'><p><a href="/blog">Blog</a></p></div>

    <div class='grid_12 space-out visibility_460 animate'>
    <h2 id='about'>About</h2>
    <p>Built on top of the Drupal Content Management Framework, ELMS provides carefully crafted functionality that simplifies course creation, management, and distribution.  Unlike other tools, it has been developed by instructional designers, for instructionally focused course content authoring.  Many projects have come out of the ELMS Initiative since 2008 both for education as well as the Drupal community including <a href="http://drupal.org/project/cis">ELMS</a>, <a href="http://drupal.org/project/elmsmedia">ELMS Media</a>, <a href="http://drupal.org/project/ulmus">Ulmus</a>, the Open Studio and over 50 modules and themes.  One of the main goals of ELMS is to allow educators to leverage the power of Drupal. <a href="http://drupal.org/project/cis">Download it today!</a></p>
    </div>
    <div class='grid_12 space-out visibility_460 animate'>
	<h2 id='features'>Features</h2>
    </div>

        <div class='grid_3 visibility_460 animate'><img src='images/icon_01.png' alt="Content Centric"></div>
        <div class='grid_8 visibility_460 animate'>
        <h3>Content Centric</h3>
        <p>ELMS puts the focus on course content, not generic course spaces.</p>
        </div>
        <div class='grid_3 visibility_460 animate'><img src='images/icon_02.png' alt="Publish to HTML"></div>
        <div class='grid_8 visibility_460 animate'>
          <h3>Publish to HTML</h3>
          <p>Export any course space to a static HTML package or XML for back up.</p>
        </div>
        <div class='grid_3 visibility_460 animate'><img src='images/icon_03.png' alt="Open Studio"></div>
        <div class='grid_8 visibility_460 animate'>
          <h3>Open Studio</h3>
          <p>Student-centric, open assignment submission for  critique, feedback and collaboration.</p>
        </div>
        <div class='grid_3 visibility_460 animate'><img src='images/icon_04.png' alt="Designed by IDs"></div>
        <div class='grid_8 visibility_460 animate'>
          <h3>Designed by IDs</h3>
          <p>Developed based on learning design best practices established by Penn State instructional designers.</p>
        </div>
        <div class='grid_3 visibility_460 animate'><img src='images/icon_05.png' alt="Built on Drupal"></div>
        <div class='grid_8 visibility_460 animate'>
          <h3>Built on Drupal</h3>
          <p>Scalable and sustainable thanks to the massive Drupal open source community.</p>
        </div>
        <div class='grid_3 visibility_460 animate'><img src='images/icon_06.png'></div>
        <div class='grid_8 visibility_460 animate'>
          <h3>Glossary</h3>
          <p>Highlight terms in content and it will automatically find them throughout the course while creating a large vocab list.</p>
        </div>
        <div class='grid_3 visibility_460 animate'><img src='images/icon_07.png' alt="Asset Management"></div>
        <div class='grid_8 visibility_460 animate'>
          <h3>Asset Management</h3>
          <p>Separate system integrated to help maintain copyright, accessibility, and ease of use.</p>
        </div>
        <div class='grid_3 visibility_460 animate'><img src='images/icon_08.png' alt="Scalability"></div>
        <div class='grid_8 visibility_460 animate'>
          <h3>Scalability</h3>
          <p>Leveraging Drupal best practices for a platform that's powered large scale websites like <a href="http://whitehouse.gov">The White House.</a></p>
        </div>
        <div class='grid_3 visibility_460 animate'><img src='images/icon_09.png' alt="Simple user interface"></div>
        <div class='grid_8 visibility_460 animate'>
          <h3>Simple User Interface</h3>
          <p>Drupal based without all the difficulty of learning Drupal.</p>
        </div>
        <div class='grid_3 visibility_460 animate'><img src='images/icon_10.png' alt="Theme Flexibility"></div>
        <div class='grid_8 visibility_460 animate'>
          <h3>Theme Flexibility</h3>
          <p>Use Drupal's powerful theme layer to make each course match its topic matter</p>
        </div>


  <div class='grid_10 space-out suffix_2 visibility_460 animate'>
<h2 id='community'>Community</h2>
    <p>Join the community today and connect with the project through these sources!</p>
    <p>
        <a href="http://twitter.com/psu_elms"><img class="promo-image" src="images/twitter.png" alt="Follow psu_elms on twitter" title="Follow psu_elms on twitter"></a>
        <a href="https://www.facebook.com/pages/ELMS/225492544152120"><img class="promo-image" src="images/facebook.png" alt="Like our Facebook page" title="Like our Facebook page"></a>
        <a href="http://drupal.psu.edu/taxonomy/term/12/0/feed"><img class="promo-image" src="images/rss.png" alt="Subscribe to the ELMS project RSS feed" title="Subscribe to the ELMS project RSS feed"></a>
        <a href="mailto:elms@psu.edu"><img class="promo-image" src="images/email.png" alt="email elms@psu.edu" title="email elms@psu.edu"></a>
        <a href="http://elearning.psu.edu/"><img class="promo-image" src="images/eli.png" alt="Check out the elearning institute" title="Check out the elearning institute"></a></p>
  </div>


<!-- content set 720 -->
	<div class='grid_2 prefix_2 visibility_720 animate'><p><img src="images/elms_logo_02.png" alt="ELMS Logo"/></p></div>
	<div class='grid_8 visibility_720 text_block  animate'>
    <h2 class='title'>ELMS</h2>
    </div>
    <div class='grid_4 nav_link animate visibility_720'><p class='highlight'><a class='highlight' href="http://drupal.org/project/cis">Download</a></p></div>

    <div class='grid_8 prefix_2 visibility_720 text_block suffix_2 animate'><p>The E-Learning Management System (ELMS) is a Drupal package that allows you to create and manage an online course infrastructure from a simple interface.</p>
    </div>


        <div class='grid_2 prefix_2 nav_link animate visibility_720'><p><a href="#about1">About</a></p></div>
        <div class='grid_2 nav_link animate visibility_720'><p><a href="#features1">Features</a></p></div>
		<div class='grid_2 nav_link animate visibility_720'><p><a href="#community1">Community</a></p></div>
    <div class='grid_2 nav_link animate visibility_720'><p><a href="/blog">Blog</a></p></div>
    <div class='grid_8 space-out prefix_2 suffix_2 visibility_720 animate'>
    <h2 id='about1'>About</h2>
    <p>Built on top of the Drupal Content Management Framework, ELMS provides carefully crafted functionality that simplifies course creation, management, and distribution.  Unlike other tools, it has been developed by instructional designers, for instructionally focused course content authoring.  Many projects have come out of the ELMS Initiative since 2008 both for education as well as the Drupal community including <a href="http://drupal.org/project/cis">ELMS</a>, <a href="http://drupal.org/project/elmsmedia">ELMS Media</a>, <a href="http://drupal.org/project/ulmus">Ulmus</a>, the Open Studio and over 50 modules and themes.  One of the main goals of ELMS is to allow educators to leverage the power of Drupal/p. <a href="http://drupal.org/project/cis">Download it today!</a></p>
    </div>
    <div class='grid_10 space-out prefix_2 visibility_720 animate'>
<h2 id='features1'>Features</h2>
</div>

        <div class='grid_2 prefix_2 visibility_720 animate'>
          <p><img src='images/icon_01.png' alt="Content Centric"></p>
        </div>
        <div class='grid_3 visibility_720 animate'>
          <h3>Content Centric</h3>
          <p>ELMS puts the focus on course content, not generic course spaces.</p>
        </div>
        <div class='grid_2  visibility_720 animate'>
          <p><img src='images/icon_02.png' alt="Publish to HTML"></p>
        </div>
        <div class='grid_3  visibility_720 animate'>
          <h3>Publish to HTML</h3>
          <p>Export any course space to a static HTML package or XML for back up.</p>
        </div>
        <div class='clear'>&nbsp;</div>
        <div class='grid_2 prefix_2 visibility_720 animate'>
          <p><img src='images/icon_03.png' alt="Open Studio"></p>
        </div>
        <div class='grid_3  visibility_720 animate'>
          <h3>Open Studio</h3>
          <p>Student-centric, open assignment submission for  critique, feedback and collaboration.</p>
        </div>
        <div class='grid_2  visibility_720 animate'>
          <p><img src='images/icon_04.png' alt="Designed by IDs"></p>
        </div>
        <div class='grid_3  visibility_720 animate'>
          <h3>Designed by IDs</h3>
          <p>Developed based on learning design best practices established by Penn State instructional designers.</p>
        </div>
        <div class='clear'>&nbsp;</div>
        <div class='grid_2 prefix_2 visibility_720 animate'>
          <p><img src='images/icon_05.png' alt="Built on Drupal"></p>
        </div>
       <div class='grid_3 visibility_720 animate'>
          <h3>Built on Drupal</h3>
          <p>Scalable and sustainable thanks to the massive Drupal open source community.</p>
        </div>
        <div class='grid_2  visibility_720 animate'>
          <p><img src='images/icon_06.png' alt="Glossary"></p>
        </div>
        <div class='grid_3  visibility_720 animate'>
          <h3>Glossary</h3>
          <p>Highlight terms in content and it will automatically find them throughout the course while creating a large vocab list.</p>
        </div>
        <div class='clear'>&nbsp;</div>
        <div class='grid_2 prefix_2 visibility_720 animate'>
          <p><img src='images/icon_07.png' alt="Asset Management"></p>
        </div>
        <div class='grid_3  visibility_720 animate'>
          <h3>Asset Management</h3>
          <p>Separate system integrated to help maintain copyright, accessibility, and ease of use.</p>
        </div>
        <div class='grid_2  visibility_720 animate'>
          <p><img src='images/icon_08.png' alt="Scalability"></p>
        </div>
        <div class='grid_3  visibility_720 animate'>
          <h3>Scalability</h3>
          <p>Leveraging Drupal best practices for a platform that's powered large scale websites like <a href="http://whitehouse.gov">The White House</a></p>
        </div>
        <div class='clear'>&nbsp;</div>
        <div class='grid_2 prefix_2 visibility_720 animate'>
          <p><img src='images/icon_09.png' alt="Simple user Interface"></p>
        </div>
        <div class='grid_3  visibility_720 animate'>
          <h3>Simple User Interface</h3>
          <p>Drupal based without all the difficulty of learning Drupal.</p>
        </div>
        <div class='grid_2  visibility_720 animate'>
          <p><img src='images/icon_10.png' alt="Theme Flexibility"></p>
        </div>
        <div class='grid_3  visibility_720 animate'>
        <h3>Theme Flexibility</h3>
        <p>Use Drupal's powerful theme layer to make each course match its topic matter.</p>
        </div>

  <div class='grid_10 space-out prefix_2 visibility_720 animate'>
<h2 id='community1'>Community</h2>
<p>Join the community today and connect with the project through these sources!</p>
<p><a href="http://twitter.com/psu_elms"><img class="promo-image" src="images/twitter.png" alt="Follow psu_elms on twitter" title="Follow psu_elms on twitter"></a>
<a href="https://www.facebook.com/pages/ELMS/225492544152120"><img class="promo-image" src="images/facebook.png" alt="Like our Facebook page" title="Like our Facebook page"></a>
<a href="http://drupal.psu.edu/taxonomy/term/12/0/feed"><img class="promo-image" src="images/rss.png" alt="Subscribe to the ELMS project RSS feed" title="Subscribe to the ELMS project RSS feed"></a>
<a href="mailto:elms@psu.edu"><img class="promo-image" src="images/email.png" alt="email elms@psu.edu" title="email elms@psu.edu"></a>
<a href="http://elearning.psu.edu/"><img class="promo-image" src="images/eli.png" alt="Check out the elearning institute" title="Check out the elearning institute"></a></p>
  </div>

    <div class='clear'>&nbsp;</div>

<div class='grid_8 space-out prefix_2 suffix_2 animate'>
    	<p class="footer">This website is &copy; Pennsylvania State University College of Arts and Architecture, e-Learning Institute 2007-2014. All ELMS code is released under the <a href="http://www.gnu.org/licenses/gpl-2.0.html">General Public License (GPL)</a></p>
    </div>

</div>
</body>
</html>
