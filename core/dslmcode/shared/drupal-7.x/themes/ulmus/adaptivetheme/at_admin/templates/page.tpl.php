<div id="page">
  <div class="topbar-wrapper">
    <div class="container">
      <div id="topbar" class="clearfix">
        <?php print $breadcrumb; ?>
        <?php if ($datetime_rfc): ?>
          <time datetime="<?php print $datetime_iso; ?>"><?php print $datetime_rfc; ?></time>
        <?php endif; ?>
      </div>
    </div>
  </div>

  <div id="header" class="content-header">
    <div class="container">
      <header<?php print $content_header_attributes; ?>>

        <?php print render($title_prefix); ?>
        <?php if ($title): ?>
          <h1 id="page-title"><?php print $title; ?></h1>
        <?php endif; ?>
        <?php print render($title_suffix); ?>

        <?php if ($primary_local_tasks): ?>
          <nav id="primary-tasks" class="clearfix<?php print $secondary_local_tasks ? ' with-secondary' : '' ?>" role="navigation">
            <ul class="tabs primary"><?php print render($primary_local_tasks); ?></ul>
          </nav>
        <?php endif; ?>

      </header>
    </div>
  </div>

  <?php if ($secondary_local_tasks): ?>
    <div class="secondary-tasks-wrapper">
      <div class="container">
        <nav id="secondary-tasks" class="clearfix menu-wrapper" role="navigation">
          <ul class="tabs secondary clearfix"><?php print render($secondary_local_tasks); ?></ul>
        </nav>
      </div>
    </div>
  <?php endif; ?>

  <div id="columns" class="columns clearfix">
    <div class="container">
      <div id="content-column" class="content-column" role="main">
        <div class="content-inner">

          <?php print render($page['highlighted']); ?>
          <?php print $messages; ?>
          <?php print render($page['help']); ?>

          <?php if ($action_links): ?>
            <nav class="actions-wrapper menu-wrapper clearfix">
              <ul class="action-links clearfix">
                <?php print render($action_links); ?>
              </ul>
            </nav>
          <?php endif; ?>

          <<?php print $tag; ?> id="main-content">

            <!-- region: Main Content -->
            <?php if ($content = render($page['content'])): ?>
              <div id="content">
                <?php print $content; ?>
              </div>
            <?php endif; ?>

            <!-- Feed icons (RSS, Atom icons etc -->
            <?php print $feed_icons; ?>
            
          </<?php print $tag; ?>><!-- /end #main-content -->

        </div><!-- /end .content-inner -->
      </div><!-- /end #content-column -->

      <!-- regions: Sidebar first and Sidebar second -->
      <?php $sidebar_first = render($page['sidebar_first']); print $sidebar_first; ?>
      <?php $sidebar_second = render($page['sidebar_second']); print $sidebar_second; ?>

    </div><!-- /end #columns -->

  </div>

  <?php if ($page['footer']): ?>
    <footer id="page-footer">
      <div class="container">
        <?php print render($page['footer']); ?>
      </div>
    </footer>
  <?php endif; ?>

</div>

