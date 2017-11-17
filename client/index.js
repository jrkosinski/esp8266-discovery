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
var udpConnect = require('./util/udpConnect');
var wifiConnect = require('./util/wifiConnect');
var module = require('./package.json');

var savedIp;
var appData;

// * * *
// entry point
// returns: nothing
var main = async(function() {
    var serverFound = false;

    //look for saved IP 
    if (!savedIp){
        logger.info('getting saved app data...');
        appData = await(storage.getAppData());
        savedIp = appData.ip;
    }

    //we have a saved IP
    if (savedIp && savedIp.length){
        logger.info('trying saved ip ' + savedIp);
        //try it 
        if (await(webConnect.pingServer(savedIp))) {

            serverFound = true; 

            //great! so the chip must be connected to our wifi 
            logger.info('found server at ' + savedIp + ' up & running');
        }
        else{
            logger.info('server not found.');
        }
    }

    //if not found, send out UDP broadcast to find it
    if (!serverFound){
        logger.info('sending UDP broadcast...');
        var serverData = await(udpConnect.sendUdpBroadcast()); 

        //found something? save the ip for next time 
        if (serverData && serverData.ip){
            serverFound = true;
            appData.ip = serverData.ip;
            await(storage.saveAppData(appData));
            savedIp = appData.ip;
            logger.info('found server at ' + savedIp + ' by UDP');
            return await(callMain());
        }
        else{
            logger.info('server not found by UDP.');
        }
    }

    //if still not found, we need to scan for the wifi AP 
    if (!serverFound){
        logger.info('scanning for wifi AP...');
        if (await(wifiConnect.scan())) {

            //connected to AP 
            logger.info('found AP, sending request...');

            //send web request to set data 
            var newAppData = await (webConnect.sendRequest(appData)); 
            if (newAppData) {                
                logger.info('request accepted, saving data...');
                savedIp = appData.ip;
                await(storage.saveAppData(appData));
                return await(callMain());
            }
        }
        else{
            logger.info('wifi AP not found or unable to connect.');
        }
    }

    //we've exhausted all reasonable options
    if (!serverFound)
        logger.info("utter abject failure, exiting...");
});

function callMain(){
    setTimeout(function(){
        main();
    }, 3000);
}


main();