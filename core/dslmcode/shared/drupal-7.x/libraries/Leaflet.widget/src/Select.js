L.Control.Draw.mergeOptions({
    select: {
        title: 'Select items'
    }
});

// TODO: Remove hack to 'open' object.
var onAdd = L.Control.Draw.prototype.onAdd;

L.Control.Draw.include({
    onAdd: function (map) {
        var className = 'leaflet-control-draw',
            container = onAdd.call(this, map);

        if (this.options.select) {
            this.handlers.select = new L.Handler.Select(map, this.options.select);
            this._createButton(
                    this.options.select.title,
                    className + '-select',
                    container,
                    this.handlers.select.enable,
                    this.handlers.select
            );
            this.handlers.select.on('activated', this._disableInactiveModes, this);
        }

        return container;
    }
});

L.Handler.Select = L.Handler.extend({
    includes: L.Mixin.Events,

    options: {},

    initialize: function (map, options) {
        L.Util.setOptions(this, options);
        L.Handler.prototype.initialize.call(this, map);
    },

    enable: function () {
        this.fire('activated');
        L.Handler.prototype.enable.call(this);
    },

    // Called when handler is enabled.
    addHooks: function () {
        if (this._map && this.options.selectable) {
            this._selected = L.layerGroup();
            this._selectable = this.options.selectable;

            this._selectable.eachLayer(function (layer) {
                this._bind(layer);
            }, this);

            this._map.on({
                // TODO: Determine whether this is necessary: can layers be
                //       added while this handler is enabled?
                layeradd: this._bind,
                layerremove: this._unbind
            }, this);
        }
    },

    // Called when handler is disabled.
    removeHooks: function () {
        if (this._map && this._selectable) {
            // Clean up selected layers.
            this._selectable.eachLayer(function (layer) {
                this._unbind(layer);
            }, this);
            delete this._selected;

            this._map.off({
                layeradd: this._bind,
                layerremove: this._unbind
            }, this);
        }
    },

    select: function (e) {
        var layer = e.layer || e.target || e;
        layer.off('click', this.select);
        layer.on('click', this.deselect, this);
        this._selected.addLayer(layer);
        this._map.fire('selected', { layer: layer });
    },

    deselect: function (e, permanent) {
        var layer = e.layer || e.target || e;
        layer.off('click', this.deselect);
        this._selected.removeLayer(layer);
        this._map.fire('deselected', { layer: layer });

        if (!permanent) {
            layer.on('click', this.select, this);
        }
    },

    applyToSelected: function (callback, context) {
        this._selected.eachLayer(callback, context);
    },

    _bind: function (e) {
        var layer = e.layer ? e.layer : e;
        if (this._selectable.hasLayer(layer)) {
            layer.on('click', this.select, this);
        }
    },

    _unbind: function (e) {
        var layer = e.layer ? e.layer : e;
        if (this._selectable.hasLayer(layer)) {
            if (this._selected.hasLayer(layer)) {
                this.deselect(layer, true);
            }
        }
    }
});

L.LayerGroup.include({
    hasLayer: function (layer) {
        return !!this._layers[L.Util.stamp(layer)];
    }
});

L.Control.Select = L.Control.extend({
    options: {
        title: 'Remove selected features',
        position: 'bottomright',
        remove: true
    },

    onAdd: function (map) {
        this._map = map;

        var class_name = 'leaflet-select-control',
            container = L.DomUtil.create('div', class_name);

        if (this.options.remove) {
            this._createButton(
                    this.options.remove.title,
                    class_name + '-remove',
                    container,
                    this._delete,
                    this
            );
        }

        return container;
    },

    _delete: function () {
        this._map.drawControl.handlers.select.applyToSelected(function (layer) {
            this._map.removeLayer(layer);
        }, this);
    },

    _createButton: function (title, className, container, fn, context) {
        var link = L.DomUtil.create('a', className, container);
        link.href = '#';
        link.title = title;

        L.DomEvent
                .on(link, 'click', L.DomEvent.stopPropagation)
                .on(link, 'mousedown', L.DomEvent.stopPropagation)
                .on(link, 'dblclick', L.DomEvent.stopPropagation)
                .on(link, 'click', L.DomEvent.preventDefault)
                .on(link, 'click', fn, context);

        return link;
    }
});

L.Map.addInitHook(function () {
    if (this.options.drawControl.select) {
        this.selectControl = L.Control.select(this.options.drawControl.select);
        this.addControl(this.selectControl);
    }
});

L.Control.select = function (options) {
    return new L.Control.Select(options);
};
