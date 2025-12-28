from flask import Flask, jsonify
from dotenv import load_dotenv
import os
import requests

load_dotenv()

app = Flask(__name__)

@app.route("/health")
def health():
    return jsonify(health="ok", key=os.getenv("GOTRANSIT_KEY"))

app.run(host="0.0.0.0", port=8080)
