// -*- coding: utf-8 -*-

var model = null;
var runner = null;
var SIZE = 256;
var viewer;
var imageryProvider;
var layersArr = [];

function callback_progressbar(current, total) {
    var pct = Math.round(current / total * 100);
    p.p = pct;
    p.update();
    // console.log("test", current, total);
}

// refer http://cya.sakura.ne.jp/java/loading.htm
function display_inference() {
    var inf = document.querySelector('#calc');
    var myY = (window.innerHeight !== undefined) ? window.innerHeight : document.body.clientHeight;
    var myX = (window.innerWidth !== undefined) ? window.innerWidth : document.body.clientWidth;
    inf.style.top = (myY/2-70 < 0) ? 0 : myY/2-70;
    inf.style.left = (myX/2-300 <0) ? 0 : myX/2-300;
    inf.style.visibility = "visible";
    return inf;
}

function hide_inference() {
    var inf = document.querySelector('#calc');
    inf.style.visibility = "hidden";
}

// ref: https://www.nishishi.com/javascript-tips/setinterval-passage.html

var sec = 0;
function showPassage() {
    sec ++;
    var msg = sec + "sec";
    document.getElementById("sec").innerText = msg;
}

function startTimer() {
    sec = 0;
    PassageId = setInterval('showPassage()', 1000);
    document.getElementById("inference").style.disabled = true;
    document.getElementById("sec").innerText = "";
}

function stopTimer() {
    clearInterval(PassageId);
    document.getElementById("inference").style.disabled = false;
}

window.onload = function() {
	viewer = new Cesium.Viewer('cesiumContainer');

	document.getElementById("modelURL").value = './csmap';
	document.getElementById("tileURL").value = "https://gsj-seamless.jp/labs/elev/m/{z}/{y}/{x}.png";
	document.getElementById("tileStartX").value = 7286;
	document.getElementById("tileEndX").value = 7290;
	document.getElementById("tileStartY").value = 3230;
	document.getElementById("tileEndY").value = 3231;
	document.getElementById("tileZ").value = 13;
};


function clearLayers() {
	var imageryLayers =viewer.imageryLayers;

	layersNum = layersArr.length;

	for (var i = 0; i < layersNum; i++) {
		imageryLayers.remove(layersArr[i]);
	}

	layersArr = [];
}

function start() {

    if (!(document.getElementById("tileStartX").value.match(/^[0-9]+$/) && document.getElementById("tileEndX").value.match(/^[0-9]+$/) &&
    	document.getElementById("tileStartY").value.match(/^[0-9]+$/) && document.getElementById("tileEndY").value.match(/^[0-9]+$/) &&
    	document.getElementById("tileZ").value.match(/^[0-9]+$/))) {
    	alert("error : Tile range must be a positive integer.");
    	return;
    } else if ((document.getElementById("tileStartX").value > document.getElementById("tileEndX").value) ||
    		   (document.getElementById("tileStartY").value > document.getElementById("tileEndY").value)) {
    	alert("error : Tile range is error.");
    	return;
    }

    if (document.getElementById("tileURL").value == '') {
    	alert("error : Tile path is empty.");
    	return;
    }

    if (!runner) {
    	alert("error : Please load a model.");
    	return;
    }

    console.log("start");

	clearLayers();
    var tilePosArr = [];

    tileRangeX = [Number(document.getElementById("tileStartX").value), Number(document.getElementById("tileEndX").value)];
    tileRangeY = [Number(document.getElementById("tileStartY").value), Number(document.getElementById("tileEndY").value)];
    tileRangeZ = [Number(document.getElementById("tileZ").value), Number(document.getElementById("tileZ").value)];

    for (var z = tileRangeZ[0]; z <= tileRangeZ[1]; z++) {
    for (var x = tileRangeX[0]; x <= tileRangeX[1]; x++) {
    for (var y = tileRangeY[0]; y <= tileRangeY[1]; y++) {
		tilePosArr.push([x, y, z]);
	}}}

	var url = document.getElementById("tileURL").value;

	display_inference();
	startTimer();

	gettile(0, tilePosArr, url);
}

