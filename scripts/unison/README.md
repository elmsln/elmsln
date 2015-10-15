# ELMSLN Unison

Unison is an alternative to Virtualbox's native file sharing as well as rsync and nfs.  It performs bidirectional file syncing while not causing performance issues for your virtual server.

## Prerequisites

Identical versions of Unison must be installed on you local computer and within the vagrant installation.  Please DO NOT use the vagrant unison plugin.

## Remove the contents of the config file from the host machine.  This will ensure that the config files on the virtual machine will not be overriden.

```
$ rm -rf config/*
```

## Setup unison profile

From your local computer, run the following bash script.

```
$ bash scripts/unison/unison-setup.bash
```

## Run Unison

```
$ unison elsmln
```