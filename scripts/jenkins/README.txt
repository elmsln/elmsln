Jenkins

This includes jobs that have been used in Jenkins setups to automate the management of multiple ELMSLN deployments. These scripts are simple and tend to tap other bash scripts used in local development / on remote deployments

SETUP
=====
Stand up jenkins, then start to setup keys with remote hosts. Create a user like “jenkins” on the remote hosts via the commands
# setup jenkins server first
# on jenkins server follow the prompts
ssh-keygen
cat ~/.ssh/id_rsa.pub
# move over to the remote
# assuming ELMSLN is in place in /var/www/elmsln
sudo chown -R jenkins:admin /var/www/elmsln
# make the jenkins user
useradd -gadmin jenkins
# setup elmsln administration for jenkins user
sudo -i -u jenkins
bash /var/www/elmsln/scripts/install/user/elmsln-admin-user.sh
# make a local key and follow the prompts
ssh-keygen
touch .ssh/authorized_keys
# copy your public key from jenkins server and paste it in authorized keys on the remote system

#back to jenkins
# test that the SSH binding is correct
ssh jenkins@whatever.com
# if no password was required you should be good to go
# now add this into your ~/.elmsln/elmsln-hosts file so that it can be spidered to manage multiple deployments!