/*
 * Date Format 1.2.3
 * (c) 2007-2009 Steven Levithan <stevenlevithan.com>
 * MIT license
 *
 * Includes enhancements by Scott Trenda <scott.trenda.net>
 * and Kris Kowal <cixar.com/~kris.kowal/>
 *
 * Updated 2017-2019 ATgroup09 <atgroup09@gmail.com>
 *
 * Accepts a date, a mask, or a date and a mask.
 * Returns a formatted version of the given date.
 * The date defaults to the current date/time.
 * The mask defaults to dateFormat.masks.default.
 *
 * Date.get_current_time_stamp()
 */

var dateFormat = function () {
	var	token = /d{1,4}|m{1,4}|yy(?:yy)?|([HhMsTt])\1?|[LloSZ]|"[^"]*"|'[^']*'/g,
		timezone = /\b(?:[PMCEA][SDP]T|(?:Pacific|Mountain|Central|Eastern|Atlantic) (?:Standard|Daylight|Prevailing) Time|(?:GMT|UTC)(?:[-+]\d{4})?)\b/g,
		timezoneClip = /[^-+\dA-Z]/g,
		pad = function (val, len) {
			val = String(val);
			len = len || 2;
			while (val.length < len) val = "0" + val;
			return val;
		};

	// Regexes and supporting functions are cached through closure
	return function (date, mask, utc) {
		var dF = dateFormat;

		// You can't provide utc if you skip other args (use the "UTC:" mask prefix)
		if (arguments.length == 1 && Object.prototype.toString.call(date) == "[object String]" && !/\d/.test(date)) {
			mask = date;
			date = undefined;
		}

		// Passing date through Date applies Date.parse, if necessary
		date = date ? new Date(date) : new Date;
		if (isNaN(date)) throw SyntaxError("invalid date");

		mask = String(dF.masks[mask] || mask || dF.masks["default"]);

		// Allow setting the utc argument via the mask
		if (mask.slice(0, 4) == "UTC:") {
			mask = mask.slice(4);
			utc = true;
		}

		var	_ = utc ? "getUTC" : "get",
			d = date[_ + "Date"](),
			D = date[_ + "Day"](),
			m = date[_ + "Month"](),
			y = date[_ + "FullYear"](),
			H = date[_ + "Hours"](),
			M = date[_ + "Minutes"](),
			s = date[_ + "Seconds"](),
			L = date[_ + "Milliseconds"](),
			o = utc ? 0 : date.getTimezoneOffset(),
			flags = {
				d:    d,
				dd:   pad(d),
				ddd:  dF.i18n.dayNames[D],
				dddd: dF.i18n.dayNames[D + 7],
				m:    m + 1,
				mm:   pad(m + 1),
				mmm:  dF.i18n.monthNames[m],
				mmmm: dF.i18n.monthNames[m + 12],
				yy:   String(y).slice(2),
				yyyy: y,
				h:    H % 12 || 12,
				hh:   pad(H % 12 || 12),
				H:    H,
				HH:   pad(H),
				M:    M,
				MM:   pad(M),
				s:    s,
				ss:   pad(s),
				l:    pad(L, 3),
				L:    pad(L > 99 ? Math.round(L / 10) : L),
				t:    H < 12 ? "a"  : "p",
				tt:   H < 12 ? "am" : "pm",
				T:    H < 12 ? "A"  : "P",
				TT:   H < 12 ? "AM" : "PM",
				Z:    utc ? "UTC" : (String(date).match(timezone) || [""]).pop().replace(timezoneClip, ""),
				o:    (o > 0 ? "-" : "+") + pad(Math.floor(Math.abs(o) / 60) * 100 + Math.abs(o) % 60, 4),
				S:    ["th", "st", "nd", "rd"][d % 10 > 3 ? 0 : (d % 100 - d % 10 != 10) * d % 10]
			};

		return mask.replace(token, function ($0) {
			return $0 in flags ? flags[$0] : $0.slice(1, $0.length - 1);
		});
	};
}();

