function lonestar_read(read_value,callback,auth)
{
	var xmlhttp=new XMLHttpRequest();

	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4&&xmlhttp.status==200)
			if(callback)
				callback(xmlhttp.responseText);
	};

	var request="read="+read_value;

	var auth_str="";
	if(auth)
		auth_str="&auth="+to_hex_string(hmac_sha3_512(auth,request));

	xmlhttp.open("GET","?"+request+auth_str);
	xmlhttp.send();
}

function lonestar_write(write_value,write_array,callback,auth)
{
	var xmlhttp=new XMLHttpRequest();

	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4&&xmlhttp.status==200)
			if(callback)
				callback(xmlhttp.responseText);
	};

	var write_data=JSON.stringify(write_array);
	var request="write="+write_value;

	var auth_str="";
	if(auth)
		auth_str="&auth="+to_hex_string(hmac_sha3_512(auth,request+write_data));

	xmlhttp.open("POST","?"+request+auth_str);
	xmlhttp.setRequestHeader("Content-Type","application/json");
	xmlhttp.send(write_data);
	console.log("?"+request+auth_str);
	console.log(write_data);
}

function lonestar_write_and_read(write_value,write_array,read_value,callback,auth)
{
	var xmlhttp=new XMLHttpRequest();

	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4&&xmlhttp.status==200)
			if(callback)
				callback(xmlhttp.responseText);
	};

	var write_data=JSON.stringify(write_array);
	var request="write="+write_value+"&read="+read_value;

	var auth_str="";
	if(auth)
		auth_str="&auth="+to_hex_string(hmac_sha3_512(auth,request+write_data));

	xmlhttp.open("POST","?"+request+auth_str);
	xmlhttp.setRequestHeader("Content-Type","application/json");
	xmlhttp.send(write_data);
}