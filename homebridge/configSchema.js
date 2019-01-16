const { PLUGIN_NAME } = require('./constants');

const schemaRFCommand = {
    type: 'object',
    properties: {
        code: {
            type: 'integer',
            minimum: 0
        },
        codeLength: {
            type: 'integer',
            minimum: 0
        },
        protocol: {
            type: 'integer',
            minimum: 0
        },
        repeat: {
            type: 'integer',
            minimum: 0
        },
        pulseLength: {
            type: 'integer',
            minimum: 0
        }
    },
    required: ['code', 'codeLength']
};

module.exports = {
    type: 'object',
    properties: {
        name: {
            type: 'string',
            pattern: '\\S'
        },
        platform: {
            type: 'string',
            enum: [PLUGIN_NAME]
        },
        host: {
            type: 'string',
            format: 'hostname'
        },
        accessories: {
            type: 'array',
            items: {
                type: 'object',
                properties: {
                    name: {
                        type: 'string',
                        pattern: '\\S'
                    },
                    type: {
                        type: 'string',
                        enum: ['lightbulb']
                    },

                    initialState: {
                        type: 'boolean'
                    },
                    on: schemaRFCommand,
                    off: schemaRFCommand
                },
                required: ['name', 'type', 'on', 'off']
            }
        }
    },
    required: ['name', 'platform', 'host', 'accessories']
};
