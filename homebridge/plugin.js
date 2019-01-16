const Platform = require('./Platform');
const { PLUGIN_ID, PLUGIN_NAME } = require('./constants');

module.exports = homebridge => {
    homebridge.registerPlatform(PLUGIN_ID, PLUGIN_NAME, Platform);
};
