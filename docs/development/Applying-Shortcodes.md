Creating Tokens
===============

###Background info for navigating section offerings
Before we begin implementing tokens, you need to move away from the master section.

1. Select your course and access the service
2. Move away from the master section by clicking the admin tab on the top left of the screen
3. Find the section chooser, and select a different section.
4. Make sure that you click the switch section button to change the display
![change section](https://cloud.githubusercontent.com/assets/16597608/13934293/cfbe0914-ef87-11e5-8dbf-184cf31ed16d.png)

###What are tokens?
Tokens are often used when something such as a date is used throughout the site.
If someone plans on making changes, and does not want to do it individually they will use tokens.
Tokens allow you to make the change once and it will be implemented throughout.

###Now we are ready to establish a set of tokens
1. Click admin and settings, scroll down until you see the collapsed-state field set for course tokens. Open it.
![settings tokens](https://cloud.githubusercontent.com/assets/16597608/13933548/184ca7b6-ef84-11e5-9fa9-251e1e0cf5a6.png)
2. Right now there are meaningless placeholding tokens. They are not tied to anything, have no value, and should be rewritten into a real token.
3. The first part (module_1) is the token name. The pipe (|) demarcates the token name from its value. The last part, (Module 1) is the token value.
4. Create your token using that format. For example: Assignment_1_due_date|4/1. Make sure to hit save configuration
  ![create token](https://cloud.githubusercontent.com/assets/16597608/13933785/45b8a136-ef85-11e5-9dc1-0aae8ee73983.png)
5. In the course outline for that section, you can edit the page and now include the token.
    To include the token you must include [elmsln_section:token_name].
 ![token module](https://cloud.githubusercontent.com/assets/16597608/13933924/d93cea8e-ef85-11e5-8065-751e750409a8.png)
6. Now when you view the page you can see that the token is used and the date is printed.
 ![token displayed](https://cloud.githubusercontent.com/assets/16597608/13934017/4ba816b6-ef86-11e5-9857-03b631e525d0.png)
