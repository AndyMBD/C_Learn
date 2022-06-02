function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "Led_Blink"};
	this.sidHashMap["Led_Blink"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<Root>/Data Type Conversion"] = {sid: "Led_Blink:28"};
	this.sidHashMap["Led_Blink:28"] = {rtwname: "<Root>/Data Type Conversion"};
	this.rtwnameHashMap["<Root>/Pulse Generator"] = {sid: "Led_Blink:27"};
	this.sidHashMap["Led_Blink:27"] = {rtwname: "<Root>/Pulse Generator"};
	this.rtwnameHashMap["<Root>/Out1"] = {sid: "Led_Blink:26"};
	this.sidHashMap["Led_Blink:26"] = {rtwname: "<Root>/Out1"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
