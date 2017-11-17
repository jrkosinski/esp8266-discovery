'use strict';

// * * * * * 
// index - main module.
//
// John R. Kosinski
// 11 Nov 2017
var async = require('asyncawait/async');
var await = require('asyncawait/await');
var config = require('./config');
var logger = require('./util/logger');
var storage = require('./util/storage');
var webConnect = require('./util/webConnect');
var module = require('./package.json');

main();

// * * *
// entry point
// returns: nothing
function main(requestContext) {

    //look for saved IP 
    var appData = storage.getAppData();
    var savedIp = appData.ip;
    var serverFound = false;

    //we have a saved IP
    if (savedIp && savedIp.length){
        //try it 
        if (webConnect.pingServer(savedIp)) {

            serverFound = true; 

            //great! so the chip must be connected to our wifi 
            logger.info('Connected to server, no problems');
        }
    }

    //if not found, send out UDP broadcast to find it
    if (!serverFound){
        
    }
}



