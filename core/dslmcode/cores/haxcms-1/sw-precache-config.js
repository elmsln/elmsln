module.exports = {
  runtimeCaching: [
    {
      urlPattern: /'^https:\/\/cdn.waxam.io\/'/,
      handler: "networkFirst"
    }
  ]
};