function gettile(index, tilePosArr, url_ori) {
	if (index >= tilePosArr.length) {
		stopTimer();
		hide_inference();
		return;
	}

	x_pos = tilePosArr[index][0]
	y_pos = tilePosArr[index][1]
	z_pos = tilePosArr[index][2]

	var url = url_ori;

	url = url.replace('{x}', String(x_pos));
	url = url.replace('{y}', String(y_pos));
	url = url.replace('{z}', String(z_pos));

	var start_lonlat = tile2latlon(x_pos, y_pos, z_pos);
	var end_lonlat = tile2latlon(x_pos+1, y_pos+1, z_pos);
	url = url.replace('{minx}', String(start_lonlat[0]));
	url = url.replace('{miny}', String(end_lonlat[1]));
	url = url.replace('{maxx}', String(end_lonlat[0]));
	url = url.replace('{maxy}', String(start_lonlat[1]));
	url = url.replace('{output_width}', String(256));
	url = url.replace('{output_height}', String(256));

	var req = new XMLHttpRequest();
	req.open("GET", url, true);
	req.responseType = "arraybuffer";
	req.addEventListener("load", function (event) {
		if (req.status == 200) {// 一応ステータスコードだけ確認

		    // Blobを作成しURLを取得する
		    var blob = new Blob([req.response]),
		    	blobUrl = URL.createObjectURL(blob);

		    WebDNN.Image.getImageArray(blobUrl, { scale: [255, 255, 255], order: WebDNN.Image.Order.CHW}).then(function (img) {
			console.log("runner called : " + z_pos + "/" + x_pos + "/" + y_pos);
			var x = runner.getInputViews()[0];
			var y = runner.getOutputViews()[0];
			// console.log(img)
			x.set(img);
			runner.run().then(function () {
			    console.log("output");
			    var ret = y.toActual();
			    var cvs = document.createElement('canvas');
			    cvs.width  = 256;
		        cvs.height = 256;
		        var ctx = cvs.getContext('2d');
		        ctx.clearRect(0, 0, 256, 256);
			    var clip = [];
			    // console.log(ret);
			    WebDNN.Image.setImageArrayToCanvas(ret, 256, 256, cvs, {
				scale: [255, 255, 255],
				bias: [0, 0, 0],
				color: WebDNN.Image.Color.RGB,
				order: WebDNN.Image.Order.CHW
			    });
				var start_lonlat = tile2latlon(x_pos, y_pos, z_pos);
				var end_lonlat = tile2latlon(x_pos+1, y_pos+1, z_pos);

				imageryProvider = new SingleTileImageryProviderCustom({
												canvas : cvs,
												rectangle : Cesium.Rectangle.fromDegrees(start_lonlat[0], end_lonlat[1], end_lonlat[0], start_lonlat[1])
											});
				var layer = viewer.imageryLayers.addImageryProvider(imageryProvider);
				layersArr.push(layer);
				gettile(index+1, tilePosArr, url_ori);
			});
			});
		} else {
			gettile(index+1, tilePosArr, url_ori);
		}
	});

	req.send(null);
}


function modelRead()
{
	p.p = 0;
    p.update();
    // フォームデータを取得
    var modelURL = document.getElementById("modelURL").value;
    if (modelURL == '') {
    	alert("error : Model path is empty.");
    	return;
    }

    var stat = document.querySelector("#status");
    stat.textContent = "Loading model...";

    model = WebDNN.load(modelURL, {progressCallback: callback_progressbar}).then(function (r) {
    	var stat = document.querySelector("#status");
    	stat.textContent = "Loaded.";
		runner = r;
		var v = document.getElementById("prog-bar");
		v.style.visiblility = "hidden";
    });
}


// タイル座標→緯度経度
function tile2latlon(x, y, z) {
	lon = (x / 2.0**z) * 360 - 180 // 経度（東経）
    mapy = (y / 2.0**z) * 2 * Math.PI - Math.PI
    lat = 2 * Math.atan(Math.E ** (- mapy)) * 180 / Math.PI - 90 // 緯度（北緯）
    return [lon,lat]
}

// 緯度経度→タイル座標
function latlon2tile(lon, lat, z, roundType=0) {
	x_tmp = ((lon / 180 + 1) * 2**z / 2) // x座標
	y_tmp = (((-Math.log(math.tan((45 + lat / 2) * Math.PI / 180)) + Math.PI) * 2**z / (2 * Math.PI))) // y座標
	if (roundType == 0) {
	    x = int(Math.floor(x_tmp))
	    y = int(Math.floor(y_tmp))
	} else if (roundType == 1) {
	    x = int(Math.ceil(x_tmp))
	    y = int(Math.ceil(y_tmp))
	}

	return [x,y], [x_tmp-x, y_tmp-y]
}

