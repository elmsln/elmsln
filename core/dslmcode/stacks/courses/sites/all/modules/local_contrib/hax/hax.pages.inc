<?php

/**
 * Edit mode callback.
 */
function hax_page_edit($node) {
  drupal_add_js(drupal_get_path('module', 'hax') . '/js/hax-drag-drop.js');
  drupal_add_css(drupal_get_path('module', 'hax') . '/css/hax.css');
  // @todo make this more generic then simply the node body field
  $markup = check_markup($node->body['und'][0]['value'], $node->body['und'][0]['format']);
  // quick and dirty substitution, all p/img tags can be moved
  $markup = str_replace('<p', '<p data-draggable="item"', $markup);
  $markup = str_replace('<img', '<img data-draggable="item"', $markup);
  // quick and dirty substitution, all div tags are containers
  $markup = str_replace('<div', '<div data-draggable="target"', $markup);
  $output = '<div class="columns hax-accessible hax-body">
  <!-- drop zones (need to add these via jquery) -->
  ' . $markup . '
  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
      <p data-draggable="item"><strong>Directions:</strong> Tab to this item. To Select via Keyboard, press spacebar. To confirm a Move, press Enter. To release selection, press escape.</p>
      <h2 data-draggable="item">HEADER: DRAG ME</h2>
      <h3 data-draggable="item">SUB HEADER</h3>
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
      <p data-draggable="item"><strong>Directions:</strong> Tab to this item. To Select via Keyboard, press spacebar. To confirm a Move, press Enter. To release selection, press escape.</p>
      <p data-draggable="item">Pellentesque vel dui sed orci faucibus iaculis. Suspendisse dictum magna id purus tincidunt rutrum. Nulla congue. Vivamus sit amet lorem posuere dui vulputate ornare. Phasellus mattis sollicitudin ligula. Duis dignissim felis et urna. Integer adipiscing
        congue metus. Nam pede. Etiam non wisi. Sed accumsan dolor ac augue. Pellentesque eget lectus. Aliquam nec dolor nec tellus ornare venenatis. Nullam blandit placerat sem. Curabitur quis ipsum. Mauris nisl tellus, aliquet eu, suscipit eu, ullamcorper
        quis, magna. Mauris elementum, pede at sodales vestibulum, nulla tortor congue massa, quis pellentesque odio dui id est. Cras faucibus augue.</p>
    </div>
  </div>


  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
      <div class="row layout-group" data-draggable="item" data-equalizer>
        <div class="columns small-12 sub-target" data-draggable="target" data-equalizer-watch></div>
      </div>
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
      <div class="row layout-group" data-draggable="item" data-equalizer>
        <div class="columns small-8 sub-target" data-draggable="target" data-equalizer-watch>
          <img data-draggable="item" src="http://placehold.it/1200x400&text=[text]">
          <img data-draggable="item" src="http://placehold.it/1200x400&text=[text]">
        </div>
        <div class="columns small-4 sub-target" data-draggable="target" data-equalizer-watch>
          <img data-draggable="item" src="http://placehold.it/1200x400&text=[text]">
        </div>
      </div>
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
      <div class="row layout-group" data-draggable="item" data-equalizer>
        <div class="columns small-4 sub-target" data-draggable="target" data-equalizer-watch>
          <img data-draggable="item" src="http://placehold.it/1200x400&text=[text]">
        </div>
        <div class="columns small-8 sub-target" data-draggable="target" data-equalizer-watch>
          <img data-draggable="item" src="http://placehold.it/1200x400&text=[text]">
        </div>
      </div>
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
      <div class="row layout-group" data-draggable="item" data-equalizer>
        <div class="columns small-6 sub-target" data-draggable="target" data-equalizer-watch><img data-draggable="item" src="http://placehold.it/1200x400&text=[text]"></div>
        <div class="columns small-6 sub-target" data-draggable="target" data-equalizer-watch><img data-draggable="item" src="http://placehold.it/1200x400&text=[text]"></div>
      </div>
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
      <div class="row layout-group" data-draggable="item" data-equalizer>
        <div class="columns small-4 sub-target" data-draggable="target" data-equalizer-watch><img data-draggable="item" src="http://placehold.it/1200x400&text=[text]"></div>
        <div class="columns small-4 sub-target" data-draggable="target" data-equalizer-watch><img data-draggable="item" src="http://placehold.it/1200x400&text=[text]"></div>
        <div class="columns small-4 sub-target" data-draggable="target" data-equalizer-watch><img data-draggable="item" src="http://placehold.it/1200x400&text=[text]"></div>
      </div>
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
      <div class="row layout-group" data-draggable="item" data-equalizer>
        <div class="columns small-3 sub-target" data-draggable="target" data-equalizer-watch></div>
        <div class="columns small-3 sub-target" data-draggable="target" data-equalizer-watch></div>
        <div class="columns small-3 sub-target" data-draggable="target" data-equalizer-watch></div>
        <div class="columns small-3 sub-target" data-draggable="target" data-equalizer-watch></div>
      </div>
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target " data-draggable="target">
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
    </div>
  </div>
  <hr>
  <div>
    <p>This is how you make things sortable. Now... where to put it: Sortable.create(selections.owner);</p>
  </div>
  <div class="row layout-garage collapse">
    <div class="columns small-12 sub-target" data-draggable="target">
      <img class="drag-item" data-draggable="item" src="http://placehold.it/1200x200&text=[text]">
      <img class="drag-item" data-draggable="item" src="http://placehold.it/1200x100&text=[text]">
      <img class="drag-item" data-draggable="item" src="http://placehold.it/1200x80&text=[text]">
    </div>
  </div>

  <div class="row layout-garage collapse">
    <div id="sortable-items" class="columns small-12 sub-target" data-draggable="target">
       <div class="drag-item" data-draggable="item"><img class=" list-group-item"  src="http://placehold.it/1200x200&text=[text]"></div>
      <div class="drag-item" data-draggable="item"><img class=" list-group-item"  src="http://placehold.it/1200x100&text=[text]"></div>
      <div class="drag-item" data-draggable="item"><img   src="http://placehold.it/1200x80&text=[text]"></div>
    </div>
  </div>
</div>';

  // apply the toolbar to the interface
  $output .= _hax_render_toolbar();
  return $output;
}
