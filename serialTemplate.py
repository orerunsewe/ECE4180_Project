from flask import Flask, render_template
import datetime
import serial
app = Flask(__name__)

@app.route("/")

def serialString():
  port = serial.Serial("/dev/ttyACM0",9600)
  now  = datetime.datetime.now()
  timeStr = now.strftime("%Y-%m-%d %H:%M")
 # while True:
  distance_str =port.readline().decode()
  distance_str = distance_str.replace('\r', '')
  distance_str = distance_str.replace('\n', '')
  print(distance_str)

  return render_template('main.html', distance_str = distance_str, timeStr=timeStr)
if __name__ == "_main__":
   app.run(host='0.0.0.0',port=5000, debug = True)
