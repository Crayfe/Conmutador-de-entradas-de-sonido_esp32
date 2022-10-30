const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html"; charset="UTF-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="icon" href="data:,">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
        <link href="https://fonts.googleapis.com/css?family=Cabin+Sketch&display=swap" rel="stylesheet">
        <link href="https://fonts.googleapis.com/css?family=VT323&display=swap" rel="stylesheet">
        <link href="https://fonts.googleapis.com/css2?family=Black+Ops+One&display=swap" rel="stylesheet">
        <style>
            body {background-image: url(https://i.ibb.co/rv44vFj/wood.jpg);background-attachment: fixed;background-repeat: no-repeat;background-size: cover; text-align: center;font-family: 'Cabin Sketch', cursive;}
            .header{padding: 0px; width:400px; height:150px;}
            .testInput{padding: 15px; width:400px;}
            .logo{float:left; padding: 30px 10px 20px 20px;}
            .title-header{font-family: 'Black Ops One', cursive; font-size: 40px; color: black;}
            .wrap{padding:20px;width: 470px;margin-right: auto; margin-left: auto;display: inline-block;}
            .content{background-image: url(https://i.ibb.co/H2k5kdP/papel.jpg); padding: 5px 20px 20px 20px; margin-top: 20px;}
            .button{background-color: #195B6A; border: none; color: white; padding: 16px 20px; font-family: 'VT323', monospace;text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}
            .button1{background-color: #F33319; border: none; color: white; padding: 16px 20px; font-family: 'VT323', monospace;text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}
            .button2{background-color: #9AFF40; border: none; color: white; padding: 16px 20px; font-family: 'VT323', monospace;text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}
            .input_text{color: black; padding: 16px;text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}
            .separator{border-color: #000;}
        </style>
    </head>

<body> 
    <div class="wrap">
    <div class="content">
        <div class="header">
            <h1 class="title-header">Crayfe's Sound Manager</h1></p>
        </div>
        <hr class="separator"/>
            <div class="testInput">
            <p><h2 style="font-family: 'Cabin Sketch';">General</h2></p>
            <p style="font-family: 'Cabin Sketch'; font-size: 15px;"><b>Amplificador</b> <button class="button1" id="Ampli" onclick="swapAmpli()">OFF</button></p>
            <p style="font-family: 'Cabin Sketch'; font-size: 15px;"><b>Bluetooth</b> <button class="button1" id="Bt" onclick="swapBt()">OFF</button></p>
        </div>
        <hr class="separator"/> 
<div class="testInput">
            <p><h2 style="font-family: 'Cabin Sketch';">Selector de fuente de audio</h2></p>
            <p><button class="button" id="PC" onclick="setOption('PC')">PC</button><button class="button" id="Bluetooth" onclick="setOption('Bluetooth')">Bluetooth</button><button class="button" id="Aux input I" onclick="setOption('Aux input I')">Aux input I</button><button class="button" id="Aux input II" onclick="setOption('Aux input II')">Aux input II</button></p>
        </div>
        <hr class="separator"/> 
    </div>
    </div>
    <script>
      var button;

      var buttonAmp = document.getElementById("Ampli");
      var buttonBt = document.getElementById("Bt");
      
      var button1 = document.getElementById("PC");
      var button2 = document.getElementById("Bluetooth");
      var button3 = document.getElementById("Aux input I");
      var button4 = document.getElementById("Aux input II");

      function swapAmpli() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            if(buttonAmp.innerHTML == "OFF"){
                buttonAmp.innerHTML = "ON";
                buttonAmp.className = "button2";
            }else{
                buttonAmp.innerHTML = "OFF";
                buttonAmp.className = "button1";
            }
          }
        };
        xhttp.open("GET", "swapAmpli?Ampli="+buttonAmp.innerHTML, true);
        xhttp.send();
      }

      function swapBt() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            if(buttonBt.innerHTML == "OFF"){
                buttonBt.innerHTML = "ON";
                buttonBt.className = "button2";
            }else{
                buttonBt.innerHTML = "OFF";
                buttonBt.className = "button1";
            }
          }
        };
        xhttp.open("GET", "swapBt?Bt="+buttonBt.innerHTML, true);
        xhttp.send();
      }
      
      
      function setOption(opt) {
        button = document.getElementById(opt);
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById(opt).innerHTML =
            this.responseText;
            button1.className = "button";
            button2.className = "button";
            button3.className = "button";
            button4.className = "button";

            
            button.className = "button2";
          }
        };
        xhttp.open("GET", "setOption?Option="+opt, true);
        xhttp.send();
      }


     function getOption() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            
            
            button1.className = "button";
            button2.className = "button";
            button3.className = "button";
            button4.className = "button";
            document.getElementById(this.responseText).className = "button2";
          }
        };
        xhttp.open("GET", "readOption", true);
        xhttp.send();
      }

$(function() {

    // request data every 5 seconds
    setInterval(requestData, 500);

    function requestData() {

      // ajax request for latest sensor data
      $.get("/variables")
        .done(function(data) {

          console.log(data);  // debugging - remove when satisfied

          if (data) { // if the returned data is not null, update the values
            $("#Ampli").text(data.Ampli);
            if(data.Ampli == "ON"){
                buttonAmp.innerHTML = ampst;
                buttonAmp.className = "button2";
            }else{
                buttonAmp.innerHTML = ampst;
                buttonAmp.className = "button1";
            }
            $("#Bt").text(data.Bt);
            if(data.Bt == "ON"){
                buttonBt.innerHTML = btst;
                buttonBt.className = "button2";
            }else{
                buttonBt.innerHTML = btst;
                buttonBt.className = "button1";
            }
          } else { // a problem occurred
            $("#Ampli").text("?");
            $("#Bt").text("?");

          }
        }).fail(function() {
          console.log("The was a problem retrieving the data.");
        });
    }

  });
      
    </script>
</body>
</html>
)=====";
