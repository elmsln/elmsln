ELMS: CIS Connector
Copyright (C) 2015  The Pennsylvania State University

Bryan Ollendyke
bto108@psu.edu

12 Borland
University Park, PA 16802

This module provides some standard functions for building an invisible,
distributed registry of educational services.  This keeps our implementation
specific settings abstracted in another module that invokes this one.

The primary reason for this is that internally we create a module with the
namespace of {university}_{college}_settings which invokes edu_service_registry
to supply the connection details of an educational service to the data hub.

This also would allow others to implement this technology should they so
choose but this most likely will only make sense in the context of education
and drupal for that matter.

Please see the cis_connector.api.php file for an example of how to implement this, but you should always set this up via the automated installation method provided in the main ELMSLN repository.
Basically you create an account in the CIS that enables remove connections via restWS.
Then you make a service account which has the role SERVICE ACCOUNT. See the sub-module
to restWS for details on how to securely allow for remote / authenticated http requests.
This will enable you to have cis_connector based distributions connect securely and
consistently to your CIS just be defining a few values in this small module.

Once you've created this module, keep it in a safe place and only deploy it on the
distributions that you want to be able to connect.  A secondary level of security that is
recommended is to create an alternate address for your CIS and IP lock your distributed
services to this address.  This way you have a single account that can only be logged in remotely from a handful of boxes at a firewall level.

Developer Note:
CIS Connector is a library required by all systems in ELMSLN. There is a mix of name spaces between CIS_* and ELMSLN_*. ELMSLN under the interface labeling of ELMSLN Core (typically) is the newer convention that is utilized. CIS based name spaces often reference ELMSLN but may have historically been used for "calling home" which was CIS as the system was originally concieved.

This is because cis_connector.module used to be a library for talking just to CIS and quickly evolved to be a more abstract call library for quickly and securely talking to anything following the ELMSLN pattern of design.

