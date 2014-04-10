<!DOCTYPE html>
<html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">
<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <div id="skip-link">
    <a href="#main-content"><?php print t('Skip to main content'); ?></a>
  </div>
  <?php print $page_top; ?>
  <div id="page" class="container">
    <header id="banner" class="clearfix">
      <?php if ($logo or $site_name): ?>
        <div id="branding">
          <div class="brand-elements">
            <strong>
              <?php if (!empty($logo)): ?>
                <span id="logo">
                  <a href="<?php print $base_path; ?>" title="<?php print t('Home page'); ?>" rel="home">
                    <img src="<?php print $logo; ?>" alt="<?php print t('Home page'); ?>" />
                  </a>
                </span>
              <?php endif; ?>
              <?php if (!empty($site_name)): ?>
                <span id="site-name">
                  <a href="<?php print $base_path ?>" title="<?php print t('Home page'); ?>" rel="home">
                    <?php print $site_name; ?>
                  </a>
                </span>
              <?php endif; ?>
            </strong>
          </div>
        </div>
      <?php endif; ?>
    </header>
    <div id="main-content">
      <?php if ($title): ?>
        <h1 id="page-title"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print $messages; ?>
      <div id="content">
        <?php print $content; ?>
      </div>
    </div>
    <footer><?php print $attribution; ?></footer>
  </div>
  <?php print $page_bottom ?>
</body>
</html>