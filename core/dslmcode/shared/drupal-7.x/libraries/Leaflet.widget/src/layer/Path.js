L.Path.include({
    toGeoJSON: function () {
        return L.GeoJSONUtil.feature(this.toGeometry());
    }
});
