#!/bin/sh
#
# Cloud Hook: environment-indicator
#
# The post-code-deploy hook is run whenever you use the Workflow page to
# deploy new code to an environment, either via drag-drop or by selecting
# an existing branch or tag from the Code drop-down list. This hook will
# maintain a variable with the realease information.

site="$1"
target_env="$2"
source_branch="$3"
deployed_tag="$4"
repo_url="$5"
repo_type="$6"

if [ "$source_branch" != "$deployed_tag" ]; then
    drush @$site.$target_env vset --exact environment_indicator_remote_release.$target_env $source_branch
else
    drush @$site.$target_env vset --exact environment_indicator_remote_release.$target_env $deployed_tag
fi
echo "Updated release info for environment indicator."
