'use strict';

// * * * * * 
// logger - for logging.
// 
// John R. Kosinski
// 4 Oct 2017

var config = require('../config');

var logType = {
    info : 'info',
    debug : 'debug',
    warn : 'warn',
    error : 'error'
};

// values: 'ALL', 'NONE', or array of logType values. s
var loggingLevel = config.loggingLevel;

// * * *
// outputs only the body for a speech response with card.
// returns: string (json)
function log(s, type=logType.info) {
    var log = true;

    if (Array.isArray(loggingLevel)){
        log = false;
        var found = loggingLevel.filter( function(i) { return (i === type || i === 'all');} );
        if (found && found.length)
            log = true;
    }
    else{
        if (loggingLevel.toUpperCase() == 'ALL')
            log = true; 
        else if (loggingLevel.toUpperCase() == 'NONE') 
            log = false;
    }

    if (log)
        console.log('[' + type + '] ' + s);
}

module.exports = {
    log : log,
    info : (s) => { log(s, logType.info);},
    debug : (s) => { log(s, logType.debug);},
    warn : (s) => { log(s, logType.warn);},
    error : (s) => { log(s, logType.error);},
    logType : logType
};