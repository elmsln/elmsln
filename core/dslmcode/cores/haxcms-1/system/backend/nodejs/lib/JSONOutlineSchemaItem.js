const fs = require('fs-extra');
const { v4: uuidv4 } = require('uuid');
/**
 * JSONOutlineSchemaItem - a single item without an outline of items.
 */
class JSONOutlineSchemaItem
{
  /**
   * Establish defaults for a new item
   */
  constructor() {
    this.id = 'item-' + uuidv4();
    this.indent = 0;
    this.location = '';
    this.slug = '';
    this.order = 0;
    this.parent = '';
    this.title = 'New item';
    this.description = '';
    this.metadata = {};
  }
  /**
   * Load data from the location specified
   */
  async readLocation(basePath = '') {
    if (fs.lstatSync(basePath + this.location).isFile()) {
      return await fs.readFileSync(basePath + this.location,
        {encoding:'utf8', flag:'r'});
    }
    return false;
  }
  /**
   * Load data from the location specified
   */
  async writeLocation(body, basePath = '') {
    // ensure we have a blank set
    if (body == '') {
      body = '<p></p>';
    }
    try {
      if (fs.lstatSync(basePath + this.location).isFile()) {
        fs.writeFileSync(basePath + this.location, body);
      }
      return true;
    }
    catch(e) {
      return false;
    }
  }
}
module.exports = JSONOutlineSchemaItem;