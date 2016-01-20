#!/bin/bash
# ensure the ulmus user doesn't have to run with a tty or all sudo commands won't work
echo '# ELMSLN users dont need tty' >> /etc/sudoers
echo 'Defaults:ulmus    !requiretty' >> /etc/sudoers
