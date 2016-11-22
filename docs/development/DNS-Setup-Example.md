This guide provides detailed instructions on how to register for a DNS through the Namecheap hosting service. If you wish to use other hosting providers, you will be following a similar setup process to the one listed here. You should follow this guide before installing ELMS:LN on a server as this guide sets up both the DNS registration process and how to request SSH access to your new server. 

## Registering the DNS

1. Navigate to namecheap.com and click sign-up if you do not already have an account. Fill out account information and submit the form
    **_Note: You may set up dual-factor authentication for the account during this step_**
2. After logging in and registering you will be redirected to your dashboard. This dashboard will allow you to make changes to sites you own. 

![dashboard](https://cloud.githubusercontent.com/assets/7243665/20538181/14c08d8c-b0be-11e6-877a-3b7df8640519.png)

3. From the dashboard menu you will hover over the `Domains` dropdown and click`Registration`. This will bring up a menu where you can request a Domain Name for your website.
4. Type a desired domain such as `example.com` into the search bar to see if the domain is available. If it is, click on the shopping cart icon next to the domain and follow checkout instructions. 
    **_Note: There are options for DNS protection and other extra items. Talk to your IT staff about whether your organization wishes to buy extra protection for the site_**

![searchbar](https://cloud.githubusercontent.com/assets/7243665/20314212/68d6cca2-ab27-11e6-90bd-9a04cf7b1c71.png)

5. After you have completed the domain purchase, it will show up on the dashboard menu as shown in the first image and the image below.

![dashboard](https://cloud.githubusercontent.com/assets/7243665/20538181/14c08d8c-b0be-11e6-877a-3b7df8640519.png)

## Setting up SSH

After you have registered the DNS you will want to go to the online version of the server. This is where you will set up SSH configuration and will be able to install software such as Drupal, Wordpress, and other CMS services. 

1. Click the manage tab on your new domain and then click the products tab. Here you will see an option to manage your hosting. Click Manage and continue to the next page. 
2. Log into CPanel using the username provided by Namecheap in an email. If you cannot find this email contact [Namecheap Support](https://www.namecheap.com/support/live-chat/general.aspx?loc) and they can look it up for you. 

![login](https://cloud.githubusercontent.com/assets/7243665/20538196/23591878-b0be-11e6-92b6-2c20930a2ca2.png)

3. If you have completed all the steps properly you will see the following page: 

![cpanel](https://cloud.githubusercontent.com/assets/7243665/20314724/28500098-ab29-11e6-9140-eb7b78995098.png)

4. If you have seen the above page, contact [Namecheap Support ](https://www.namecheap.com/support/live-chat/general.aspx?loc)and ask them for ssh access. They will set up the ssh configuration and you will be able to login and manage your server files via shell. 

**Now enjoy your new site! And enjoy installing ELMS:LN!**
