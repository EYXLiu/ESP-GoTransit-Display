from flask import Flask, jsonify, request
from dotenv import load_dotenv
import os
import requests
from datetime import datetime

load_dotenv()

app = Flask(__name__)

@app.route("/health")
def health():
    return jsonify(health="ok")

@app.route("/station")
def stations():
    url = f"https://api.openmetrolinx.com/OpenDataAPI/api/V1/Stop/All?key={os.getenv("GOTRANSIT_KEY")}"
    response = requests.get(url)
    j = response.json()
    return j["Stations"]


@app.route("/station/<identifier>")
def stationGet(identifier):
    url = f"https://api.openmetrolinx.com/OpenDataAPI/api/V1/Stop/All?key={os.getenv("GOTRANSIT_KEY")}"
    response = requests.get(url)
    j = response.json()
    ret = []
    for s in j["Stations"]["Station"]:
        if s["LocationName"] == identifier or s["LocationCode"] == identifier:
            ret.append(s["LocationCode"])
    return jsonify(busses=ret)

@app.route("/route/<identifier>")
def routeGet(identifier):
    url = f"https://api.openmetrolinx.com/OpenDataAPI/api/V1/Stop/NextService/{identifier}?key={os.getenv("GOTRANSIT_KEY")}"
    response = requests.get(url)
    j = response.json()
    ret = []
    if j["NextService"]:
        for bus in j["NextService"]["Lines"]:
            scheduled = datetime.strptime(bus["ScheduledDepartureTime"], "%Y-%m-%d %H:%M:%S")
            now = datetime.now()
            delta = scheduled - now
            delta = round(delta.total_seconds() / 60)
            delta = abs(delta)
            
            hours, minutes = divmod(delta, 60)
            
            time = scheduled.strftime("%Y-%m-%d %H:%M")
            
            val = {
                "LineName": bus["LineName"],
                "BusName": bus["DirectionName"].split("-")[0].strip(),
                "Destination": bus["DirectionName"].split("-")[1].strip(),
                "ScheduledDepartureDate": time.split(" ")[0],
                "ScheduledDepartureTime": time.split(" ")[1],
                "TimeFromNow": f"{hours}h {minutes}m",
                "ScheduledPlatform": bus["ScheduledPlatform"],
                "_sort": delta
            }
            ret.append(val)
        
    ret.sort(key=lambda x: x["_sort"])
    
    return jsonify(upcoming=ret)

app.run(host="0.0.0.0", port=8080)
