'use strict';

// * * * * * 
// exceptionUtil - standard handling for exceptions. 
// 
// John R. Kosinski
// 3 Oct 2017
var config = require('../config');
var logger = require('./logger');


// * * *
// wraps the given expression in a try/catch, and provides standard handling for any errors.
// returns: return value of given expression
function tryCatch(requestContext, expr, defaultVal=null){
    try{
        return expr();
    }
    catch(err){
        handleError(err, requestContext);
        return defaultVal;
    }
};

// * * *
// provides standard handling for any errors.
// returns: nothing
function handleError(err, requestContext){
    logger.error(err);
    if (requestContext)
        requestContext.error = err;
}


module.exports = {
    try : tryCatch,
    handleError : handleError
};