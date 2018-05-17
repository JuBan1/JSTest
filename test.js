function Timer() {
	return Qt.createQmlObject("import QtQuick 2.0; Timer {}", root);
}

// This is really silly stuff. Ignore.
/*
function Apple (type) {
	this.type = type;
	this.color = "red";
}

Apple.prototype.getInfo = function() {
	return this.color + ' ' + this.type + ' apple';
};
*/

function whitespaceremover() {
    var val = NqqExt.getTextEditContents();
	val newVal =  val.replace(' ', '_')
	NqqExt.setTextEditContents(newVal);
}

function func() {
	print("Extension is loaded and will now display the number of hated whitespace characters every few seconds!")

	var timer = new Timer();
	timer.interval = 2500;
	timer.repeat = true;
	
	timer.triggered.connect(function () {
		var val = NqqExt.getTextEditContents();
		var count =  (val.match(/ /g) || []).length;
	
		print("There are still " + count + " ws characters left to exterminate!");
	})

	timer.start();
}
