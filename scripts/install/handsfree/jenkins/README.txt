hands free jenkins install.sh

This is to pull off a remotely tripped installation over SSH via jenkins.
The only real difference is that it doesn’t run certain calls via sudo
(something not possible over a non-interactive connection).