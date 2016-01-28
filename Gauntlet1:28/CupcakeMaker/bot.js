/*
* Cupcake generator twitter bot
* Jessica Shen 
* jshen1
* 51-482 Interactive Art and Computational Design 
* January 28, 2016
*
*
* relied on https://www.youtube.com/playlist?action_edit=1&list=PLRqwX-V7Uu6atTSxoRiVnSuOn6JHnq2yV 
* for learning node.js and twitter implementation
*/


var fs = require("fs");
console.log('The bot is starting');

var Twit = require('twit');
var fs = require('fs');
var config = require('./config');
var exec = require('child_process').exec;

var T = new Twit(config);

tweetIt();
setInterval(tweetIt, 1000*120);

//random choosing from list
 function choose(list) {
    return list[Math.floor(Math.random() * list.length)];
}

//generate text for tweet - make a cupcake!
function generateTweet() {

 	 var flavorFile = fs.readFileSync("data/flavors.json");
 	 var flavorList = JSON.parse(flavorFile);
 	 var flavors = flavorList.flavors;

 	 var toppingsFile = fs.readFileSync("data/toppings.json");
 	 var toppingList = JSON.parse(toppingsFile);
 	 var toppings = toppingList.flavors;

     var inside = [ "", " with " + choose(flavors) + " filling"];
     var topping = [ "", " and " + choose(toppings)] ;
     var fancy = [ "", " and " + choose(toppings) + " on top"];


    return choose(flavors) + " cupcake with " + choose(flavors) + " frosting" + choose(inside) 
    + choose(topping) + choose(fancy);
}


//tweet image and text
function tweetIt(txt){
	var cmd = 'processing-java --sketch=`pwd`/cupcake --run 6'
	exec(cmd, processing)

	function processing() { 
		var file = 'cupcake/output.png';
		var params = {
			encoding: 'base64'
		}
		var b64content = fs.readFileSync(file, params);
		T.post('media/upload', {media_data: b64content}, uploaded);

		function uploaded(err, data, response){
			var id = data.media_id_string;
			var tweet = {
				status: generateTweet(),
				media_ids: [id]
			}
			T.post('statuses/update', tweet, tweeted);

		}
		function tweeted(err, data, response) {
			if (err){
				console.log("derp");
			} else {
				console.log("yay");
			}
		}

	}

}

