<?php
  header("Content-Type:application/json");
  $step = file_get_contents('/var/www/elmsln/config/tmp/STEP-LOG.txt');
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
  print json_encode(trim(preg_replace('/\s+/', ' ', 'Step ' . $step . ' of 6: ' . $steptext)));
?>