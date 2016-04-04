Working with Git can be a large challenge in almost every project. When submitting a Pull-Request (PR) it is best practice to try and submit the PR as one commit to be pushed. This way it is easier to see exactly what was worked on within the code. Sometimes an individual may make a mistake in pushing a commit that was incorrect. Through these steps you can reverse the commit and push in order to make your PR only have one accurrate commit.

WARNING: THIS PROCESS IS POTENTIALLY DESTRUCTIVE

    Step 1: Get the ID of the commit you want to reset to and run the following command...
    git reset [ID]
    Step 2: Commit changes
    git commit -m 'these are my changes' 
    Step 3: Force Push to origin master (i.e. your forked repository) 
    git push --force origin master 

These steps will allow you to smoosh multiple commits into one and make corrections to pushes in a PR that contained incorrect commits.
