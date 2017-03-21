As ELMS:LN is moving towards using webcomponents for many of its designs, some developers may wish to develop these tools on their own using the polymer-cli project. This guide is a step-by-step guide on how to set up polymer-cli on your local machine for development purposes: 

1.  Install `npm` - this tool will allow you to access node and install polymer-cli as well as other packages. This is done through one of two methods: 
- Download the files via: https://nodejs.org/en/download/
- `curl -L https://www.npmjs.com/install.sh | sh`
2. Once `npm` is installed you will want to install the `nvm` package manager. this allows you to switch between different versions of `npm`. 
- Guide: https://github.com/psudug/nittany-vagrant/wiki/Manually-installing-node-and-npm 
3. Once `nvm` and `npm` are installed, you are ready to begin installing polymer-cli
4. Run `nvm use 4.1.2` to switch your version of node to 4.1.2.
5. Run `npm install -g polymer-cli` to download polymer-cli to your local machine. This may take a few minutes...
6. After the install is finished you can create a new folder and setup your project with polymer init
- `mkdir example `
- `cd example`
- `polymer init`
7. Follow the prompt's instructions and any of the documentation on polymer's site to begin your first project! (https://www.polymer-project.org/1.0/start/first-element/intro)
