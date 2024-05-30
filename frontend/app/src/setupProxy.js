const { createProxyMiddleware } = require('http-proxy-middleware');

module.exports = function(app) {
  app.use(
    '/Broker',
    createProxyMiddleware({
      target: 'http://broker:5202',
      changeOrigin: true,
    })
  );
};