<<<<<<< HEAD
<ul class="menu book-oultine slide-panels">
  <li><a class="accordion-btn">Unit 1</a>
    <dl class="accordion" data-accordion="myAccordionGroup">
      <dd class="accordion-navigation">
        <a href="#panel1c">Lesson 1</a>
        <div id="panel1c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <a href="#panel2c">Lesson 2</a>
        <div id="panel2c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <a href="#panel3c">Lesson 3</a>
        <div id="panel3c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
      </dd>
    </dl>
  </li>
  
  <li><a class="accordion-btn">Unit 2</a>
    <dl class="accordion" data-accordion="myAccordionGroup">
      <dd class="accordion-navigation">
        <a href="#panel4c">Lesson 4</a>
        <div id="panel4c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <a href="#panel5c">Lesson 5</a>
        <div id="panel5c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <a href="#panel6c">Lesson 6</a>
        <div id="panel6c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
      </dd>
    </dl>
  </li>

  <li><a class="accordion-btn">Unit 4</a>
    <dl class="accordion" data-accordion="myAccordionGroup">
      <dd class="accordion-navigation">
        <a href="#panel7c">Lesson 7</a>
        <div id="panel7c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <a href="#panel8c">Lesson 8</a>
        <div id="panel8c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <a href="#panel9c">Lesson 9</a>
        <div id="panel9c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
      </dd>
    </dl>
  </li>

</ul>

=======
>>>>>>> FETCH_HEAD
<div class="sticky-nav book-outline main-a"><?php print $content; ?></div>
<div class="book-outline sticky-book-outline">
  <a href="#" data-dropdown="book-sticky-nav" class="button dropdown">
    <?php print (($active = _cis_service_connection_active_outline()) ? $active->title : t('Lessons')); ?>
  </a>
  <? print '<ul id="book-sticky-nav" data-downdown-content class="f-dropdown nav nav-list">' . $content . '</ul>'; ?>
</div>
