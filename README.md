# Compile
A Go Transit API Key is required for this, set it in the `.env` file as "GOTRANSIT_KEY"  
Run the following commands to set up the virtual environment  
```
python -m venv .venv
source .venv/bin/activate
pip install requirements.txt
```
To get the MAC_IP, on macOS, run `ipconfig getifaddr en0` and that's the MAC_IP  
Run `export MAC_IP=`${ip}`  
