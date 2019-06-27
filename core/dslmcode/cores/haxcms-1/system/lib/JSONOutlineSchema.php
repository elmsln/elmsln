<?php
/**
 * JSONOutlineSchema - An object for interfacing with the JSON Outline schema
 * specification. @see https://github.com/LRNWebComponents/json-outline-schema
 * for more details. This provides a simple way of loading outlines, parsing
 * and working with the items in them while writing back to the specification
 * accurately.
 */

include_once 'JSONOutlineSchemaItem.php';

class JSONOutlineSchema
{
    public $file;
    public $id;
    public $title;
    public $author;
    public $description;
    public $license;
    public $metadata;
    public $items;
    /**
     * Establish defaults
     */
    public function __construct()
    {
        $this->file = null;
        $this->id = $this->generateUUID();
        $this->title = 'New site';
        $this->author = '';
        $this->description = '';
        $this->license = 'by-sa';
        $this->metadata = new stdClass();
        $this->items = array();
    }

    /**
     * Get a reasonable license name from the short hand
     */
    public function getLicenseDetails()
    {
        $list = array(
            "by" => array(
                'name' => "Creative Commons: Attribution",
                'link' => "https://creativecommons.org/licenses/by/4.0/",
                'image' => "https://i.creativecommons.org/l/by/4.0/88x31.png"
            ),
            "by-sa" => array(
                'name' => "Creative Commons: Attribution Share a like",
                'link' => "https://creativecommons.org/licenses/by-sa/4.0/",
                'image' => "https://i.creativecommons.org/l/by-sa/4.0/88x31.png"
            ),
            "by-nd" => array(
                'name' => "Creative Commons: Attribution No derivatives",
                'link' => "https://creativecommons.org/licenses/by-nd/4.0/",
                'image' => "https://i.creativecommons.org/l/by-nd/4.0/88x31.png"
            ),
            "by-nc" => array(
                'name' => "Creative Commons: Attribution non-commercial",
                'link' => "https://creativecommons.org/licenses/by-nc/4.0/",
                'image' => "https://i.creativecommons.org/l/by-nc/4.0/88x31.png"
            ),
            "by-nc-sa" => array(
                'name' =>
                    "Creative Commons: Attribution non-commercial share a like",
                'link' => "https://creativecommons.org/licenses/by-nc-sa/4.0/",
                'image' =>
                    "https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png"
            ),
            "by-nc-nd" => array(
                'name' =>
                    "Creative Commons: Attribution Non-commercial No derivatives",
                'link' => "https://creativecommons.org/licenses/by-nc-nd/4.0/",
                'image' =>
                    "https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png"
            )
        );
        if (isset($list[$this->license])) {
            return $list[$this->license];
        }
        return array();
    }
    /**
     * Get a new item matching schema standards
     * @return new JSONOutlineSchemaItem Object
     */
    public function newItem()
    {
        $item = new JSONOutlineSchemaItem();
        return $item;
    }
    /**
     * Add an item to the outline
     * @var $item an array of values, keyed to match JSON Outline Schema
     * @return count of items in the array
     */
    public function addItem($item)
    {
        $safeItem = $this->validateItem($item);
        $count = array_push($this->items, $safeItem);
        return $count;
    }
    /**
     * Validate that an item matches JSONOutlineSchemaItem format
     * @var $item JSONOutlineSchemaItem
     * @return JSONOutlineSchemaItem matching the specification
     */
    private function validateItem($item)
    {
        // create a generic schema item
        $tmp = new JSONOutlineSchemaItem();
        // crush the item given into a stdClass object
        $ary = get_object_vars($item);
        foreach ($ary as $key => $value) {
            // only set what the element from spec allows into a new object
            if (isset($tmp->{$key})) {
                $tmp->{$key} = $value;
            }
        }
        return $tmp;
    }
    /**
     * Remove an item from the outline if it exists
     * @var $id an id that's in the array of items
     * @return JSONOutlineSchemaItem or FALSE if not found
     */
    public function removeItem($id)
    {
        foreach ($this->items as $key => $item) {
            if ($item->id == $id) {
                $tmp = $this->items[$key];
                unset($this->items[$key]);
                return $tmp;
            }
        }
        return false;
    }
    /**
     * Update an item in the outline
     * @var $id an id that's in the array of items
     * @return JSONOutlineSchemaItem or FALSE if not found
     */
    public function updateItem($item, $save = false)
    {
        // verify this is a legit item
        $safeItem = $this->validateItem($item);
        foreach ($this->items as $key => $tmpItem) {
            // match the current item's ID to our safeItem passed in
            if ($tmpItem->id == $safeItem->id) {
                // overwrite the item
                $this->items[$key] = $safeItem;
                // if we save, then we let that return the whole file
                if ($save) {
                    return $this->save();
                }
                // this was successful
                return true;
            }
        }
        // we didn't find a match on the ID to bother saving an update
        return false;
    }
    /**
     * Load a schema from a file
     */
    public function load($location)
    {
        if (file_exists($location)) {
            $this->file = $location;
            $fileData = json_decode(file_get_contents($location));
            $vars = get_object_vars($fileData);
            foreach ($vars as $key => $var) {
                if (isset($this->{$key}) && $key != 'items') {
                    $this->{$key} = $var;
                }
            }
            // check for items and escalate to full JSONOutlineSchemaItem object
            // also ensures data matches only what is supported
            if (isset($vars['items'])) {
                foreach ($vars['items'] as $key => $item) {
                    $newItem = new JSONOutlineSchemaItem();
                    $newItem->id = $item->id;
                    $newItem->indent = $item->indent;
                    $newItem->location = $item->location;
                    $newItem->order = $item->order;
                    $newItem->parent = $item->parent;
                    $newItem->title = $item->title;
                    $newItem->description = $item->description;
                    // metadata can be anything so whatever
                    $newItem->metadata = $item->metadata;
                    $this->items[$key] = $newItem;
                }
            }
            return true;
        }
        return false;
    }
    /**
     * Get an item by ID
     */
    public function getItemById($id) {
        foreach ($this->items as $item) {
            if ($item->id === $id) {
                return $item;
            }
        }
        return false;
    }
    /**
     * Save data back to the file system location
     */
    public function save($reorder = true)
    {
        // on every save we ensure it's sorted in the right order
        if ($reorder) {
            $this->items = $this->orderTree($this->items);
        }
        $schema = get_object_vars($this);
        $file = $schema['file'];
        unset($schema['file']);
        $schema['items'] = array();
        foreach ($this->items as $item) {
            $newItem = get_object_vars($item);
            array_push($schema['items'], $newItem);
        }
        // ensure we have valid json object
        if ($output = json_encode($schema, JSON_PRETTY_PRINT)) {
          return @file_put_contents($file,$output);
        }
    }
    /**
     * Organize the items based on tree order. This makes front end navigation line up correctly
     */
    public function orderTree($items)
    {
        $sorted = array();
        // do an initial by order
        usort($items, function ($a, $b) {
            return $a->order > $b->order;
        });
        $this->orderRecurse($items, $sorted);
        // sanity check, should always be equal
        if (count($sorted) == count($items)) {
            return $sorted;
        }
        // if it bombed just pass it through... again, sanity
        return $items;
    }
    /**
     * Sort a JOS
     */
    private function orderRecurse(
        $currentItems,
        &$sorted = array(),
        &$idList = array()
    ) {
        foreach ($currentItems as $item) {
            if (!array_search($item->id, $idList)) {
                array_push($idList, $item->id);
                array_push($sorted, $item);
                $children = array();
                foreach ($this->items as $child) {
                    if ($child->parent == $item->id) {
                        array_push($children, $child);
                    }
                }
                // sort the kids
                usort($children, function ($a, $b) {
                    return $a->order > $b->order;
                });
                // only walk deeper if there were children for this page
                if (count($children) > 0) {
                    $this->orderRecurse($children, $sorted, $idList);
                }
            }
        }
    }
    /**
     * Generate a UUID
     */
    private function generateUUID()
    {
        return sprintf(
            '%04x%04x-%04x-%04x-%04x-%04x%04x%04x',
            // 32 bits for "time_low"
            mt_rand(0, 0xffff),
            mt_rand(0, 0xffff),
            // 16 bits for "time_mid"
            mt_rand(0, 0xffff),
            // 16 bits for "time_hi_and_version",
            // four most significant bits holds version number 4
            mt_rand(0, 0x0fff) | 0x4000,
            // 16 bits, 8 bits for "clk_seq_hi_res",
            // 8 bits for "clk_seq_low",
            // two most significant bits holds zero and one for variant DCE1.1
            mt_rand(0, 0x3fff) | 0x8000,
            // 48 bits for "node"
            mt_rand(0, 0xffff),
            mt_rand(0, 0xffff),
            mt_rand(0, 0xffff)
        );
    }
}
