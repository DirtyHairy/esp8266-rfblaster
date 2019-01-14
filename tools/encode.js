module.exports.encodeTristate = (codeTristate) => {
    let code = 0;
    let length = 0;

    for (let i = 0; i < codeTristate.length; i++) {
        code <<= 2;

        switch (codeTristate[i]) {
            case "F":
                code |= 0x01;
                length += 2;
                break;

            case "1":
                code |= 0x03;
                length += 2;
                break;

            case "0":
            case "S":
                length += 2;
        }
    }

    return {
        code,
        length
    };
}
