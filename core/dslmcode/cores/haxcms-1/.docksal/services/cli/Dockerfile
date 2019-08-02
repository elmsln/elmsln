# Use a stock Docksal image as the base
FROM docksal/cli:php7.1
# All further commands will be performed as the docker user.
USER docker

# Install additional global npm dependencies
RUN \
    # Initialize nvm environment
    . $NVM_DIR/nvm.sh && \
    # Install node packages
    npm i npm@latest --global
    npm install -g surge
    bash ${PROJECT_ROOT}/scripts/haxtheweb.sh admin admin admin@admin.admin admin

# IMPORTANT! Switching back to the root user as the last instruction.
USER root
