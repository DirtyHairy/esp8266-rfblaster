const uuidv3 = require('uuid/v3');

const UUID_NAMESPACE = 'EB669A45-BF04-410B-8170-7BD372965CC6';

module.exports.generateUUID = id => uuidv3(id, UUID_NAMESPACE);
