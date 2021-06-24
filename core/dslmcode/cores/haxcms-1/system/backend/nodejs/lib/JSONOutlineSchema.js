const fs = require('fs-extra');
const { v4: uuidv4 } = require('uuid');
const json_decode = require('locutus/php/json/json_decode');
const JSONOutlineSchemaItem = require('./JSONOutlineSchemaItem.js');
const array_search = require('locutus/php/array/array_search');
const usort = require('locutus/php/array/usort');

/**
 * JSONOutlineSchema - An object for interfacing with the JSON Outline schema
 * specification. @see https://github.com/LRNWebComponents/json-outline-schema
 * for more details. This provides a simple way of loading outlines, parsing
 * and working with the items in them while writing back to the specification
 * accurately.
 */

class JSONOutlineSchema
{
    /**
     * Establish defaults
     */
     constructor()
    {
        this.file = null;
        this.id = uuidv4();
        this.title = 'New site';
        this.author = '';
        this.description = '';
        this.license = 'by-sa';
        this.metadata = {};
        this.items = [];
    }

    /**
     * Get a reasonable license name from the short hand
     */
    getLicenseDetails()
    {
        list = {
            "by": {
                'name':"Creative Commons: Attribution",
                'link':"https://creativecommons.org/licenses/by/4.0/",
                'image':"https://i.creativecommons.org/l/by/4.0/88x31.png"
            },
            "by-sa":{
                'name':"Creative Commons: Attribution Share a like",
                'link':"https://creativecommons.org/licenses/by-sa/4.0/",
                'image':"https://i.creativecommons.org/l/by-sa/4.0/88x31.png"
            },
            "by-nd":{
                'name':"Creative Commons: Attribution No derivatives",
                'link':"https://creativecommons.org/licenses/by-nd/4.0/",
                'image':"https://i.creativecommons.org/l/by-nd/4.0/88x31.png"
            },
            "by-nc":{
                'name':"Creative Commons: Attribution non-commercial",
                'link':"https://creativecommons.org/licenses/by-nc/4.0/",
                'image':"https://i.creativecommons.org/l/by-nc/4.0/88x31.png"
            },
            "by-nc-sa":{
                'name' :
                    "Creative Commons: Attribution non-commercial share a like",
                'link':"https://creativecommons.org/licenses/by-nc-sa/4.0/",
                'image' :
                    "https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png"
            },
            "by-nc-nd":{
                'name' :
                    "Creative Commons: Attribution Non-commercial No derivatives",
                'link':"https://creativecommons.org/licenses/by-nc-nd/4.0/",
                'image' :
                    "https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png"
            }
        };
        if (list[this.license]) {
            return list[this.license];
        }
        return {};
    }
    /**
     * Get a new item matching schema standards
     * @return new JSONOutlineSchemaItem Object
     */
    newItem()
    {
        let item = new JSONOutlineSchemaItem();
        return item;
    }
    /**
     * Add an item to the outline
     * @var item an array of values, keyed to match JSON Outline Schema
     * @return count of items in the array
     */
    addItem(item)
    {
        let safeItem = this.validateItem(item);
        let count = this.items.push(safeItem);
        return count;
    }
    /**
     * Validate that an item matches JSONOutlineSchemaItem format
     * @var item JSONOutlineSchemaItem
     * @return JSONOutlineSchemaItem matching the specification
     */
    validateItem(item)
    {
        // create a generic schema item
        let tmp = new JSONOutlineSchemaItem();
        // crush the item given into a stdClass object
        let ary = (item);
        for (var key in ary) {
            // only set what the element from spec allows into a new object
            if (tmp.hasOwnProperty(key)) {
                tmp[key] = ary[key];
            }
        }
        return tmp;
    }
    /**
     * Remove an item from the outline if it exists
     * @var id an id that's in the array of items
     * @return JSONOutlineSchemaItem or false if not found
     */
    removeItem(id)
    {
        for (var key in this.items) {
            if (this.items[key].id == id) {
                tmp = this.items[key];
                delete this.items[key];
                return tmp;
            }
        }
        return false;
    }
    /**
     * Update an item in the outline
     * @var id an id that's in the array of items
     * @return JSONOutlineSchemaItem or false if not found
     */
    updateItem(item, save = false)
    {
        // verify this is a legit item
        let safeItem = this.validateItem(item);
        for (var key in this.items) {
            // match the current item's ID to our safeItem passed in
            if (this.items[key].id == safeItem.id) {
                // overwrite the item
                this.items[key] = safeItem;
                // if we save, then we let that return the whole file
                if (save) {
                    return this.save();
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
    async load(location)
    {
        if (fs.lstatSync(location).isFile()) {
            this.file = location;
            let fileData = json_decode(await fs.readFileSync(location,
                {encoding:'utf8', flag:'r'}));
            let vars = (fileData);
            for (var key in vars) {
                if ((this[key]) && key != 'items') {
                    this[key] = vars[key];
                }
            }
            // check for items and escalate to full JSONOutlineSchemaItem object
            // also ensures data matches only what is supported
            if ((vars['items'])) {
                for (var key in vars['items']) {
                    let item = vars['items'][key];
                    let newItem = new JSONOutlineSchemaItem();
                    newItem.id = item.id;
                    newItem.indent = item.indent;
                    newItem.location = item.location;
                    newItem.slug = item.slug;
                    newItem.order = item.order;
                    newItem.parent = item.parent;
                    newItem.title = item.title;
                    newItem.description = item.description;
                    // metadata can be anything so whatever
                    newItem.metadata = item.metadata;
                    this.items[key] = newItem;
                }
            }
            return true;
        }
        return false;
    }
    /**
     * Get an item by ID
     */
    getItemById(id) {
        for (var id in this.items) {
            if (this.items[id].id === id) {
                return this.items[id];
            }
        }
        return false;
    }
    /**
     * Save data back to the file system location
     */
    async save(reorder = true)
    {
        // on every save we ensure it's sorted in the right order
        if (reorder) {
            this.items = this.orderTree(this.items);
        }
        let schema = (this);
        let file = schema['file'];
        // delete so it doesn't show up in the site.json file
        delete schema['file'];
        let output;
        // ensure we have valid json object
        if (output = JSON.stringify(schema, null, 2)) {
          // reassign so we don't lose it in the transaction
          this.file = file;
          return fs.writeFileSync(file, output);
        }
    }
    /**
     * Organize the items based on tree order. This makes front end navigation line up correctly
     */
    orderTree(items)
    {
        let sorted = [];
        // do an initial by order
        usort(items, function (a, b) {
            return a.order > b.order;
        });
        this.orderRecurse(items, sorted);
        // sanity check, should always be equal
        if (sorted.length == items.length) {
            return sorted;
        }
        // if it bombed just pass it through... again, sanity
        return items;
    }
    /**
     * Sort a JOS
     */
    orderRecurse(
        currentItems,
        sorted = [],
        idList = []
    ) {
        for (var key in currentItems) {
            let item = currentItems[key];
            if (!array_search(item.id, idList)) {
                idList.push(item.id);
                sorted.push(item);
                let children = [];
                for (var key2 in this.items) {
                    let child = this.items[key2];
                    if (child.parent == item.id) {
                        children.push(child);
                    }
                }
                // sort the kids
                usort(children, function (a, b) {
                    return a.order > b.order;
                });
                // only walk deeper if there were children for this page
                if (children.length > 0) {
                    this.orderRecurse(children, sorted, idList);
                }
            }
        }
    }
}
module.exports = JSONOutlineSchema;