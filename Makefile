SHELL := /bin/bash
PIDFILE := .backend.pid
LOGFILE := .backend.log

ifeq ($(strip $(GOTRANSIT_KEY)),)
$(error GOTRANSIT_KEY is not set)
endif

run:
	@echo "starting backend server"
	.venv/bin/python -u backend/main.py >> $(LOGFILE) 2>&1 & echo $$! > $(PIDFILE)
	@echo "making pio file"
	pio run -e esp32doit-devkit-v1 -v
	@echo "finished"

clean:
	@echo "stopping backend server"
	@if [ -f $(PIDFILE) ]; then \
		kill $$(cat $(PIDFILE)) 2>/dev/null || true; \
		rm -f $(PIDFILE); \
		rm -f $(LOGFILE); \
	fi
