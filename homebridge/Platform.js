const Ajv = require('ajv');
const axios = require('axios');
const querystring = require('querystring');

const { generateUUID } = require('./util');
const configSchema = require('./configSchema');

class Platform {
    constructor(logger, config, homebridge) {
        this.validateConfig(config);

        this.log = logger;
        this.config = config;
        this.homebridge = homebridge;

        this.Accessory = this.homebridge.platformAccessory;
        this.Service = this.homebridge.hap.Service;
        this.Characteristic = this.homebridge.hap.Characteristic;
    }

    async accessories(callback) {
        const accessories = await Promise.all(this.config.accessories.map(config => this.createAccessory(config)));

        callback(accessories);
    }

    async createAccessory(config) {
        const accessory = new this.Accessory(config.name, generateUUID(config.name));
        accessory.name = config.name;

        await this.addAccessoryService(accessory, this.getAccessoryServiceType(config), config);

        return accessory;
    }

    getAccessoryServiceType(config) {
        switch (config.type) {
            case 'lightbulb':
                return this.Service.Lightbulb;

            default:
                throw new Error('cannot happen --- forbidden by validation');
        }
    }

    async addAccessoryService(accessory, serviceType, config) {
        const service = accessory.addService(serviceType, config.name);

        let state = !!config.initialState;
        this.log(`Setting initial state of ${config.name} to ${state ? 'on' : 'off'}`);

        try {
            this.toggle(config, state);
        } catch (e) {}

        service.getCharacteristic(this.Characteristic.On).on('set', async (value, callback) => {
            try {
                await this.toggle(config, value);

                state = value;
                callback();
            } catch (e) {
                callback(e);
            }
        });

        service.getCharacteristic(this.Characteristic.On).on('get', callback => callback(undefined, state));

        accessory.getServices = () => [service];
    }

    async toggle(config, state) {
        const commandConfig = state ? config.on : config.off;

        try {
            await this.sendRfCommand(commandConfig);

            this.log(`${config.name} set to ${state ? 'on' : 'off'}`);
        } catch (e) {
            this.log(e && e.message ? e.message : 'unknown error, request failed');

            throw e;
        }
    }

    async sendRfCommand(config) {
        const queryParams = {
            code: config.code,
            'code-length': config.codeLength
        };

        if (config.protocol) queryParams['protocol'] = config.protocol;
        if (config.repeat) queryParams['repeat'] = config.repeat;
        if (config.pulseLength) queryParams['pulse-length'] = config.pulseLength;

        const query = querystring.stringify(queryParams);
        const url = `http://${this.config.host}/command/send?${query}`;

        this.log(`posting device at ${url}`);

        await axios.post(url);
    }

    validateConfig(config) {
        const ajv = new Ajv();
        if (!ajv.validate(configSchema, config)) {
            throw new Error(`esp8266-rfblaster: invalid config: ${ajv.errorsText()}`);
        }
    }
}

module.exports = Platform;
