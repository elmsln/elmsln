Book Cache

This provides a drop in performance improvement when navigating through books. It does this by providing a cache bin in drupal specifically for book pagination data. The footer links that provide the next - previous navigation in the book module is extremely bloated by default (as much as 600 to 800 KB for that one function!).

Using this module in the wild has shown the ability to reduce that function to about 250 KB.

This can also be used as an api to utilize the cache bin in other modules since it stores prev, next, tree, and parent. The CID is keyed as bid:mlid so you can easily target a specific menu item in a book or all items in a book.