// Some common format strings
dateFormat.masks = {
	"default":      "ddd mmm dd yyyy HH:MM:ss",
	shortDate:      "m/d/yy",
	mediumDate:     "mmm d, yyyy",
	longDate:       "mmmm d, yyyy",
	fullDate:       "dddd, mmmm d, yyyy",
	shortTime:      "h:MM TT",
	mediumTime:     "h:MM:ss TT",
	longTime:       "h:MM:ss TT Z",
	isoDate:        "yyyy-mm-dd",
	isoTime:        "HH:MM:ss",
	isoDateTime:    "yyyy-mm-dd'T'HH:MM:ss",
	isoUtcDateTime: "UTC:yyyy-mm-dd'T'HH:MM:ss'Z'",
	isoDateTimeNorm: "yyyy-mm-dd HH:MM:ss"
};

// Internationalization strings
dateFormat.i18n = {
	dayNames: [
		"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat",
		"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
	],
	monthNames: [
		"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
		"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
	]
};

// For convenience...
Date.prototype.format = function(mask, utc) {
	return dateFormat(this, mask, utc);
};

// Method: Modification the value of date
//     In: 
//       value - The value of the time/date interval to add. You can specify positive and negative values for this parameter
//        unit - The unit type of the interval. Can be one of the following values
//				 = "microsecond"
//				 = "second"
//				 = "minute"
//				 = "hour"
//				 = "day"
//				 = "week",
//				 = "year"
//   Out:
//       none
//
Date.prototype.date_add = function(value, unit) {

	if(typeof value == "number" && typeof unit == "string")
	{
		var Res = value;
		
		switch(unit)
		{
			case "week":
				Res = (Res*7);		//toDays
				
			case "day":
				Res = (Res*24);		//toHours
		
			case "hour":
				Res = (Res*60);		//toMinutes
				
			case "minute":
				Res = (Res*60);		//toSeconds
				
			case "second":
				Res = (Res*1000);	//toMicroseconds
				
			case "microsecond":
				var Ts = this.getTime();
				Ts+= Res;
				this.setTime(Ts);
				break;
			
			case "year":
				var YYYY = this.getFullYear();
				YYYY+= Res;
				this.setFullYear(YYYY);
		}
	}
};


/*
@brief  Get current Unix TimeStamp.
@param  None.
@return Current Unix TimeStamp.
*/
Date.prototype.get_current_time_stamp = function() {

	return (Math.round((new Date()).getTime()/1000));
};

Date.prototype.getCurrentTimeStamp = function() {

	return (this.get_current_time_stamp());
};


/*
@brief  Set Unix TimeStamp.
@param  SecIn - Date and Time in UnixTimeStamp format (the number of seconds from 1970 year).
@return None.
*/
Date.prototype.set_time_stamp = function(value) {

	if(typeof value == "number")
	{
		if(value >= 0) this.setTime((value*1000));
	}
};

Date.prototype.setTimeStamp = function(SecIn) {

	this.set_time_stamp(SecIn);
};


/*
@brief  Convert seconds to hours
@param  SecIn - seconds
@return Hours
*/
Date.prototype.SecToHours = function(SecIn) {

	if(typeof SecIn == "number")
	{
		if(SecIn > 0)
		{
			var Hours = SecIn/3600;
			return (Math.floor(Hours)-0);
		}
	}
	
	return (0);
};


/*
@brief  Convert seconds to minutes
@param  SecIn - seconds
@return Hours
*/
Date.prototype.SecToMinutes = function(SecIn) {

	if(typeof SecIn == "number")
	{
		if(SecIn > 0)
		{
			var Hours   = this.SecToHours(SecIn);
			var Minutes = (SecIn-(Hours*3600))/60;
			return (Math.floor(Minutes)-0);
		}
	}
	
	return (0);
};


/*
@brief  Convert seconds to string of ISO-format (HH:MM:SS)
@param  SecIn - seconds (<= 1327104000)
@return String of ISO-format "HH:MM:SS" or NULL
*/
Date.prototype.SecToIsoTime = function(SecIn) {

	if(typeof SecIn == "number")
	{
		if(SecIn > 0 && SecIn <= 1327104000)
		{
			var Hours   = this.SecToHours(SecIn);
			var Minutes = this.SecToMinutes(SecIn);
			var Seconds = SecIn - (Hours*3600) - (Minutes*60);
			
			var Res = ((Hours < 10) ? ('0'+Hours) : (''+Hours));
			Res+= ':';
			Res+= ((Minutes < 10) ? ('0'+Minutes) : (''+Minutes));
			Res+= ':';
			Res+= ((Seconds < 10) ? ('0'+Seconds) : (''+Seconds));
			return (Res);
		}
	}
	
	return (null);
};
