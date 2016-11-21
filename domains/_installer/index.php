<?php
// tee up logging for step and install log
$step = file_get_contents('/var/www/elmsln/config/tmp/STEP-LOG.txt');
$step = trim(preg_replace('/\s+/', ' ', $step));
$log = file_get_contents('/var/www/elmsln/config/tmp/INSTALL-LOG.txt');
// walk through the steps to present messages
switch ($step) {
  case 0:
    $steptext = 'Optimizing server for ELMS:LN';
  break;
  case 1:
    $steptext = 'Calculating network topology';
  break;
  case 2:
    $steptext = 'Installing services';
  break;
  case 3:
    $steptext = 'Installing authorities';
  break;
  case 4:
    $steptext = 'Cleaning up permissions';
  break;
  case 5:
    $steptext = 'Finishing up integration';
  break;
  case 6:
    $steptext = 'Install complete!';
  break;
  default:
    $step = 0;
    $steptext = 'Installing server dependencies';
  break;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0"/>
  <title>ELMSLN Installation screen</title>

  <!-- CSS  -->
  <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
  <link href="css/materialize.css" type="text/css" rel="stylesheet" media="screen,projection"/>
  <link href="css/style.css" type="text/css" rel="stylesheet" media="screen,projection"/>
  <link href="elmsln/elmsln-font-styles.css" type="text/css" rel="stylesheet" media="screen,projection"/>
</head>
<body>
  <nav class="light-blue lighten-1" role="navigation">
    <div class="nav-wrapper container"><a id="logo-container" href="#" class="brand-logo"><i class="icon icon-network white-text"></i>ELMSLN Installer</a>
      <ul class="right hide-on-med-and-down">
        <li><a href="https://github.com/elmsln/elmsln" target="_blank">Github</a></li>
        <li><a href="https://github.com/elmsln/elmsln/issues" target="_blank">Issue queue</a></li>
        <li><a href="https://elmsln.readthedocs.io/en/latest/" target="_blank">Documentation</a></li>
        <li><a href="https://twitter.com/elmsln" target="_blank">Twitter</a></li>
        <li><a href="https://www.elmsln.org/" target="_blank">ELMSLN.org</a></li>
      </ul>

      <ul id="nav-mobile" class="side-nav">
        <li><a href="https://github.com/elmsln/elmsln" target="_blank">Github</a></li>
        <li><a href="https://github.com/elmsln/elmsln/issues" target="_blank">Issue queue</a></li>
        <li><a href="https://elmsln.readthedocs.io/en/latest/" target="_blank">Documentation</a></li>
        <li><a href="https://twitter.com/elmsln" target="_blank">Twitter</a></li>
        <li><a href="https://www.elmsln.org/" target="_blank">ELMSLN.org</a></li>
      </ul>
      <a href="#" data-activates="nav-mobile" class="button-collapse"><i class="material-icons">menu</i></a>
    </div>
  </nav>
  <div class="section no-pad-bot" id="index-banner">
    <div class="">
      <h1 class="header center orange-text steptext">Step <?php print $step;?> of 6: <?php print $steptext; ?></h1>
      <div class="row">
        <div class="col s12 m8 push-m2">
          <div id="logid" class="logarea-wrapper">
            Log:
            <pre class="logarea"><?php print $log;?></pre>
          </div>
        </div>
      </div>
      <h2 class="blue-text">While you wait</h2>
      <div class="row center">
        <div class="col s10 m8 push-s1 push-m2">
          <div class="video-container">
            <iframe width="560" height="315" src="https://www.youtube.com/embed/videoseries?list=PLJQupiji7J5fdTItbAp-op9Gfiwx1LvEE" frameborder="0" allowfullscreen></iframe>
          </div>
        </div>
      </div>
    </div>
  </div>


  <div class="">
    <div class="section">

      <!--   Icon Section   -->
      <div class="row">
        <div class="col s12 m4">
          <div class="icon-block">
            <h2 class="center light-blue-text"><i class="material-icons">flash_on</i></h2>
            <h5 class="center">Innovative</h5>

            <p class="light">ELMSLN is a self-federated next generation digital learning environment. What's that mean? It means we can get data to anywhere from anywhere within the system. This improves workflows, user experiences, integrations, and ultimately we believe with the produciton of better, more engaging course experiences with less time to build and maintain. It's a win for faculty and staff members but most importantly, a win for learners!</p>
          </div>
        </div>

        <div class="col s12 m4">
          <div class="icon-block">
            <h2 class="center light-blue-text"><i class="material-icons">group</i></h2>
            <h5 class="center">User focused</h5>

            <p class="light">Our community is embedded in higher education, giving you the highest quality experience possible. We've lived your day to day pain with traditional learning management solutions and boldly proclaim: no more.</p>
          </div>
        </div>

        <div class="col s12 m4">
          <div class="icon-block">
            <h2 class="center light-blue-text"><i class="material-icons">settings</i></h2>
            <h5 class="center">Customizable</h5>

            <p class="light">Leveraging Drupal at it's core, ELMSLN is the most robust and flexible solution you'll ever meet. We don't sacrifice usability for power though, but when your ready to tap into the raw power of Drupal, it's always there.</p>
          </div>
        </div>
      </div>

    </div>
  </div>

  <!--  Scripts-->
  <script src="https://code.jquery.com/jquery-2.1.1.min.js"></script>
  <script src="js/materialize.js"></script>
  <script src="js/init.js"></script>

  </body>
</html>
