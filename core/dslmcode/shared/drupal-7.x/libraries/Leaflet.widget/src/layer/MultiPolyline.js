L.MultiPolyline.include({
    toGeometry: function () {
        var coords = [];

        this.eachLayer(function (layer) {
            coords.push(layer.toGeometry().coordinates);
        });

        return {
            type: "MultiLineString",
            coordinates: coords
        };
    }
});
